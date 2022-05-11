#include "Cell.h"
#include <iostream>

int main(){
    Cell ***ArrTest;
    ArrTest = new Cell**[5];
    for(int i = 0; i < 5; i++){
        ArrTest[i] = new Cell*[5];
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            ArrTest[i][j] = new Cell(100e-9, 5e-7);
        }
    }
    Cell **Arr1d = new Cell*[5];
    for(int i = 0; i < 5; i++){
        Arr1d[i] = new Cell(100e-9, 5e-7);
    }
    Cell *test = new Cell(100e-9, 5e-7);
    return 0;
}