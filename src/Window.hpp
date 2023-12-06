#ifndef GLCRAFT_WINDOW_HPP
#define GLCRAFT_WINDOW_HPP

#include <GLFW/glfw3.h>

class Window {

public:
    GLFWwindow* window;

    GLuint width = 640;
    GLuint height = 480;
    Window(GLuint _width, GLuint _height);
    ~Window();

    void swapBuffers();
    void moveCursorToCenter() const;
};


#endif //GLCRAFT_WINDOW_HPP
