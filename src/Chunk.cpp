#include "glcraft.hpp"

void Chunk::setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type) {
    uint32_t section = y / sectionsSize;
    y %= sectionsSize;

    if (section >= sectionsSize) {
        return;
    }

    if (section >= _sections.size()) {
        if (type == BlockType::AIR) {
            return;
        }

        _sections.emplace_back(ChunkSection());
    }

    ChunkSection* s = &_sections[section];

    s->setBlock(x, y, z, type);
}

void Chunk::buildMesh() {
    mesh = std::make_unique<Mesh>();

    for (ChunkSection& section : _sections) {
        if (!section.mesh) {
            section.buildMesh();
        }

        mesh->add(section.mesh.get());
    }
}