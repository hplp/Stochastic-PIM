#include "StochasticPIM.h"
#include <iostream>
#include <vector>
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

void PIM::Initialize(std::vector<std::vector<float>> weights){
    this->ROW = weights.size();
    this->COL = weights[0].size();    
    this->pxAmp = 0.51;
    this->schOutLevel = 1;
    this->schThrPerc = 0.5;
    this->schThr = this->schThrPerc*this->schOutLevel;
    this->foc = 25e3;
    this->Toc = 1/this->foc;
    this->K = this->Toc*this->schOutLevel*this->pxAmp/(2*this->schThr);
    this->timeStep = 10e-9;
    this->Fs = 1/this->timeStep;
    this->timeEnd = 1e-3;
    this->samples = this->timeEnd/this->timeStep;
    this->maxConductance = 5e-6;
    this->minConductance = 100e-9;
    this->activationOutput = new float*[this->COL];
    this->convolutionOutput = new float*[this->COL];
    this->cell = new Cell**[this->COL];
    for(int i = 0; i < this->COL; i++){
        this->cell[i] = new Cell*[this->ROW];
    }
    

    for(int i = 0; i < this->COL; i++){
        for(int j = 0; j < this->ROW; j++){
            this->cell[i][j] = new Cell(this->minConductance, this->maxConductance);
            this->cell[i][j]->Write(weights[j][i], 1, -1);
        }

    }
    for(int i = 0; i < this->COL; i++){
        this->convolutionOutput[i] = new float[samples];
    }
}

void PIM::convolutionFunction(std::vector<float> pxInput){
    float D_MIN = 0.0098;
    float D_MAX = .9902;
    float* px = new float[this->samples];
    this->asdmGen = new float** [this->ROW];

    for(int i = 0; i < this->ROW; i++){
        for(int j = 0; j < samples; j++){
            px[j] = pxInput[i];
        }
        this->asdmGen[i] = new float*[3];
        this->asdmGen[i] = ASDM(px, this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples);
        }
    

    // for(int i = 0; i < this->ROW; i++){
    //     std::cout << (averageDutyCycle(dutyCycle(this->asdmGen[i][0], this->Toc, this->timeStep, this->samples))-D_MIN)/(D_MAX-D_MIN) << std::endl;
    // }


    float** currents = new float*[this->COL];
    for(int i = 0; i < this->COL; i++){
        currents[i] = new float[this->ROW];
    }
    
    for(int i = 0; i < this->COL; i++){
        for(int j = 0; j < this->ROW; j++){
            currents[i][j] = this->cell[i][j]->Read();
            
        }
    }

    float*** streamCurrents = new float**[this->COL];
    for(int i = 0; i < this->COL; i++){
        streamCurrents[i] = new float*[this->ROW];
        for(int j = 0; j < this->ROW; j++){
            streamCurrents[i][j] = new float[this->samples];
        }
    }

    float** I_total = new float*[this->COL];
    for(int i = 0; i < this->COL; i++){
        I_total[i] = new float[this->samples];
    }

    float I_min = minConductance*this->ROW;
    float I_max = this->ROW*maxConductance;

    float** C_total = new float*[this->COL];
    for(int i = 0; i < this->COL; i++){
        C_total[i] = new float[samples];
    }
    
    for(int i = 0; i < this->COL; i++){
        for(int j = 0; j < this->ROW; j++){
            for(int k = 0; k < this->samples; k++){
                streamCurrents[i][j][k] = currents[i][j]*max(this->asdmGen[j][0][k], 0);
            }
        }
    }

    float currentTotal = 0;
    for(int i = 0; i < this->COL; i++){
        for(int j = 0; j < this->samples; j++){
            currentTotal = 0;
            for(int k = 0; k < this->ROW; k++){
                currentTotal += streamCurrents[i][k][j];
            }
            I_total[i][j] = currentTotal;
            C_total[i][j] = (I_total[i][j]-(I_min+I_max)/2)/std::abs(I_max-(I_min+I_max)/2);
        }
    }

    for(int i = 0; i < this->COL; i++){
        this->convolutionOutput[i] = ASDM(C_total[i], this->schThrPerc, this->K, 2*this->pxAmp, this->schOutLevel, this->timeStep, this->samples)[0];
    }
   // std::cout << currents[0][0] << std::endl;


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
    float D_MIN = 0.0098;
    float D_MAX = .9902;
}

void PIM::doEverything(std::vector<float> pxInput){
    this->convolutionFunction(pxInput);
    this->activationFunction();
    this->poolingFunction();
}