#include "glcraft.hpp"

std::unordered_map<BlockType, BlockTexture> blockTexture = {
        {
            BlockType::GRASS,
            BlockTexture{
                .front = 0,
                .back = 0,
                .left = 0,
                .right = 0,
                .top = 0,
                .bottom = 0,
            },
        },
};