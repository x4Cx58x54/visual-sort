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

void updateCubeColour(int i)
{
    painting[i] = true;
    paint[i].process = 0.0f;
    paint[i].startR = curCubeColour[i].r;
    paint[i].endR = cubeColour[i].r;
    paint[i].distR = cubeColour[i].r - curCubeColour[i].r;
    paint[i].startG = curCubeColour[i].g;
    paint[i].endG = cubeColour[i].g;
    paint[i].distG = cubeColour[i].g - curCubeColour[i].g;
    paint[i].startB = curCubeColour[i].b;
    paint[i].endB = cubeColour[i].b;
    paint[i].distB = cubeColour[i].b - curCubeColour[i].b;
}


void unsort()
{
    for(int i = 0; i < cubeNum; ++i)
    {
        cubeColour[i] = colourInit;
        curCubeColour[i] = colourInit;
        cubePosX[i] = cubeX(cubeNum, i);
        updateCubePos(i);
    }
    visualSortState = STATE_IDLE;
}


void postsort()
{
    std::vector<int> allCubes;
    for(int i = 0; i < cubeNum; ++i)
        allCubes.push_back(i);
    paintMultipleCube.push_back(allCubes);
    command.push_back({COMMAND_PAINT_MULTIPLE, paintMultipleCube.size()-1, COLOUR_SORTED});
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
        curCubeColour[ci] = colourDeleting;
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
    else if (command[cmdp].x == COMMAND_PAINT)
    {
        cubeColour[command[cmdp].y] = colours[command[cmdp].z];
        updateCubeColour(command[cmdp].y);
        printf("Paint %d %d\n", command[cmdp].y, command[cmdp].z);
    }
    else if (command[cmdp].x == COMMAND_PAINT_MULTIPLE)
    {
        for(int i = 0; i < paintMultipleCube[command[cmdp].y].size(); ++i)
        {
            int paintCube = paintMultipleCube[command[cmdp].y][i];
            cubeColour[paintCube] = colours[command[cmdp].z];
            updateCubeColour(paintCube);
            printf("Paint %d %d\n", paintCube, command[cmdp].z);
        }
    }
    else if (command[cmdp].x == COMMAND_DELAY)
    {
        cubeDelaying = command[cmdp].y;
    }
}
