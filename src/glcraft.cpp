#include "glcraft.hpp"

std::unique_ptr<Window> window = nullptr;
std::unique_ptr<Scene> scene = nullptr;
std::unique_ptr<TextureManager> texman = nullptr;
std::unique_ptr<InputManager> inman = nullptr;
std::unique_ptr<Camera> camera = nullptr;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept {
    try {
        stbi_set_flip_vertically_on_load(true);

        inman = std::make_unique<InputManager>();
        window = std::make_unique<Window>(hInstance, nShowCmd);
        texman = std::make_unique<TextureManager>();
        camera = std::make_unique<Camera>();
        scene = std::make_unique<Scene>();

        glcraft_mainloop();
        return 0;
    } catch (std::exception &exception) {
        glcraft_error(exception.what());
        return -1;
    }
}

void glcraft_mainloop() {
    MSG msg;

    bool active = true;

    while(active) {
        window->moveCursorToCenter();

        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                active = false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Update cursor
        POINT mouse = window->getCursorDeviation();

        inman->mouseDX = (float)mouse.x;
        inman->mouseDY = (float)mouse.y;

        scene->render();
        window->swapBuffers();
    }
}


void glcraft_error(const char* message) {
    MessageBoxA( NULL, message, "GLCraft error", MB_ICONERROR | MB_OK);
}