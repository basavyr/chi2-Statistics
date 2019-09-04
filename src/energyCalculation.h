//energyCalculation.h
#ifndef ENERGY_CALCUALTION_H
#define ENERGY_CALCULATION_H

#include <iostream>
#include <cmath>

using namespace std;

void showStatusEnergyCalculation();
double computeEnergy(int band, double spin, double param1, double param2);

//functions for the ENERGY CALCULATIONS
double inertiaMoment(double izero, double beta, double gamma, int k);
double inertiaFactor1(double izero, double beta, double gamma);
double inertiaFactor2(double izero, double beta, double gamma);
double inertiaFactor3(double izero, double beta, double gamma);
double term1(double spin, double oddSpin, double izero, double beta, double gamma);
double term2(double spin, double oddSpin, double izero, double beta, double gamma);
double term3(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double term4(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double bigTerm1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double bigTerm2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double Omega1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double Omega2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double minHamiltonian(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);

//energies
double energyBand1(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double energyBand2(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double energyBand3(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);
double energyBand4(double spin, double oddSpin, double izero, double beta, double gamma, double particlePotential);

#endif /*ENERGY_CALCULATION_H*/