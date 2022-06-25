#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#define BLOCK_TEXTURE_WIDTH 16
#define BLOCK_TEXTURE_HEIGHT 16

#include <memory>
#include <string>
#include <exception>
#include <vector>

#include <windows.h>
#include <gl/glew.h>
#include "../dependencies/stb_image.h"
#include "../dependencies/linmath.h"

// Block types
enum class BlockType {
    AIR = 0, // Воздух
    GRASS,   // Блок травы
    DIRT,    // Земля
    SAND,    // Песок
    STONE,   // Камень
    BEDROCK, // Бедрок
    WOOD,    // Дерево
    LEAVES,  // Листва
    WATER,   // Вода
};

// Forward declaration
class Window;
class Scene;
class Shader;
class Chunk;
class TextureManager;


struct Vertex {
    vec4 position;
    vec3 normal;
    vec2 texCoords;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

#include "Window.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Chunk.hpp"
#include "TextureManager.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<Scene> scene;
extern std::unique_ptr<TextureManager> texman;

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept;
void glcraft_mainloop();
void glcraft_error(const char* message);

#endif //GLCRAFT_GLCRAFT_HPP
