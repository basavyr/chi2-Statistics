#include "chiSquared.h"
#include <iostream>

void showStatusChi()
{
    std::cout << "computing chi squared...";
    std::cout << endl;
}

double chiSquared(double expValue, double thValue)
{
    return (double)pow(expValue - thValue, 2) / expValue;
}

double computeChiSquared(vector<double> exp, vector<double> th)
{
    int N1, N2;
    N1 = exp.size();
    N2 = th.size();
    if (N1 != N2)
        return 0;
    double sumChi = 0;
    for (int i = 0; i < N1; ++i)
    {
        if (chiSquared(exp.at(i), th.at(i)))
            sumChi += chiSquared(exp.at(i), th.at(i));
    }
    if (!sumChi)
        return 0;
    return (double)sumChi / N1;
}

void showChiSquared(vector<double> exp, vector<double> th, double *result)
{
    showStatusChi();
    *result = computeChiSquared(exp, th);
}