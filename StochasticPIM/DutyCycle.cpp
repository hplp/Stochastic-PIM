#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
int findRisingEdge(float* signal, int index, int numSamples){

    int tracker = index;
    while(signal[tracker+1] <= signal[tracker]){
        if(tracker >= numSamples-1){
            return -1;
        }
        tracker++;
    }
    return tracker;
}

int findNextFallingEdge(float* signal, int index, int numSamples){

    int tracker = index;
    while(signal[tracker+1] >= signal[tracker]){
        if(tracker >= numSamples-1){
            return -1;
        }
        tracker++;
    }
    return tracker;
}

vector<float> dutyCycle(float* signal, float T, float timeStep, int numSamples){
    int risingEdge = findRisingEdge(signal, 0, numSamples);
    int fallingEdge = findNextFallingEdge(signal, risingEdge, numSamples);
    int nextRisingEdge = findRisingEdge(signal, fallingEdge, numSamples);
    vector<float> dutyCycles;
    dutyCycles.push_back((fallingEdge-risingEdge)/((float)nextRisingEdge-(float)risingEdge));
    
    while(1){
        risingEdge = nextRisingEdge;
        fallingEdge = findNextFallingEdge(signal, risingEdge, numSamples);
        nextRisingEdge = findRisingEdge(signal, fallingEdge, numSamples);
        if(risingEdge == -1 || fallingEdge == -1 || nextRisingEdge == -1){
            break;
        }
        dutyCycles.push_back((fallingEdge-risingEdge)/((float)nextRisingEdge-(float)risingEdge));
        
    }
    //cout << samplesPerPeriod << endl;

    return dutyCycles;
}

vector<float> findFrequencies(float* signal, float T, float timeStep, int numSamples){
    int risingEdge = findRisingEdge(signal, 0, numSamples);
    int fallingEdge = findNextFallingEdge(signal, risingEdge, numSamples);
    int nextRisingEdge = findRisingEdge(signal, fallingEdge, numSamples);
    vector<float> frequencies;
    frequencies.push_back((fallingEdge-risingEdge)/((float)nextRisingEdge-(float)risingEdge));
    
    while(1){
        risingEdge = nextRisingEdge;
        nextRisingEdge = findRisingEdge(signal, fallingEdge, numSamples);
        if(risingEdge == -1 || nextRisingEdge == -1){
            break;
        }
        frequencies.push_back(1/(((float)risingEdge-(float)nextRisingEdge)*timeStep));
        
    }
    //cout << samplesPerPeriod << endl;

    return frequencies;
}

float averageDutyCycle(vector<float> dutyCycles){
    float total = 0;
    for(int i = 0; i < dutyCycles.size(); i++){
        total += dutyCycles[i];
    }
    total = total/dutyCycles.size();
    return total;
}

float averageFrequency(vector<float> frequencies){
    float total = 0;
    for(int i = 0; i < frequencies.size(); i++){
        total += frequencies[i];
    }
    total = total/frequencies.size();
    return total;
}