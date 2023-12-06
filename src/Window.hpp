#ifndef GLCRAFT_WINDOW_HPP
#define GLCRAFT_WINDOW_HPP

#include <GLFW/glfw3.h>

struct Point {
    double x;
    double y;
};

class Window {
public:
    GLFWwindow* window;

    GLuint width = 800;
    GLuint height = 600;
    Window(bool isServer);
    ~Window();

    void swapBuffers();
    void moveCursorToCenter() const;

private:
    std::unique_ptr<Point> _getCursorCenterPoint() const;
};


#endif //GLCRAFT_WINDOW_HPP
