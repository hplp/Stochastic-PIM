#include <iostream>
#include <algorithm>
#include "Parser.h"
using namespace std;
#include <vector>

int main(){
    vector<vector<float>> weights = readWeights("InputWeights.csv");
    vector<float> px = readInputs("InputASDM.csv");
    cout << weights[0][0] << endl;

   // cout << weights[7][5] << endl;
  // float** px = readInputs("InputASDM.txt", 8, 100);
//    cout << px[0][0] << endl;
//    cout << px[1][0] << endl;
//    cout << px[2][0] << endl;
//    cout << px[3][0] << endl;
//    cout << px[4][0] << endl;
//    cout << px[5][0] << endl;
//    cout << px[6][0] << endl;
//    cout << px[7][0] << endl;
    return 0;
}