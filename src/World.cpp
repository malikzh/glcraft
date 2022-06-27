#include "glcraft.hpp"

World::World() {
    _shader = Shader::fromFile("resources/shader/chunk/vertex.glsl", "resources/shader/chunk/fragment.glsl");
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


void World::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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