#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//using namespace std;



class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }

        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str,line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream,cell,','))
            {
                m_data.push_back(cell);
            }
        }
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   


int main()
{
    std::ifstream       file("W:\plop.csv");

    CSVRow              row;

	std::vector<std::vector<double>> MatX(178);
	
	for (int i=0; i<178; i++)
	{
		MatX[i]=std::vector<double>(13);

	}

	std::vector<std::vector<int>> MatY(178);
	for (int i=0; i<178; i++)
	{
		MatY[i]=std::vector<int>(3);

	}

	int i=0;

    while(file >> row)
    {
		for (int j=0; j<13; j++)
		{
			double a=atof(row[j+1].c_str());
			MatX[i][j]=a;
		}

		if (row[0]=="1")
		{
			MatY[i][0]=1;
		}

		if (row[0]=="2")
		{
			MatY[i][1]=1;
		}

		if (row[0]=="3")
		{
			MatY[i][2]=1;
		}
		i++;

	}
}