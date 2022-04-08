#include <iostream>
#include "ASDM.h"
#include "Activation.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
#include <vector>
using namespace std;

int main(){
    float pxAmp = 1;
    float schOutLevel = 1;
    float schThrPerc = 0.5;
    float schThr = schThrPerc*schOutLevel;
    float foc = 25e3;
    float Toc = 1/foc;
    float K = Toc*schOutLevel*pxAmp/(2*schThr);
    float timeStep = 1e-9;
    float Fs = 1/timeStep;
    float timeEnd = 2e-3;
    int samples = timeEnd/timeStep;

    float fi1 = 1e3;
    float *px1 = new float[samples];
    for(int i = 0; i < samples; i++){
        px1[i] = 0;
    }

    float **asdm_0 = new float*[3];
    asdm_0 = ASDM(px1, schThrPerc, K, 2*pxAmp , schOutLevel, timeStep, samples);
    float *input = new float[samples];
    float **ASDM_OUT = new float*[3];
    for(int i = 0; i <= 20; i++){
        for(int j = 0 ; j < samples; j++){
            input[j] = (float)(i-10)/(float)(10); 
        }
        ASDM_OUT = ASDM(input, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
        cout << "Input p = " << (float)(i-10)/(float)(10) << ": " << averageDutyCycle(dutyCycle(activation(ASDM_OUT[0], asdm_0[0], Toc, timeStep, samples), Toc, timeStep, samples)) << endl;
    }

}