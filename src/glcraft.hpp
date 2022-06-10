#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#include <memory>
#include <string>
#include <exception>

#include <windows.h>
#include <gl/glew.h>

#include "Window.hpp"
#include "Scene.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<Scene> scene;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept;
void glcraft_mainloop();
void glcraft_error(const char* message);

#endif //GLCRAFT_GLCRAFT_HPP
