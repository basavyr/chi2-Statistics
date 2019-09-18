#include <iostream>
#include <vector>

using namespace std;

double func1(double x, double y)
{
    double sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        sum += x * i + y;
    }
    return sum;
}
double func2(double x, double y)
{
    double sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        sum += x - i * y;
    }
    return sum;
}

//non-vectorized function
double chi2NV(double x, double y)
{
    double sum = 0;
    for (int i = 0; i <= 10; ++i)
    {
        sum += abs(func1(x, y) * func2(x, y));
    }
    return sum;
}

//vectorez functin
vector<vector<double>> chi2Vector(double x, double y)
{
    vector<vector<double>> results;
    size_t rows = 30;
    size_t columns = 2;
    const double epsilon = -0.3;
    for (int i = 0; i <= 5; ++i)
    {
        results.push_back(vector<double>());
        for (int j = 0; j < 1; ++j)
        {
            results[i].push_back(epsilon * i - 0.1);
            results[i].push_back(chi2NV(x, y * (epsilon * i - 0.1)));
        }
        //results[1].push_back(chi2NV(x, y));
    }
    /* for (int i = 0; i <= 5; ++i)
        arr.push_back(i * epsilon - 0.1);
    for (vector<double>::iterator it = arr.begin(); it != arr.end(); ++it)
    {
        results.push_back(chi2NV(x, y * (*it)));
    } */
    return results;
}

int main()
{
    double x, y;
    x = 1;
    y = 2;
    const double epsilon = -0.3;
    vector<double> arr;
    for (int i = 0; i <= 5; ++i)
        arr.push_back(i * epsilon - 0.1);
    cout << "NON-VECTORIZED FORM:" << endl;
    for (vector<double>::iterator it = arr.begin(); it != arr.end(); ++it)
    {
        cout << *it << " " << chi2NV(x, y * (*it)) << endl;
    }
    vector<vector<double>> vec;
    vec = chi2Vector(x, y);
    cout << "VECTORIZED FORM:" << endl;
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
            cout << vec[i][j] << " ";
        cout << endl;
    }
    return 0;
}