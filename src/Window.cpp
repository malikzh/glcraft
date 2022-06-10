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
    wc.style = 0;
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
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
                return 0;
            }
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}