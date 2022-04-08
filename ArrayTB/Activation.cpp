#include <iostream>
#include "Activation.h"
#include "DutyCycle.h"
#include <vector>
using namespace std;
float* activation(float* signal, float* ASDM_0, float T, float timeStep, int numSamples){
    if(averageDutyCycle(dutyCycle(signal, T, timeStep, numSamples)) < 0.5){
        return ASDM_0;
    }
    else{
        return signal;
    }
}