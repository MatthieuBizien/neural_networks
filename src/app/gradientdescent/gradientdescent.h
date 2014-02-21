#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

#include "acostfunctionminimizeur.h"
#include "neuralnets/multilayerperceptron.h"

using std::vector;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

/**
  @brief
    Plain, normal, gradient descent. Do just that but do it well.
  */
class GradientDescent: public ACostFunctionMinimizeur {
public:
    /**
     * @brief GradientDescent
     *  Plain, normal, gradient descent. Do just that but do it well.
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     * @param Y
     *  The expected output. It must have as many rows as X and as many columns
     *  as the last layer of the network.
     * @param dimensions
     *   The dimensions of the perceptron. The first item is the size of the
     *   input, the last one the size of the output.
     *  @param learningRate
     *   The global learning rate of the descent of the gradient.
      */
    GradientDescent(const Matrix& X, const Matrix& Y,
                    const vector<int>& dimensions,
                    float learningRate)
        :perceptron_(dimensions)
    {
        X_ = X;
        Y_ = Y;
        learningRate_ = learningRate;
    }

    float computeError(const Matrix &Xval, const Matrix &Yval) const {
        return perceptron_.computeError(Xval, Yval);
    }


    virtual MultiLayerPerceptron getPerceptron() {
        return perceptron_;
    }

private:
    float doIteration_() {
		// Basic gradient descent.
        auto error_gradient = perceptron_.computeGradient(X_, Y_);
        ArrayX& gradient = get<1>(error_gradient);
        perceptron_.getWeights().data() -= gradient * learningRate_;
        return get<0>(error_gradient);
    }

    /** @brief X_
      The input of the stored data.
      */
    Matrix X_;
    /** @brief Y_
      The output of the stored data.
      */
    Matrix Y_;

    /** @brief learningRate_
      The learning rate of the descent
      */
    float learningRate_;
    MultiLayerPerceptron perceptron_;
};

#endif // GRADIENTDESCENT_H
