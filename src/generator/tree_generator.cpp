#include "../glcraft.hpp"

void generate_tree(int32_t x, int32_t y, int32_t z) {

    // Ствол
    for (int32_t i=0; i<7; ++i) {
        world->setBlock(x, y++, z, BlockType::WOOD);
    }

    // Листва
    for (int32_t j = 0; j<=3; ++j) {
        for (int32_t i = -2 + j; i<=2 - j; ++i) {
            for (int32_t k = -3 + j; k<=3 - j; ++k) {
                world->setBlock(x + i, y + j, z + k, BlockType::LEAVES);
            }
        }
    }
}