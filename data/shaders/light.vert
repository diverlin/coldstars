#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform struct Matrices
{
    mat4 model;
    mat4 projectionView;
    mat3 normal;
} u_Matrices;

uniform vec3 u_EyePos;

uniform struct Light
{
    vec3  position;
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec3  attenuation;
} u_Light;

uniform struct Material
{
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec4  emission;
    float shininess;
} u_Material;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texcoord;
layout(location = VERTEX_NORMAL_LOCATION)   in vec3 normal;

out struct Vertex
{
    vec3 normal_n;
    vec2 texcoord;
    vec3 lightDir_n; 
    vec3 eyeDir_n; 
} v_Vertex;

void main(void)
{
    vec4 vertexPos = u_Matrices.model * vec4(position, 1.0f);      
    gl_Position    = u_Matrices.projectionView * vertexPos; 

    v_Vertex.normal_n   = normalize(u_Matrices.normal * normal);   
    v_Vertex.texcoord   = texcoord;           
    v_Vertex.lightDir_n = normalize(u_Light.position - vertexPos.xyz);              
    v_Vertex.eyeDir_n   = normalize(u_EyePos         - vertexPos.xyz);   
}


