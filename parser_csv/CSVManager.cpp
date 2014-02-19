#include "CSVManager.h"


Matrix getX(Matrix& MatX, int i, int nrow, int ncol, CSVRow row)
{	
	for (int j=0; j<ncol; j++)
		{
			double a=atof(row[j+1].c_str());
			MatX(i,j)= a;
		}
	return MatX;
}


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