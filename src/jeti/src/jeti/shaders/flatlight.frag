#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 fragColor;
	
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_light_ambient;

uniform vec4 u_light0_diffuse;
uniform vec3 u_light0_dir;
uniform float u_light0_attenuation;

uniform vec4 u_light1_diffuse;
uniform vec3 u_light1_dir;
uniform float u_light1_attenuation;

uniform vec4 u_light2_diffuse;
uniform vec3 u_light2_dir;
uniform float u_light2_attenuation;

in vec2 v_texCoord;
in mat2 v_rotateMat2;

float diffuse_factor(vec3 light_dir, float attenuation, vec3 normal) 
{
	float diffuse = dot(normal, normalize(light_dir));
	diffuse = max(diffuse, 0.0);
	diffuse *= attenuation;
	return diffuse;
}
	
void main (void)
{
	// Extract color from color map  	  
	vec4 texel = texture2D(u_texture, v_texCoord.st); 
	
	// Extract the normal from the normal map 
	vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
	vec2 normal2 = v_rotateMat2 * normal.xy;
	normal = vec3(normal2, normal.z);	  
	
	// apply ambient component
	vec4 color = texel*u_light_ambient;

	// apply diffuse components
	float factor0 = diffuse_factor(u_light0_dir, u_light0_attenuation, normal);
	color += factor0*texel*u_light0_diffuse;

	float factor1 = diffuse_factor(u_light1_dir, u_light1_attenuation, normal);
	color += factor1*texel*u_light1_diffuse;

	float factor2 = diffuse_factor(u_light2_dir, u_light2_attenuation, normal);
	color += factor2*texel*u_light2_diffuse;
		
	// Set the output color of our current pixel  	
	color.a = texel.a;
	
	fragColor = color;
}	
