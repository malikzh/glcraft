#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#define BLOCK_TEXTURE_WIDTH 16
#define BLOCK_TEXTURE_HEIGHT 16

#include <memory>
#include <string>
#include <exception>
#include <utility>
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
class Matrix;
class Vector;
class InputManager;
class Camera;
struct Vertex;
struct Mesh;
struct TexCoord;

#include "Window.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Chunk.hpp"
#include "TextureManager.hpp"
#include "math/Matrix.hpp"
#include "math/Vector.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<Scene> scene;
extern std::unique_ptr<TextureManager> texman;
extern std::unique_ptr<InputManager> inman;
extern std::unique_ptr<Camera> camera;

struct Vertex {
    Vector position;
    Vector normal;
    Vector texCoords;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

struct TexCoord {
    GLfloat left;
    GLfloat bottom;
    GLfloat right;
    GLfloat top;
};

int glcraft_boot(HINSTANCE hInstance, int nShowCmd) noexcept;
void glcraft_mainloop();
void glcraft_error(const char* message);

std::unique_ptr<Mesh> cube_createFrontMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createLeftMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createRightMesh(const TexCoord& texCoords);

#endif //GLCRAFT_GLCRAFT_HPP
