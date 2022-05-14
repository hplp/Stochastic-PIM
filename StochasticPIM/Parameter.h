#ifndef PARAMETER_H_
#define PARAMETER_H_
struct InputParameter{
    //ASDM and ASC adder Inputs
    float pxAmp = 0.51;
    float schOutLevel = 1;
    float schThrPerc= 0.5;
    float foc = 25e3;
    float timeStep = 10e-9;
    float timeEnd = 1e-3;
    
    //Cell specific input
    float maxConductance = 5e-6;
    float minConductance = 100e-9;

    //pooling function
    int averagingWindowSize = 4;

};

#endif 