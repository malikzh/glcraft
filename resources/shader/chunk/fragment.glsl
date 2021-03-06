#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float brightness;

uniform sampler2D tx0;

void main()
{
    vec4 color = texture(tx0, TexCoord).rgba;

    color.rgb *= 0.6f + (0.4f * brightness);

    FragColor = color;
}