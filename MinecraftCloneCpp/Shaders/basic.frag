#version 460 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D texSampler1;
uniform sampler2D texSampler2;
uniform float alpha;

void main()
{
    FragColor = mix(texture(texSampler1, texCoords), texture(texSampler2, texCoords), alpha);
} 