// variance.h
#ifndef VARIANCE_H
#define VARIANCE_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

void showStatusVariance();

double computeVarianceFunction(vector<double> a);
double computeMean(vector<double> a);

void computeVariance(vector<double> a, double *result);

#endif /* VARIANCE_H */
