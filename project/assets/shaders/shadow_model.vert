#version 430

layout (location = 0) in vec4 aPos;


uniform mat4 model;
uniform mat4 projView;


void main() {
    gl_Position = lightSpaceMatrix * model * aPos;
}