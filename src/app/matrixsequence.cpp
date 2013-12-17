#include <vector>
#include <Eigen/Dense>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;
using Eigen::Map;

#include "matrixsequence.h"


MatrixSequence::MatrixSequence(vector<tuple<int, int> > shapes) {
    shapes_.reset(new vector<tuple<int, int>>(shapes.size()));
    beginning_matrix.reset(new vector<int>(shapes_->size() +1));
    for(unsigned int i=0; i<shapes_->size(); ++i) {
        shapes_->at(i) = shapes.at(i);
        const tuple<int, int>& shape = shapes_->at(i);
        beginning_matrix->at(i+1) = beginning_matrix->at(i) +
                get<0>(shape) * get<1>(shape)
                ;
    }
    data_.resize(beginning_matrix->back());
}


Map<ArrayX> MatrixSequence::data() {
    return Map<ArrayX>(&data_[0], data_.size());
}

const Map<const ArrayX> MatrixSequence::data() const {
    return Map<const ArrayX>(&data_[0], data_.size());
}


Map<Matrix> MatrixSequence::matrix(unsigned int i) {
    assert(i <= shapes_->size());
    auto* beginning = &data_.at(beginning_matrix->at(i));
    auto& shape = shapes_->at(i);
    return Map<Matrix>(beginning, get<0>(shape), get<1>(shape));
}

const Map<const Matrix> MatrixSequence::matrix(unsigned int i) const {
    assert(i <= shapes_->size());
    auto* beginning = &data_.at(beginning_matrix->at(i));
    auto& shape = shapes_->at(i);
    return Map<const Matrix>(beginning, get<0>(shape), get<1>(shape));
}


std::ostream& operator<<(std::ostream &outputStream,
                    const MatrixSequence &sequence) {
    outputStream << "Sequence ";
    for(unsigned int i=0; i<sequence.shapes_->size(); i++) {
        outputStream << get<0>(sequence.shapes_->at(i)) << "x"
                     << get<1>(sequence.shapes_->at(i));
        if(i < sequence.shapes_->size() ) {
            outputStream << " ";
        }
    }
    for(unsigned int i=0; i<sequence.shapes_->size(); i++) {
        outputStream << "\n" << sequence.matrix(i) << "\n";
    }
    return outputStream;
}
