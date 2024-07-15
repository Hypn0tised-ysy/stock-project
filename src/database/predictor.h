#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <QObject>
#include <QVariantList>
#include <Eigen/Dense>
#include "database.h"
#include "arma.h"
class ARMA;
class Predictor : public QObject
{
    Q_OBJECT
public:
    enum{Start=0,End=60,Predict=10};//使用前Start分钟到前End分钟项数据，预测Predict项数据
    explicit Predictor(Database *db, QObject *parent = nullptr);
    bool enoughData(const QString &symbol);//判断是否有足够数据，如果返回为true再调用getPrices函数
    bool enoughData(const QString &symbol,int numHistory);
    QVariantList predictStockPrices(const QString &symbol);
    QVariantList predictStockPrices(const QString &symbol,int numHistory,int numFuture);
    std::vector<double> getPrices(const QString &symbol);//返回值result，result[0]得到预测的第一项price数据，类型为double,共有Predict项数据
    std::vector<double> getPrices(const QString &symbol,int numHistory,int numFuture);//num参数为使用历史数据的个数
    std::vector<double> getPricesArma(const QString &symbol);//使用arma模型预测价格走势,预测的数据个数为Predict个
    std::vector<double> getPricesArma(const QString &symbol,int numHistory,int numFuture);
    private:
    Database *dbPtr;
    ARMA* armaModel;
    Eigen::VectorXd linearRegression(const Eigen::MatrixXd &data);
    Eigen::VectorXd predict(const Eigen::VectorXd &beta, int start, int end);
};
extern Predictor predictor;

/*使用predictor获取Predictor::Predict项预测数据,能够进行预测的前提是至少有Predictor::End-Predictor::Start项历史数据，参数可以改
std::vector<double> predictData;
if(predictor.enoughData())
{
    //linear regression
    predictData=predictor.getPrices("股票代码");
    //arma
    predictData=predictor.getPricesArma("股票代码");
}
*/

#endif // PREDICTOR_H
