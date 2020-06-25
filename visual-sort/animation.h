#pragma once

#include "config.h"
#include "geometry.h"
#include "sort.h"


void updateCubePos(int i)
{
    moving[i] = true;
    move[i].process = 0.0f;
    move[i].start = curCubePosX[i];
    move[i].end = cubePosX[i];
    move[i].dist = cubePosX[i] - curCubePosX[i];
}

void updateCubeHeight(int i)
{
    growing[i] = true;
    grow[i].process = 0.0f;
    grow[i].start = curCubeHeight[i];
    grow[i].end = cubeHeight[i];
    grow[i].dist = cubeHeight[i] - curCubeHeight[i];
}


void unsort()
{
    for(int i = 0; i < cubeNum; ++i)
    {
        cubeColour[i] = colourInit;
        cubePosX[i] = cubeX(cubeNum, i);
        updateCubePos(i);
    }
    visualSortState = STATE_IDLE;
}


void visualSortInit()
{
    visualSortState = STATE_INIT;
    // for(int i = 0; i < maxCubeNum; ++i)
    // {
    //     cubeIndex[i] = i;
    // }
    for(int ci = 0; ci < cubeNum; ++ci)
    {
        cubeHeight[ci] = -0.1f;
        cubeColour[ci] = colourDeleting;
        cubePosX[ci] = 0.0f;
        cubeActivated[ci] = false;
        updateCubeHeight(ci);
        updateCubePos(ci);
    }
}

void swapCube(int i1, int i2)
{
    swap(cubePosX[i1], cubePosX[i2]);
    updateCubePos(i1);
    updateCubePos(i2);
}

void parseCommand()
{
    if (command[cmdp].x == COMMAND_SWAP)
    {
        swapCube(command[cmdp].y, command[cmdp].z);
        printf("Swap %d %d\n", command[cmdp].y, command[cmdp].z);
    }
}
