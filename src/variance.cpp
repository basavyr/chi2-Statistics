#include "variance.h"

void showStatusVariance()
{
    std::cout << "computing variance...";
    std::cout << endl;
}

double computeMean(vector<double> a)
{
    int N = a.size();
    double sumMean = 0;
    for (int i = 0; i < N; ++i)
        sumMean += a.at(i);
    return (double)sumMean / N;
}

double computeVarianceFunction(vector<double> a)
{
    int N = a.size();
    double sumVar = 0.0;
    double mean = 0.0;
    mean = computeMean(a);
    for (int i = 0; i < N; ++i)
    {
        sumVar += pow(a.at(i) - mean, 2);
    }
    return (double)sumVar / (N - 1);
}

void computeVariance(vector<double> a, double *result)
{
    showStatusVariance();
    /*   cout << "The Variance made by the function is " << computeVarianceFunction(a) << endl;
   */
    *result = computeVarianceFunction(a);
    return;
}