#ifndef MATH_H
#define MATH_H


/**
 * @brief logistic
 *  Compute the logistic transformation of some array. The formula is
 *  exp(z)/(1+exp(z)) = 1/(exp(-z)+1). The derivative is f(x)*(1-f(x)).
 *
 * @param input
 *  The original matrix.
 */
inline Matrix logistic(const Matrix& input) {
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
inline Matrix addOneCol(const Matrix& input) {
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
inline vector<tuple<int, int>> getShapes(const vector<int>& dimensions_layers) {
    vector<tuple<int, int>> shapes(dimensions_layers.size() -1);
    for(unsigned int i=0; i<dimensions_layers.size() -1; i++) {
        shapes.at(i) = tuple<int, int>(dimensions_layers.at(i+1),
                                       dimensions_layers.at(i) +1);
    }
    return shapes;
}


#endif // MATH_H
