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

int main(int argc, char** argv){
    if(argc == 3){   
        std::vector<std::vector<float>> weights = readWeights(argv[1]);
        std::vector<float> px = readInputs(argv[2]);
        if(weights.size() == px.size()){
            PIM *tested = new PIM();
            tested->Initialize(weights);
            tested->convolutionFunction(px);
            for(int i = 0; i < tested->COL; i++){
                std::cout << "Average Duty Cycle of Column " << i << ": " << averageDutyCycle(dutyCycle(tested->convolutionOutput[i], tested->Toc, tested->timeStep, tested->samples)) << std::endl;
            }
        }
        else{
            std::cout << "ERROR: Dimensions of files not matching" << std::endl;
        }
    }
    else{
        std::cout << "ERROR: Two file names are needed" << std::endl;
    }
        return 0;
}