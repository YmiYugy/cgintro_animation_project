#version 430 core
out vec3 FragColor;
in vec2 UV;

uniform sampler2D textureSampler;

void main()
{
    FragColor = texture(textureSampler, UV).rgb;

}