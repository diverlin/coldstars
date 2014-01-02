#version 330 core

#define FRAG_OUTPUT0 0

uniform sampler2D u_Texture;

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

in struct Vertex
{
    vec2 texcoord;
    vec3 normal;
    vec3 lightDir; 
    vec3 eyeDir; 
    float attenuation;
} v_Vertex;
 
layout(location = FRAG_OUTPUT0) out vec4 color;

void main (void)
{  	
    vec3 normal_n   = normalize(v_Vertex.normal); 
    vec3 lightDir_n = normalize(v_Vertex.lightDir);  
    vec3 eyeDir_n   = normalize(v_Vertex.eyeDir); 

    color  = u_Material.emission;
    color += u_Material.ambient * u_Light.ambient /** v_Vertex.attenuation*/;

    float NdotL = max(dot(normal_n, -lightDir_n), 0.0);
    color += u_Material.diffuse * u_Light.diffuse * NdotL /** v_Vertex.attenuation*/;

    vec3 lightDirRefl = reflect(-lightDir_n, normal_n);
    float RdotVpow = max(pow(dot(lightDirRefl, eyeDir_n), u_Material.shininess), 0.0);
    color += u_Material.specular * u_Light.specular * RdotVpow /** v_Vertex.attenuation*/;

    color *= texture(u_Texture, v_Vertex.texcoord);
}


