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

#include <boost/assign/list_of.hpp>

MatrixSequence::MatrixSequence(vector<tuple<int, int> > dims) {
    dims_.reset(new vector<tuple<int, int>>(dims.size()));
    beginning_matrix.reset(new vector<int>(dims_->size() +1));
    for(unsigned int i=0; i<dims_->size(); ++i) {
        dims_->at(i) = dims.at(i);
        const tuple<int, int>& dim_current = dims_->at(i);
        beginning_matrix->at(i+1) = beginning_matrix->at(i) +
                get<0>(dim_current) * get<1>(dim_current)
                ;
    }
    data_.resize(beginning_matrix->back());
}

Map<ArrayX> MatrixSequence::data() {
    Map<ArrayX> out(&data_[0], data_.size());
    return out;
}

Map<Matrix> MatrixSequence::matrix(unsigned int i) {
    assert(i <= dims_->size());
    auto* beginning = &data_.at(beginning_matrix->at(i));
    const tuple<int, int>& dim_current = dims_->at(i);
    Map<Matrix> out(beginning, get<0>(dim_current), get<1>(dim_current));
    return out;
}

int MatrixSequence::size() {
    return dims_->size();
}
