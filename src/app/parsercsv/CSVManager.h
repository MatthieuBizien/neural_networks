#include "CSVRow.h"
#include <Eigen/Dense>

using std::vector;
using Eigen::MatrixXd;
typedef Eigen::MatrixXd Matrix;

    /**
     * @brief getX and getY functions
	 * see CSVManager.cpp for more informations
    **/
Matrix getX(Matrix &, int, int, int, CSVRow);
Matrix getY(Matrix &, int, int, int, CSVRow);
