#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 viewProjectionMatrix;

out vec2 TexCoord;

void main()
{
    gl_Position = viewProjectionMatrix * aPos;
    TexCoord = aTexCoord;
}