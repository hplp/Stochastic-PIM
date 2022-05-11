#include "Parser.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<float>> readWeights(const char* fileName){
    std::vector<std::vector<float>> weights;
    std::ifstream file(fileName);
    std::string line;
    while(std::getline(file, line)){
        weights.push_back(std::vector<float>());
        std::stringstream iss(line);
        std::string val;
        while(std::getline(iss, val, ',')){
            weights[weights.size()-1].push_back(std::stof(val));
        }

    }
  

    return weights;

}

std::vector<float> readInputs(const char* fileName){
    std::vector<float> px;
    std::ifstream file(fileName);
    std::string line = "";
    while(std::getline(file, line)){
        px.push_back(std::stof(line));
    }
    return px;

}