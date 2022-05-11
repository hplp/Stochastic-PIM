#include <iostream>
#include "Cell.h"


void Cell::Write(float weight, float maxWeight, float minWeight){
    this->conductance = (weight - minWeight)/(maxWeight-minWeight) * (this->maxConductance-this->minConductance);
    this->weight = weight;
}

float Cell::Read(){
    return this->conductance;
}