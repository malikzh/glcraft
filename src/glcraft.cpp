#include "glcraft.hpp"

std::unique_ptr<Window> window;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept {
    try {
        window = std::make_unique<Window>(hInstance, nShowCmd);

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
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                active = false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // todo rendering loop
    }
}


void glcraft_error(const char* message) {
    MessageBoxA( NULL, message, "GLCraft error", MB_ICONERROR | MB_OK);
}