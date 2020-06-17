#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 modelView;

uniform mat4 projection;


void main()
{
    gl_Position = projection * modelView * vec4(aPos, 1.0f);
}