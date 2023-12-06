#include "glcraft.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

std::unique_ptr<Window> window = nullptr;
std::unique_ptr<Scene> scene = nullptr;
std::unique_ptr<TextureManager> texman = nullptr;
std::unique_ptr<InputManager> inman = nullptr;
std::unique_ptr<Camera> camera = nullptr;
std::unique_ptr<World> world = nullptr;
std::unique_ptr<Lighting> lighting = nullptr;

int glcraft_boot(int argc, char** argv) {
    try {
        stbi_set_flip_vertically_on_load(true);

        inman = std::make_unique<InputManager>();
        window = std::make_unique<Window>();
        texman = std::make_unique<TextureManager>();
        camera = std::make_unique<Camera>();
        world = std::make_unique<World>();
        lighting = std::make_unique<Lighting>();
        scene = std::make_unique<Scene>();

        glcraft_mainloop();
        return 0;
    } catch (std::exception &exception) {
        glcraft_error(exception.what());
        return -1;
    }
}

void glcraft_mainloop() {
    while(!glfwWindowShouldClose(window->window)) {
        glfwGetWindowSize(window->window, (int*)&window->width, (int*)&window->height);
        scene->updateProjectionMatrix((float)window->width / (float)window->height);
        //window->moveCursorToCenter();

        // Update cursor
        //POINT mouse = window->getCursorDeviation();

//        inman->mouseDX += (float)mouse.x;
//        inman->mouseDY += (float)mouse.y;

        scene->render();
        window->swapBuffers();
        glfwPollEvents();
    }
}


void glcraft_error(const char* message) {
    std::cout << "GLCraft error: " <<  message << std::endl;
}
