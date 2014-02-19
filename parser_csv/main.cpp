#include "CSVManager.h"

//lecture ligne par ligne du fichier
std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

int main()
{
	//chargement du fichier
    std::ifstream       file("G:\wine.csv");

    CSVRow              row;
	
	//initialisation des param�tres du fichier avec ncol ne contenant pas la colonne de Y
	int ncol=13;
	int nrow=178;
	int nlabel=3;

	//Cr�ation des matrices X et Y
	std::vector<std::vector<double>> X=CreateX(nrow,ncol);
	std::vector<std::vector<int>> Y=CreateY(nrow,nlabel);
	
	//Remplissage des matrices X et Y
	int i=0;

    while(file >> row)
    {
		GetX(X,i,nrow,ncol,row);
		GetY(Y,i,nrow,nlabel,row);
		i++;
	}
}