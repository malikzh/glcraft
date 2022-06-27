#include "../glcraft.hpp"

void terrain_generate_flat() {
    for (size_t i=0; i<2; ++i) {
        for (size_t j=0; j<2; ++j) {
            world->setBlock((int32_t)i*16, (int32_t)0, (int32_t)j*16, BlockType::GRASS);
        }
    }
}