#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <memory>

#include "matrixsequence.h"
#include "multilayerperceptron.h"
#include "dimensionalexception.h"

using std::shared_ptr;
using std::vector;
using std::tuple;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

/**
 * @brief logistic
 *  Compute the logistic transformation of some array. The formula is
 *  exp(z)/(1+exp(z)) = 1/(exp(-z)+1). The derivative is f(x)*(1-f(x)).
 *
 * @param input
 *  The original matrix.
 */
Matrix logistic(const Matrix& input) {
    return ((-input.array()).exp() + 1).inverse();
}


/**
 * @brief addOneCol
 *  Return an updated version of the input, with a column equal to 1 at the
 *  beginning. It is the equivalent of matlab [1 input].
 *
 * @param input
 *  The original matrix.
 */
Matrix addOneCol(const Matrix& input) {
    Matrix next_input = Matrix::Ones(input.rows(), input.cols() +1);
    next_input.rightCols(input.cols()) = input;
    return next_input;
}


/**
 * @brief getShapes
 *  Compute the shapes of the matrix of the perceptron.
 *
 * @param dimensions_layers
 *  The sequence of dimensions of the layers of the perceptron.
 */
vector<tuple<int, int>> getShapes(const vector<int>& dimensions_layers) {
    vector<tuple<int, int>> shapes(dimensions_layers.size() -1);
    for(unsigned int i=0; i<dimensions_layers.size() -1; i++) {
        shapes.at(i) = tuple<int, int>(dimensions_layers.at(i+1),
                                       dimensions_layers.at(i) +1);
    }
    return shapes;
}


MultiLayerPerceptron::MultiLayerPerceptron(const vector<int> &dimensions_layers)
    :coefficients_(getShapes(dimensions_layers))
{
    // Set dimensions_layers_.
    dimensions_layers_.reset(new vector<int>(dimensions_layers.size()));
    for(unsigned int i=0; i<dimensions_layers.size(); i++) {
        dimensions_layers_->at(i) = dimensions_layers.at(i);
    }

    // Random initialisation of the coefficients.
    // We use an empirical formula recommended by Andrew Ng.
    for(unsigned int i=0; i<dimensions_layers.size() -1; i++) {
        const Matrix& coefficient = coefficients_.matrix(i);
        double epsilon = sqrt(6.0f/ coefficient.rows() / coefficient.cols());
        coefficients_.matrix(i) = Matrix::Random(coefficient.rows(),
                                                 coefficient.cols()) * epsilon;
    }

    // Initialise workingWeights.
    workingWeights_ = std::make_shared<MatrixSequence>(coefficients_);
    for(unsigned int i=0; i<dimensions_layers.size() -1; i++) {
        const Matrix& coefficient = coefficients_.matrix(i);
        workingWeights_ ->matrix(i).col(0) =
                Matrix::Zero(coefficient.rows(), 1);
        workingWeights_ ->matrix(i).leftCols(coefficient.cols() -1) =
                Matrix::Ones(coefficient.rows(), coefficient.cols() -1);
    }
}


Matrix MultiLayerPerceptron::compute(const Matrix& input) const {
    return compute_output_layers(input).last();
}


double MultiLayerPerceptron::computeError(const Matrix &X, const Matrix &Y) const {
    const Matrix& result = compute(X);
    return -1.0d/X.rows() * (
                Y.array() * result.array().log() +
                (1-Y.array()) * (1-result.array()).log()
                ).sum();
}


/*
 * We use a classic backpropagation algorithm.
 */
tuple<double, ArrayX> MultiLayerPerceptron::computeGradient(const Matrix &X,
                                                     const Matrix &Y) const {
    if(X.rows() != Y.rows()) {
        throw DimensionalException<int>(Y.rows(), X.rows(), "rows");
    }

    MatrixSequence output_layers = compute_output_layers(X);

    const Matrix& result = output_layers.last();
    double error = -1.0d/X.rows() * (
                Y.array() * result.array().log() +
                (1-Y.array()) * (1-result.array()).log()
                ).sum();

    // For each observation, the corresponding row is  the derivative of the
    // error according to  the current layer's output.
    Matrix error_layer = output_layers.last().array() - Y.array();

    // We do backpropagation. At each iteration we update d and
    // gradient.matrix(i).
    MatrixSequence gradient = coefficients_;
    for(int i=coefficients_.size()-1; i>=0; i--) {
        const Matrix& input = output_layers.matrix(i);
        gradient.matrix(i) =
                error_layer.transpose() * addOneCol(input) / X.rows();
        if(i>0) {
            Matrix tmp = error_layer * coefficients_.matrix(i);
            error_layer = tmp.rightCols(tmp.cols()-1).array()
                    *  input.array() * (1-input.array());
        }
    }

    return tuple<double, ArrayX>(error, gradient.data());
}


const MatrixSequence
MultiLayerPerceptron::compute_output_layers(const Matrix &X) const {
    assert(dimensions_layers_->size() == coefficients_.size() +1);
    if(X.cols() != dimensions_layers_->at(0)) {
        int n = dimensions_layers_->at(0); int nn = X.cols();
        throw new DimensionalException<int>(n, nn, "cols");
    }

    vector<tuple<int, int>> dimension(dimensions_layers_->size());
    for(unsigned int i=0; i<dimension.size(); i++) {
        dimension.at(i) = tuple<int, int>(X.rows(),
                                          dimensions_layers_->at(i));
    }

    MatrixSequence output_layers = MatrixSequence(dimension);
    output_layers.matrix(0) = X;

    for(unsigned int i=0; i< output_layers.size() -1; i++) {
        const Matrix& input = output_layers .matrix(i);
        const Matrix& theta = coefficients_.matrix(i).transpose();
        // Y = f(theta * [1 Y]) , f logistic function.
        output_layers.matrix(i+1) = logistic(addOneCol(input) * theta);
    }
    return output_layers;
}
