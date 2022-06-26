#include "glcraft.hpp"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * Конструктор окна
 * @param hinstance
 * @param nShowCmd
 */
Window::Window(HINSTANCE hInstance, int nShowCmd) {
    _hInstance = hInstance;
    _nShowCmd = nShowCmd;

    // Register class
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = _hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = (LPSTR)NULL;
    wc.lpszClassName = (LPSTR)(_className.c_str());
    RegisterClass(&wc);

    // Create window
    hWnd = CreateWindowEx(0,
                          _className.c_str(),         // имя класса окна
                          _title.c_str(),       // заголовок окна
                          WS_OVERLAPPEDWINDOW, // стиль окна
                          CW_USEDEFAULT,       // задаем размеры и расположение
                          CW_USEDEFAULT,       // окна, принятые по умолчанию
                          _defaultWidth,
                          _defaultHeight,
                          NULL,                   // идентификатор родительского окна
                          NULL,                   // идентификатор меню
                          _hInstance,           // идентификатор приложения
                          NULL);

    if (!hWnd) {
        throw std::exception("Window creation failure");
    }

    // Show window
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    // Get Device Context
    hDC = GetDC(hWnd);

    // Configure OpenGL context
    PIXELFORMATDESCRIPTOR pfd =
            {
                    sizeof(PIXELFORMATDESCRIPTOR),
                    1,
                    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
                    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                    32,                   // Colordepth of the framebuffer.
                    0, 0, 0, 0, 0, 0,
                    0,
                    0,
                    0,
                    0, 0, 0, 0,
                    24,                   // Number of bits for the depthbuffer
                    8,                    // Number of bits for the stencilbuffer
                    0,                    // Number of Aux buffers in the framebuffer.
                    PFD_MAIN_PLANE,
                    0,
                    0, 0, 0
            };

    int  letWindowsChooseThisPixelFormat;
    letWindowsChooseThisPixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC,letWindowsChooseThisPixelFormat, &pfd);

    glContext = wglCreateContext(hDC);
    wglMakeCurrent(hDC, glContext);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        throw std::exception("GLEW initialization failure");
    }

    RECT rect;

    if(GetClientRect(hWnd, &rect)) {
        glViewport(0, 0, rect.right, rect.bottom);
    } else {
        glViewport(0, 0, _defaultWidth, _defaultHeight);
    }

}

Window::~Window() {
    wglMakeCurrent(NULL, NULL);

    if (glContext) {
        wglDeleteContext(glContext);
    }

    if (hDC && hWnd) {
        ReleaseDC(hWnd, hDC);
    }

    if(hWnd) {
        DestroyWindow(hWnd);
    }
}

void Window::swapBuffers() {
    SwapBuffers(hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
                return 0;
            } else if (wParam == 'W') {
                inman->forwardKeyPressed = true;
            } else if (wParam == 'S') {
                inman->backwardKeyPressed = true;
            } else if (wParam == 'A') {
                inman->leftKeyPressed = true;
            } else if (wParam == 'D') {
                inman->rightKeyPressed = true;
            } else if (wParam == VK_SPACE) {
                inman->spaceKeyPressed = true;
            } else if (wParam == VK_F11) {
                ShowWindow(hWnd, SW_SHOWMAXIMIZED);
                UpdateWindow(hWnd);
            }
            break;
        case WM_KEYUP:
            if (wParam == 'W') {
                inman->forwardKeyPressed = false;
            } else if (wParam == 'S') {
                inman->backwardKeyPressed = false;
            } else if (wParam == 'A') {
                inman->leftKeyPressed = false;
            } else if (wParam == 'D') {
                inman->rightKeyPressed = false;
            } else if (wParam == VK_SPACE) {
                inman->spaceKeyPressed = false;
            }
            break;
        case WM_SIZE:
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);

            glViewport(0, 0, (GLint)width, (GLint)height);

            if (scene) {
                scene->updateProjectionMatrix((float)width / (float)height);
            }

        }
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}