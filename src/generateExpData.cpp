#include "generateExpData.h"

void showStatusGeneration()
{
    cout << "generating experimental data...";
    cout << endl;
}

data163 adddata(double spin1, double spin2, double spin3, double spin4, double tsd1, double tsd2, double tsd3, double tsd4)
{
    data163 points = {spin1, spin2, spin3, spin4, tsd1, tsd2, tsd3, tsd4};
    return points;
}

void generateExpData(vector<double> *spin1, vector<double> *spin2, vector<double> *spin3, vector<double> *spin4, vector<double> *tsd1, vector<double> *tsd2, vector<double> *tsd3, vector<double> *tsd4)
{
    // showStatusGeneration();
    double band1[21] = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
    double band2[17] = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
    double band3[14] = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
    double band4[10] = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};
    int size1 = *(&band1 + 1) - band1;
    int size2 = *(&band2 + 1) - band2;
    int size3 = *(&band3 + 1) - band3;
    int size4 = *(&band4 + 1) - band4;
    /*    cout << "size if array is " << size1 << endl;
    cout << "size if array is " << size2 << endl;
    cout << "size if array is " << size3 << endl;
    cout << "size if array is " << size4 << endl;
  */
    //Nk = number of states for each band
    int N1, N2, N3, N4;
    N1 = 21;
    N2 = 17;
    N3 = 14;
    N4 = 10;
    for (int i = 0; i < N1; ++i)
    {
        spin1->push_back(8.5 + i * 2);
    }
    for (int i = 0; i < N2; ++i)
    {
        spin2->push_back(13.5 + i * 2);
    }
    for (int i = 0; i < N3; ++i)
    {
        spin3->push_back(16.5 + 2 * i);
    }
    for (int i = 0; i < N4; ++i)
    {
        spin4->push_back(23.5 + 2 * i);
    }
    for (int i = 0; i < size1; ++i)
    {
        tsd1->push_back(band1[i]);
    }
    for (int i = 0; i < size2; ++i)
    {
        tsd2->push_back(band2[i]);
    }
    for (int i = 0; i < size3; ++i)
    {
        tsd3->push_back(band3[i]);
    }
    for (int i = 0; i < size4; ++i)
    {
        tsd4->push_back(band4[i]);
    }
}