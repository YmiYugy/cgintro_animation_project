#version 430 core
layout (location = 0) in vec4 aPos;

uniform mat4 projectionView;

out vec4 color;

void main()
{
    gl_Position = projectionView * aPos;
    if (gl_VertexID == 0) {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        color = vec4(0.5, 0.1, 0.2, 1.0);
    }
}