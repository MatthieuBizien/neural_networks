#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include <unittest++/UnitTest++.h>

#include "gradientdescent.h"

using std::vector;
using std::get;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;

TEST(GRADIENT_DESCENT_XOR) {
    srand(1664);
    const unsigned int n=5;
    Matrix X(n, 2), Y(n, 1);
    for(unsigned int i=0; i<n; i++) {
        int n1 = rand()>0.5? 1: 0;
        int n2 = rand()>0.5? 1: 0;
        X.row(i) << n1, n2;
        Y.row(i) << (n1 ^ n2);
    }
    static const int arr[] = {2, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    GradientDescent estimateur(X, Y, dimensions);
    for(int i=0; i<15; i++) {
        estimateur.doIteration();
    }
    CHECK_CLOSE(estimateur.computeError(X, Y), 0, 5e-2);
}
