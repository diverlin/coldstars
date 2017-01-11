#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionViewMatrix;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_COLOR_LOCATION) in vec4 color;

out vec4 v_color;
 
void main(void)
{
    vec4 vertexPos = u_ModelMatrix * vec4(position, 1.0f);      
    gl_Position = u_ProjectionViewMatrix * vertexPos; 

    v_color = color;                                                         
}


