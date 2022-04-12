#include "ASDM.h"
#include "SchmittTrigger.h"
#include "DutyCycle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
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
    float *time = new float[samples];
    float *px1 = new float[samples];
    for(int i = 0; i < samples; i++){
        time[i] = i*timeStep;
        px1[i] = 1;
    }

    float **asdm = new float*[3];
    asdm = ASDM(px1, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    std::vector<float> dutyCycles = dutyCycle(asdm[0], Toc, timeStep, samples);
    cout << endl;
    for(int i = 0; i < dutyCycles.size(); i++){
        cout << dutyCycles[i] << ',';
    }

    
    return 0;
}