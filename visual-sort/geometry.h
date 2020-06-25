#pragma once

#include <math.h>
#include <stdlib.h>
#include <time.h>

int randomint(int lower_bound, int upper_bound)
{
    //srand((unsigned)time(NULL));
    return rand() % (upper_bound - lower_bound + 1) + lower_bound;
}

float cubicPos(float des, float t)
{
    return (3.0f*des*t*t) - (2.0f*des*t*t);
    // return (3.0f*des*t*t)/(endt*endt) - (2.0f*des*t*t)/(endt*endt*endt);
}

float cubeX(int cubeNum, int cubeIndex, float gap = 0.3)
{
    if (cubeNum <= 1) return 0.0f;
    float border = gap * (cubeNum - 1) / 2.0f;
    return -border + gap * cubeIndex;
}
