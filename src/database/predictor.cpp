#include "predictor.h"
#include <QDebug>
#include <cmath>
#include <cstdlib>

extern Database db;
Predictor predictor(&db);
Predictor::Predictor(Database *db, QObject *parent) :
    QObject(parent), dbPtr(db),armaModel()
{
}
bool Predictor::enoughData(const QString &symbol)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);
    if (stocks.size()<Predictor::End-Predictor::Start) {
        return false;
    }
    else return true;
}
bool Predictor::enoughData(const QString &symbol,int numHistory)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);
    if (stocks.size()<numHistory) {
        return false;
    }
    else return true;
}

QVariantList Predictor::predictStockPrices(const QString &symbol)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);

    if (stocks.size() < End-Start) {
        qDebug() << "Not enough data to perform prediction.";
        return QVariantList();
    }

    Eigen::MatrixXd data(End-Start, 2);//End-Start个向量，每个向量2个元素
    for (int i = 0; i < End-Start; ++i) {
        data(i, 0) = i;
        data(i, 1) = stocks[i].price;
    }

    Eigen::VectorXd beta = linearRegression(data);
    Eigen::VectorXd predictions = predict(beta, End-Start, End-Start+Predict);

    QVariantList result;
    for (int i = 0; i < predictions.size(); ++i) {
        QVariantMap prediction;
        prediction["minute"] = End-Start + i;
        prediction["predictedPrice"] = predictions(i);
        result.append(prediction);
    }

    return result;
}
QVariantList Predictor::predictStockPrices(const QString &symbol,int numHistory,int numFuture)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);

    if (stocks.size() < numHistory) {
        qDebug() << "Not enough data to perform prediction.";
        return QVariantList();
    }

    Eigen::MatrixXd data(numHistory, 2);//numHistory个向量，每个向量2个元素
    for (int i = 0; i < numHistory; ++i) {
        data(i, 0) = i;
        data(i, 1) = stocks[i].price;
    }

    Eigen::VectorXd beta = linearRegression(data);
    Eigen::VectorXd predictions = predict(beta, numHistory, numHistory+numFuture);

    QVariantList result;
    for (int i = 0; i < predictions.size(); ++i) {
        QVariantMap prediction;
        prediction["minute"] = End-Start + i;
        prediction["predictedPrice"] = predictions(i);
        result.append(prediction);
    }

    return result;
}
std::vector<double> Predictor::getPrices(const QString &symbol)
{
    QVariantList qList=predictStockPrices(symbol);
    std::vector<double> result;
    for(int i=0;i<qList.size();i++)
    {
        result.push_back(qList[i].toMap()["predictedPrice"].toDouble());
    }
    return result;
}
std::vector<double> Predictor::getPrices(const QString &symbol,int numHistory,int numFuture)
{
    QVariantList qList=predictStockPrices(symbol,numHistory,numFuture);
    std::vector<double> result;
    for(int i=0;i<qList.size();i++)
    {
        result.push_back(qList[i].toMap()["predictedPrice"].toDouble());
    }
    return result;
}
std::vector<double> Predictor::getPricesArma(const QString &symbol)
{
    armaModel=new ARMA(2,2);//这里把p和q分别设置成2和2
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);
    std::vector<double> data;
    for(auto item:stocks)
    {
        data.push_back(item.price);
    }
    armaModel->fit(data);
    std::vector<double> result=armaModel->predict(Predict);
    return result;
}
std::vector<double> Predictor::getPricesArma(const QString &symbol,int numHistory,int numFuture)
{
    armaModel=new ARMA(2,2);//这里把p和q分别设置成2和2
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol,true);
    std::vector<double> data;
    for(auto item:stocks)
    {
        data.push_back(item.price);
    }
    armaModel->fit(data);
    std::vector<double> result=armaModel->predict(numFuture);
    return result;
}

Eigen::VectorXd Predictor::linearRegression(const Eigen::MatrixXd &data)
{
    int numPoints = data.rows();
    Eigen::VectorXd x = data.col(0);
    Eigen::VectorXd y = data.col(1);

    Eigen::MatrixXd X(numPoints, 2);
    X.col(0) = Eigen::VectorXd::Ones(numPoints);
    X.col(1) = x;

    Eigen::VectorXd beta = (X.transpose() * X).ldlt().solve(X.transpose() * y);
    return beta;
}

Eigen::VectorXd Predictor::predict(const Eigen::VectorXd &beta, int start, int end)
{
    int numPoints = end - start;
    Eigen::VectorXd predictions(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        predictions(i) = beta(0) + beta(1) * (start + i);
    }
    return predictions;
}
