#include "../glcraft.hpp"

void terrain_generate_flat() {
    for (size_t i=0; i<100; ++i) {
        for (size_t j=0; j<100; ++j) {
            world->setBlock((int32_t)i - 50, 0, (int32_t)j - 50, BlockType::GRASS);
        }
    }
}