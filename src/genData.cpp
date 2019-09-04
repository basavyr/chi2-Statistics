#include "genData.h"
#include "generateExpData.h"
#include "genTheoreticalData.h"

ofstream output("/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/lu163_august2019_2paramMinimize/cpp-files/fitAlgorithm/chi2-Statistics/data/inputData.dat");

void showGenDataStatus()
{
    cout << "generating data..." << endl;
}

void generateData(double param1, double param2)
{
    // showGenDataStatus();
    vector<double> spin1;
    vector<double> spin2;
    vector<double> spin3;
    vector<double> spin4;
    //EXPERIMENTAL ENERGIES
    vector<double> tsd1;
    vector<double> tsd2;
    vector<double> tsd3;
    vector<double> tsd4;
    //THEORETICAL ENERGIES
    vector<double> tsd1th;
    vector<double> tsd2th;
    vector<double> tsd3th;
    vector<double> tsd4th;

    //CREATE EXPERIMENTAL DATA SET
    generateExpData(&spin1, &spin2, &spin3, &spin4, &tsd1, &tsd2, &tsd3, &tsd4);
    // cout << "getting theoretical data..." << endl;
    //CREATE HTOERETICAL DATA SET
    generateThData(param1, param2, spin1, spin2, spin3, spin4, &tsd1th, &tsd2th, &tsd3th, &tsd4th);

    for (int i = 0; i < spin1.size(); ++i)
    {
        output << spin1.at(i) << "," << tsd1.at(i) << "," << tsd1th.at(i);
        output << endl;
    }
    for (int i = 0; i < spin2.size(); ++i)
    {
        output << spin2.at(i) << "," << tsd2.at(i) << "," << tsd2th.at(i);
        output << endl;
    }
    for (int i = 0; i < spin3.size(); ++i)
    {
        output << spin3.at(i) << "," << tsd3.at(i) << "," << tsd3th.at(i);
        output << endl;
    }
    for (int i = 0; i < spin4.size(); ++i)
    {
        output << spin4.at(i) << "," << tsd4.at(i) << "," << tsd4th.at(i);
        output << endl;
    }
    /* cout << spin1.size() << " " << tsd1.size() << endl;
    cout << spin2.size() << " " << tsd2.size() << endl;
    cout << spin3.size() << " " << tsd3.size() << endl;
    cout << spin4.size() << " " << tsd4.size() << endl;
    for (vector<double>::iterator it = spin1.begin(); it != spin1.end(); ++it)
        cout << *it << " ";
    cout << endl;
    for (vector<double>::iterator it = spin2.begin(); it != spin2.end(); ++it)
        cout << *it << " ";
    cout << endl;
    for (vector<double>::iterator it = spin3.begin(); it != spin3.end(); ++it)
        cout << *it << " ";
    cout << endl;
    for (vector<double>::iterator it = spin4.begin(); it != spin4.end(); ++it)
        cout << *it << " ";
    cout << endl; */
    /* 
    if (spin1.size() == tsd1.size())
        cout << "OK" << endl;
    if (spin2.size() == tsd2.size())
        cout << "OK" << endl;
    if (spin3.size() == tsd3.size())
        cout << "OK" << endl;
    if (spin4.size() == tsd4.size())
        cout << "OK" << endl; */
}