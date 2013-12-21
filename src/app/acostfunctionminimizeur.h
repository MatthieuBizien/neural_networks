#ifndef ACOSTFUNCTIONMINIMIZEUR_H
#define ACOSTFUNCTIONMINIMIZEUR_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

typedef Eigen::MatrixXd Matrix;

using std::tuple;
using std::get;

class ACostFunctionMinimizeur {
public:
    /**
     * @brief doIteration
     *  Compute a new iteration of the minimizeur and update the weights.
     **/
    void doIteration() {
        float error = doIteration_();
        errors_.push_back(error);
        if(validationSet_) {
            float errorValidation = computeError(get<0>(*validationSet_.get()),
                                                 get<1>(*validationSet_.get()));
            errorsValidation_.push_back(errorValidation);
        }
    }

	/**
     * @brief getErrors
     *  Return the history of the errors of the network on the training set.
     */
    const std::vector<float> getErrors() const {
        return errors_;
    }

	/**
     * Compute the error using the final network.
     */
    virtual float computeError(const Matrix& X, const Matrix& Y) const
            = 0;

    friend std::ostream& operator<<(std::ostream& os,
                                    const ACostFunctionMinimizeur& sequence) {
        for(unsigned int i=0; i<sequence.errors_.size(); i++) {
            os << i << ": " << sequence.errors_.at(i) << "\n";
        }
        return os;
    }


protected:
	/**
     * @brief doIteration_
     *  Do an iteration of your optimizeur procedure and return the error.
     *  Override it for your own iterative procedure.
     */
    virtual float doIteration_() = 0;
    std::shared_ptr<tuple<Matrix, Matrix>> validationSet_;

private:
    std::vector<float> errors_;
    std::vector<float> errorsValidation_;
};

#endif // ACOSTFUNCTIONMINIMIZEUR_H
