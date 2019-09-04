#include "genTheoreticalData.h"
#include "energyCalculation.h"

void showStatusGenThData()
{
    cout << "creating theoretical data...";
    cout << endl;
}

void generateThData(double param1, double param2, vector<double> spin1, vector<double> spin2, vector<double> spin3, vector<double> spin4, vector<double> *tsd1, vector<double> *tsd2, vector<double> *tsd3, vector<double> *tsd4)
{
   // showStatusGenThData();
  //  cout << param1 << " " << param2 << endl;
    for (int i = 0; i < spin1.size(); ++i)
    {
        tsd1->push_back(computeEnergy(1, spin1.at(i), param1, param2));
    }
    for (int i = 0; i < spin2.size(); ++i)
    {
        tsd2->push_back(computeEnergy(2, spin2.at(i), param1, param2));
    }
    for (int i = 0; i < spin3.size(); ++i)
    {
        tsd3->push_back(computeEnergy(3, spin3.at(i), param1, param2));
    }
    for (int i = 0; i < spin4.size(); ++i)
    {
        tsd4->push_back(computeEnergy(4, spin4.at(i), param1, param2));
    }
    return;
}