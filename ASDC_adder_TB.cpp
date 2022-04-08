#include <iostream>
#include <vector>
#include "ASC_adder.h"
#include "ASDM.h"
#include "SchmittTrigger.h"
#include "DutyCycle.h"

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
    float* px1 = new float[samples];
    float* px2 = new float[samples];
    float* px3 = new float[samples];
    float* px4 = new float[samples];

    for(int i = 0; i < samples; i++){
        px1[i] = 0.7;
        px2[i] = 0.11;
        px3[i] = 0.3;
        px4[i] = 0.7;
    }

    float **ASDM1 = new float*[3];
    float **ASDM2 = new float*[3];
    float **ASDM3 = new float*[3];
    float **ASDM4 = new float*[3];

    ASDM1 = ASDM(px1, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    ASDM2 = ASDM(px2, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    ASDM3 = ASDM(px3, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    ASDM4 = ASDM(px4, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);

    float** adderStream = new float*[4];
    adderStream[0] = ASDM1[0];
    adderStream[1] = ASDM2[0];
    adderStream[2] = ASDM3[0];
    adderStream[3] = ASDM4[0];

    float** ASC_ADDER = new float*[3];
    ASC_ADDER = ASC_adder(adderStream, 4, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    std::vector<float> dutyCycles = dutyCycle(ASC_ADDER[0], Toc, timeStep, samples);

    std::cout << averageDutyCycle(dutyCycles) << std::endl;
  
}