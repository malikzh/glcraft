#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float brightness;

uniform sampler2D tx0;

void main()
{
    vec4 color = texture(tx0, TexCoord).rgba;

    FragColor = color;
}