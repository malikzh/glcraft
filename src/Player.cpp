//
// Created by Malik Zharykov on 06.12.2023.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include "glcraft.hpp"

static std::unique_ptr<Mesh> createHeadMesh() {
    auto front = cube_createFrontMesh(*texman->getCoord(5));
    auto back = cube_createBackMesh(*texman->getCoord(8));
    auto right = cube_createRightMesh(*texman->getCoord(6));
    auto left = cube_createLeftMesh(*texman->getCoord(7));
    auto top = cube_createTopMesh(*texman->getCoord(9));

    auto mesh = std::make_unique<Mesh>();
    mesh->add(front.get());
    mesh->add(back.get());
    mesh->add(right.get());
    mesh->add(left.get());
    mesh->add(top.get());

    return mesh;
}

Player::Player() {
    _mesh = std::make_unique<Mesh>();
    _mesh->add(createHeadMesh().get());

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    auto vertices = _mesh->getVerticesArray();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _mesh->getVerticesArraySize(), vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto texcoords = _mesh->getTexCoordArray();

    glGenBuffers(1, &_vbo2);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _mesh->getTexCoordArraySize(), texcoords.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Indices
    glGenBuffers(1, &_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _mesh->indices.size(), _mesh->indices.data(), GL_STATIC_DRAW);

    // unbind vao
    glBindVertexArray(0);
    indicesSize = _mesh->indices.size();

    _shader = Shader::fromFile("resources/shader/player/vertex.glsl", "resources/shader/player/fragment.glsl");
}

void Player::render() {

    Matrix matrix;

    texman->bind();

    _shader->use();

    //matrix.scale(2.0f, 2.0f, 2.0f);
    matrix.translate(position.x, position.y, position.z);

    camera->setPOV(&matrix);
    matrix.apply(scene->projectionMatrix.get());
    _shader->setValue("viewProjectionMatrix", &matrix);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}