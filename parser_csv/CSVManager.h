#include "CSVRow.h"
#include <Eigen/Dense>

using std::vector;
using Eigen::MatrixXd;
typedef Eigen::MatrixXd Matrix;

Matrix getX(Matrix &, int, int, int, CSVRow);
Matrix getY(Matrix &, int, int, int, CSVRow);
