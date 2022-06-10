#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#include <memory>
#include <string>

#include <windows.h>

#include "Window.hpp"

extern std::unique_ptr<Window> window;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept;
void glcraft_mainloop();
void glcraft_error(const char* message);

#endif //GLCRAFT_GLCRAFT_HPP
