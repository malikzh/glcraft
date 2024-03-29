cmake_minimum_required(VERSION 3.22)
project(glcraft)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DGLEW_STATIC)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(glcraft WIN32 main.cpp src/Window.cpp src/Window.hpp src/glcraft.hpp src/glcraft.cpp src/Scene.cpp src/Scene.hpp dependencies/stb_image.h dependencies/stb_image.c src/Chunk.cpp src/Chunk.hpp src/Shader.cpp src/Shader.hpp src/TextureManager.cpp src/TextureManager.hpp src/cube.cpp src/math/Matrix.cpp src/math/Matrix.hpp src/InputManager.cpp src/InputManager.hpp src/Camera.cpp src/Camera.hpp src/math/Vector.cpp src/math/Vector.hpp src/ChunkSection.cpp src/ChunkSection.hpp src/World.cpp src/World.hpp src/util.cpp src/generator/flat_terrain_generator.cpp src/blocks.cpp src/Mesh.cpp src/Lighting.cpp src/Lighting.hpp src/generator/tree_generator.cpp
        src/Player.cpp
        src/Player.hpp
        src/Network.cpp
        src/Network.hpp)
target_link_libraries(glcraft ${OPENGL_LIBRARIES} ${GLEW_STATIC_LIBRARIES} GLEW::GLEW glfw)