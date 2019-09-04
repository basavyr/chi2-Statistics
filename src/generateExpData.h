//gemerateExpData.h
#ifndef GENERATE_EXPDATA_H
#define GENERATE_EXPDATA_H

#include <iostream>
#include <vector>

using namespace std;

typedef struct DataExp
{
    double spin1, spin2, spin3, spin4;
    double tsd1, tsd2, tsd3, tsd4;
} data163;

data163 adddata(double spin1, double spin2, double spin3, double spin4, double tsd1, double tsd2, double tsd3, double tsd4);

void showStatusGeneration();

void generateExpData(vector<double> *spin1, vector<double> *spin2, vector<double> *spin3, vector<double> *spin4, vector<double> *tsd1, vector<double> *tsd2, vector<double> *tsd3, vector<double> *tsd4);

#endif