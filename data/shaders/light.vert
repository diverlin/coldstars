#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionViewMatrix;
uniform mat3 u_NormalModelMatrix;

uniform vec3 u_LightPos;
uniform vec3 u_EyePos;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texcoord;
layout(location = VERTEX_NORMAL_LOCATION)   in vec3 normal;

out vec3 vVert2light_n; 
out vec3 vVert2eye_n; 
out vec3 vNormal_n;
out vec2 vTexcoord;
 
void main(void)
{
    vec4 vertexPos = u_ModelMatrix * vec4(position, 1.0f);      /* transformed vertex to world space */ 
    gl_Position = u_ProjectionViewMatrix * vertexPos; 
        
    vVert2light_n = normalize(u_LightPos - vertexPos.xyz);              
    vVert2eye_n   = normalize(u_EyePos   - vertexPos.xyz);                              
    vNormal_n     = normalize(u_NormalModelMatrix * normal);   

    vTexcoord = texcoord;                                                         
}


