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

using namespace std;
int main(){
    PIM *tested = new PIM();
    tested->Initialize(1, 4);

    tested->Inputs->WriteCell(0, 0, -1, 0.5, 1, -1, false);
    tested->Inputs->WriteCell(0, 1, -1, 0.25, 1, -1, false);
    tested->Inputs->WriteCell(0, 2, -1, 0.4, 1, -1, false);
    tested->Inputs->WriteCell(0, 3, -1, 0.6, 1, -1, false);
    float **pxInputs = new float*[4];
    for(int i = 0; i < 4; i++){
        pxInputs[i] = new float[tested->samples];
    }
    for(int i = 0; i < tested->samples; i++){
        pxInputs[0][i] = 0.6;
        pxInputs[1][i] = -0.3;
        pxInputs[2][i] = 0.45;
        pxInputs[3][i] = -0.2;
        
    }
    
    tested->convolutionFunction(pxInputs);
    cout << averageDutyCycle(dutyCycle(tested->convolutionOutput[0], tested->Toc, tested->timeStep, tested->samples)) << endl;
    
    return 0;
}