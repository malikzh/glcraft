#include "glcraft.hpp"

void Mesh::add(Mesh* mesh, Matrix* matrix) {
    for (Vertex vertex : mesh->vertices) {
        if (matrix) {
            vertex.position.apply(matrix);
        }

        vertices.emplace_back(vertex);
    }

    size_t offset = vertices.size();

    for (GLuint index : mesh->indices) {
        indices.push_back(offset + index);
    }
}