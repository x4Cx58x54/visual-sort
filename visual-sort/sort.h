#pragma once

#include "config.h"

template<typename T>
void swap(T& a, T& b)
{
    T swaptemp = a;
    a = b;
    b = swaptemp;
}


struct SortTable{
    int i;
    float h;
} sortTable[maxCubeNum];

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
    swapMultipleCube.clear();
}


void bubbleSort(int l, int r)
{
    printf("Bubble Sort.\n");
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < r - i; ++j)
        {
            int operator1 = sortTable[j].i, operator2 = sortTable[j + 1].i;
            paintMultipleCube.push_back({operator1, operator2});
            command.push_back({COMMAND_PAINT_MULTIPLE, paintMultipleCube.size()-1, COLOUR_LOOKAT});
            if (sortTable[j].h > sortTable[j + 1].h)
            {
                command.push_back({COMMAND_SWAP, sortTable[j].i, sortTable[j + 1].i});
                swap(sortTable[j], sortTable[j + 1]);
            }
            else
            {
                command.push_back({COMMAND_DELAY, cubeDelayTime, 0});
            }
            paintMultipleCube.push_back({operator1, operator2});
            command.push_back({COMMAND_PAINT_MULTIPLE, paintMultipleCube.size()-1, COLOUR_INIT});
        }
        command.push_back({COMMAND_PAINT, sortTable[r - i].i, COLOUR_SORTED});
    }
}


void insertionSort(int l, int r)
{
    printf("Insertion Sort.\n");
    for(int i = l; i <= r; ++i)
    {
        printf("Here\n");
        int insert = sortTable[i].i;
        for(int j = i - 1; j >= l; --j)
        {
            command.push_back({COMMAND_PAINT, insert, COLOUR_LOOKAT});
            if (sortTable[j].h > sortTable[j + 1].h)
            {
                command.push_back({COMMAND_SWAP, sortTable[j].i, sortTable[j + 1].i});
                swap(sortTable[j], sortTable[j + 1]);
                insert = sortTable[j].i;
            }
            else
            {
                break;
            }
        }
        command.push_back({COMMAND_PAINT, insert, COLOUR_SORTED});
    }
}


void selectionSort(int l, int r)
{
    printf("Selection Sort.\n");
    for (int i = l, j; i <= r; ++i)
    {
        int min = i;
        command.push_back({COMMAND_PAINT, sortTable[i].i, COLOUR_CRITICAL});
        for (j = i + 1; j <= r; ++j)
        {
            command.push_back({COMMAND_PAINT, sortTable[j].i, COLOUR_LOOKAT});
            command.push_back({COMMAND_DELAY, cubeDelayTime, 0});
            if (sortTable[j].h < sortTable[min].h)
            {
                command.push_back({COMMAND_PAINT, sortTable[j].i, COLOUR_CRITICAL});
                command.push_back({COMMAND_PAINT, sortTable[min].i, COLOUR_INIT});
                min = j;
            }
            else
            {
                command.push_back({COMMAND_PAINT, sortTable[j].i, COLOUR_INIT});
            }
        }
        command.push_back({COMMAND_SWAP, sortTable[min].i, sortTable[i].i});
        command.push_back({COMMAND_PAINT, sortTable[min].i, COLOUR_SORTED});
        swap(sortTable[min], sortTable[i]);
    }
}


int partition(int l, int r)
{
    int pivot = sortTable[l].h;
    command.push_back({COMMAND_PAINT, sortTable[l].i, COLOUR_CRITICAL});
    while(l < r)
    {
        while(l < r && sortTable[r].h >= pivot)
            r--;
        while(l < r && sortTable[l].h <= pivot)
            l++;
        command.push_back({COMMAND_SWAP, sortTable[l].i, sortTable[r].i});
        swap(sortTable[l], sortTable[r]);
    }
    return l;
}

void quickSort(int l, int r)
{
    if (l >= r) return;
    int p = partition(l, r);
    quickSort(l, p);
    quickSort(p+1, r);
    command.push_back({COMMAND_PAINT, sortTable[p].i, COLOUR_SORTED});
}


void bogoSort(int l, int r)
{
    printf("Bogosort.\n");
    std::vector<int> sortIndex;
    srand((unsigned)time(NULL));
    for(int i = l; i <= r; ++i)
    {
        sortIndex.push_back(i);
    }
    while (1)
    {
        std::random_shuffle(sortIndex.begin(), sortIndex.end());
        swapMultipleCube.push_back(sortIndex);
        command.push_back({COMMAND_SWAP_MULTIPLE, swapMultipleCube.size() - 1, 0});
        command.push_back({COMMAND_DELAY, cubeDelayTime/3, 0});
        bool checked = true;
        for(int i = l; i < r; ++i)
        {
            if (sortTable[sortIndex[i]].h > sortTable[sortIndex[i+1]].h)
            {
                checked = false;
                break;
            }
        }
        if (checked)
        {
            for(int i = 0; i < cubeNum; ++i)
            {
                printf("%d ", sortIndex[i]);
            }
            putchar('\n');
            break;
        }
    }
}
