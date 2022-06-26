//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_CHUNKSECTION_HPP
#define GLCRAFT_CHUNKSECTION_HPP


class ChunkSection {
public:
    static const int sectionSize = 16;

    std::unique_ptr<Mesh> mesh;

    void setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type);
    void buildMesh();

private:
    std::unordered_map<std::size_t, BlockType> _blocks;
    static size_t _positionToIndex(uint32_t x, uint32_t y, uint32_t z);
    static std::unique_ptr<uint32_t[]> _indexToPosition(size_t index);

};


#endif //GLCRAFT_CHUNKSECTION_HPP
