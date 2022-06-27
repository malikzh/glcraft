#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tx0;

void main()
{
    FragColor = texture(tx0, TexCoord).rgba;
}