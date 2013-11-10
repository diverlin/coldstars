#version 330 core

#define VERT_POSITION 0
#define VERT_TEXCOORD 1
#define VERT_NORMAL   2

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionViewMatrix;
uniform mat3 u_NormalModelMatrix;

uniform vec3 u_LightPos;
uniform vec3 u_EyePos;

layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;
layout(location = VERT_NORMAL)   in vec3 normal;

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


