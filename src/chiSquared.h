// chiSquared.h
#ifndef CHI_SQUARED_H
#define CHI_SQUARED_H

#include <vector>
#include <cmath>
using namespace std;

void showStatusChi();

double chiSquared(double expValue, double thValue);
double computeChiSquared(vector<double> exp, vector<double> th);

void showChiSquared(vector<double> exp, vector<double> th, double *result);

#endif /* CHI_SQUARED_H */