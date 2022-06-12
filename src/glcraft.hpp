#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#include <memory>
#include <string>
#include <exception>
#include <vector>

#include <windows.h>
#include <gl/glew.h>
#include "../dependencies/stb_image.h"
#include "../dependencies/linmath.h"

// Forward declaration
class Window;
class Scene;
class Shader;
class Chunk;

struct Vertex {
    vec4 position;
    vec3 normal;
    vec2 texCoords;
};

struct Texture {
    GLuint id;
    std::string type;
};

#include "Window.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Chunk.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<Scene> scene;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept;
void glcraft_mainloop();
void glcraft_error(const char* message);

#endif //GLCRAFT_GLCRAFT_HPP
