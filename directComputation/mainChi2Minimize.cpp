#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream output("outputData.dat");

const int dim1 = 21, dim2 = 17, dim3 = 14, dim4 = 10;
double tsd1[21] = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
double tsd2[17] = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
double tsd3[14] = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
double tsd4[10] = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};
double spin1Exp[dim1] = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
double spin2Exp[dim2] = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
double spin3Exp[dim3] = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
double spin4Exp[dim4] = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};

double inertiaMoment(double izero, double beta, double gamma, int k)
{
    double rez, pi = 3.141592654;
    rez = (double)izero / (1.0 + sqrt(5.0 / (16.0 * pi)) * beta) * (1.0 - sqrt(5.0 / (4.0 * pi)) * beta * cos(gamma + 2.0 / 3.0 * pi * k));
    return rez;
}

double inertiaFactor1(double izero, double beta, double gamma)
{
    return (double)1.0 / (2.0 * inertiaMoment(izero, beta, gamma, 1));
}

double inertiaFactor2(double izero, double beta, double gamma)
{
    return (double)1.0 / (2.0 * inertiaMoment(izero, beta, gamma, 2));
}

double inertiaFactor3(double izero, double beta, double gamma)
{
    return (double)1.0 / (2.0 * inertiaMoment(izero, beta, gamma, 3));
}

double term1(double spin, double oddSpin, double izero, double beta, double gamma)
{
    double rez;
    double a1, a2, a3;
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (2.0 * spin - 1.0) * (a3 - a1) + 2.0 * oddSpin * a1;
    return rez;
}

double term2(double spin, double oddSpin, double izero, double beta, double gamma)
{
    double rez;
    double a1, a2, a3;
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (2.0 * spin - 1.0) * (a2 - a1) + 2.0 * oddSpin * a1;
    return rez;
}

double term3(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez;
    double a1, a2, a3;
    double sing, cosg, rad3;
    rad3 = sqrt(3.0);
    sing = sin(gamma);
    cosg = cos(gamma);
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (2.0 * oddSpin - 1.0) * (a3 - a1) + 2.0 * spin * a1 + particlePotential * (2.0 * oddSpin - 1.0) / (oddSpin * (oddSpin + 1.0)) * rad3 * (rad3 * cosg + sing);
    return rez;
}

double term4(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez;
    double a1, a2, a3;
    double sing, cosg, rad3;
    rad3 = sqrt(3.0);
    sing = sin(gamma);
    cosg = cos(gamma);
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (2.0 * oddSpin - 1.0) * (a2 - a1) + 2.0 * spin * a1 + particlePotential * (2.0 * oddSpin - 1.0) / (oddSpin * (oddSpin + 1.0)) * 2.0 * rad3 * sing;
    return rez;
}

double bigTerm1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez = 0;
    double a1, a2, a3;
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = term1(spin, oddSpin, izero, beta, gamma) * term2(spin, oddSpin, izero, beta, gamma) + 8.0 * a2 * a3 * spin * oddSpin + term3(spin, oddSpin, izero, beta, gamma, particlePotential) * term4(spin, oddSpin, izero, beta, gamma, particlePotential);
    return -1.0 * rez;
}

double bigTerm2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez = 0;
    double a1, a2, a3;
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (term1(spin, oddSpin, izero, beta, gamma) * term3(spin, oddSpin, izero, beta, gamma, particlePotential) - 4.0 * spin * oddSpin * a3 * a3) * (term2(spin, oddSpin, izero, beta, gamma) * term4(spin, oddSpin, izero, beta, gamma, particlePotential) - 4.0 * spin * oddSpin * a2 * a2);
    return rez;
}

//wobbling frequencies

double Omega1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez;
    rez = sqrt(0.5 * (-bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential) - pow(pow(bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential), 2.0) - 4.0 * bigTerm2(spin, oddSpin, izero, beta, gamma, particlePotential), 0.5)));
    return rez;
}

double Omega2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez;
    rez = sqrt(0.5 * (-bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential) + pow(pow(bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential), 2) - 4.0 * bigTerm2(spin, oddSpin, izero, beta, gamma, particlePotential), 0.5)));
    return rez;
}

