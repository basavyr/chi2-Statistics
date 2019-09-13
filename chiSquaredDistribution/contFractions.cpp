#include <iostream>
#include <cmath>
#include <cstdio>
#define epsilon 1e-7
#define shift 1e-30
using namespace std;

void showAlgorithmStatus(const char *appname)
{
    cout << "This Algorithm computes " << appname << endl;
}

double computeFractions()
{
    double f, b;
    double C, D, Delta;
    b = 0;
    if (!b)
        f = shift;
    C = f;
    D = 0;
    bool ok = true;
    int j = 1;
    double a;
    while (ok)
    {
        D = D * a + b;
        if (!D)
            D = shift;
        C = a / C + b;
        if (!C)
            C = shift;
        D = 1 / D;
        Delta = C * D;
        f = f * Delta;
        if (Delta - 1 < epsilon)
            ok = 0;
    }
    return f;
}

int main()
{
    const char *appName = "Continued Fractions";
    showAlgorithmStatus(appName);
    cout << epsilon + 1.0 << endl;
    cout << shift + 1.0 << endl;
    cout << computeFractions() << endl;
}