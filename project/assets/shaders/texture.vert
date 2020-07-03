#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 vertexUV;

uniform mat4 projectionView;
uniform mat4 model;

out vec2 UV;


void main()
{
    gl_Position = projectionView /** model*/ * aPos;
    UV = vertexUV;
}