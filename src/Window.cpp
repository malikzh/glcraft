#include "glcraft.hpp"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Window::Window(GLuint _width, GLuint _height) {
    width = _width;
    height = _height;

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

//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    switch(msg) {
//        case WM_CLOSE:
//            PostQuitMessage(0);
//            break;
//        case WM_KEYDOWN:
//            if (wParam == VK_ESCAPE) {
//                PostQuitMessage(0);
//                return 0;
//            } else if (wParam == 'W') {
//                inman->forwardKeyPressed = true;
//            } else if (wParam == 'S') {
//                inman->backwardKeyPressed = true;
//            } else if (wParam == 'A') {
//                inman->leftKeyPressed = true;
//            } else if (wParam == 'D') {
//                inman->rightKeyPressed = true;
//            } else if (wParam == VK_SPACE) {
//                inman->spaceKeyPressed = true;
//            } else if (wParam == VK_F11) {
//                ShowWindow(hWnd, SW_SHOWMAXIMIZED);
//                UpdateWindow(hWnd);
//            } else if (wParam == VK_SHIFT) {
//                inman->shiftKeyPressed = true;
//            }
//            break;
//        case WM_KEYUP:
//            if (wParam == 'W') {
//                inman->forwardKeyPressed = false;
//            } else if (wParam == 'S') {
//                inman->backwardKeyPressed = false;
//            } else if (wParam == 'A') {
//                inman->leftKeyPressed = false;
//            } else if (wParam == 'D') {
//                inman->rightKeyPressed = false;
//            } else if (wParam == VK_SPACE) {
//                inman->spaceKeyPressed = false;
//            } else if (wParam == VK_SHIFT) {
//                inman->shiftKeyPressed = false;
//            }
//            break;
//        case WM_SIZE:
//        {
//            UINT width = LOWORD(lParam);
//            UINT height = HIWORD(lParam);
//
//            glViewport(0, 0, (GLint)width, (GLint)height);
//
//            if (window) {
//                window->width = width;
//                window->height = height;
//            }
//
//            if (scene) {
//                scene->updateProjectionMatrix((float)width / (float)height);
//            }
//
//        }
//            break;
//        default:
//            return DefWindowProc(hWnd, msg, wParam, lParam);
//    }
//
//    return 0;
//}

//POINT Window::_getCursorCenterPoint() const {
//    RECT rect;
//    POINT center;
//
//    center.x = 0;
//    center.y = 0;
//
//    if (GetClientRect(hWnd, &rect)) {
//        center.x = rect.right / 2L;
//        center.y = rect.bottom / 2L;
//
//        ClientToScreen(hWnd, &center);
//    }
//
//    return center;
//}
//
//void Window::moveCursorToCenter() const {
//    POINT point = _getCursorCenterPoint();
//    SetCursorPos(point.x, point.y);
//}
//
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