#define _USE_MATH_DEFINES
#include <cmath>
#include "../glcraft.hpp"

void terrain_generate_flat() {
    for (size_t i=0; i<100; ++i) {
        for (size_t j=0; j<100; ++j) {
            world->setBlock((int32_t)i-1, (int32_t)( 5.0f + floor(3.0f*cosf((float)i/3.0f) + sin(3.0f*cosf((float)j/3.0f)) ) ), (int32_t)j-1, BlockType::GRASS);
        }
    }
}