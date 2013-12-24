#ifndef REGULARIZEDMULTILAYERPERCEPTRON_H
#define REGULARIZEDMULTILAYERPERCEPTRON_H

#include "neuralnets/multilayerperceptron.h"

using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

class RegularizedMultiLayerPerceptron: public MultiLayerPerceptron {
public:

    RegularizedMultiLayerPerceptron(const vector<int> &dimensions_layers,
                                    const float regularization)
        :MultiLayerPerceptron(dimensions_layers)
    {
        regularization_ = regularization;

        // Initialise workingWeights.
        workingWeights_ = std::make_shared<MatrixSequence>(getWeights());
        for(unsigned int i=0; i<dimensions_layers.size() -1; i++) {
            const Matrix& coefficient = getWeights().matrix(i);
            workingWeights_ ->matrix(i).col(0) =
                    Matrix::Zero(coefficient.rows(), 1);
            workingWeights_ ->matrix(i).leftCols(coefficient.cols() -1) =
                    Matrix::Ones(coefficient.rows(), coefficient.cols() -1);
        }
    }

    tuple<double, ArrayX> computeGradient(const Matrix& X,
                                          const Matrix& Y) const {
        tuple<double, ArrayX> error_gradient =
                MultiLayerPerceptron::computeGradient(X, Y);
        ArrayX workingWeights = workingWeights_->data() * regularization_;
        //TODO div par m
        double square_weights = (workingWeights.square() / 2).sum();
        return tuple<double, ArrayX>(get<0>(error_gradient) + square_weights
                                     / X.rows(),
                                     get<1>(error_gradient) - workingWeights
                                     / X.rows());
    }


private:
    float regularization_;

    /**
     * @brief workingWeights_
     *  The weights that are not associated to a constant neurone. It is shared
     *  because it can't be modified.
     */
    shared_ptr<MatrixSequence> workingWeights_;
};

#endif // REGULARIZEDMULTILAYERPERCEPTRON_H
