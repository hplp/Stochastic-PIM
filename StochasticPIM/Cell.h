#ifndef CELL_H_
#define CELL_H_

class Cell{
    public:
        float minConductance;
        float maxConductance;
        float conductance;
        float weight;
        Cell(float minConductance, float maxConductance){
            this->minConductance = minConductance;
            this->maxConductance = maxConductance;
            this->conductance = minConductance;
        }
        void Write(float weight, float maxWeight, float minWeight);
        float Read();

};

#endif