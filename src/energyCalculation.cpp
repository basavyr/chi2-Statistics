#include "energyCalculation.h"

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
    rez = sqrt(0.5 * (-1.0 * bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential) + pow(pow(bigTerm1(spin, oddSpin, izero, beta, gamma, particlePotential), 2) - 4.0 * bigTerm2(spin, oddSpin, izero, beta, gamma, particlePotential), 0.5)));
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

//energies

double energyBand1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));
    rez = minHamiltonian(spin, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spin, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin, oddSpin, izero, beta, gamma, particlePotential));
    return rez - eZero;
}

double energyBand2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));
    rez = minHamiltonian(spin, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spin, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin, oddSpin, izero, beta, gamma, particlePotential));
    return rez - eZero;
}

double energyBand3(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero;
    spinZero = 6.5;
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));
    rez = minHamiltonian(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (3.0 * Omega1(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin - 1.0, oddSpin, izero, beta, gamma, particlePotential));
    return rez - eZero;
}

double energyBand4(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential)
{
    double rez, eZero, spinZero = 6.5, secondSpin = 4.5;
    eZero = minHamiltonian(spinZero, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spinZero, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spinZero, oddSpin, izero, beta, gamma, particlePotential));
    oddSpin = secondSpin;
    rez = minHamiltonian(spin, oddSpin, izero, beta, gamma, particlePotential) + 0.5 * (Omega1(spin, oddSpin, izero, beta, gamma, particlePotential) + Omega2(spin, oddSpin, izero, beta, gamma, particlePotential));
    return rez - eZero;
}

void showStatusEnergyCalculation()
{
    cout << "computing energy...";
    cout << endl;
}
double computeEnergy(int band, double spin, double param1, double param2)
{
    switch (band)
    {
    case 1:
    {
        double pi = 3.141592654;
        double gm = 17.0 * pi / 180.0;
        double beta = 0.38;
        return energyBand1(spin, 6.5, param1, beta, gm, param2);
        break;
    }
    case 2:
    {
        double pi = 3.141592654;
        double gm = 17.0 * pi / 180.0;
        double beta = 0.38;
        return energyBand2(spin, 6.5, param1, beta, gm, param2);
        break;
    }
    case 3:
    {
        double pi = 3.141592654;
        double gm = 17.0 * pi / 180.0;
        double beta = 0.38;
        return energyBand3(spin, 6.5, param1, beta, gm, param2);
        break;
    }
    case 4:
    {
        double pi = 3.141592654;
        double gm = 17.0 * pi / 180.0;
        double beta = 0.38;
        return energyBand4(spin, 4.5, param1, beta, gm, param2);
        break;
    }
    default:
        break;
    }
}
