#version 330 core

#define VERTEX_POSITION_LOCATION 0


uniform mat4 u_ModelMatrix;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;

void main(void)
{
    gl_Position = u_ModelMatrix * vec4(position, 1.0f);
}


