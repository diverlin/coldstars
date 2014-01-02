#version 330 core

#define FRAG_OUTPUT0 0

uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

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
    vec3 lightDir_ts; 
    vec3 eyeDir_ts; 
    float attenuation;
} v_Vertex;

layout(location = FRAG_OUTPUT0) out vec4 color;

void main(void)
{  	
    vec3 lightDir_ts_n = (v_Vertex.lightDir_ts);
    vec3 eyeDir_ts_n   = (v_Vertex.eyeDir_ts);

    vec4 texColor = texture2D(u_texture, v_Vertex.texcoord);
    
	vec3 normaltex_n = normalize(texture2D(u_normalmap, v_Vertex.texcoord).rgb * 2.0 - 1.0); // Extract the normal from the normal map  

    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	
    //vec3 r    = reflect(-v_VertPos2eyePos_n, v_Normal_n);
    	
    vec3 diff = u_Light.diffuse.xyz * max(0.0, dot(normaltex_n, -lightDir_ts_n));
    //vec4 spec = specColor * pow(0.0, max(0.0, dot(v_VertPos2lightPos_n, r)), specPower);
 
   	color = (vec4(diff, 1.0f) + u_Light.ambient) * texColor;
}
