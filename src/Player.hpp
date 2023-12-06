//
// Created by Malik Zharykov on 06.12.2023.
//

#ifndef GLCRAFT_PLAYER_HPP
#define GLCRAFT_PLAYER_HPP


class Player {
private:
    std::unique_ptr<Mesh> _mesh;
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _vbo2 = 0;
    GLuint _ebo = 0;
    size_t indicesSize = 0;
    Vector position = Vector();

    std::unique_ptr<Shader> _shader;

public:
    Player();
    void render();
};


#endif //GLCRAFT_PLAYER_HPP
