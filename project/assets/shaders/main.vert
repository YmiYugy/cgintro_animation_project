#version 430 core
layout (location = 0) in vec4 aPos;

uniform mat4 projectionView;
uniform mat4 model;

out vec4 color;


void main()
{
    gl_Position = projectionView /** model*/ * aPos;
    color = vec4(0.3, 1.0, 0.2, 0.5);
}