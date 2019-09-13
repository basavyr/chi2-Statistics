#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <cstring>

#define MAXITERATIONS 100
#define epsilon 3.0e-7
#define TINY 1.0e-30

using namespace std;

void showAppStatus()
{
    cout << "Running ChiSquaredDistribution algoritm C++...";
    cout << endl;
}

void panicError(const char *errorDM)
{
    cout << errorDM << endl;
}

// GAMMA FUNCTION USING COEFFICIENT APPROXIMATION (NUMERICAL RECIPES C)
// loggamma calculates the log of Gamma(x)
double logGamma(double xx)
{
    const double coef[6] = {76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5};
    double x, y, temp, ser;
    y = x = xx;
    temp = x + 5.5;
    temp = temp - (x + 0.5) * log(temp);
    ser = 1.000000000190015;
    for (int j = 0; j < 5; ++j)
    {
        ser += coef[j] / ++y;
    }
    return -temp + log(2.5066282746310005 * ser / x);
}

double numericalGamma(double z)
{
    return exp(logGamma(z));
}

double getCriticalValue(double exp[100], double th[100], int dim)
{
    double criticalValue = 0;
    double xSquared;
    for (int i = 0; i < dim; ++i)
    {
        xSquared = pow(exp[i] - th[i], 2.0);
        criticalValue += (xSquared / exp[i]);
    }
    return criticalValue;
}

void gammaSeriesRepresentation(double *gsr, double a, double x, double *lng)
{
    const char *err;
    const char *err2;
    err = "argument x is less than 0 in the Series Representation function";
    err2 = "a is too large, MAXITERATION reached.";
    double sum, del, ap;

    *lng = log(tgamma(a));
    if (x <= 0.0)
    {
        if (x < 0.0)
            panicError(err);
        *gsr = 0.0;
        return;
    }
    else
    {
        ap = a;
        del = sum = 1.0 / a;
        for (int n = 1; n <= MAXITERATIONS; ++n)
        {
            ++ap;
            del *= x / ap;
            sum + del;
            if (fabs(del) < fabs(sum) * epsilon)
            {
                *gsr = sum * exp(-x + a * log(x) - (*lng));
                return;
            }
        }
        panicError(err2);
        return;
    }
}

//computes the continued fraction Q(a,x) with fraction method
void gammaContinuedFractions(double *gcf, double a, double x, double *lng)
{
    const char *err;
    err = "a is too large, MAXITERATION reached.";
    double an, b, c, d, delta, h;

    int i;
    *lng = log(tgamma(a));
    b = x + 1.0 - a;
    c = 1.0 / TINY;
    d = 1.0 / b;
    h = d;
    for (i = 1; i <= MAXITERATIONS; ++i)
    {
        an = -i * (i - a);
        b += 2.0;
        d = an * d + b;
        if (fabs(d) < TINY)
            d = TINY;
        c = b + an / c;
        if (fabs(c) < TINY)
            c = TINY;
        d = 1.0 / d;
        delta = d * c;
        h *= delta;
        if (fabs(delta - 1.0) < epsilon)
            break;
    }
    if (i > MAXITERATIONS)
        panicError(err);
    *gcf = exp(-x + a * log(x) - (*lng)) * h;
}

//computes the P(a,x) incomplete gamma function (Numerical Recipes C)
double gammaP(double a, double x)
{
    const char *err;
    err = "Invalid arguments in the Gamma P(a,x) function";
    //void gammaContinuedFractions(double *gammaFraction, double a, double x, double *lnGamma);
    //void gammaSeriesRepresentation(double *gammaSeries, double a, double x, double *lnGamma);
    double gammaSeries, gammaFractions, lnGamma;

    if (x < 0.0 || a <= 0.0)
        panicError(err);
    //use series representation
    if (x < (a + 1.0))
    {
        gammaSeriesRepresentation(&gammaSeries, a, x, &lnGamma);
        return gammaSeries;
    }
    //use continued fractions
    else
    {
        gammaContinuedFractions(&gammaFractions, a, x, &lnGamma);
        return 1 - gammaFractions;
    }
}

//computes the Q(a,x) incomplete gamma function (Numerical Recipes C)
double gammaQ(double a, double x)
{
    const char *err;
    err = "Invalid arguments in the Gamma Q(a,x) function";
    //void gammaContinuedFractions(double *gammaFraction, double a, double x, double *lnGamma);
    //void gammaSeriesRepresentation(double *gammaSeries, double a, double x, double *lnGamma);
    double gammaSeries, gammaFractions, lnGamma;
    if (x < 0.0 || a <= 0.0)
        panicError(err);
    //use series representation
    if (x < (a + 1.0))
    {
        gammaSeriesRepresentation(&gammaSeries, a, x, &lnGamma);
        return 1 - gammaSeries;
    }
    //use continued fractions
    else
    {
        gammaContinuedFractions(&gammaFractions, a, x, &lnGamma);
        return gammaFractions;
    }
}

double incompleteGF(double S, double Z)
{
    if (Z < 0.0)
    {
        return 0.0;
    }
    double Sc = (1.0 / S);
    Sc *= pow(Z, S);
    Sc *= exp(-Z);

    double Sum = 1.0;
    double Nom = 1.0;
    double Denom = 1.0;

    for (int I = 0; I < 200; I++)
    {
        Nom *= Z;
        S++;
        Denom *= S;
        Sum += (Nom / Denom);
    }
    return Sum * Sc;
}

double chiSquared(int DOF, double criticalValue)
{
    if (criticalValue < 0 || DOF < 1)
        return 0;
    double K = (double(DOF)) * 0.5;
    double X = criticalValue * 0.5;
    if (DOF == 2)
        return exp(-1.0 * X);
    double pValue = incompleteGF(K, X);
    if (isnan(pValue) || isinf(pValue) || pValue <= 1e-8)
        return 1e-14;
    pValue = pValue / tgamma(K);
    return 1 - pValue;
}

ifstream fin("sampleData.dat");

int main()
{
    showAppStatus();
    std::srand(std::time(nullptr));
    std::srand(std::time(0));
    int dim = 99;
    double arrExp[100], arrTh[100];
    double x;
    double y, z;
    //generate sample data
    int i = 0;
    while (i < dim)
    {
        fin >> x >> y >> z;
        arrExp[i] = y;
        arrTh[i] = z;
        // cout << i << " " << arrExp[i] << " " << arrTh[i] << endl;
        i++;
    }
    /* for (int i = 0; i < dim; ++i)
    {
        arrExp[i] = i + ((double)rand() / (RAND_MAX));
        arrTh[i] = i + 0.0;
    }
     */
    cout << getCriticalValue(arrExp, arrTh, dim) << endl;
    cout << chiSquared(dim, getCriticalValue(arrExp, arrTh, dim)) << endl;
    //normal random generator
    /*
    double lower_bound = 0;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    double v = unif(re);
    cout << v << " " << x << endl; */
    cout << tgamma(4.0) << " " << numericalGamma(4.0) << endl;
    cout << log(tgamma(4.0)) << " " << logGamma(4.0) << endl;
    cout << gammaP(3, 2) << " " << gammaQ(3, 2) << " " << incompleteGF(3, 2) << endl;
    return 0;
}