double minHamiltonian(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, pi = 3.141592654, sing;
    sing = sin(gamma + pi / 6.0);
    double a1, a2, a3;
    a1 = inertiaFactor1(izero, beta, gamma);
    a2 = inertiaFactor2(izero, beta, gamma);
    a3 = inertiaFactor3(izero, beta, gamma);
    rez = (a2 + a3) * (spin + oddSpin) / 2.0 + a1 * pow(spin - oddSpin, 2) - particlePotential * (2.0 * oddSpin - 1.0) / (oddSpin + 1.0) * sing;
}

//energy functions

double energyBand1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    //excitation energy of the first TSD1 band I=13/2
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));

    //ACTUAL ENERGY OF THE BAND LEVEL I
    rez = minHamiltonian(spin, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spin, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin, oddSpin, izero, beta, gamma, particlePotential));

    return rez - eZero;
}

double energyBand2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    //excitation energy of the first TSD1 band I=13/2  (keep constant)
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));

    //ACTUAL ENERGY OF THE BAND LEVEL I
    rez = minHamiltonian(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (3.0 * Omega1(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential));

    return rez - eZero;
}

double energyBand3(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    //excitation energy of the first TSD1 band I=13/2 (keep constant)
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));

    //ACTUAL ENERGY OF THE BAND LEVEL I
    rez = minHamiltonian(spin - 2.0, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (5.0 * Omega1(spin - 2.0, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin - 2.0, oddSpin, izero, beta, gamma, particlePotential));

    return rez - eZero;
}

double energyBand4(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero = 6.5, secondSpin = 4.5;
    double singleParticleEnergy = -0.334;
    //excitation energy of the first TSD1 band I=13/2  (keep constant)
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));
    oddSpin = secondSpin;

    //ACTUAL ENERGY OF THE BAND LEVEL I
    rez = minHamiltonian(spin - 3.0, secondSpin, izero, beta, gamma, particlePotential) + 0.5 * (7.0 * Omega1(spin - 3.0, secondSpin, izero, beta, gamma, particlePotential) + Omega2(spin - 3.0, secondSpin, izero, beta, gamma, particlePotential));

    return rez - eZero + singleParticleEnergy;
}

double chiSuqaredMinimize(double izero, double particlePotential)
{
    double pi = 3.141592654;
    double rez;
    int count = 0;
    double oddSpin = 6.5, secondSpin = 4.5;
    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;
    double beta, gamma;
    beta = 0.38;
    gamma = 17.0 * pi / 180.0;

    //experimental data

    double temp;
    bool ok = 1;
    while (ok)
    {
        for (int i = 0; i < dim1 && ok; ++i)
        {
            temp = pow((double)(tsd1[i] - energyBand1(spin1Exp[i], oddSpin, izero, beta, gamma, particlePotential)), 2.0) / tsd1[i];
            if (isnan(temp))
            {
                ok = false;
                break;
            }
            if (!isnan(temp))
            {
                sum1 += temp;
                count++;
            }
        }
        for (int i = 0; i < dim2 && ok; ++i)
        {
            temp = pow((double)(tsd2[i] - energyBand2(spin2Exp[i], oddSpin, izero, beta, gamma, particlePotential)), 2.0) / tsd2[i];
            if (isnan(temp))
            {
                ok = false;
                break;
            }
            if (!isnan(temp))
            {
                sum2 += temp;
                count++;
            }
        }
        for (int i = 0; i < dim3 && ok; ++i)
        {
            temp = pow((double)(tsd3[i] - energyBand3(spin3Exp[i], oddSpin, izero, beta, gamma, particlePotential)), 2.0) / tsd3[i];
            if (isnan(temp))
            {
                ok = false;
                break;
            }
            if (!isnan(temp))
            {
                sum3 += temp;
                count++;
            }
        }
        for (int i = 0; i < dim4 && ok; ++i)
        {
            temp = pow((double)(tsd4[i] - energyBand4(spin4Exp[i], oddSpin, izero, beta, gamma, particlePotential)), 2.0) / tsd4[i];
            if (isnan(temp))
            {
                ok = false;
                break;
            }
            if (!isnan(temp))
            {
                sum4 += temp;
                count++;
            }
        }
        if (ok)
            ok = false;
    }
    rez = (double)sqrt((sum1 + sum2 + sum3 + sum4) / (dim1 + dim2 + dim3 + dim4));
    if (sum1 && sum2 && sum3 && sum4 && count == (dim1 + dim2 + dim3 + dim4))
        return rez;
    return 0;
}

