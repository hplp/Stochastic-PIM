#ifndef DUTYCYCLE_H_
#define DUTYCYCLE_H_
#include <vector>

std::vector<float> dutyCycle(float* signal, float T, float timeStep, int numSamples);
float averageDutyCycle(std::vector<float> dutyCycles);
#endif