#include "glcraft.hpp"

TextureManager::TextureManager() {
    int nrChannels;
    unsigned char *data = stbi_load("resources/texture.png", &_width, &_height, &nrChannels, 0);

    if (!data) {
        throw std::exception("Cannot load texture");
    }

    if (_width % BLOCK_TEXTURE_WIDTH != 0 || _height % BLOCK_TEXTURE_HEIGHT != 0) {
        throw std::exception("Texture size must be multiple by 16");
    }

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

TextureManager::~TextureManager() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &_id);
}