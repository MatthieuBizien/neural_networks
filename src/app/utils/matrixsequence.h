#ifndef MATRIXSEQUENCE_H
#define MATRIXSEQUENCE_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::tuple;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;
using Eigen::Map;

/**
 * @brief The MatrixSequence class
 *  This class allows you to manage a sequence of hetegoreneous matrix, and to
 *  switch from the matrix view to the array view, where the array is a flatten
 *  version of the sequence.
 */
class MatrixSequence
{
public:
    /**
     * @brief MatrixSequence
     *  Create a sequence of matrix.
     * @param shapes
     *  The tuple of shapes of the matrix. Each matrix can have a different
     *  shape.
     */
    MatrixSequence(vector<tuple<int, int> > shapes) {
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

    /**
     * @brief matrix
     *  Get a reference to the matrix i. This operation doesn't construct a
     *  new matrix.
     * @param i
     *  The index of the matrix to get.
     * @return
     *  A reference to the matrix.
     *  WARNING: it is your responsability to check the shape is right for an
     *      assignement.
     *  WARNING: if you want to assign some data to the matrix, you either have
     *      to directly do obj.matrix() = somematrix, or to store obj.matrix()
     *      in a Map<Matrix> object or to use auto. DO NOT STORE obj.matrix()
     *      IN A MATRIX FOR ASSIGNEMENT !
     */
    Map<Matrix> matrix(unsigned int i) {
        assert(i <= shapes_->size());
        auto* beginning = &data_.at(beginning_matrix->at(i));
        auto& shape = shapes_->at(i);
        return Map<Matrix>(beginning, get<0>(shape), get<1>(shape));
    }
    const Map<const Matrix> matrix(unsigned int i) const {
        assert(i <= shapes_->size());
        auto* beginning = &data_.at(beginning_matrix->at(i));
        auto& shape = shapes_->at(i);
        return Map<const Matrix>(beginning, get<0>(shape), get<1>(shape));
    }

    /**
     * @brief data
     *  Get a reference to the flatten version of the sequence. This operation
     *  doesn't construct a new array.
     * @return
     *  A reference to the array.
     *  WARNING: it is your responsability to check the shape is right for an
     *      assignement.
     *  WARNING: if you want to assign some data to the array, you either have
     *      to directly do obj.array() = somearray, or to store obj.array()
     *      in a Map<ArrayXd> object or to use auto. DO NOT STORE obj.array()
     *      IN AN ARRAY FOR ASSIGNEMENT !
     */
    Map<ArrayX> data() {
        return Map<ArrayX>(&data_[0], data_.size());
    }
    const Map<const ArrayX> data() const {
        return Map<const ArrayX>(&data_[0], data_.size());
    }

    /**
     * @brief getNbrMatrix
     *  Get the number of elements in the sequence.
     * @return
     */
    unsigned int size() {
        return shapes_->size();
    }
    unsigned int size() const {
        return shapes_->size();
    }

    /**
     * @brief last
     *  Get the last matrix of the sequence.
     * @return
     */
    Map<Matrix> last() {
        return matrix(size() -1);
    }
    const Map<const Matrix> last() const {
        return matrix(size() -1);
    }

    friend std::ostream& operator<<(std::ostream& outputStream,
                                    const MatrixSequence& sequence) {
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

private:
    /**
     * @brief shapes_
     *  The shapes of the matrix.
     */
    shared_ptr<vector<tuple<int, int>>> shapes_;

    /**
     * @brief beginning_matrix
     *  The location in data_ of the beginning of each matrix.
     */
    shared_ptr<vector<int>> beginning_matrix;

    /**
     * @brief data_
     *  The actual data. Each matrix is a contiguous subvector of data.
     */
    vector<double> data_;
};

#endif // MATRIXSEQUENCE_H
