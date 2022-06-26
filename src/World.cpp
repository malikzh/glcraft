#include "glcraft.hpp"

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
        x = 16 + x;
    }


    if (z < 0) {
        z = 16 + z;
    }

    _chunks[pos].setBlock(x, y, z, type);
}

void World::buildMesh() {
    mesh = std::make_unique<Mesh>();

    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        int32_t x = it->first.first;
        int32_t z = it->first.second;

        if (!it->second.mesh) {
            it->second.buildMesh();
        }

        auto matrix = Matrix::translation((float)x, 0.0f, (float)z);
        mesh->add(it->second.mesh.get());
    }
}


void World::buffer() {
    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        it->second.buffer();
    }
}


void World::render() {
    for (auto it = _chunks.begin(); it != _chunks.end(); it++) {
        it->second.render();
    }
}