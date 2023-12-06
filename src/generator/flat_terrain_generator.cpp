#define _USE_MATH_DEFINES
#include <cmath>
#include "../glcraft.hpp"

void terrain_generate_flat() {
    long X = 8;
    for (size_t i=0; i<150; ++i) {
        for (size_t j=0; j<150; ++j) {
            int32_t y = (int32_t)( 10.0f + floor(3.0f*cosf((float)i/3.0f) + 3.0f*cosf((float)j/3.0f) ) );


            world->setBlock((int32_t)i-1, y, (int32_t)j-1, BlockType::GRASS);

            X = (1103515245 * X + 12345) % 65536;

            if (X  % 107 == 0) {
                generate_tree(i, y, j);
            }
        }
    }
}