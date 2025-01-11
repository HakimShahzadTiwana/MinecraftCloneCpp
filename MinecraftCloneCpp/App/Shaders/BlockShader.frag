#version 460 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D texSampler1;

void main()
{
    FragColor = texture(texSampler1, texCoords);
} 