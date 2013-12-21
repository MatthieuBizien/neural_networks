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
 * @brief The RProp class
 *  Use the RProp algorithm for gradient descent.
 *  See http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.21.1417 for
 *  more informations about the algorithm.
 */
class Rprop: public ACostFunctionMinimizeur {
public:
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
    ArrayX lastGradient;
    ArrayX individualRates;
    MultiLayerPerceptron perceptron_;
    Matrix X_, Y_;
    float maxLearningRate_;
};

#endif // ADAPTATIVEGRADIENTDESCENT_H
