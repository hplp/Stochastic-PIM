#ifndef DUTYCYCLE_H_
#define DUTYCYCLE_H_
#include <vector>

std::vector<float> dutyCycle(float* signal, float T, float timeStep, int numSamples);
std::vector<float> findFrequencies(float* signal, float T, float timeStep, int numSamples);
float averageFrequency(std::vector<float> frequencies);
float averageDutyCycle(std::vector<float> dutyCycles);
#endif