#include <fstream>
#include <memory>
#include <Eigen/Dense>

#include "utils/io.h"
#include "utils/math.h"
#include "acostfunctionminimizeur.h"
#include "gradientdescent/rprop.h"
#include "neuralnets/regularizedmultilayerperceptron.h"
#include "gradientdescent/gradientdescent.h"

typedef Eigen::MatrixXd Matrix;

int main()
{
    srand(42);
    std::cout << "Welcome to the best program worldwide for neural networks!"
              << "\nWhich dataset do you want to use ? We have for you:"
              << "\n1: 4000 observations of MNIST, the handwritten recognition"
                 "database, and 1000 test data. Available at "
                 "$BASEDIR/data/miniMinst"
              << std::endl;

    char path0[FILENAME_MAX];
    if (!GetCurrentDir(path0, sizeof(path0))) {
        return errno;
    }
    path0[sizeof(path0) - 1] = '\0'; /* not really required */
    std::string path(path0);

    Matrix X, Y0, Xtest, Ytest0;
    try {
        X = matrix_of_file<double>(path, "train-images.csv");
        Y0 = matrix_of_file<double>(path, "train-labels.csv");
        Xtest = matrix_of_file<double>(path, "test-images.csv");
        Ytest0 = matrix_of_file<double>(path, "test-labels.csv");
    } catch (const std::ios::failure exc) {
        std::cerr << exc.what() << std::endl;
        return 2;
    }

    int ncol = 1 + int(Y0.array().maxCoeff());
    auto Y = getMatrixOfClasses(Y0, ncol);
    auto Ytest = getMatrixOfClasses(Ytest0, ncol);

    const int arr[] = {int(X.cols()), 100, 20, int(Y.cols())};
    const vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    for (auto c : dimensions) std::cout << c << ' '; std::cout << std::endl;
    // TODO bug
//    GradientDescent minimizeur(X, Y,
    Rprop minimizeur(X, Y,
                     std::unique_ptr<RegularizedMultiLayerPerceptron>(
                         new RegularizedMultiLayerPerceptron(dimensions, 1)),
                     10, 1);
//                     0.01);
//    Rprop minimizeur(X, Y,
//                     std::unique_ptr<MultiLayerPerceptron>(
//                         new MultiLayerPerceptron(dimensions)), 50, 1);
    for(int i=0; i<10000; i++) {
        minimizeur.doIteration();
        std::cout << i << "\t"
                  << minimizeur.getErrors().back() << "   \t"
                  << minimizeur.computeError(Xtest, Ytest)
                  << std::endl;
        const MatrixSequence& coeffs = minimizeur.getNeuralNet().getWeights();
        for(unsigned int i=0; i<coeffs.size(); i++) {
            std::cout << " M" << i
                      << " (" << coeffs.matrix(i).rows()
                      << "," << coeffs.matrix(i).cols() << ")"
                      << " \t" << coeffs.matrix(i).minCoeff()
                      << " \t" << coeffs.matrix(i).norm()
                      << "    \t" << coeffs.matrix(i).maxCoeff()
                      << std::endl;
        }

    }
}
