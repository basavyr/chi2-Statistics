#include "minimize.h"

void showStatusMinimize()
{
    cout << "minimizing function...";
    cout << endl;
}

void computeMinimum(vector<double> a, double *result)
{
    //showStatusMinimize();
    *result = *min_element(a.begin(), a.end());
}