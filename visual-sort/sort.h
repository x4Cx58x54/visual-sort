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
    paintMultipleCube.clear();
}


void bubbleSort()
{
    for (int i = 0; i < cubeNum - 1; i++)
    {
        for (int j = 0; j < cubeNum - 1 - i; j++)
        {
            int operator1 = sortTable[j].i, operator2 = sortTable[j+1].i;
            paintMultipleCube.push_back({operator1, operator2});
            command.push_back({COMMAND_PAINT_MULTIPLE, paintMultipleCube.size()-1, COLOUR_LOOKAT});
            if (sortTable[j].h > sortTable[j + 1].h)
            {
                command.push_back({COMMAND_SWAP, sortTable[j].i, sortTable[j+1].i});
                swap(sortTable[j], sortTable[j+1]);
            }
            else
            {
                command.push_back({COMMAND_DELAY, cubeDelayTime, 0});
            }
            paintMultipleCube.push_back({operator1, operator2});
            command.push_back({COMMAND_PAINT_MULTIPLE, paintMultipleCube.size()-1, COLOUR_INIT});
        }
        command.push_back({COMMAND_PAINT, sortTable[cubeNum - i - 1].i, COLOUR_SORTED});
    }
    printf("Bubble Sort.\n");
}
