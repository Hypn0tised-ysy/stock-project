#include "arma.h"

ARMA::ARMA(int p, int q) : p(p), q(q) {}

void ARMA::fit(const std::vector<double>& data) {
    this->data = data;
    estimateParameters();
}

void ARMA::estimateParameters() {
    int n = data.size();
    Eigen::MatrixXd X(n - p, p);
    Eigen::VectorXd Y(n - p);

    for (int i = 0; i < n - p; ++i) {
        Y(i) = data[p + i];
        for (int j = 0; j < p; ++j) {
            X(i, j) = data[p + i - j - 1];
        }
    }

    // Estimate AR parameters
    ar_params = (X.transpose() * X).ldlt().solve(X.transpose() * Y);

    // Calculate residuals
    residuals.resize(n - p);
    for (int i = 0; i < n - p; ++i) {
        double predicted = 0;
        for (int j = 0; j < p; ++j) {
            predicted += ar_params(j) * data[p + i - j - 1];
        }
        residuals[i] = data[p + i] - predicted;
    }

    // Estimate MA parameters
    Eigen::MatrixXd Z(n - p - q, q);
    Eigen::VectorXd W(n - p - q);

    for (int i = 0; i < n - p - q; ++i) {
        W(i) = residuals[q + i];
        for (int j = 0; j < q; ++j) {
            Z(i, j) = residuals[q + i - j - 1];
        }
    }

    ma_params = (Z.transpose() * Z).ldlt().solve(Z.transpose() * W);
}

std::vector<double> ARMA::predict(int steps) {
    int n = data.size();
    std::vector<double> predictions(steps);

    for (int i = 0; i < steps; ++i) {
        double predicted = 0;

        for (int j = 0; j < p; ++j) {
            int index = n - j - 1 + i;
            if (index < n) {
                predicted += ar_params(j) * data[index];
            } else {
                predicted += ar_params(j) * predictions[index - n];
            }
        }

        for (int j = 0; j < q; ++j) {
            int index = n - p - j - 1 + i;
            if (index < n - p) {
                predicted += ma_params(j) * residuals[index];
            } else {
                predicted += ma_params(j) * (i - j - 1 >= 0 ? predictions[i - j - 1] : 0);
            }
        }

        predictions[i] = predicted;
    }

    return predictions;
}
