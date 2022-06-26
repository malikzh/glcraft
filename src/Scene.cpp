#define _USE_MATH_DEFINES
#include <cmath>
#include "glcraft.hpp"

GLfloat vertices[] = {
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
};

unsigned int VBO;
unsigned int VBO2;
unsigned int EBO;

std::unique_ptr<Shader> shader;
std::unique_ptr<Mesh> frontFace;
std::unique_ptr<Mesh> backFace;
std::unique_ptr<Mesh> leftFace;
std::unique_ptr<Mesh> rightFace;
std::unique_ptr<Mesh> topFace;

std::vector<GLfloat> vx;
std::vector<GLfloat> tx;
std::vector<GLuint> ex;

/// Инициализация сцены
Scene::Scene() {
    // {0.0f, 1.0f - 1.0f / 10.0f, 1.0f / 6.0f, 1.0f}
    frontFace = cube_createFrontMesh(*texman->getCoord(1));
    backFace = cube_createBackMesh(*texman->getCoord(1));
    leftFace = cube_createLeftMesh(*texman->getCoord(0));
    rightFace = cube_createRightMesh(*texman->getCoord(0));
    topFace = cube_createTopMesh(*texman->getCoord(2));


    for (const Vertex& v : frontFace->vertices) {
        v.position.pack4(&vx);
        v.texCoords.pack2(&tx);
    }

    ex.insert(ex.end(), frontFace->indices.begin(), frontFace->indices.end());

    size_t offset = frontFace->vertices.size();

    // left
    for (const Vertex& v : leftFace->vertices) {
        v.position.pack4(&vx);
        v.texCoords.pack2(&tx);
    }

    for (auto it = leftFace->indices.begin(); it != leftFace->indices.end(); it++) {
        ex.push_back(*it + offset);
    }

    offset += leftFace->vertices.size();

    // right

    for (const Vertex& v : rightFace->vertices) {
        v.position.pack4(&vx);
        v.texCoords.pack2(&tx);
    }

    for (auto it = rightFace->indices.begin(); it != rightFace->indices.end(); it++) {
        ex.push_back(*it + offset);
    }

    offset += rightFace->vertices.size();

    // back

    for (const Vertex& v : backFace->vertices) {
        v.position.pack4(&vx);
        v.texCoords.pack2(&tx);
    }

    for (auto it = backFace->indices.begin(); it != backFace->indices.end(); it++) {
        ex.push_back(*it + offset);
    }

    offset += backFace->vertices.size();

    // top

    for (const Vertex& v : topFace->vertices) {
        v.position.pack4(&vx);
        v.texCoords.pack2(&tx);
    }

    for (auto it = topFace->indices.begin(); it != topFace->indices.end(); it++) {
        ex.push_back(*it + offset);
    }

    offset += topFace->vertices.size();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vx.size(), vx.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * ex.size(), ex.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tx.size(), tx.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    shader = Shader::fromFile("resources/shader/vertex.glsl", "resources/shader/fragment.glsl");

    // Initialize projection matrix

    projectionMatrix = createProjectionMatrix(1.0f);
}

/**
 * The main rendering method
 *
 * Это главный метод для рендеринга сцены
 */

float x = 0.0f;

void Scene::render() {
    Matrix matrix;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    camera->handleInput();

    camera->setPOV(&matrix);
    matrix.apply(projectionMatrix.get());
    shader->setValue("projectionMatrix", &matrix);

    glDrawElements(GL_TRIANGLES, ex.size(), GL_UNSIGNED_INT, 0);
}


void Scene::updateProjectionMatrix(float aspect) {
    projectionMatrix = createProjectionMatrix(aspect);
}

std::unique_ptr<Matrix> Scene::createProjectionMatrix(float aspect) {
    return Matrix::perspective(45.0f * (M_PI / 180.0f), aspect, 1.0f, 100.0f);
}