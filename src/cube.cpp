#define _USE_MATH_DEFINES
#include <cmath>
#include "glcraft.hpp"

std::unique_ptr<Mesh> cube_createFrontMesh(const TexCoord& texCoords) {
    return std::make_unique<Mesh>(Mesh{
        .vertices = {
                Vertex{
                    .position = {0.5f, -0.5f, 0.5f},
                    .normal = {0.0f, 0.0f, 1.0f},
                    .texCoords = {texCoords.right, texCoords.bottom},
                },
                Vertex{
                    .position = {0.5f, 0.5f, 0.5f, 1.0f},
                    .normal = {0.0f, 0.0f, 1.0f},
                        .texCoords = {texCoords.right, texCoords.top},
                },
                Vertex{
                    .position = {-0.5f, 0.5f, 0.5f, 1.0f},
                    .normal = {0.0f, 0.0f, 1.0f},
                    .texCoords = {texCoords.left, texCoords.top},
                },
                Vertex{
                    .position = {-0.5f, -0.5f, 0.5f, 1.0f},
                    .normal = {0.0f, 0.0f, 1.0f},
                    .texCoords = {texCoords.left, texCoords.bottom},
                },
        },
        .indices = {
                0, 1, 2,
                0, 2, 3,
                },
    });
}

std::unique_ptr<Mesh> cube_createRightMesh(const TexCoord& texCoords) {
    auto mesh = cube_createFrontMesh(texCoords);
    auto matrix = Matrix::rotationY(M_PI_2);

    for (Vertex& v : mesh->vertices) {
        v.position.apply(matrix.get());
        v.normal.apply(matrix.get());
    }

    return mesh;
}

std::unique_ptr<Mesh> cube_createLeftMesh(const TexCoord& texCoords) {
    auto mesh = cube_createFrontMesh(texCoords);
    auto matrix = Matrix::rotationY(-M_PI_2);

    for (Vertex& v : mesh->vertices) {
        v.position.apply(matrix.get());
        v.normal.apply(matrix.get());
    }

    return mesh;
}