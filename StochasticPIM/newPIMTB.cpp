#include "StochasticPIM.h"
#include <iostream>
#include "Parser.h"
#include <vector>
#include <cmath>
#include "Cell.h"
#include "ASDM.h"
#include "DutyCycle.h"
#include "SchmittTrigger.h"
#include "ASC_adder.h"
#include "Activation.h"
using namespace std;

#define INPUT_COLS 10
#define INPUT_ROWS 8

int main(){
    PIM *tested = new PIM();
    vector<vector<float>> weights = readWeights("InputWeights.csv");
    tested->Initialize(weights);
    vector<float> px = readInputs("InputASDM.csv");

    tested->convolutionFunction(px);
    // tested->activationFunction();
    // tested->poolingFunction();
    

    // cout << "-- CONVOLUTION -- " << endl; 
    // cout << "Duty Cycle for Column1: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[0], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 2: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[1], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 3: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[2], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 4: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[3], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 5: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[4], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 6: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[5], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 7: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[6], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 8: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[7], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 9: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[8], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 10: " << averageDutyCycle(dutyCycle(tested->convolutionOutput[9], tested->Toc, tested->timeStep, tested->samples)) << endl;

    // tested->activationFunction();
    // cout << "-- ACTIVATION -- " << endl;
    // cout << "Duty Cycle for Column 1: " << averageDutyCycle(dutyCycle(tested->activationOutput[0], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 2: " << averageDutyCycle(dutyCycle(tested->activationOutput[1], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 3: " << averageDutyCycle(dutyCycle(tested->activationOutput[2], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 4: " << averageDutyCycle(dutyCycle(tested->activationOutput[3], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 5: " << averageDutyCycle(dutyCycle(tested->activationOutput[4], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 6: " << averageDutyCycle(dutyCycle(tested->activationOutput[5], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 7: " << averageDutyCycle(dutyCycle(tested->activationOutput[6], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 8: " << averageDutyCycle(dutyCycle(tested->activationOutput[7], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 9: " << averageDutyCycle(dutyCycle(tested->activationOutput[8], tested->Toc, tested->timeStep, tested->samples)) << endl;
    // cout << "Duty Cycle for Column 10: " << averageDutyCycle(dutyCycle(tested->activationOutput[9], tested->Toc, tested->timeStep, tested->samples)) << endl;

    // tested->poolingFunction();
    //  << "-- POOLING -- " << endl;
    // cout << "Duty Cycle for total: " << averageDutyCycle(dutyCycle(tested->poolingOutput, tested->Toc, tested->timeStep, tested->samples)) << endl;
    return 0;
}