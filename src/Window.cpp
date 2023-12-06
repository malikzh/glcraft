#include "glcraft.hpp"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    inman->mouseDX += (xpos - inman->mouseX) * 0.1;
    inman->mouseX = xpos;

    inman->mouseDY += (ypos - inman->mouseY) * 0.1;
    inman->mouseY = ypos;
}

Window::Window() {

    if (!glfwInit ())
    {
        std::cerr<<"ERROR: could not start GLFW3"<<std::endl;
        exit(1);
    }

#ifdef __APPLE__
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow (width, height, "ComputerNetworksCraft", NULL, NULL);

    if (!window)
    {
        std::cerr<<"ERROR: could not open window with GLFW3"<<std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent (window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                inman->forwardKeyPressed = true;
                break;
            case GLFW_KEY_S:
                inman->backwardKeyPressed = true;
                break;
            case GLFW_KEY_A:
                inman->leftKeyPressed = true;
                break;
            case GLFW_KEY_D:
                inman->rightKeyPressed = true;
                break;
            case GLFW_KEY_SPACE:
                inman->spaceKeyPressed = true;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                inman->shiftKeyPressed = true;
                break;
            case GLFW_KEY_ESCAPE:
                exit(0);
                break;
        }
    } else if (action == GLFW_RELEASE) {
        switch(key) {
            case GLFW_KEY_W:
                inman->forwardKeyPressed = false;
                break;
            case GLFW_KEY_S:
                inman->backwardKeyPressed = false;
                break;
            case GLFW_KEY_A:
                inman->leftKeyPressed = false;
                break;
            case GLFW_KEY_D:
                inman->rightKeyPressed = false;
                break;
            case GLFW_KEY_SPACE:
                inman->spaceKeyPressed = false;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                inman->shiftKeyPressed = false;
                break;
        }
    }
}

//POINT Window::getCursorDeviation() const {
//    POINT cursor;
//
//    cursor.x = 0;
//    cursor.y = 0;
//
//    if (GetCursorPos(&cursor)) {
//        POINT center = _getCursorCenterPoint();
//
//        cursor.x -= center.x;
//        cursor.y -= center.y;
//    }
//
//    return cursor;
//}