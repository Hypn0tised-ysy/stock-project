#include "predictor.h"
#include <QDebug>
#include <cmath>
#include <cstdlib>

extern Database db;
Predictor predictor;
Predictor::Predictor(Database *database, QObject *parent) :
    QObject(parent), dbPtr(db)
{
}
bool Predictor::enoughData(const QString &symbol)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol);
    if (stocks.size()<Predictor::End-Predictor::Start) {
        return false;
    }
    else return true;
}

QVariantList Predictor::predictStockPrices(const QString &symbol)
{
    std::vector<StockPrice> stocks=dbPtr->getStockPrice(symbol);

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

Eigen::VectorXd Predictor::linearRegression(const MatrixXd &data)
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

Eigen::VectorXd Predictor::predict(const VectorXd &beta, int start, int end)
{
    int numPoints = end - start;
    Eigen::VectorXd predictions(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        predictions(i) = beta(0) + beta(1) * (start + i);
    }
    return predictions;
}
