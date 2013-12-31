#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

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
    vec3 normal_n;
    vec2 texcoord;
    vec3 lightDir_n; 
    vec3 eyeDir_n; 
} v_Vertex;
 
void main (void)
{  	
    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    //vec3 r    = reflect(-vVertPos2eyePos_n, vNormal_n);
    	
    vec4 diffuse = u_Light.diffuse * max(0.0, dot(v_Vertex.normal_n, v_Vertex.lightDir_n));
    //vec4 spec = light.specular * pow(max(dot(v_VertPos2lightPos_n, r), 0.0), specPower);
    	 
    vec4 texel = texture2D(u_Texture, v_Vertex.texcoord);
 
   	color = (diffuse + u_Light.ambient) * texel;
}
