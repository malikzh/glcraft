#include "glcraft.hpp"

World::World() {
    _shader = Shader::fromFile("resources/shader/chunk/vertex.glsl", "resources/shader/chunk/fragment.glsl");

    glGenFramebuffers(1, &_fbo);
    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void World::setBlock(int32_t x, int32_t y, int32_t z, BlockType type) {
    int32_t chunkX = x / Chunk::size;
    int32_t chunkY = z / Chunk::size;

    std::pair<int32_t, int32_t> pos = std::make_pair(chunkX, chunkY);

    if (!_chunks.contains(pos)) {
        _chunks.insert(std::make_pair(pos, Chunk()));
    }

    x %= Chunk::size;
    z %= Chunk::size;

    if (x < 0) {
        x = -x;
    }


    if (z < 0) {
        z = -z;
    }

    _chunks[pos].setBlock(x, y, z, type);
}

void World::buildMesh() {
    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        if (!it->second.mesh) {
            it->second.buildMesh();
        }
    }
}


void World::buffer() {
    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        it->second.buffer();
    }
}

void World::renderShadowMap() {
    glViewport(0, 0, shadowMapWidth, shadowMapHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_DEPTH_BUFFER_BIT);

    auto pos = camera->position.copy();
    auto look = camera->look.copy();
    camera->position = lighting->lightVector;
    render();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window->width, window->height);
    camera->position = *pos;
    camera->look = *look;
}

void World::render() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texman->bind();

    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        Matrix matrix;
        _shader->use();

        int32_t x = it->first.first;
        int32_t z = it->first.second;

        matrix.translate((float)(x * 16), 0.0f, (float)(z * 16));

        Matrix viewProjectionMatrix;
        camera->setPOV(&viewProjectionMatrix);
        viewProjectionMatrix.apply(scene->projectionMatrix.get());

        _shader->setValue("viewProjectionMatrix", &viewProjectionMatrix);
        _shader->setValue("worldMatrix", &matrix);
        _shader->setValue("sunPosition", &lighting->lightVector);

        it->second.bindVao();
        glDrawElements(GL_TRIANGLES, (GLint)it->second.indicesSize, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}