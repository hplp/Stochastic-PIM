#include "StochasticPIM.h"
#include <iostream>
#include <vector>
#include "Array.h"
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
#include "ASC_adder.h"
#include "Activation.h"

float max(float a, float b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

void PIM::Initialize(int x, int y){
    this->COL = x;
    this->ROW = y;
    this->Inputs = new Array(x, y, 100);
    this->Inputs->Initialization<IdealDevice>();
    this->pxAmp = 1;
    this->schOutLevel = 1;
    this->schThrPerc = 0.5;
    this->schThr = this->schThrPerc*this->schOutLevel;
    this->foc = 25e3;
    this->Toc = 1/this->foc;
    this->K = this->Toc*this->schOutLevel*this->pxAmp/(2*this->schThr);
    this->timeStep = 1e-9;
    this->Fs = 1/this->timeStep;
    this->timeEnd = 2e-3;
    this->samples = this->timeEnd/this->timeStep;
    this->maxConductance = 5e-6;
    this->minConductance = 100e-9;
    this->activationOutput = new float*[this->COL];
    this->convolutionOutput = new float*[this->COL];
}

void PIM::convolutionFunction(float** pxInput){
    this->asdmGen = new float** [this->ROW];
    for(int i = 0; i < this->ROW; i++){
        this->asdmGen[i] = new float*[3];
        this->asdmGen[i] = ASDM(pxInput[i], this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples);
    } 
    //TODO: PARSER AND WRITE THE ARRAY CELLS
    float** currents = new float*[this->COL];
    for(int i = 0; i < this->COL; i++){
        currents[i] = new float[this->ROW];
    }
    float I_min = this->minConductance*0.25;
    float I_max = this->maxConductance*this->ROW;
    float** I_total = new float*[this->COL];
    float** C_total = new float*[this->COL];
    for(int i = 0; i < this->COL; i++){
        I_total[i] = new float[this->samples];
        C_total[i] = new float[this->samples];
        for(int k = 0; k < this->samples; k++){
            I_total[i][k] = 0;
        }
        for(int j = 0; j < this->ROW; j++){
            currents[i][j] = this->Inputs->ReadCell(i, j, "LSB");
        }
    }
    float** streamCurrents = new float*[this->ROW];
    for(int i = 0; i < this->ROW; i++){
        streamCurrents[i] = new float[this->samples];
    }

    for(int i = 0; i < this->COL; i++){
        for(int j = 0; j < this->ROW; j++){
            for(int k = 0; k < samples; k++){
                streamCurrents[j][k] = currents[i][j]*max(this->asdmGen[j][0][k], 0.0);
                I_total[i][k] += streamCurrents[j][k];
            }
        }

    }
    float **ConvolutionASDM = new float*[3];

    for(int i = 0; i < this->COL; i++){
        this->convolutionOutput[i] = new float[this->samples];
        for(int j = 0; j < this->samples; j++){
            C_total[i][j] = (I_total[i][j]-(I_min+I_max)/2)/abs(I_max-(I_min+I_max)/2);
        }
        this->convolutionOutput[i] = ASDM(C_total[i], this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples)[0];
    }
    

    
}

void PIM::activationFunction(){
    float* zeroes = new float[this->samples];
    for(int i = 0; i < this->COL; i++){
        this->activationOutput[i] = new float[this->samples];
        this->activationOutput[i] = activation(this->convolutionOutput[i], ASDM(zeroes, this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples)[0], this->Toc, this->timeStep, this->samples);      
    }
}

void PIM::poolingFunction(){
    this->poolingOutput = new float[samples];
    float** ADDER = new float*[3];
    ADDER = ASC_adder(this->activationOutput, this->COL, this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples);
    this->poolingOutput = ADDER[0];
}

void PIM::doEverything(float** pxInput){
    this->convolutionFunction(pxInput);
    this->activationFunction();
    this->poolingFunction();
}