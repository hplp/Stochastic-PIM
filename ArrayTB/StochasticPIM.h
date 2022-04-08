#ifndef STOCHASTICPIM_H_
#define STOCHASTICPIM_H_
#include <iostream>
#include <vector>
#include "Array.h"
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
#include "ASC_ADDER.h"
#include "Activation.h"

class PIM{
    public:
        void Initialize(int x, int y);
        void convolutionFunction(float **pxInput);
        void activationFunction();
        void poolingFunction();
        void doEverything(float **pxInput);
        Array *Inputs;
        float ***asdmGen;
        float *px;
        float pxAmp, schOutLevel, schThrPerc, schThr, foc, Toc, K, timeStep, Fs, timeEnd, maxConductance, minConductance;
        int samples, COL, ROW;
        float** convolutionOutput;
        float** activationOutput;
        float* poolingOutput;


};

#endif

