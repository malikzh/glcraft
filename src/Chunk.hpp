#ifndef GLCRAFT_CHUNK_HPP
#define GLCRAFT_CHUNK_HPP

struct Block {

};

class Chunk {
public:
    static const int width    = 16;
    static const int length   = 16;
    static const int sections = 24;

    void setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type);

private:
    std::vector<ChunkSection> _sections;
};


#endif //GLCRAFT_CHUNK_HPP
