#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aNormal;

uniform mat4 worldMatrix;
uniform mat4 viewProjectionMatrix;
uniform vec4 sunPosition;

out vec2 TexCoord;
out float brightness;

void main()
{
    brightness = 0.0f;//dot(normalize(sunPosition.xyz - aPos.xyz), );

    gl_Position = viewProjectionMatrix * worldMatrix * aPos;
    TexCoord = aTexCoord;
}