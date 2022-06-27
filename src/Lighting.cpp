#define _USE_MATH_DEFINES
#include <cmath>
#include "glcraft.hpp"

Lighting::Lighting() {
    // Солнце будет у нас квадратным :)
    _mesh = std::make_unique<Mesh>(Mesh{
        .vertices = {
                Vertex{
                    .position = Vector(1.0f, -1.0f, 0.0f),
                },
                Vertex{
                        .position = Vector(1.0f, 1.0f, 0.0f),
                },
                Vertex{
                        .position = Vector(-1.0f, 1.0f, 0.0f),
                },
                Vertex{
                        .position = Vector(-1.0f, -1.0f, 0.0f),
                },
        },
        .indices = {
                0, 1, 2,
                0, 2, 3,
        }
    });

    // Pass data to opengl
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    auto vertices = _mesh->getVerticesArray();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _mesh->getVerticesArraySize(), vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Indices
    if (!_ebo) {
        glGenBuffers(1, &_ebo);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _mesh->indices.size(), _mesh->indices.data(), GL_STATIC_DRAW);

    // unbind vao
    glBindVertexArray(0);
    indicesSize = _mesh->indices.size();

    _shader = Shader::fromFile("resources/shader/lighting/vertex.glsl", "resources/shader/lighting/fragment.glsl");
}

void Lighting::render() {
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    Matrix matrix;

    matrix.scale(100.0f, 100.0f, 100.0f);
    matrix.translate(50.0f, 0.0f, -1000.0f);

    // Ставим солнце в положении согласно времени
    matrix.rotateX(((float)time / 30000.0f) * (float)M_PI);

    _shader->use();

    camera->setPOV(&matrix);
    matrix.apply(scene->projectionMatrix.get());
    _shader->setValue("projectionMatrix", &matrix);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    time++;
    time %= 60000;
}