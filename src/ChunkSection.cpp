#include "glcraft.hpp"

size_t ChunkSection::_positionToIndex(uint32_t x, uint32_t y, uint32_t z) {
    return sectionSize*sectionSize*y + sectionSize*z + x;
}

void ChunkSection::setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type) {
    std::size_t index = _positionToIndex(x, y, z);
    _blocks.insert(std::make_pair(index, type));
}

void ChunkSection::buildMesh() {
    mesh = std::make_unique<Mesh>();

    for (size_t index = 0; index<_blocks.size(); ++index) {
        auto pos = _indexToPosition(index);

        if (_blocks[index] == BlockType::AIR || (uint8_t)_blocks[index] == 255) {
            continue;
        }

        auto faces = blockTexture[_blocks[index]];

        std::unique_ptr<Mesh> frontFace = cube_createFrontMesh(*texman->getCoord(faces.front));
        std::unique_ptr<Mesh> backFace = cube_createBackMesh(*texman->getCoord(faces.back));
        std::unique_ptr<Mesh> leftFace = cube_createLeftMesh(*texman->getCoord(faces.left));
        std::unique_ptr<Mesh> rightFace = cube_createRightMesh(*texman->getCoord(faces.right));
        std::unique_ptr<Mesh> topFace = cube_createTopMesh(*texman->getCoord(faces.top));
        std::unique_ptr<Mesh> bottomFace = cube_createBottomMesh(*texman->getCoord(faces.bottom));

        auto m = Matrix::translation((float)pos[0], (float)pos[1], (float)pos[2]);

        mesh->add(frontFace.get(), m.get());
        mesh->add(backFace.get(), m.get());
        mesh->add(leftFace.get(), m.get());
        mesh->add(rightFace.get(), m.get());
        mesh->add(topFace.get(), m.get());
        mesh->add(bottomFace.get(), m.get());
    }
}


std::unique_ptr<uint32_t[]> ChunkSection::_indexToPosition(size_t index) {
    auto pos = std::make_unique<uint32_t[]>(3);

    size_t sectionArea = sectionSize * sectionSize;


    pos[1] = index / sectionArea;
    pos[2] = (index - (pos[1] * sectionArea)) / sectionSize;
    pos[0] = index - (pos[1] * sectionArea) - (pos[2] *sectionSize);

    return pos;
}

bool ChunkSection::empty() {
    return _blocks.empty();
}