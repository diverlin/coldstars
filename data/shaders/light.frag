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
    vec2 texcoord;
    vec3 normal_n;
    vec3 lightDir_n; 
    vec3 eyeDir_n; 
    float attenuation;
} v_Vertex;
 
void main (void)
{  	
    color  = vec4(0.0f);//u_Material.emission;
    //color += u_Material.ambient * u_Light.ambient /** v_Vertex.attenuation*/;

    //float NdotL = max(dot(v_Vertex.normal_n, v_Vertex.lightDir_n), 0.0);
    //color += u_Material.diffuse * u_Light.diffuse * NdotL /** v_Vertex.attenuation*/;

    //float RdotVpow = max(pow(dot(-reflect(-v_Vertex.lightDir_n, v_Vertex.normal_n), v_Vertex.eyeDir_n), u_Material.shininess), 0.0);
    //color += u_Material.specular * u_Light.specular * RdotVpow /** v_Vertex.attenuation*/;

float specPower = 10.0f;
    vec3 r    = reflect(-v_Vertex.eyeDir_n, v_Vertex.normal_n);
    vec4 spec = u_Material.specular * u_Light.specular * pow(max(dot(v_Vertex.lightDir_n, r), 0.0), specPower);

    color *= texture(u_Texture, v_Vertex.texcoord);
}



    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    //vec3 r    = reflect(-vVertPos2eyePos_n, vNormal_n);
    	
    //vec4 diffuse = u_Light.diffuse * max(0.0, dot(v_Vertex.normal_n, v_Vertex.lightDir_n));
    //vec4 spec = light.specular * pow(max(dot(v_VertPos2lightPos_n, r), 0.0), specPower);
    	 
    //vec4 texel = texture2D(u_Texture, v_Vertex.texcoord);
