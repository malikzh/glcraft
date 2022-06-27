#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projectionMatrix;

out vec2 TexCoord;

void main()
{
    gl_Position = projectionMatrix * aPos;
    TexCoord = aTexCoord;
}