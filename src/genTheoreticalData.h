//geTheoreticalData.h
#ifndef GEN_THEORETICALDATA_H
#define GEN_THEORETICALDATA_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void showStatusGenThData();
void generateThData(double param1, double param2, vector<double> spin1, vector<double> spin2, vector<double> spin3, vector<double> spin4, vector<double> *tsd1, vector<double> *tsd2, vector<double> *tsd3, vector<double> *tsd4);

#endif /*genTheoreticalData.h */