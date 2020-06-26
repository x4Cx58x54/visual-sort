#pragma once

#include "config.h"
#include "utils.h"
#include "animation.h"
//#include <algorithm>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        if (cubeNum < maxCubeNum)
        {
            // visualSortState = ADD;
            cubeActivated[cubeNum] = true;
            ++cubeNum;
            cubeHeight[cubeNum - 1] = randomint(1, maxCubeHeight);
            updateCubeHeight(cubeNum - 1);
            curCubeHeight[cubeNum - 1] = 0.0f;
            curCubePosX[cubeNum - 1] = cubeX(cubeNum, cubeNum-1) + 0.1;
            for(int ci = 0; ci < cubeNum; ++ci)
            {
                cubePosX[ci] = cubeX(cubeNum, ci);
                updateCubePos(ci);
            }
            cubeColour[cubeNum - 1] = colourInit;
            curCubeColour[cubeNum - 1] = colourInit;
        }
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        if (cubeNum > 0)
        {
            // visualSortState = DEL;
            cubeActivated[cubeNum - 1] = false;
            cubeHeight[cubeNum - 1] = 0.0f;
            cubeColour[cubeNum - 1] = colourDeleting;
            curCubeColour[cubeNum - 1] = colourDeleting;
            updateCubeHeight(cubeNum - 1);
            for(int ci = 0; ci < cubeNum; ++ci)
            {
                cubePosX[ci] = cubeX(cubeNum - 1, ci);
                updateCubePos(ci);
            }
        }
    }
    else if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
    {
        visualSortInit();
        glfwSetWindowTitle(window,"Visualsort");
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
    {
        unsort();
        glfwSetWindowTitle(window,"Visualsort");
    }
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        presort();
        bubbleSort(0, cubeNum - 1);
        glfwSetWindowTitle(window,"Bubble Sort - Visualsort");
        postsort();
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        presort();
        insertionSort(0, cubeNum - 1);
        glfwSetWindowTitle(window,"Insertion Sort - Visualsort");
        postsort();
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        presort();
        selectionSort(0, cubeNum - 1);
        glfwSetWindowTitle(window,"Selection Sort - Visualsort");
        postsort();
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        presort();
        quickSort(0, cubeNum - 1);
        glfwSetWindowTitle(window,"Quick Sort - Visualsort");
        postsort();
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && visualSortState == STATE_IDLE)
    {
        presort();
        unsortedPos.clear();
        for(int i = 0; i < cubeNum; ++i)
        {
            unsortedPos.push_back(cubePosX[i]);
        }
        bogoSort(0, cubeNum - 1);
        glfwSetWindowTitle(window,"Bogosort - Visualsort");
        postsort();
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}
