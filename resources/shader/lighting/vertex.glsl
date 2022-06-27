#version 330 core
layout (location = 0) in vec4 aPos;

uniform mat4 projectionMatrix;

void main()
{
    vec4 pos =  projectionMatrix * aPos;

    gl_Position = pos.xyww;
}