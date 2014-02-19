#include "CSVRow.h"
#include <C:/Users/Kami/Documents/GitHub/neural_networks/src/libs/Eigen/Dense>

using std::vector;
using Eigen::MatrixXd;
typedef Eigen::MatrixXd Matrix;

Matrix getX(Matrix &, int, int, int, CSVRow);
Matrix getY(Matrix &, int, int, int, CSVRow);
