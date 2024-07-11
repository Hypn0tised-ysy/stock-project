#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <QObject>
#include <QVariantList>
#include <Eigen/Dense>
#include "database.h"

class Predictor : public QObject
{
    Q_OBJECT
public:
    enum{Start=0,End=60,Predict=10}//使用前Start分钟到前End分钟项数据，预测Predict项数据
    explicit Predictor(Database *db, QObject *parent = nullptr);
    bool enoughData(const QString &symbol);//判断是否有足够数据，如果返回为true再调用getPrices函数
    QVariantList predictStockPrices(const QString &symbol);
    std::vector<double> getPrices(const QString &symbol);//返回值result，result[0]得到预测的第一项price数据，类型为double,共有Predict项数据
private:
    Database *dbPtr;
    Eigen::VectorXd linearRegression(const Eigen::MatrixXd &data);
    Eigen::VectorXd predict(const Eigen::VectorXd &beta, int start, int end);
};

#endif // PREDICTOR_H
