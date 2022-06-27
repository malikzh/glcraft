#include "glcraft.hpp"

void Chunk::setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type) {
    uint32_t section = y / sectionsSize;
    y %= sectionsSize;

    if (section >= sectionsSize) {
        return;
    }

    while (section >= _sections.size()) {
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

    size_t y = 0;

    for (ChunkSection& section : _sections) {
        if (section.empty()) {
            continue;
        }

        if (!section.mesh) {
            section.buildMesh();
        }

        mesh->add(section.mesh.get(), Matrix::translation(0.0f, (float)y, 0.0f).get());
        y+= sectionsSize;
    }
}

void Chunk::buffer() {
    if (!_vao) {
        glGenVertexArrays(1, &_vao);
    }

    glBindVertexArray(_vao);

    if (!_vbo) {
        glGenBuffers(1, &_vbo);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Vertices
    auto vertices = mesh->getVerticesArray();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->getVerticesArraySize(), vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Textures
    auto texcoords = mesh->getTexCoordArray();

    if (!_vbo2) {
        glGenBuffers(1, &_vbo2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh->getTexCoordArraySize(), texcoords.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Indices
    if (!_ebo) {
        glGenBuffers(1, &_ebo);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->indices.size(), mesh->indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    indicesSize = mesh->indices.size();
}

void Chunk::bindVao() {
    if (!_vao) {
        return;
    }

    glBindVertexArray(_vao);
}
