#ifndef MINIMIZEUR_H
#define MINIMIZEUR_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

typedef Eigen::MatrixXd Matrix;

using std::tuple;
using std::get;

class AbstractMinimizeur
{
public:
    void doIteration() {
        float error = doIteration_();
        errors_.push_back(error);
        if(validationSet_) {
            float errorValidation = computeError(get<0>(*validationSet_.get()),
                                                 get<1>(*validationSet_.get()));
            errorsValidation_.push_back(errorValidation);
        }
    }

    const std::vector<float> getErrors() const {
        return errors_;
    }

    virtual float computeError(const Matrix& X, const Matrix& Y) const
            = 0;

    friend std::ostream& operator<<(std::ostream& os,
                                    const AbstractMinimizeur& sequence) {
        for(unsigned int i=0; i<sequence.errors_.size(); i++) {
            os << i << ": " << sequence.errors_.at(i) << "\n";
        }
        return os;
    }


protected:
    virtual float doIteration_() = 0;
    std::shared_ptr<tuple<Matrix, Matrix>> validationSet_;

private:
    std::vector<float> errors_;
    std::vector<float> errorsValidation_;
};

#endif // MINIMIZEUR_H
