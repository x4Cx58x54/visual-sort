#pragma once

#include "utils.h"


// Screen
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;



const int maxCubeNum = 50;
const int maxCubeHeight = 100;

float speed = 3.0f; // Max 100/{move, grow, paint}Rate.


float cubePosX[maxCubeNum] = {
    0.0f, 0.3f,
};
float curCubePosX[maxCubeNum] = {
    0.0f, 0.3f,
};

bool moving[maxCubeNum] = { false };
float moveRate = 0.03 * speed;
struct {
    float start, end, dist, process;
} move[maxCubeNum];


float cubeHeight[maxCubeNum] = {};
float curCubeHeight[maxCubeNum] = {};
bool growing[maxCubeNum] = { false };
float growRate = moveRate;
struct {
    float start, end, dist, process;
} grow[maxCubeNum];


glm::vec3 cubeColour[maxCubeNum];
glm::vec3 curCubeColour[maxCubeNum];
bool painting[maxCubeNum] = { false };
float paintRate = 0.09 * speed;
struct {
    float startR, endR, distR;
    float startG, endG, distG;
    float startB, endB, distB;
    float process;
} paint[maxCubeNum];


int cubeDelaying = 0;

int cubeDelayTime = int(24 / speed);



int cubeNum = 0;

float unitX = 0.1;
float unitY = 0.02;
float unitZ = 0.1;

glm::vec3 lightPos(0.8f, 1.1f, 1.2f);


// float omegaX = 0.131f;
// float omegaY = 0.079f;
// float omegaZ = 0.057f;
// float thetaX = 0.0f, thetaY = 0.0f, thetaZ = 0.0f;

// Colours

glm::vec3 colourInit(0.2f, 0.2f, 0.44f);
glm::vec3 colourDeleting(0.32f, 0.32f, 0.50f);
glm::vec3 colourBlink(0.95f, 0.95f, 0.99f);
glm::vec3 colourCritical(0.6f, 0.0f, 0.9f);
glm::vec3 colourLookAt(0.1f, 0.5f, 0.2f);
glm::vec3 colourSorted(0.8f, 0.54f, 0.0f);

enum {
    COLOUR_INIT,
    COLOUR_DELETING,
    COLOUR_BLINK,
    COLOUR_CRITICAL,
    COLOUR_LOOKAT,
    COLOUR_SORTED,
};

glm::vec3 colours[] = {
    colourInit,
    colourDeleting,
    colourBlink,
    colourCritical,
    colourLookAt,
    colourSorted,
};



// int cubeIndex[maxCubeNum];

bool cubeActivated[maxCubeNum] = { false };

enum {
    STATE_IDLE,
    STATE_INIT,
    STATE_SORT,
    STATE_SORT_INTER,
    STATE_ADD,
    STATE_DEL,
};
int visualSortState = STATE_IDLE;

enum {
    COMMAND_DELAY,
    COMMAND_PAINT,
    COMMAND_PAINT_MULTIPLE,
    COMMAND_SWAP,
    COMMAND_SWAP_MULTIPLE,
};

std::vector<glm::ivec3> command;
int cmdp = 0;
// COMMAND_DELAY, frameNum, 0
// COMMAND_PAINT, i, colour
// COMMAND_PAINT_MULTIPLE, paintMultipleCube ptr, colour
// COMMAND_SWAP_MULTIPLE, swapMultipleCube ptr, 0

std::vector< std::vector<int> > paintMultipleCube;

std::vector< std::vector<int> > swapMultipleCube;

std::vector<float> unsortedPos;
