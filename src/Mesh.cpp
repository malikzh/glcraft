#include "glcraft.hpp"

void Mesh::add(Mesh* mesh) {
    vertices.insert(vertices.end(), mesh->vertices.begin(), mesh->vertices.end());

    size_t offset = vertices.size();

    for (GLuint index : mesh->indices) {
        indices.push_back(offset + index);
    }
}