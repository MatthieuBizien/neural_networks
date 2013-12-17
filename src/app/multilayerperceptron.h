#ifndef MULTILAYERPERCEPTRON_H
#define MULTILAYERPERCEPTRON_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

#include "matrixsequence.h"

using std::shared_ptr;
using std::vector;
using std::tuple;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

class MultiLayerPerceptron
{
public:
    /**
     * @brief MultiLayerPerceptron
     *  Create a new logistic perceptron with a configurable number of hidden
     *  layers.
     *
     * @param dimensions
     *  The dimension of the network. The first item is the size of the input
     *  and the last one is the size of the output. The other ones are the
     *  hidden layers.
     **/
    MultiLayerPerceptron(const vector<int> &dimensions_layers);

    /**
     * @brief compute
     *  Calculate the expected output of the network. One line must be one input.
     *
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     */
    Matrix compute(const Matrix& X) const;

    /**
     * @brief compute_output_layers
     *  Compute the normalized error term of the network, compared to the expected value.
     *
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     * @param Y
     *  The expected output. It must have as many rows as X and as many columns
     *  as the last layer of the network.
     *
     * @return
     *  The mean error term.
     */
    double computeError(const Matrix& X, const Matrix& Y) const;

    /**
     * @brief getGradient
     *  Compute the normalized error term and the gradient of the network, compared to the expected value.
     *
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     * @param Y
     *  The expected output. It must have as many rows as X and as many columns
     *  as the last layer of the network.
     *
     * @return
     *  The first term of the tuple is the mean error term.
     *  The secund argument is the gradient of the error term.
     */
    tuple<double, ArrayX> computeGradient(const Matrix& X, const Matrix& Y) const;

    /**
     * @brief getWeights
     *  Give the current weights used by the network.
     * @return
     *  A reference to the weights. Can't live longer than the weights themselves.
     */
    MatrixSequence& getWeights() {
        return coefficients_;
    }
    const MatrixSequence& getWeights() const {
        return coefficients_;
    }

private:
    /**
     * @brief compute_output_layers
     *  Compute the ouputs of each layers of the network.
     *
     * @param X
     *  The input of the network. It must have one row per observation and as
     *  many columns as the first layer of the network.
     *
     * @return
     *  The sequence of outputs of the layers. The first output is the input,
     *  the last the network's output.
     */
    const MatrixSequence compute_output_layers(const Matrix& X) const;

    /**
     * @brief dimensions_layers_
     *  The size of each layers. It is shared because it can't be modified.
     */
    shared_ptr<vector<int>> dimensions_layers_;

    /**
     * @brief workingWeights_
     *  The weights that are not associated to a constant neurone. It is shared
     *  because it can't be modified.
     */
    shared_ptr<MatrixSequence> workingWeights_;

    /**
     * @brief coefficients_
     *  The weights of the network.
     */
    MatrixSequence coefficients_;
};

#endif // MULTILAYERPERCEPTRON_H
