#include <vector>
#include <Eigen/Dense>
#include <iostream>

#include <unittest++/UnitTest++.h>

#include "matrixsequence.h"

using std::vector;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

typedef tuple<int, int> Dimension;

TEST(MATRIXSEQUENCE_RETURN_DIMENSIONS) {
    static const Dimension arr[] = { Dimension(1, 2), Dimension(2, 2),\
                                     Dimension(4, 8) };
    vector<Dimension> shapes (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MatrixSequence matrixSequence(shapes);
    CHECK_EQUAL(matrixSequence.size(), 3);
    CHECK_EQUAL(matrixSequence.data().rows(), 1*2 + 2*2 + 4*8);
    CHECK_EQUAL(matrixSequence.matrix(0).rows(), 1);
    CHECK_EQUAL(matrixSequence.matrix(0).cols(), 2);
    CHECK_EQUAL(matrixSequence.matrix(1).rows(), 2);
    CHECK_EQUAL(matrixSequence.matrix(1).cols(), 2);
    CHECK_EQUAL(matrixSequence.matrix(2).rows(), 4);
    CHECK_EQUAL(matrixSequence.matrix(2).cols(), 8);
}

TEST(MATRIXSEQUENCE_PRINT){
    static const Dimension arr[] = { Dimension(1, 2), Dimension(2, 2),\
                                     Dimension(4, 8) };
    vector<Dimension> shapes (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MatrixSequence matrixSequence(shapes);
    std::stringstream nullStream;
    nullStream << matrixSequence << std::endl;
    // std::cout << matrixSequence << std::endl;
}

TEST(MATRIXSEQUENCE_CHANGE_VALUE_BY_VECTOR) {
    static const Dimension arr[] = { Dimension(1, 2), Dimension(2, 2) };
    vector<Dimension> shapes (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MatrixSequence matrixSequence(shapes);
    ArrayX normalArray(6);
    normalArray << 10, 11, 20, 21, 22, 23;

    // Basic assign
    // WARNING: you should use auto data, or Map<ArrayX> for assignement
    //Array
    auto data = matrixSequence.data();
    data = normalArray;
    auto newData = matrixSequence.data();
    CHECK(newData.isApprox(normalArray));
    CHECK(matrixSequence.data().isApprox(normalArray));

    // Change the original array: the object must be unchanged
    normalArray = normalArray * 2;
    CHECK(normalArray.isApprox(matrixSequence.data() *2));

    // Check the consistency of the matrix
    Matrix first = matrixSequence.matrix(0);
    Matrix secund = matrixSequence.matrix(1);
    matrixSequence.data() = matrixSequence.data()*2;
    CHECK(matrixSequence.matrix(0).isApprox(first*2));
    CHECK(matrixSequence.matrix(1).isApprox(secund*2));
}

TEST(MATRIXSEQUENCE_CHANGE_VALUE_BY_MATRIX) {
    static const Dimension arr[] = { Dimension(1, 2), Dimension(2, 2) };
    vector<Dimension> shapes (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MatrixSequence matrixSequence(shapes);

    Matrix first = Matrix::Ones(1, 2);
    Matrix secund(2, 2);
    secund << 21, 22, 23, 24;

    // Basic changes
    matrixSequence.matrix(0) = first;
    matrixSequence.matrix(1) = secund;
    CHECK(matrixSequence.matrix(0).isApprox(Matrix::Ones(1, 2)));
    CHECK(matrixSequence.matrix(1).isApprox(secund));

    // Change the value of the original matrix
    first << 3, 4;
    CHECK(matrixSequence.matrix(0).isApprox(Matrix::Ones(1, 2)));
    CHECK(matrixSequence.matrix(1).isApprox(secund));

    // Check the consistency of the array
    ArrayX origin = matrixSequence.data();
    matrixSequence.matrix(0) << Matrix::Ones(1, 2) * 2;
    matrixSequence.matrix(1) << secund * 2;
    CHECK(matrixSequence.data().isApprox(origin *2));
    CHECK(matrixSequence.matrix(0).isApprox(Matrix::Ones(1, 2)*2));
    CHECK(matrixSequence.matrix(1).isApprox(secund*2));
}

TEST(MATRIXSEQUENCE_COPY) {
    static const Dimension arr[] = { Dimension(1, 2), Dimension(2, 2) };
    vector<Dimension> shapes (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MatrixSequence matrixSequence(shapes);

    ArrayX normalArray(6);
    normalArray << 10, 11, 20, 21, 22, 23;
    matrixSequence.data() = normalArray;
    MatrixSequence matrixSequence2 = matrixSequence;
    CHECK(matrixSequence.data().isApprox(normalArray));
    CHECK(matrixSequence2.data().isApprox(normalArray));

    matrixSequence2.data() = Matrix::Ones(6, 1);
    CHECK(matrixSequence.data().isApprox(normalArray));
    CHECK(matrixSequence2.data().isApprox((Matrix::Ones(6, 1)).array()));
}
