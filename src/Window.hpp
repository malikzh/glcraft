#ifndef GLCRAFT_WINDOW_HPP
#define GLCRAFT_WINDOW_HPP


class Window {
    const int _defaultWidth = 500;
    const int _defaultHeight = 500;

    const std::string _className = "glcraft";
    const std::string _title = "GLCraft by Malik Zharykov";

    HINSTANCE _hInstance = nullptr;
    int _nShowCmd = 0;
public:
    HWND hWnd = nullptr;
    HDC hDC = nullptr;
    HGLRC glContext = nullptr;

    Window(HINSTANCE hInstance, int nShowCmd);
    ~Window();

    void swapBuffers();
};


#endif //GLCRAFT_WINDOW_HPP
