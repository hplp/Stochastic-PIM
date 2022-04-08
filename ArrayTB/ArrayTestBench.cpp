#include <iostream>
#include <vector>
#include "Array.h"
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
using namespace std;
float max(float a, float b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}
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
    float *px2 = new float[samples];
    float *px3 = new float[samples];
    float *px4 = new float[samples];
    float *px5 = new float[samples];
    for(int i = 0; i < samples; i++){
        time[i] = i*timeStep;
        px1[i] = 0.5;
        px2[i] = -0.4;
        px3[i] = 0.65;
        px4[i] = 0.8;
    }

    float **asdm1 = new float*[3];
    float **asdm2 = new float*[3];
    float **asdm3 = new float*[3];
    float **asdm4 = new float*[3];
    float **asdm5 = new float*[3];
    asdm1 = ASDM(px1, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    asdm2 = ASDM(px2, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    asdm3 = ASDM(px3, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    asdm4 = ASDM(px4, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    Array *ASDMTest = new Array(1, 5, 100);
    ASDMTest->Initialization<IdealDevice>();

    ASDMTest->WriteCell(0, 0, -2, 0.8, 1, -1, false);
    ASDMTest->WriteCell(0, 1, -1, 0.8, 1, -1, false);
    ASDMTest->WriteCell(0, 2, -1, 0.35, 1, -1, false);
    ASDMTest->WriteCell(0, 3, -1, 0.15, 1, -1, false);
    
    float *currents = new float[4];
    for(int i = 0; i < 4; i++){
        currents[i] = ASDMTest->ReadCell(0, i, "LSB");
    }
    float **streamCurrents = new float*[4];
    for(int i = 0; i < 4; i++){
        streamCurrents[i] = new float[samples];
    }
    float *I_total = new float[samples];
    double maxConductance = 5e-6; // from ideal cell
    double minConductance = 100e-9; //from ideal cell
    float I_min = minConductance*0.25;
    float I_max = 4*maxConductance*0.25;
    float *C_total = new float[samples];
    for(int i = 0; i < samples; i++){
        streamCurrents[0][i] = currents[0]*max(asdm1[0][i], 0);
        streamCurrents[1][i] = currents[1]*max(asdm2[0][i], 0);
        streamCurrents[2][i] = currents[2]*max(asdm3[0][i], 0);
        streamCurrents[3][i] = currents[3]*max(asdm4[0][i], 0);
        I_total[i] = streamCurrents[0][i] + streamCurrents[1][i] + streamCurrents[2][i] + streamCurrents[3][i];
        C_total[i] = (I_total[i]-(I_min+I_max)/2)/abs(I_max-(I_min+I_max)/2);
    }
    float **ASDM_C = new float*[3];
    ASDM_C = ASDM(C_total, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples);
    
    std::vector<float> dutyCycles = dutyCycle(ASDM_C[0], Toc, timeStep, samples);
    for(int i = 0; i < dutyCycles.size(); i++){
        cout << dutyCycles[i] << endl;
    }
    cout << averageDutyCycle(dutyCycles) << endl;
   // float C_tot = (I_total-(I_min+I_max)/2)/abs(I_max-(I_min+I_max)/2);
    //cout << C_tot << endl;
    
    return 0;
}