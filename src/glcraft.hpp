#ifndef GLCRAFT_GLCRAFT_HPP
#define GLCRAFT_GLCRAFT_HPP

#define BLOCK_TEXTURE_WIDTH 16
#define BLOCK_TEXTURE_HEIGHT 16


#include <cstdint>
#include <memory>
#include <array>
#include <string>
#include <exception>
#include <utility>
#include <vector>
#include <unordered_map>
#include <functional>

#include <windows.h>
#include <gl/glew.h>
#include "../dependencies/stb_image.h"

// Block types
enum class BlockType : uint8_t {
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
class World;
class ChunkSection;
class TextureManager;
class Matrix;
class Vector;
class InputManager;
class Camera;
struct Vertex;
struct Mesh;
struct TexCoord;
class Lighting;

// Util
size_t hash_combine( size_t lhs, size_t rhs );

struct BlockTexture {
    GLuint front;
    GLuint back;
    GLuint left;
    GLuint right;
    GLuint top;
    GLuint bottom;
};

#include "Window.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "ChunkSection.hpp"
#include "Chunk.hpp"
#include "World.hpp"
#include "TextureManager.hpp"
#include "math/Matrix.hpp"
#include "math/Vector.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Lighting.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<Scene> scene;
extern std::unique_ptr<TextureManager> texman;
extern std::unique_ptr<InputManager> inman;
extern std::unique_ptr<Camera> camera;
extern std::unique_ptr<World> world;
extern std::unordered_map<BlockType, BlockTexture> blockTexture;
extern std::unique_ptr<Lighting> lighting;

struct Vertex {
    Vector position;
    Vector normal;
    Vector texCoords;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void add(Mesh* mesh, Matrix* matrix = nullptr);
    std::unique_ptr<float[]> getVerticesArray() const;
    std::unique_ptr<float[]> getTexCoordArray() const;
    size_t getVerticesArraySize() const;
    size_t getTexCoordArraySize() const;
    void rotateY(float angle);
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
std::unique_ptr<Mesh> cube_createBackMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createLeftMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createRightMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createTopMesh(const TexCoord& texCoords);
std::unique_ptr<Mesh> cube_createBottomMesh(const TexCoord& texCoords);

void terrain_generate_flat();
void generate_tree(int32_t x, int32_t y, int32_t z);

#endif //GLCRAFT_GLCRAFT_HPP
