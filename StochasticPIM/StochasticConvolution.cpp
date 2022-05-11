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

int main(){
    PIM *tested = new PIM();
    std::vector<std::vector<float>> weights = readWeights("InputWeights.csv");
    tested->Initialize(weights);
    std::vector<float> px = readInputs("InputASDM.csv");

    tested->convolutionFunction(px);
    for(int i = 0; i < tested->COL; i++){
        std::cout << "Average Duty Cycle of Column " << i << ": " << averageDutyCycle(dutyCycle(tested->convolutionOutput[i], tested->Toc, tested->timeStep, tested->samples)) << std::endl;
    }
    return 0;
}