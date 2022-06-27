#include "glcraft.hpp"

void Mesh::add(Mesh* mesh, Matrix* matrix) {
    size_t offset = vertices.size();

    for (Vertex vertex : mesh->vertices) {
        if (matrix) {
            vertex.position.apply(matrix);
        }

        vertices.push_back(vertex);
    }

    for (GLuint index : mesh->indices) {
        indices.push_back(offset + index);
    }
}


std::unique_ptr<float[]> Mesh::getVerticesArray() const {
    auto arr = std::make_unique<float[]>(getVerticesArraySize());

    size_t i = 0;
    for (const Vertex& v : vertices) {
        arr[i++] = v.position.x;
        arr[i++] = v.position.y;
        arr[i++] = v.position.z;
        arr[i++] = v.position.w;
    }

    return arr;
}
std::unique_ptr<float[]> Mesh::getTexCoordArray() const {
    auto arr = std::make_unique<float[]>(getTexCoordArraySize());

    size_t i = 0;
    for (const Vertex& v : vertices) {
        arr[i++] = v.texCoords.x;
        arr[i++] = v.texCoords.y;
    }

    return arr;
}
size_t Mesh::getVerticesArraySize() const {
    return vertices.size() * 4;
}

size_t Mesh::getTexCoordArraySize() const {
    return vertices.size() * 2;
}


void Mesh::rotateY(float angle) {
    auto m = Matrix::rotationY(angle);

    for (Vertex& vertex : vertices) {
        vertex.position.apply(m.get());
        vertex.normal.apply(m.get());
    }
}


std::unique_ptr<float[]> Mesh::getNormalsArray() const {
    auto arr = std::make_unique<float[]>(getNormalsArraySize());

    if (!arr) {
        throw std::exception("Allocation failure");
    }

    size_t i = 0;
    for (const Vertex& v : vertices) {
        arr[i++] = v.normal.x;
        arr[i++] = v.normal.y;
        arr[i++] = v.normal.z;
        arr[i++] = v.normal.w;
    }

    return arr;
}

size_t Mesh::getNormalsArraySize() const {
    return vertices.size() * 4;
}