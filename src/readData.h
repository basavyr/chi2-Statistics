//readData.h
#ifndef READ_DATA_H
#define READ_DATA_H
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Data
{
public:
    std::string x;
    double expVal, thVal;

public:
    friend istream &operator>>(istream &in, Data &db);
};

double getX(Data &db);
double getExpVal(Data &db);
double getThVal(Data &db);

typedef struct datapoints
{
    double x;
    double exp;
    double th;
} dp;

dp adddata(double x, double exp, double th);

void showStatus();
void readData(const char *inputfile, const char *outputfile, vector<dp> *arr);

#endif /* READ_DATA_H */