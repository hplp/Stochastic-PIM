#include <iostream>
#include "Parser.h"
using namespace std;

int main(){
    float** weights = readWeights("InputWeights.csv", 10, 8);
   // cout << weights[7][5] << endl;
   float** px = readInputs("InputASDM.csv", 8, 100);
   cout << px[0][0] << endl;
   cout << px[1][0] << endl;
   cout << px[2][0] << endl;
   cout << px[3][0] << endl;
   cout << px[4][0] << endl;
   cout << px[5][0] << endl;
   cout << px[6][0] << endl;
   cout << px[7][0] << endl;
    return 0;
}