#include "CSVManager.h"

    /**
     * @brief getX function 
     *  We suppose that the first column in csv file is the variable of interest
     * @param
     *  The first item is the Eigen Matrix of features : MatX with 
	 *  nrow numbers of instances, ncol numbers of features
     *  i refers to the instance i
     **/
Matrix getX(Matrix& MatX, int i, int nrow, int ncol, CSVRow row)
{	
	for (int j=0; j<ncol; j++)
		{
			double a=atof(row[j+1].c_str());
			MatX(i,j)= a;
		}
	return MatX;
}

    /**
     * @brief getY function 
     *  We suppose that the first column in csv file is the variable of interest
	 *  getY creates dummies for each label of the variable of interest
	 *  labels numbers have to start by 1
     * @param
     *  The first item is the Eigen Matrix of labels dummies : MatY with 
	 *  nrow numbers of instances, nlabel numbers of labels
     *  i refers to the instance i
     **/

Matrix getY(Matrix & MatY, int i, int nrow, int nlabel, CSVRow row)
{
	for (int j=0; j<nlabel; j++)
	{
		double a=atof(row[0].c_str());
		
		if (a==j+1)
		{
			MatY(i,j)= 1;
		} else 
		{
			MatY(i,j)= 0;
		}
	}
	return MatY;
}