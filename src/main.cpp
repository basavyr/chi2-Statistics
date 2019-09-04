#include "readData.h"
#include "variance.h"
#include "chiSquared.h"
#include "generateExpData.h"
#include "genData.h"

#include <iostream>
#include <ctime>

using namespace std;

typedef struct P
{
    double x;
    double exp, th;

public:
    friend ostream &operator<<(ostream &out, P &pq);
} P;

/* ostream &operator<<(ostream &output, P &pq)
{
    output << pq.x << " " << pq.exp << " " << pq.th;
    output << endl;
    return output;
}
 */
vector<P> xx;

void generateArray(vector<dp> a, vector<double> *a1, vector<double> *a2)
{
    /*     if (a.size())
        a.clear(); */
    if (a.size())
    {
        for (int i = 0; i < a.size(); ++i)
        {
            a1->push_back(a.at(i).exp);
            a2->push_back(a.at(i).th);
        }
    }
}

vector<dp> arr;

int main()
{
    const char *input = "/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/lu163_august2019_2paramMinimize/cpp-files/fitAlgorithm/chi2-Statistics/data/inputData.dat";
    const char *output = "/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/lu163_august2019_2paramMinimize/cpp-files/fitAlgorithm/chi2-Statistics/data/outputData.dat";
    const char *chiOutput = "/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/lu163_august2019_2paramMinimize/cpp-files/fitAlgorithm/chi2-Statistics/data/chiOutput.dat";

    //outputfile for chi2 results (depending on IZERO and V)
    ofstream outputchi2(chiOutput);

    double result;
    vector<double> arrexp, arrth;
    vector<double> spin1, spin2, spin3, spin4;
    vector<double> tsd1, tsd2, tsd3, tsd4;
    clock_t myclock;
    vector<double> arrChi2;
    myclock = clock();
    //readData(input, output, &arr);
    //SIMULATION ALGORITHM
    for (int i = 1; i <= 2; ++i)
    {
        for (double v = 0.05; v <= 10; v += 5)
        {
            generateData((double)i, v);
            readData(input, output, &arr);
            generateArray(arr, &arrexp, &arrth);
            showChiSquared(arrexp, arrth, &result);
            arrChi2.push_back(result);
            //            cout << i << " " << v << " " << result << endl;
        }
    }
    for (vector<double>::iterator it = arrChi2.begin(); it != arrChi2.end(); ++it)
    {
        outputchi2 << *it << endl;
    }

    // cout << arr.size() << endl;
    //cout << arrexp.size() << endl;
    /*     for (int i = 0; i < arr.size(); ++i)
    {
        arrexp.push_back(arr.at(i).exp);
        arrth.push_back(arr.at(i).th);
    } */

    /*
    generateExpData(&spin1, &spin2, &spin3, &spin4, &tsd1, &tsd2, &tsd3, &tsd4);
    myclock = clock() - myclock;
    cout << "array 1" << endl;
    for (vector<double>::iterator it = tsd1.begin(); it != tsd1.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "array 2" << endl;
    for (vector<double>::iterator it = tsd2.begin(); it != tsd2.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "array 3" << endl;
    for (vector<double>::iterator it = tsd3.begin(); it != tsd3.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "array 4" << endl;
    for (vector<double>::iterator it = tsd4.begin(); it != tsd4.end(); ++it)
        cout << *it << " ";
    cout << endl;
    // cout << "Full exec took " << (float)myclock / CLOCKS_PER_SEC << " seconds";
    cout << endl;
    /*   cout << arrexp.size() << endl;
    cout << arrth.size() << endl;
   */
    /* 
    cout << arrexp.at(4) - arrth.at(4) << endl;
    cout << arrexp.at(5) - arrth.at(5) << endl;
    cout << arrexp.at(6) - arrth.at(6) << endl;
 */
    /*
     cout << arrexp.at(4);
    cout << endl;
    cout << arrth.at(4);
    cout << endl; */
    /* 
    cout << computeMean(arrexp) << " " << computeMean(arrth) << endl;
    computeVariance(arrth, &result);
    cout << result << endl;
    result = 0;
    computeVariance(arrexp, &result);
    cout << result << endl; */
    /* cout << "X          EXP            TH" << endl;
    for (int i = 0; i < arr.size(); ++i)
        cout << arr.at(i).x << " " << arr.at(i).exp << " " << arr.at(i).th << endl;
     */
    /*    for (vector<double>::iterator it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << " ";
    std::cout << endl;
    computeVariance(&arr);
    for (vector<double>::iterator it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << " ";
    std::cout << endl;
  */
    //   showChiSquared(a, b);
    return 0;
}