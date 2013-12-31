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

out vec3 v_VertPos2lightPos_n; 
out vec3 v_VertPos2eyePos_n; 
out vec3 v_Normal_n;
out vec2 v_Texcoord;

struct Color
{
    vec4  position;
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec3  attenuation;
};
 
void main(void)
{
    vec4 vertexPos = u_ModelMatrix * vec4(position, 1.0f);      
    gl_Position = u_ProjectionViewMatrix * vertexPos; 

    v_Normal_n     = normalize(u_NormalModelMatrix * normal);   
        
    v_VertPos2lightPos_n = normalize(u_LightPos - vertexPos.xyz);              
    v_VertPos2eyePos_n   = normalize(u_EyePos   - vertexPos.xyz);                              

    v_Texcoord = texcoord;                                                         
}


