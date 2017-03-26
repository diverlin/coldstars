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
    vec3 lightDir_ts; 
    vec3 eyeDir_ts; 
    float attenuation;
} v_Vertex;
 
void main(void)
{
    vec4 vertexPos = u_Matrices.model * vec4(position, 1.0f);      
    gl_Position = u_Matrices.projectionView * vertexPos;      
      
    v_Vertex.texcoord = texcoord; 
    v_Vertex.normal = u_Matrices.normal * normal;                            
   	vec3 lightDir = vertexPos.xyz - u_Light.position;              
    vec3 eyeDir   = vertexPos.xyz - u_EyePos; 

    // tangent space
    vec3 tangent;
    vec3 v1 = cross(normal, vec3(0.0, 0.0, 1.0));
    vec3 v2 = cross(normal, vec3(0.0, 1.0, 0.0));
    
    if(length(v1)>length(v2)) tangent=v1;
    else                      tangent=v2;
    
    vec3 n = normalize(u_Matrices.normal * normal);
    vec3 t = normalize(u_Matrices.normal * tangent);
    vec3 b = cross(n,t);
    mat3 tangent_mat = mat3(t.x, b.x, n.x, t.y, b.y, n.y, t.z, b.z, n.z);
    
    v_Vertex.lightDir_ts = normalize(tangent_mat * lightDir);
    v_Vertex.eyeDir_ts   = normalize(tangent_mat * eyeDir); 
}


