//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_WORLD_HPP
#define GLCRAFT_WORLD_HPP

struct ChunkPairHasher {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return hash_combine(h1, h2);
    }
};

class World {
public:
    World();
    void setBlock(int32_t x, int32_t y, int32_t z, BlockType type);
    void buildMesh();
    void buffer();
    void render();

private:
    std::unordered_map<std::pair<int32_t, int32_t>, Chunk, ChunkPairHasher> _chunks;
    std::unique_ptr<Shader> _shader;
};


#endif //GLCRAFT_WORLD_HPP
