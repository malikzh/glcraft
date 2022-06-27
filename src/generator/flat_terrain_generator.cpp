#define _USE_MATH_DEFINES
#include <cmath>
#include "../glcraft.hpp"

void terrain_generate_flat() {
    for (size_t i=0; i<200; ++i) {
        for (size_t j=0; j<200; ++j) {
            int32_t y = (int32_t)( 10.0f + floor(3.0f*cosf((float)i/3.0f) + 3.0f*cosf((float)j/3.0f) ) );



            world->setBlock((int32_t)i-1, y, (int32_t)j-1, BlockType::GRASS);

            if (rand() % 200 == 0) {
                generate_tree(i, y, j);
            }
        }
    }
}