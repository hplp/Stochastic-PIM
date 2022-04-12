#include <iostream>
#include <vector>
#include "Array.h"
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"

#define COLUMN 2
#define ROW 6
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
    float ** px = new float*[ROW];
    for(int i = 0; i < ROW; i++){
        px[i] = new float[samples];
    }
    
    
    return 0;
}