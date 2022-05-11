#include <stdio.h>
#include <vector>
#include "ASDM.h"
#include <iostream>
#include "SchmittTrigger.h"
using namespace std;


//vals[0] = vOut, vals[1] = vInt, vals[2] = vError

float** ASDM(float* x, float schThrPerc, float K, float feedB, float schOutLevel, float timeStep, int samples){
    float schmittTriggerThreshold = schThrPerc*schOutLevel;
    float* vError = new float[samples];
    float* vFeedback = new float[samples];
    float* vInt = new float[samples];
    float* vOut = new float[samples];
    vFeedback[0] = feedB*schOutLevel;
    vInt[0] = 0;
    vError[0] = 0;
    vFeedback[0] = feedB*schOutLevel;
    vOut[0] = 0;
    for(int i = 1; i < samples; i++){
        vError[i] = (x[i]-vFeedback[i-1]);
        vInt[i] = (vInt[i-1]+(vError[i]*timeStep/K));
        vOut[i] = (schmittTrigger(vInt[i], vOut[i-1], schThrPerc, schOutLevel));
        vFeedback[i] = feedB*vOut[i];
    }
    float** vOuts = new float*[3];
    vOuts[0]= vOut;
    vOuts[1] = vInt;
    vOuts[2] = vError;

    return vOuts;
}
