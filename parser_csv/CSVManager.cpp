#include "CSVManager.h"



std::vector<std::vector<double>> CreateX(int nrow, int ncol)
{
	std::vector<std::vector<double>> MatX(nrow);
	for (int i=0; i<nrow; i++)
	{
		MatX[i]=std::vector<double>(ncol);

	}
	return MatX;
}

std::vector<std::vector<int>> CreateY(int nrow, int nlabel)
{
	std::vector<std::vector<int>> MatY(nrow);
	for (int i=0; i<nrow; i++)
	{
		MatY[i]=std::vector<int>(nlabel);

	}
	return MatY;
}

std::vector<std::vector<double>> GetX(std::vector<std::vector<double>>& MatX, int i, int nrow, int ncol, CSVRow row)
{
	
	for (int j=0; j<ncol; j++)
		{
			double a=atof(row[j+1].c_str());
			MatX[i][j]=a;
		}
	return MatX;
}

std::vector<std::vector<int>> GetY(std::vector<std::vector<int>>& MatY, int i, int nrow, int nlabel, CSVRow row)
{
	
	for (int j=0; j<nlabel; j++)
	{
		double a=atof(row[0].c_str());
		
		if (a==j+1)
		{
			MatY[i][j]=1;
		}
	}
	return MatY;		
}