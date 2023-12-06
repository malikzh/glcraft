#include "glcraft.hpp"
#include <algorithm>

TextureManager::TextureManager() {
    int nrChannels;
    unsigned char *data = stbi_load("resources/texture.png", &_width, &_height, &nrChannels, 4);

    if (!data) {
        throw std::runtime_error("Cannot load texture");
    }

    if (_width % BLOCK_TEXTURE_WIDTH != 0 || _height % BLOCK_TEXTURE_HEIGHT != 0) {
        throw std::runtime_error("Texture size must be multiple by 16");
    }

    glGenTextures(1, &_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

TextureManager::~TextureManager() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &_id);
}


std::unique_ptr<TexCoord> TextureManager::getCoord(unsigned int id) {
    unsigned int cols = _width / BLOCK_TEXTURE_WIDTH;
    unsigned int rows = _height / BLOCK_TEXTURE_HEIGHT;

    unsigned int maxId =  rows * cols - 1;
    id = std::max(id, 0u);
    id = std::min(id, maxId);

    unsigned int x = id % cols;
    unsigned int y = id / cols;

    float u = 1.0f / (float)cols;
    float v = 1.0f / (float)rows;

    return std::make_unique<TexCoord>(TexCoord{
        .left   = u * (float)x,
        .bottom = 1.0f - v * (float)(y + 1),
        .right  = u * (float)(x + 1),
        .top    = 1.0f - v * (float)y
    });
}

void TextureManager::bind() {
    glBindTexture(GL_TEXTURE_2D, _id);
}