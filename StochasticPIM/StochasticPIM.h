#ifndef STOCHASTICPIM_H_
#define STOCHASTICPIM_H_
#include <iostream>
#include <vector>
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
#include "ASC_adder.h"
#include "Activation.h"

class PIM{
    public:
        void Initialize(std::vector<std::vector<float>> weights);
        void convolutionFunction(std::vector<float> pxInput);
        void activationFunction();
        void poolingFunction();
        void doEverything(std::vector<float> pxInput);
        Cell ***cell;
        float ***asdmGen;
        float *px;
        float pxAmp, schOutLevel, schThrPerc, schThr, foc, Toc, K, timeStep, Fs, timeEnd, maxConductance, minConductance;
        int samples, COL, ROW;
        float** convolutionOutput;
        float** activationOutput;
        float* poolingOutput;


};

#endif