//array of results
typedef struct datapoints
{
    double izero, particlePotential, chi2;
} dp;

//constructor for datda
dp adddata(double izero, double particlePotential, double chi2)
{
    dp points = {izero, particlePotential, chi2};
    return points;
}
/* 
void computeMinimum(vector<dp> a, dp *result)
{
    *result = *min_element(a.begin(), a.end());
    cout << "Minimum is result " << result << endl;
}
 */

static bool customCompare(const dp &x, const dp &y)
{
    return x.chi2 < y.chi2;
}

ofstream tsd1out("/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/DevWorkspace/GO_codes/go/src/plotMaker/tsd1.dat");
ofstream tsd2out("/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/DevWorkspace/GO_codes/go/src/plotMaker/tsd2.dat");
ofstream tsd3out("/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/DevWorkspace/GO_codes/go/src/plotMaker/tsd3.dat");
ofstream tsd4out("/mnt/c/Users/rober/OneDrive/Desktop/PIPELINE/DevWorkspace/GO_codes/go/src/plotMaker/tsd4.dat");

void makeEnergyData(double izero, double particlePotential)
{
    vector<double> energy1, energy2, energy3, energy4;
    const double pi = 3.141592654;
    double beta = 0.38, gamma = 17 * pi / 180.0, oddSpin = 6.5, secondSpin = 4.5;
    for (int i = 0; i < dim1; ++i)
    {
        energy1.push_back(energyBand1(spin1Exp[i], oddSpin, izero, beta, gamma, particlePotential));
        tsd1out << spin1Exp[i] << "," << tsd1[i] << "," << energy1.at(i) << endl;
    }
    for (int i = 0; i < dim2; ++i)
    {
        energy2.push_back(energyBand2(spin2Exp[i], oddSpin, izero, beta, gamma, particlePotential));
        tsd2out << spin2Exp[i] << "," << tsd2[i] << "," << energy2.at(i) << endl;
    }
    for (int i = 0; i < dim3; ++i)
    {
        energy3.push_back(energyBand3(spin3Exp[i], oddSpin, izero, beta, gamma, particlePotential));
        tsd3out << spin3Exp[i] << "," << tsd3[i] << "," << energy3.at(i) << endl;
    }
    for (int i = 0; i < dim4; ++i)
    {
        energy4.push_back(energyBand4(spin4Exp[i], secondSpin, izero, beta, gamma, particlePotential));
        tsd4out << spin4Exp[i] << "," << tsd4[i] << "," << energy4.at(i) << endl;
    }
}

int main()
{
    vector<dp> chi2Array;
    dp result;
    double minValue = 123456789.0, pi = 3.141592654;
    double w1, w2, w3;
    for (double i = 45; i <= 55; i += 0.1)
    {
        for (double v = 0.01; v <= 10.0; v += 1)
        {
            if (chiSuqaredMinimize((double)i, v))
                chi2Array.push_back(adddata((double)i, v, chiSuqaredMinimize((double)i, v)));
        }
    }
    //sort(chi2Array.begin(), chi2Array.end(), [](vector<dp> &a1, vector<dp> &a2) { return });
    //sort(chi2Array.begin(), chi2Array.end(), customCompare);
    for (int i = 0; i < chi2Array.size(); ++i)
        output
            << chi2Array.at(i).izero << " " << chi2Array.at(i).particlePotential << " " << chi2Array.at(i).chi2 << "\n";
    //SHOW MINIMUM using lambda function
    auto min_chi2 = std::minmax_element(chi2Array.begin(), chi2Array.end(),
                                        [](dp const &el1, dp const &el2) { return el1.chi2 < el2.chi2; });
    cout << min_chi2.first->izero << " " << min_chi2.first->particlePotential << " " << min_chi2.first->chi2 << endl;
    makeEnergyData(min_chi2.first->izero, min_chi2.first->particlePotential);
    //computeMinimum(chi2Array, &result);
    //cout << "Program finished... ----> " << chi2Array.at(0).chi2 << endl;
    cout << "Program finished... ----> ";
    cout << endl;
    return 0;
}