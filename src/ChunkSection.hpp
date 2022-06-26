//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_CHUNKSECTION_HPP
#define GLCRAFT_CHUNKSECTION_HPP


class ChunkSection {
public:
    static const int sectionSize = 16;

    void setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type);

private:
    std::vector<BlockType> _blocks;
    static size_t _positionToIndex(uint32_t x, uint32_t y, uint32_t z);
};


#endif //GLCRAFT_CHUNKSECTION_HPP
