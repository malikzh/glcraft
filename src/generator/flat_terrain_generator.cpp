#include "../glcraft.hpp"

void terrain_generate_flat() {
    for (size_t i=0; i<10; ++i) {
        for (size_t j=0; j<10; ++j) {
            world->setBlock((int32_t)i - 5, 0, (int32_t)j - 5, BlockType::GRASS);
        }
    }
}