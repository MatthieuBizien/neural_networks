#include "CSVRow.h"
#include <Eigen/Dense>

using std::vector;
using Eigen::MatrixXd;
typedef Eigen::MatrixXd Matrix;

    /**
     * @brief getX and getY functions
     * see CSVManager.cpp for more information
    **/
Matrix getX(Matrix &, int, int, CSVRow);
Matrix getY(Matrix &, int, int, CSVRow);
