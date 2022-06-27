//
// Created by malikzh on 28.06.2022.
//

#ifndef GLCRAFT_LIGHTING_HPP
#define GLCRAFT_LIGHTING_HPP


class Lighting {
private:
    std::unique_ptr<Mesh> _mesh;
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    size_t indicesSize = 0;

    std::unique_ptr<Shader> _shader;

public:
    GLuint time = 0;
    Vector lightVector;

    Lighting();
    void render();
};


#endif //GLCRAFT_LIGHTING_HPP
