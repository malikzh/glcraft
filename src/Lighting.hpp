//
// Created by malikzh on 28.06.2022.
//

#ifndef GLCRAFT_LIGHTING_HPP
#define GLCRAFT_LIGHTING_HPP


class Lighting {
private:
    std::unique_ptr<Mesh> _mesh;
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    size_t indicesSize = 0;

    std::unique_ptr<Shader> _shader;

public:
    GLuint time = 0;
    Vector lightVector;

    Lighting();
    void render();
};


#endif //GLCRAFT_LIGHTING_HPP
