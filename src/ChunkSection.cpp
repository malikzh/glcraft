#include "glcraft.hpp"

size_t ChunkSection::_positionToIndex(uint32_t x, uint32_t y, uint32_t z) {
    return sectionSize*sectionSize*y + sectionSize*z + x;
}

void ChunkSection::setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type) {
    uint32_t index = _positionToIndex(x, y, z);

    if (index >= _blocks.size()) {
        for (size_t i = _blocks.size(); i<=index; ++i) {
            _blocks.emplace_back(BlockType::AIR);
        }
    }

    _blocks[index] = type;
}