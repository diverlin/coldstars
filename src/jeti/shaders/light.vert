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
    vec2 texcoord;
    vec3 normal;
    vec3 lightDir; 
    vec3 eyeDir; 
    float attenuation;
} v_Vertex;

void main(void)
{
    vec4 vertexPos = u_Matrices.model * vec4(position, 1.0f);      
   gl_Position = u_Matrices.projectionView * vertexPos;

    v_Vertex.texcoord = texcoord;   
    v_Vertex.normal   = u_Matrices.normal * normal; 
    v_Vertex.lightDir = vertexPos.xyz - u_Light.position;              
    v_Vertex.eyeDir   = vertexPos.xyz - u_EyePos;   
    
    float distance = length(v_Vertex.lightDir);

    v_Vertex.attenuation = 1.0f / (u_Light.attenuation[0] +
                                   u_Light.attenuation[1] * distance +
                                   u_Light.attenuation[2] * distance * distance);
}


