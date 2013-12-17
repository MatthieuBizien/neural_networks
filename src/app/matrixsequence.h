#ifndef MATRIXSEQUENCE_H
#define MATRIXSEQUENCE_H

#include <vector>
#include <Eigen/Dense>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::tuple;

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
    MatrixSequence(vector<tuple<int, int> > shapes);

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
    Map<Matrix> matrix(unsigned int i);
    const Map<const Matrix> matrix(unsigned int i) const;

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
    Map<ArrayX> data();
    const Map<const ArrayX> data() const;

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

    friend std::ostream& operator<<(std::ostream& os,
                                    const MatrixSequence& sequence);

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
