#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 pos;
layout (location = 2) in vec4 dir;

out vec4 color;
uniform mat4 projectionView;


void main()
{
    vec3 v = cross(vec3(1.0f, 0.0f, 0.0f), dir.xyz);
    vec3 u = v/length(v);
    float c = dot(vec3(1.0f, 0.0f, 0.0f), dir.xyz);
    float h = (1-c)/(1-c*c);
    mat3 rot = mat3(
    c+h*v.x*v.x, h*v.x*v.y+v.z, h*v.x*v.z-v.y,
    h*v.x*v.y-v.z, c+h*v.y*v.y, h*v.y*v.z+v.x,
    h*v.x*v.z+v.y, h*v.y*v.z-v.x, c+h*v.z*v.z
    );

    gl_Position = projectionView * vec4(rot*aPos.xyz + pos.xyz, 1.0f);
    color = vec4(0.5, 0.1, 0.2, 1.0);
}