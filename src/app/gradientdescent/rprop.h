#ifndef ADAPTATIVEGRADIENTDESCENT_H
#define ADAPTATIVEGRADIENTDESCENT_H
#include <vector>

#include <Eigen/Dense>
#include <memory>

#include "neuralnets/multilayerperceptron.h"
#include "acostfunctionminimizeur.h"

using std::vector;
using std::min;
using std::max;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

/**
 * @brief
 *  Use the RProp algorithm for gradient descent.
 *  See http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.21.1417 for
 *  more informations about the algorithm.
 */
class Rprop: public ACostFunctionMinimizeur {
public:
    /**
     * @brief Rprop
     *  Use the RProp algorithm for gradient descent.
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     * @param Y
     *  The expected output. It must have as many rows as X and as many columns
     *  as the last layer of the network.
     * @param dimensions
     *   The dimensions of the perceptron. The first item is the size of the
     *   input, the last one the size of the output.
     *  @param maxLearningRate
     *   The maximum learning rate of the descent of the individual weiths'
     *   gradient.
     *  @param initialLearningRate
     *   The initial learning rate of the descent.
      */
    Rprop(const Matrix& X, const Matrix& Y, const vector<int>& dimensions,
          float maxLearningRate, float initialLearningRate)
        :perceptron_(dimensions)
    {
        X_ = X;
        Y_ = Y;
        const Matrix& sizeCoeffs = perceptron_.getWeights().data();
        individualRates = Matrix::Constant(sizeCoeffs.rows(),
                                           sizeCoeffs.cols(),
                                           initialLearningRate);
        lastGradient = Matrix::Zero(sizeCoeffs.rows(), sizeCoeffs.cols());
        maxLearningRate_ = maxLearningRate;
    }

    float computeError(const Matrix &Xval, const Matrix &Yval) const {
        return perceptron_.computeError(Xval, Yval);
    }

    virtual MultiLayerPerceptron getPerceptron() {
        return perceptron_;
    }

private:
    float doIteration_() {
        auto error_gradient = perceptron_.computeGradient(X_, Y_);
        ArrayX& gradient = get<1>(error_gradient);
        perceptron_.getWeights().data() -= gradient *  individualRates;

        // We update the weights according to the sign of the last
        // gradients. If they are the same, we multiply by 1.2 else we
        // divide by 2. We keep the rate between 100 and 0.01.
        for(int i=0; i<lastGradient.rows(); i++) {
            // The signs are -1, 0 or 1. The product is also -1, 0 or 1.
            // It is  iff the signs are the same.
            int sign1 = (gradient(i) > 0) - (gradient(i) < 0);
            int sign2 = (lastGradient(i) > 0) - (lastGradient(i) < 0);
            static const float results[] = {0.5, 1, 1.2};
            individualRates(i) *= results[1 + sign1*sign2];
            individualRates(i) = min<double>(maxLearningRate_,
                                             double(individualRates(i)));
        }
        lastGradient = gradient;
        return std::get<0>(error_gradient);
    }

public:
    /** @brief X_
      The input of the stored data.
      */
    Matrix X_;
    /** @brief Y_
      The output of the stored data.
      */
    Matrix Y_;

    /** @brief lastGradient
      The gradient of the last iteration. Used for sign comparison.
      */
    ArrayX lastGradient;
    ArrayX individualRates;
    float maxLearningRate_;

    MultiLayerPerceptron perceptron_;
};

#endif // ADAPTATIVEGRADIENTDESCENT_H
