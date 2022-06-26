#include "glcraft.hpp"

void World::setBlock(int32_t x, int32_t y, int32_t z, BlockType type) {
    int32_t chunkX = x / Chunk::size;
    int32_t chunkY = z / Chunk::size;

    std::pair<int32_t, int32_t> pos = std::make_pair(chunkX, chunkY);

    if (!_chunks.contains(pos)) {
        _chunks[pos] = Chunk();
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