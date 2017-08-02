#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1

uniform mat4 u_ModelMatrix;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texcoord;

out vec2 v_texCoord;

void main(void)
{
    gl_Position = u_ModelMatrix * vec4(position, 1.0f);
    v_texCoord = texcoord;
}


