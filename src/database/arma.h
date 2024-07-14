#ifndef ARMA_H
#define ARMA_H
#include "database.h"
#include "predictor.h"
#include <Eigen/Dense>
#include <vector>

class ARMA {
public:
    ARMA(){p=2;q=2;}
    ARMA(int p, int q);
    void fit(const std::vector<double>& data);//拟合 ARMA 模型。将时间序列数据保存到类的成员变量中，并调用 estimateParameters 函数来估计模型参数
    std::vector<double> predict(int steps);//steps对应预测的数据的个数

private:
    int p;  // AR部分阶数
    int q;  // MA部分阶数
    Eigen::VectorXd ar_params;//AR系数
    Eigen::VectorXd ma_params;//MA系数
    std::vector<double> residuals;//残差
    std::vector<double> data;//股票价格数据

    void estimateParameters();
};

#endif // ARMA_H
