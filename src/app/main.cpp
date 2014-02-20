#include "parsercsv/CSVManager.h"
#include "gradientdescent/rprop.h"
using namespace std;
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
    std::ifstream       file("G:/data/wineAppr.csv");
    CSVRow              row;
	
	int ncol=13;
    int nrow=148;
    int nrowtest=30;
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
    std::ifstream       filetest("G:/data/wineTest.csv");

    CSVRow              rowt;
    MatrixXd Xtest(nrowtest,ncol);
    MatrixXd Ytest(nrowtest,nlabel);

    int k=0;

    while(filetest >> rowt)
    {
        getX(Xtest,k,ncol,rowt);
        getY(Ytest,k,nlabel,rowt);
        k++;
    }

    int niter = 100;

        static const int arr[] = {13, 20, 25, 3}; // 13 variables dans X,deux couches cachées de 20 et 25 neurones, 3 dans Y

        vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );

        Rprop estimateur(X, Y, dimensions, 10, 1);

        ofstream Ofile("G:/Output/WineOutput_2C_100N.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

        for(int i=0; i<niter; i++)
        {
            estimateur.doIteration();
            //std::cout << estimateur.computeError(X,Y) << "," << estimateur.getPerceptron().computeClassificationScoreMulti(X, Y) << "," << estimateur.getPerceptron().computeClassificationScoreMulti(Xtest, Ytest) << std::endl;

                    if(Ofile)
                    {

                            Ofile << i+1 << "," << estimateur.computeError(X,Y) << "," << estimateur.getPerceptron().computeClassificationScoreMulti(X, Y) << "," << estimateur.computeError(Xtest,Ytest) << "," << estimateur.getPerceptron().computeClassificationScoreMulti(Xtest, Ytest) << std::endl;
                    }

        }
        Ofile.close();


}
