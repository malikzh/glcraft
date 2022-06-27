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
        {
                BlockType::WOOD,
                BlockTexture{
                        .front = 3,
                        .back = 3,
                        .left = 3,
                        .right = 3,
                        .top = 3,
                        .bottom = 3,
                },
        },
        {
                BlockType::LEAVES,
                BlockTexture{
                        .front = 4,
                        .back = 4,
                        .left = 4,
                        .right = 4,
                        .top = 4,
                        .bottom = 4,
                },
        },
};