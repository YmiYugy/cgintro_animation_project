#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec4 Position;
out vec4 Normal;
out vec2 TexCoord;
out vec4 FragPosLightSpace;


uniform mat4 model;
uniform mat4 normalModel;
uniform mat4 projectionView;
uniform mat4 lightSpace;


void main()
{
    vec4 pos = model * aPos;
    gl_Position = projectionView * pos;
    Position = pos;
    Normal = normalModel * aNormal;
    TexCoord = aTexCoord;
    FragPosLightSpace = lightSpace * aPos;

}