#include "parsercsv/CSVManager.h"

    /**
     * @brief 
	 * Define the operator >> and read line per line a csv file with CSVRow
    **/
std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

int main()
{
	/**
     * @brief 
	 * load csv file
	 *  parameter initialization file with ncol not containing the column 
	 *  of variable of interest
	 *  Create matrix X and Y
    **/
    std::ifstream       file("G:/plop.csv");

    CSVRow              row;
	
	int ncol=13;
    int nrow=178;
	int nlabel=3;

	MatrixXd X(nrow,ncol);
	MatrixXd Y(nrow,nlabel);

	int i=0;

    while(file >> row)
    {
        getX(X,i,ncol,row);
        getY(Y,i,nlabel,row);
		i++;
	}
    std::cout << Y <<std::endl;
    std::cout << "Hi, small world!" << std::endl;

}
