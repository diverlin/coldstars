#version 330 core

#define FRAG_OUTPUT0 0

uniform sampler2D u_Texture;
uniform sampler2D u_Normalmap;

uniform struct Light {
    vec3  position;
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec3  attenuation;
} u_Light;

uniform struct Material {
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec4  emission;
    float shininess;
} u_Material;

in struct Vertex {
    vec2 texcoord;
    vec3 normal;
    vec3 lightDir_ts; 
    vec3 eyeDir_ts; 
    float attenuation;
} v_Vertex;

layout(location = FRAG_OUTPUT0) out vec4 color;

void main(void)
{  	
    vec3 lightDir_ts_n = (v_Vertex.lightDir_ts);
    vec3 eyeDir_ts_n   = (v_Vertex.eyeDir_ts);

    vec3 normaltex_n =  2.0 * normalize(texture2D(u_Normalmap, v_Vertex.texcoord).rgb) - 1.0; // Extract the normal from the normal map

    color  = u_Material.emission;
    color += u_Material.ambient * u_Light.ambient /** v_Vertex.attenuation*/;

    float NdotL = max(dot(normaltex_n, -lightDir_ts_n), 0.0);
    color += u_Material.diffuse * u_Light.diffuse * NdotL /** v_Vertex.attenuation*/;

    vec3 lightDirRefl = reflect(-lightDir_ts_n, normaltex_n);
    float RdotVpow = max(pow(dot(lightDirRefl, eyeDir_ts_n), u_Material.shininess), 0.0);
    color += u_Material.specular * u_Light.specular * RdotVpow /** v_Vertex.attenuation*/;

	vec4 orig_color = texture(u_Texture, v_Vertex.texcoord);
    color *= orig_color;
    color.a = orig_color.a;
}
