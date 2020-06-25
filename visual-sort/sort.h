#pragma once

#include "config.h"

template<typename T>
void swap(T& a, T& b)
{
    T swaptemp = a;
    a = b;
    b = swaptemp;
}


struct { int i; float h; } sortTable[maxCubeNum];

void presort()
{
    visualSortState = STATE_SORT_INTER;
    for(int i = 0; i < cubeNum; ++i)
    {
        sortTable[i].i = i;
        sortTable[i].h = cubeHeight[i];
    }
    command.clear();
    cmdp = 0;
}

void bubbleSort()
{
    presort();
    for (int i = 0; i < cubeNum - 1; i++)
    {
        for (int j = 0; j < cubeNum - 1 - i; j++)
        {
            if (sortTable[j].h > sortTable[j + 1].h)
            {
                command.push_back({COMMAND_SWAP, sortTable[j].i, sortTable[j+1].i});
                swap(sortTable[j], sortTable[j+1]);
            }
        }
    }
    printf("Bubble Sort.\n");
}
