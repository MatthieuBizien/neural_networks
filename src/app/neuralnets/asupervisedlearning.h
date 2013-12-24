#ifndef ASUPERVISEDLEARNING_H
#define ASUPERVISEDLEARNING_H

#include "utils/matrixsequence.h"

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

class ASupervisedLearning {
public:
    virtual Matrix compute(const Matrix& X) const = 0;

    virtual tuple<double, ArrayX> computeGradient(const Matrix& X,
                                                  const Matrix& Y) const = 0;

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
    double computeError(const Matrix& X, const Matrix& Y) const {
        const Matrix& result = compute(X);
        return -1.0d/X.rows() * (
                    Y.array() * result.array().log() +
                    (1-Y.array()) * (1-result.array()).log()
                    ).sum();
    }

    virtual MatrixSequence& getWeights() = 0;
    virtual const MatrixSequence& getWeights() const = 0;

    friend std::ostream&
    operator<<(std::ostream& outputStream, const ASupervisedLearning& perceptron) {
        outputStream << perceptron.getWeights() << std::endl;
        return outputStream;
    }

};

#endif // ASUPERVISEDLEARNING_H
