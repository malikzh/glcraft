//
// Created by malikzh on 25.06.2022.
//

#ifndef GLCRAFT_TEXTUREMANAGER_HPP
#define GLCRAFT_TEXTUREMANAGER_HPP


class TextureManager {
private:
    GLuint _id;
    int _width;
    int _height;

public:
    TextureManager(); // Инициализирует текстуры
    ~TextureManager();

    std::unique_ptr<TexCoord> getCoord(unsigned int id);
};


#endif //GLCRAFT_TEXTUREMANAGER_HPP
