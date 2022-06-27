#include "glcraft.hpp"

std::unordered_map<BlockType, BlockTexture> blockTexture = {
        {
            BlockType::GRASS,
            BlockTexture{
                .front = 1,
                .back = 1,
                .left = 1,
                .right = 1,
                .top = 0,
                .bottom = 2,
            },
        },
};