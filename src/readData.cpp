#include "readData.h"

using namespace std;

void showStatus()
{
    std::cout << "reading data...";
    std::cout << endl;
    std::cout.flush();
}

istream &operator>>(istream &input, Data &db)
{
    std::getline(input, db.x, ',');
    input >> db.expVal;
    input.ignore();
    input >> db.thVal;
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

double getX(Data &db)
{
    return std::stod(db.x);
}

double getExpVal(Data &db)
{
    return (double)db.expVal;
}

double getThVal(Data &db)
{
    return (double)db.thVal;
}

dp adddata(double x, double exp, double th)
{
    dp points = {x, exp, th};
    return points;
}

void readData(const char *inputfile, const char *outputfile, vector<dp> *arr)
{
    //  showStatus();

    ifstream datafile(inputfile);
    ofstream output(outputfile);

    Data input;
    vector<double> xdata, expdata, thdata;
    int it = 0;
    double t1, t2, t3;
    while (datafile >> input)
    {
        xdata.push_back(getX(input));
        expdata.push_back(getExpVal(input));
        thdata.push_back(getThVal(input));
        t1 = xdata.at(it);
        t2 = expdata.at(it);
        t3 = thdata.at(it);
        arr->push_back(adddata(t1, t2, t3));
        it++;
    }

    int N;

    if (xdata.size() == expdata.size() && thdata.size() == expdata.size())
        N = xdata.size();
    output << "X  "
           << "EXP  "
           << "TH" << endl;
    for (int i = 0; i < N; ++i)
    {
        output << xdata.at(i) << " " << expdata.at(i) << " " << thdata.at(i) << "\n";
    }
    std::cout.flush();
}