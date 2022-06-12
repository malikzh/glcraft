#include <utility>

#ifndef GLCRAFT_MESH_HPP
#define GLCRAFT_MESH_HPP


class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh() {}
    Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures) : vertices(std::move(_vertices)), indices(_indices), textures(_textures) {}

    void draw(Shader& shader);
};


#endif //GLCRAFT_MESH_HPP
