#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

float** readWeights(const char* fileName, int cols, int rows){
    float **weights = new float*[cols];
    for(int i = 0; i < cols; i++){
        weights[i] = new float[rows];
    }

    std::ifstream file(fileName);
    for(int i = 0; i < rows; i++){
        std::string line;
        getline(file, line);
        std::stringstream iss(line);
        for(int j = 0; j < cols; j++){
            std::string val;
            getline(iss, val, ',');
            std::stringstream converter(val);
            converter >> weights[j][i];
           // std::cout << "Col: "<< j << " "<< "Rows: " << i << " " << weights[i][j] << std::endl;
        }
    }
    return weights;

}

float** readInputs(const char* fileName, int rows, int samples){
    float *px = new float[rows];
    std::ifstream file(fileName);
    for(int i = 0; i < rows; i++){
        std::string line;
        getline(file, line);
        std::stringstream iss(line);
        std::string val;
        getline(iss, val, ',');
        std::stringstream converter(val);
        converter >> px[i];
    }

    float **pxOut = new float*[rows];
    for(int i = 0; i < rows; i++){
        pxOut[i] = new float[samples];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < samples; j++){
            pxOut[i][j] = px[i];
        }
    }

    return pxOut;

}