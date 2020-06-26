#include "config.h"
#include "utils.h"
#include "geometry.h"
#include "animation.h"
#include "kbcontrol.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


GLFWwindow* window;
void CreateWindow(GLFWwindow*& window);

void renderCubes();

int main()
{
    CreateWindow(window);

    Shader lightingShader("phong.vert", "phong.frag");

    float vertices[] = {
        -unitX, -0.0f, -unitZ,  0.0f,  0.0f, -1.0f,
         unitX, -0.0f, -unitZ,  0.0f,  0.0f, -1.0f,
         unitX, unitY, -unitZ,  0.0f,  0.0f, -1.0f,
         unitX, unitY, -unitZ,  0.0f,  0.0f, -1.0f,
        -unitX, unitY, -unitZ,  0.0f,  0.0f, -1.0f,
        -unitX, -0.0f, -unitZ,  0.0f,  0.0f, -1.0f,

        -unitX, -0.0f,  unitZ,  0.0f,  0.0f,  1.0f,
         unitX, -0.0f,  unitZ,  0.0f,  0.0f,  1.0f,
         unitX, unitY,  unitZ,  0.0f,  0.0f,  1.0f,
         unitX, unitY,  unitZ,  0.0f,  0.0f,  1.0f,
        -unitX, unitY,  unitZ,  0.0f,  0.0f,  1.0f,
        -unitX, -0.0f,  unitZ,  0.0f,  0.0f,  1.0f,

        -unitX, unitY,  unitZ, -1.0f,  0.0f,  0.0f,
        -unitX, unitY, -unitZ, -1.0f,  0.0f,  0.0f,
        -unitX, -0.0f, -unitZ, -1.0f,  0.0f,  0.0f,
        -unitX, -0.0f, -unitZ, -1.0f,  0.0f,  0.0f,
        -unitX, -0.0f,  unitZ, -1.0f,  0.0f,  0.0f,
        -unitX, unitY,  unitZ, -1.0f,  0.0f,  0.0f,

         unitX, unitY,  unitZ,  1.0f,  0.0f,  0.0f,
         unitX, unitY, -unitZ,  1.0f,  0.0f,  0.0f,
         unitX, -0.0f, -unitZ,  1.0f,  0.0f,  0.0f,
         unitX, -0.0f, -unitZ,  1.0f,  0.0f,  0.0f,
         unitX, -0.0f,  unitZ,  1.0f,  0.0f,  0.0f,
         unitX, unitY,  unitZ,  1.0f,  0.0f,  0.0f,

        -unitX, -0.0f, -unitZ,  0.0f, -1.0f,  0.0f,
         unitX, -0.0f, -unitZ,  0.0f, -1.0f,  0.0f,
         unitX, -0.0f,  unitZ,  0.0f, -1.0f,  0.0f,
         unitX, -0.0f,  unitZ,  0.0f, -1.0f,  0.0f,
        -unitX, -0.0f,  unitZ,  0.0f, -1.0f,  0.0f,
        -unitX, -0.0f, -unitZ,  0.0f, -1.0f,  0.0f,

        -unitX, unitY, -unitZ,  0.0f,  1.0f,  0.0f,
         unitX, unitY, -unitZ,  0.0f,  1.0f,  0.0f,
         unitX, unitY,  unitZ,  0.0f,  1.0f,  0.0f,
         unitX, unitY,  unitZ,  0.0f,  1.0f,  0.0f,
        -unitX, unitY,  unitZ,  0.0f,  1.0f,  0.0f,
        -unitX, unitY, -unitZ,  0.0f,  1.0f,  0.0f
    };

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    visualSortInit();
    visualSortState = STATE_IDLE;

    srand((unsigned)time(NULL));

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.useProgram();
        glUniform3fv(glGetUniformLocation(lightingShader.id, "viewPos"), 1, &camera.Position[0]);

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(1.0f);
        glUniform3fv(glGetUniformLocation(lightingShader.id, "light.ambient"), 1, &ambientColor[0]);
        glUniform3fv(glGetUniformLocation(lightingShader.id, "light.diffuse"), 1, &diffuseColor[0]);
        glUniform3f(glGetUniformLocation(lightingShader.id, "light.specular"), 1.0f, 1.0f, 1.0f);
        glUniform3fv(glGetUniformLocation(lightingShader.id, "light.position"), 1, &lightPos[0]);

        glUniform3f(glGetUniformLocation(lightingShader.id, "material.ambient"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.id, "material.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.id, "material.specular"), 0.2f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.id, "material.shininess"), 32.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.id, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.id, "view"), 1, GL_FALSE, &view[0][0]);

        // glm::mat4 model = glm::mat4(1.0f);
        // thetaX += omegaX;
        // if (thetaX >= 360 || thetaX <= -360) thetaX = 0.0f;
        // thetaY += omegaY;
        // if (thetaY >= 360 || thetaY <= -360) thetaY = 0.0f;
        // thetaZ += omegaZ;
        // if (thetaZ >= 360 || thetaZ <= -360) thetaZ = 0.0f;
        // model = glm::rotate(model, glm::radians(thetaX), glm::vec3(1, 0, 0));
        // model = glm::rotate(model, glm::radians(thetaY), glm::vec3(0, 1, 0));
        // model = glm::rotate(model, glm::radians(thetaX), glm::vec3(0, 0, 1));

        glBindVertexArray(cubeVAO);

        if (cubeDelaying <= 0 && visualSortState == STATE_SORT_INTER && cmdp < command.size())
        {
            parseCommand();
            visualSortState = STATE_SORT;
        }

        if (cubeDelaying <= 0)
        {
            for (int i = 0; i < cubeNum; ++i)
            {
                if (moving[i] && (cubeActivated[cubeNum - 1] || visualSortState == STATE_INIT))
                {
                    move[i].process += moveRate;
                    curCubePosX[i] = move[i].start + cubicPos(move[i].dist, move[i].process);
                    if (move[i].process >= 1.0f - moveRate/3) // At finishing
                    {
                        curCubePosX[i] = cubePosX[i];
                        moving[i] = false;
                        if (visualSortState == STATE_SORT)
                        {
                            //cubeColour[i] = colourInit;
                            //curCubeColour[i] = colourInit;
                            visualSortState = STATE_SORT_INTER;
                        }
                    }
                }
                if (growing[i])
                {
                    grow[i].process += growRate;
                    curCubeHeight[i] = grow[i].start + cubicPos(grow[i].dist, grow[i].process);
                    if (grow[i].process >= 1.0f - growRate/2) // At finishing
                    {
                        cubeHeight[i] = curCubeHeight[i];
                        if (!cubeActivated[cubeNum - 1] && cubeNum > 0)
                        {
                            --cubeNum;
                        }
                        if (visualSortState == STATE_INIT)
                        {
                            cubeNum = 0;
                            visualSortState = STATE_IDLE;
                        }
                        growing[i] = false;
                    }
                }
                if (painting[i])
                {
                    paint[i].process += paintRate;
                    curCubeColour[i].r = paint[i].startR + cubicPos(paint[i].distR, paint[i].process);
                    curCubeColour[i].g = paint[i].startG + cubicPos(paint[i].distG, paint[i].process);
                    curCubeColour[i].b = paint[i].startB + cubicPos(paint[i].distB, paint[i].process);
                    if (paint[i].process >= 1.0f - paintRate/3) // At finishing
                    {
                        curCubeColour[i] = cubeColour[i];
                        painting[i] = false;
                        if (visualSortState == STATE_SORT)
                        {
                            visualSortState = STATE_SORT_INTER;
                        }
                    }
                }

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f)); // Move down!
                model = glm::translate(model, glm::vec3(curCubePosX[i], 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(1.0f, curCubeHeight[i], 1.0f));
                glUniformMatrix4fv(glGetUniformLocation(lightingShader.id, "model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(glGetUniformLocation(lightingShader.id, "objectColor"), 1, &curCubeColour[i][0]);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }         //                                              |
        }             //                                              |  Same
        else          //                                              |  Need to eliminate redundance
        {             //                                              v
            --cubeDelaying;
            for (int i = 0; i < cubeNum; ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f)); // Move down!
                model = glm::translate(model, glm::vec3(curCubePosX[i], 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(1.0f, curCubeHeight[i], 1.0f));
                glUniformMatrix4fv(glGetUniformLocation(lightingShader.id, "model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(glGetUniformLocation(lightingShader.id, "objectColor"), 1, &curCubeColour[i][0]);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // printf(" ");
            if (cubeDelaying == 0)
            {
                visualSortState = STATE_SORT_INTER;
                // putchar('\n');
            }
        }


        if (cubeDelaying <= 0 && visualSortState == STATE_SORT_INTER && cmdp < command.size())
        {
            ++cmdp;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void CreateWindow(GLFWwindow*& window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Visualsort", NULL, NULL);
    glfwSetWindowPos(window, 200, 50);
    if (window == NULL)
    {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD.\n");
        exit(-1);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


