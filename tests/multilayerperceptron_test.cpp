#include <vector>
#include <Eigen/Dense>
#include <iostream>

#include <unittest++/UnitTest++.h>

#include "utils/matrixsequence.h"
#include "neuralnets/multilayerperceptron.h"

using std::vector;
using std::get;

typedef Eigen::VectorXd VectorX;
typedef Eigen::MatrixXd Matrix;
typedef Eigen::ArrayXd ArrayX;


/**
 * @brief computeNumericalGradient
 *  Compute the gradient by small modification of the input vector.
 */
Matrix computeNumericalGradient(const MultiLayerPerceptron& perceptron,
                                const Matrix&X, const Matrix& y) {
    double epsilon = 1e-3;
    int sizeGradient = perceptron.getWeights().data().rows();
    Matrix numericalGradient = Matrix::Zero(sizeGradient, 1);
    // We compute f'(x) ~ (f(x+epsilon)-f(x-epsilon))/(2*epsilon) because it
    // limits the impact of f''(x), compared to f(x+2*epsilon)/(2*epsilon).
    for(int i=0; i<sizeGradient; i++) {
        ArrayX increment = ArrayX::Zero(sizeGradient, 1);
        increment.row(i) += epsilon;

        MultiLayerPerceptron networkPlus = perceptron;
        networkPlus.getWeights().data() += increment;
        auto errorplus = networkPlus.computeError(X, y);

        MultiLayerPerceptron networkMoins = perceptron;
        networkMoins.getWeights().data() -= increment;
        double errorMoins = networkMoins.computeError(X, y);

        numericalGradient.row(i).array() +=
                (errorplus - errorMoins) / (2 * epsilon);
    }
    return numericalGradient;
}


/**
  Test the initialisation and the copy of a neural network.
  */
TEST(INIT_PERCEPTRON) {
    static const int arr[] = {5, 3, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    srand(42);
    Matrix X = Matrix::Random(20, 5);

    srand(314159);
    MultiLayerPerceptron perceptron(dimensions);
    perceptron.compute(X);

    MultiLayerPerceptron copy = perceptron;
    CHECK(perceptron.compute(X).isApprox(copy.compute(X)));
}

/**
  Test that null weights output a 50% probability.
  */
TEST(NULL_PERCEPTRON) {
    static const int arr[] = {2, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MultiLayerPerceptron perceptron(dimensions);
    perceptron.getWeights().data().setZero();
    Matrix X(4, 2), y(4, 1);
    X << 1,1,   1,-1,   -1,1,   -1,-1;
    Matrix computed = perceptron.compute(X);
    y << 0.5,     0.5,      0.5,      0.5;
    CHECK(y.isApprox(computed));
}

/**
  Check a perceptron which is independant of the input.
  */
TEST(CONSTANT_PERCEPTRON) {
    // Constant network network
    static const int arr[] = {2, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MultiLayerPerceptron perceptron(dimensions);
    perceptron.getWeights().data().setZero();
    perceptron.getWeights().matrix(1)(0) = 1;
    Matrix X(4, 2), y(4, 1);
    X << 1,1,   1,-1,   -1,1,   -1,-1;
    Matrix computed = perceptron.compute(X);
    double expected = 1 / (1 + std::exp(-1));
    y << expected, expected, expected, expected;
    CHECK(y.isApprox(computed));
}


/**
  Test the correctness of an hardcoded implementation of XOR against
  hard coded values.
  */
TEST(CORRECTNESS_GRADIENT_XOR) {
    static const int arr[] = {2, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    MultiLayerPerceptron perceptron(dimensions);
    perceptron.getWeights().matrix(0) << -10,  20,  20,
                                            -20,  15,  15;
    perceptron.getWeights().matrix(1) << -10,  20, -20;

    Matrix X(4, 2), y(4, 1);
    X << 0, 1,
         1, 0,
         1, 1,
         0, 0;
    y << 1, 1, 0, 0;

    tuple<double, ArrayX> error_gradient = perceptron.computeGradient(X, y);
    double J = get<0>(error_gradient);
    ArrayX gradient = get<1>(error_gradient).matrix();
    CHECK_CLOSE(J, 4.87e-5, 1e-6);
    CHECK_CLOSE(J, perceptron.computeError(X, y), 1e-7);
    // We test only the coeff that are invariant if the matrix is transposed
    CHECK_CLOSE(gradient(0), 0, 1e-7);
    CHECK_CLOSE(gradient(5), 1.71e-6, 1e-7);
    CHECK_CLOSE(gradient(6), -3.25e-6, 1e-7);
}


/**
  Test the correctness of the gradient implementation using an infinitesimal
  derivative.
  */
void test_infinitesimal_gradient(vector<int> dimensions) {
    MultiLayerPerceptron perceptron(dimensions);
    Matrix X = Matrix::Random(10, dimensions.at(0));
    Matrix y = Matrix::Random(X.rows(), dimensions.back());
    for(int i=0; i<y.rows(); i++) {y(i) = y(i)>0.5?1:0;}

    int sizeGradient = 0;
    for(unsigned int i=0; i<dimensions.size()-1; i++) {
        sizeGradient += (dimensions.at(i) +1) * dimensions.at(i+1);
    }

    Matrix numericalGradient = computeNumericalGradient(perceptron, X, y);
    const tuple<double, ArrayX> error_gradient = perceptron.computeGradient(X, y);
    Matrix gradient = get<1>(error_gradient).matrix();

    CHECK_EQUAL(gradient.rows(), sizeGradient);
    CHECK_EQUAL(gradient.cols(), 1);
    CHECK(gradient.isApprox(numericalGradient, 1e-5));
    CHECK_CLOSE(get<0>(error_gradient), perceptron.computeError(X, y), 1e-6);
}
TEST(CORRECTNESS_GRADIENT_INFINITESIMAL_41) {
    srand(41);
    static const int arr[] = {4, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    test_infinitesimal_gradient(dimensions);
}
TEST(CORRECTNESS_GRADIENT_INFINITESIMAL_221) {
    srand(221);
    static const int arr[] = {2, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    test_infinitesimal_gradient(dimensions);
}
TEST(CORRECTNESS_GRADIENT_INFINITESIMAL_991) {
    srand(991);
    static const int arr[] = {9, 9, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    test_infinitesimal_gradient(dimensions);
}
TEST(CORRECTNESS_GRADIENT_INFINITESIMAL_54321) {
    srand(54321);
    static const int arr[] = {5, 4, 3, 2, 1};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    test_infinitesimal_gradient(dimensions);
}
TEST(CORRECTNESS_GRADIENT_INFINITESIMAL_278) {
    srand(278);
    static const int arr[] = {2, 7, 8};
    vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    test_infinitesimal_gradient(dimensions);
}
