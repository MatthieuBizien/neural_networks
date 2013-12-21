#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include <unittest++/UnitTest++.h>

#include "gradientdescent/gradientdescent.h"

using std::vector;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

TEST(GRADIENT_DESCENT_XOR) {
    srand(1664);
    const unsigned int n=20;
    Matrix X(n, 2), Y(n, 1);
    for(unsigned int i=0; i<n; i++) {
        const int n1 = rand() % 2;
        const int n2 = rand() % 2;
        X.row(i) << n1, n2;
        Y.row(i) << (n1 ^ n2);
    }
    Matrix Xval(n, X.cols()), Yval(n, Y.cols());
    for(unsigned int i=0; i<n; i++) {
        const int n1 = rand() % 2;
        const int n2 = rand() % 2;
        Xval.row(i) << n1, n2;
        Yval.row(i) << (n1 ^ n2);
    }

    const int arr[] = {int(X.cols()), 4, int(Y.cols())};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    GradientDescent estimateur(X, Y, dimensions, 10);
    for(int i=0; i<100; i++) {
        estimateur.doIteration();
    }
    CHECK_CLOSE(0, estimateur.getErrors().back(), 5e-2);
    CHECK_CLOSE(0, estimateur.computeError(Xval, Yval), 5e-2);
}

TEST(GRADIENT_DESCENT_XOR3) {
    srand(1665);
    const unsigned int n=8, m=50;
    Matrix X(n, 3), Y(n, 1);
    X << 0, 0, 0,
         0, 0, 1,
         0, 1, 0,
         0, 1, 1,
         1, 0, 0,
         1, 0, 1,
         1, 1, 0,
         1, 1, 1;
    Y << 0, 1, 1, 0, 1, 0, 0, 1;
    Matrix Xval(m, X.cols()), Yval(m, Y.cols());
    for(unsigned int i=0; i<Xval.rows(); i++) {
        const int n1 = rand() % 2;
        const int n2 = rand() % 2;
        const int n3 = rand() % 2;
        Xval.row(i) << n1, n2, n3;
        Yval.row(i) << (n1 ^ n2 ^ n3);
    }

    const int arr[] = {int(X.cols()), 4, int(Y.cols())};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    GradientDescent estimateur(X, Y, dimensions, 3);
    for(int i=0; i<600; i++) {
        estimateur.doIteration();
    }

    CHECK_CLOSE(0, estimateur.getErrors().back(), 5e-2);
    CHECK_CLOSE(0, estimateur.computeError(Xval, Yval), 5e-2);
}
