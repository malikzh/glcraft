cmake_minimum_required(VERSION 3.22)
project(glcraft)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DGLEW_STATIC)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(glcraft WIN32 main.cpp src/Window.cpp src/Window.hpp src/glcraft.hpp src/glcraft.cpp src/Scene.cpp src/Scene.hpp dependencies/stb_image.h dependencies/stb_image.c src/Chunk.cpp src/Chunk.hpp src/Shader.cpp src/Shader.hpp dependencies/linmath.h src/TextureManager.cpp src/TextureManager.hpp src/cube.cpp src/math/Matrix.cpp src/math/Matrix.hpp src/InputManager.cpp src/InputManager.hpp src/Camera.cpp src/Camera.hpp src/math/Vector.cpp src/math/Vector.hpp src/ChunkSection.cpp src/ChunkSection.hpp)
target_link_libraries(glcraft ${OPENGL_LIBRARIES} ${GLEW_STATIC_LIBRARIES})