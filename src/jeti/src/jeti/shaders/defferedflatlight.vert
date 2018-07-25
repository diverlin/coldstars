#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform mat4 u_modelMatrix;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texCoord;

out vec2 v_texCoord;
 
void main(void)
{
    gl_Position = u_modelMatrix * vec4(position, 1.0f);

    v_texCoord = texCoord;
}


