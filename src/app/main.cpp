#include "parsercsv/CSVManager.h"
#include "gradientdescent/rprop.h"
#include <omp.h>
#include <stdio.h>
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

    int ncol=784;
    std::cout << "Entrez le nombre de colonnes dans X" << std::endl;
    cin >> ncol;
    int nrow=5000;
    std::cout << "Entrez le nombre de lignes dans X train" << std::endl;
    cin >> nrow;
    int nrowtest=5000;
    std::cout << "Entrez le nombre de lignes dans X test" << std::endl;
    cin >> nrowtest;
    int nlabel=10;
    std::cout << "Entrez le nombre de modalites dans Y" << std::endl;
    cin>> nlabel;

    char cheminTrain[1000];
    std::cout << "Entrez le chemin physique du fichier d'apprentissage entre double quote" << std::endl;
    cin >> cheminTrain;
    std::ifstream       file(cheminTrain);
    CSVRow              row;
	MatrixXd X(nrow,ncol);
	MatrixXd Y(nrow,nlabel);

	int i=0;

    while(file >> row)
    {
        getX(X,i,ncol,row);
        getY(Y,i,nlabel,row);
		i++;
	}

    char cheminTest[1000];
    std::cout << "Entrez le chemin physique du fichier de test entre double quote" << std::endl;
    cin >> cheminTest;
    std::ifstream       filetest(cheminTest);

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

    //double start = omp_get_wtime();
    int niter = 1000;
    std::cout << "Entrez le nombre d'iteration" << std::endl;
    cin >> niter;

    int nCouche=0;
    std::cout << "Entrez le nombre de couches cachees (1 ou 2)" << std::endl;
    cin >> nCouche;

    if (nCouche==1)
    {
        int nNeurone=0;
        std::cout << "Entrez le nombre de neurones" << std::endl;
        cin >> nNeurone;
        static const int arr[] = {ncol, nNeurone, nlabel};
        vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
		
		double TauxI=0;
		std::cout << "Entrez le taux d'apprentissage initial (par ex 1)" << std::endl;
        cin >> TauxI;
		double TauxM=0;
		std::cout << "Entrez le taux d'apprentissage maximal (par ex 10)" << std::endl;
        cin >> TauxM;

        Rprop estimateur(X, Y, dimensions, TauxM, TauxI);

        for(int i=0; i<niter; i++)
        {
            std::cout << "Iteration n_" << i+1 << std::endl;
            estimateur.doIteration();
            std::cout << "Erreur (E) Train:" << "\t" << estimateur.computeError(X,Y) << "\t" << "Biens classes Train:" << "\t" << estimateur.getPerceptron().computeClassificationScoreMulti(X, Y) << "\n"
                      << "Erreur (E) Test:" << "\t" << estimateur.computeError(Xtest,Ytest) << "\t" << "Biens classes Train:" << "\t" << estimateur.getPerceptron().computeClassificationScoreMulti(Xtest, Ytest) << std::endl;

         }
      } else {
        if (nCouche==2)
        {
            int nNeurone1=0;
            int nNeurone2=0;
            std::cout << "Entrez le nombre de neurones de la 1ere couche cachee" << std::endl;
            cin >> nNeurone1;
            std::cout << "Entrez le nombre de neurones de la 2eme couche cachee" << std::endl;
            cin >> nNeurone2;
            static const int arr[] = {ncol, nNeurone1, nNeurone2, nlabel};
            vector<int> dimensions (arr, arr + sizeof(arr) / sizeof(arr[0]) );
			
			double TauxI=0;
			std::cout << "Entrez le taux d'apprentissage initial (par ex 1)" << std::endl;
			cin >> TauxI;
			double TauxM=0;
			std::cout << "Entrez le taux d'apprentissage maximal (par ex 10)" << std::endl;
			cin >> TauxM;

            Rprop estimateur(X, Y, dimensions, TauxM, TauxI);

            for(int i=0; i<niter; i++)
            {
                std::cout << "Iteration n_" << i+1 << std::endl;
                estimateur.doIteration();
                std::cout << "Erreur (E) Train:" << "\t" << estimateur.computeError(X,Y) << "\t" << "Biens classes Train:" << "\t" << estimateur.getPerceptron().computeClassificationScoreMulti(X, Y) << "\n"
                          << "Erreur (E) Test:" << "\t" << estimateur.computeError(Xtest,Ytest) << "\t" << "Biens classes Train:" << "\t" << estimateur.getPerceptron().computeClassificationScoreMulti(Xtest, Ytest) << std::endl;

            }
          } else{
            std::cout << "Attention: le nombre de couche doit valoir 1 ou 2" << std::endl;
            }
        }

    std::cout << "\n" << std::endl;
    printf("MERCI D'AVOIR ESSAYE NOTRE PERCEPTRON MULTI-COUCHES !" );

    system("PAUSE");
        //double end = omp_get_wtime();
        //std::cout << (end - start) << std::endl;

}
