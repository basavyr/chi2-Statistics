#!/bin/sh
g++ ./src/readData.cpp ./src/variance.cpp ./src/chiSquared.cpp ./src/generateExpData.cpp ./src/genData.cpp ./src/genTheoreticalData.cpp ./src/energyCalculation.cpp ./src/minimize.cpp ./src/main.cpp -o asrc.out
./asrc.out
