#include <stdio.h>
#include <vector>
#include "ASDM.h"
#include "ASC_adder.h"
#include "SchmittTrigger.h"
using namespace std;

float** ASC_adder(float** x1, int n, float schThrPerc, float K, float feedB, float schOutLevel, float timeStep, int samples){
    float schmittTriggerThreshold = schThrPerc * schOutLevel;
    float* vError = new float[samples];
    float* vFeedback = new float[samples];
    float* vInt = new float[samples];
    float* vOut = new float[samples];
    
    vFeedback[0] = feedB*schOutLevel;
    float initCond = 0;
    vInt[0] = initCond;
    vOut[0] = initCond;
    vError[0] = initCond;
    float lin = 0;
    for(int i = 1; i < samples; i++){
        lin = 0;
        for(int j = 0; j < n; j++){
            lin = lin + x1[j][i];
        }
    vError[i] = lin-vFeedback[i-1];
    vInt[i] = vInt[i-1]+(vError[i]*timeStep/K);
    vOut[i] = schmittTrigger(vInt[i], vOut[i-1], schThrPerc, schOutLevel);
    vFeedback[i] = feedB*vOut[i];
    }
    float** vOuts = new float*[3];
    vOuts[0] = vOut;
    vOuts[1] = vInt;
    vOuts[2] = vError;
    return vOuts;
}