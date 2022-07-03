#define _USE_MATH_DEFINES
#include <cmath>
#include "glcraft.hpp"

/// Инициализация сцены
Scene::Scene() {
    terrain_generate_flat();
    world->buildMesh();
    world->buffer();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Initialize projection matrix
    projectionMatrix = createProjectionMatrix(1.0f);
    inversedProjectionMatrix = createInversedProjectionMatrix(1.0f);
}

/**
 * The main rendering method
 *
 * Это главный метод для рендеринга сцены
 */

float x = 0.0f;

void Scene::render() {
    glClearColor(0.467f, 0.659f, 1.0f, 1.0f);
    camera->handleInput();
    world->renderShadowMap();
    world->render();
    lighting->render();
}


void Scene::updateProjectionMatrix(float aspect) {
    projectionMatrix = createProjectionMatrix(aspect);
    inversedProjectionMatrix = createInversedProjectionMatrix(aspect);
}

std::unique_ptr<Matrix> Scene::createProjectionMatrix(float aspect) {
    return Matrix::perspective(45.0f * (M_PI / 180.0f), aspect, 1.0f, 1000.0f);
}

std::unique_ptr<Matrix> Scene::createInversedProjectionMatrix(float aspect) {
    return Matrix::inversedPerspective(45.0f * (M_PI / 180.0f), aspect, 0.5f, 1000.0f);
}