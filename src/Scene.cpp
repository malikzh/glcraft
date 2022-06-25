#include "glcraft.hpp"

GLfloat vertices[] = {
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
};

unsigned int VBO;
std::unique_ptr<Shader> shader;

/// Инициализация сцены
Scene::Scene() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader = Shader::fromFile("resources/shader/vertex.glsl", "resources/shader/fragment.glsl");
}

/**
 * The main rendering method
 *
 * Это главный метод для рендеринга сцены
 */
void Scene::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}