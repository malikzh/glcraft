#include "glcraft.hpp"

/**
 * The main rendering method
 *
 * Это главный метод для рендеринга сцены
 */
void Scene::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}