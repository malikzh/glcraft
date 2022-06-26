#include "glcraft.hpp"

void World::setBlock(int32_t x, int32_t y, int32_t z, BlockType type) {
    int32_t chunkX = x / Chunk::size;
    int32_t chunkY = z / Chunk::size;

    std::pair<int32_t, int32_t> pos = std::make_pair(chunkX, chunkY);

    if (!_chunks.contains(pos)) {
        _chunks[pos] = Chunk();
    }

    _chunks[pos].setBlock(x % Chunk::size, y, z % Chunk::size, type);
}