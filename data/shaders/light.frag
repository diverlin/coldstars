#version 330 core

#define FRAG_OUTPUT0 0

struct Light
{
    vec3  position;
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec3  attenuation;
};

//struct Material
//{
    //vec4  ambient;
    //vec4  diffuse;
    //vec4  specular;
    //vec4  emission;
    //float shininess;
//};

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_Texture;
uniform Light u_Light;
//uniform Material u_Material;

in vec3 v_VertPos2lightPos_n; 
in vec3 v_VertPos2eyePos_n; 
in vec3 v_Normal_n;
in vec2 v_Texcoord;
 
void main (void)
{  	
    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    //vec3 r    = reflect(-vVertPos2eyePos_n, vNormal_n);
    	
    vec4 diffuse = u_Light.diffuse * max(0.0, dot(v_Normal_n, v_VertPos2lightPos_n));
    //vec4 spec = light.specular * pow(max(dot(v_VertPos2lightPos_n, r), 0.0), specPower);
    	 
    vec4 texel = texture2D(u_Texture, v_Texcoord);
 
   	color = (diffuse + u_Light.ambient) * texel;
}
