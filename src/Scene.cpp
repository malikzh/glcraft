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

std::vector<GLfloat> vx;
std::vector<GLfloat> tx;

/// Инициализация сцены
Scene::Scene() {
    // {0.0f, 1.0f - 1.0f / 10.0f, 1.0f / 6.0f, 1.0f}
    frontFace = cube_createFrontMesh(*texman->getCoord(1));


    for (Vertex v : frontFace->vertices) {
        vx.push_back(v.position[0]);
        vx.push_back(v.position[1]);
        vx.push_back(v.position[2]);
        vx.push_back(v.position[3]);

        tx.push_back(v.texCoords[0]);
        tx.push_back(v.texCoords[1]);
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vx.size(), vx.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * frontFace->indices.size(), frontFace->indices.data(), GL_STATIC_DRAW);

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
    glClear(GL_COLOR_BUFFER_BIT);
    shader->use();

    matrix.rotateZ(x);
    x += inman->mouseDX;

    //matrix.apply(projectionMatrix.get());
    shader->setValue("projectionMatrix", &matrix);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Scene::updateProjectionMatrix(float aspect) {
    projectionMatrix = createProjectionMatrix(aspect);
}

std::unique_ptr<Matrix> Scene::createProjectionMatrix(float aspect) {
    return Matrix::perspective(45.0f * (M_PI / 180.0f), aspect, 1.0f, 100.0f);
}