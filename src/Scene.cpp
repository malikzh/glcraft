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

/// Инициализация сцены
Scene::Scene() {
    terrain_generate_flat();
    world->buildMesh();
    world->buffer();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

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
    glClearColor(0.467f, 0.659f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->handleInput();
    world->render();
}


void Scene::updateProjectionMatrix(float aspect) {
    projectionMatrix = createProjectionMatrix(aspect);
}

std::unique_ptr<Matrix> Scene::createProjectionMatrix(float aspect) {
    return Matrix::perspective(45.0f * (M_PI / 180.0f), aspect, 1.0f, 100.0f);
}