#include "schmittTrigger.h"
float schmittTrigger(float xi, float outim1, float schmittTriggerTresholdPerc, float schmittTriggerOutLevel){
    float sig = xi+outim1*schmittTriggerTresholdPerc;
    int signum;
    if(sig < 0){
        signum = -1;
    }
    else if(sig == 0){
        signum = 0;
    }
    else{
        signum = 1;
    }

    return schmittTriggerOutLevel*signum;
}