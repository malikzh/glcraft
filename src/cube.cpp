#include "glcraft.hpp"

std::unique_ptr<Mesh> cube_createFrontMesh(const TexCoord& texCoords) {
    return std::make_unique<Mesh>(Mesh{
        .vertices = {
                Vertex{
                    .position = {0.5f, -0.5f, 0.5f, 1.0f},
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