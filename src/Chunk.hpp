#ifndef GLCRAFT_CHUNK_HPP
#define GLCRAFT_CHUNK_HPP

struct Block {

};

class Chunk {
public:
    static const int size    = 16;
    static const int sectionsSize = 24;


    std::unique_ptr<Mesh> mesh;

    void setBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type);
    void buildMesh();
    void buffer();
    void render();

private:
    std::vector<ChunkSection> _sections;
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _vbo2 = 0;
    GLuint _ebo = 0;
    GLuint _indicesSize = 0;
};


#endif //GLCRAFT_CHUNK_HPP
