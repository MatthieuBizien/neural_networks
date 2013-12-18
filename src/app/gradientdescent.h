#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

#include "minimizeur.h"
#include "multilayerperceptron.h"

using std::vector;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

class GradientDescent: public AbstractMinimizeur {
public:
    GradientDescent(const Matrix& X, const Matrix& Y, const vector<int>& dimensions)
        :perceptron_(dimensions)
    {
        X_ = X;
        Y_ = Y;
    }

    float computeError(const Matrix &Xval, const Matrix &Yval) const {
        return perceptron_.computeError(Xval, Yval);
    }

private:
    float doIteration_() {
        auto error_gradient = perceptron_.computeGradient(X_, Y_);
        ArrayX& gradient = get<1>(error_gradient);
        perceptron_.getWeights().data() -= gradient;
        return get<0>(error_gradient);
    }

    MultiLayerPerceptron perceptron_;
    Matrix X_, Y_;
};

#endif // GRADIENTDESCENT_H
