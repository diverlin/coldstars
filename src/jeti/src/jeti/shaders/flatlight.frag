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

/*
uniform vec4 u_light3_diffuse;
uniform vec3 u_light3_dir;
uniform float u_light3_attenuation;

uniform vec4 u_light4_diffuse;
uniform vec3 u_light4_dir;
uniform float u_light4_attenuation;

uniform vec4 u_light5_diffuse;
uniform vec3 u_light5_dir;
uniform float u_light5_attenuation;

uniform vec4 u_light6_diffuse;
uniform vec3 u_light6_dir;
uniform float u_light6_attenuation;

uniform vec4 u_light7_diffuse;
uniform vec3 u_light7_dir;
uniform float u_light7_attenuation;
*/

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
/*
	float factor3 = diffuse_factor(u_light3_dir, u_light3_attenuation, normal);
	color += factor3*texel*u_light3_diffuse;

	float factor4 = diffuse_factor(u_light4_dir, u_light4_attenuation, normal);
	color += factor4*texel*u_light4_diffuse;

	float factor5 = diffuse_factor(u_light5_dir, u_light5_attenuation, normal);
	color += factor5*texel*u_light5_diffuse;
			
	float factor6 = diffuse_factor(u_light6_dir, u_light6_attenuation, normal);
	color += factor6*texel*u_light6_diffuse;

	float factor7 = diffuse_factor(u_light7_dir, u_light7_attenuation, normal);
	color += factor7*texel*u_light7_diffuse;
*/
	
	// Set the output color of our current pixel  	
	color.a = texel.a;
	
	fragColor = color;
}	
