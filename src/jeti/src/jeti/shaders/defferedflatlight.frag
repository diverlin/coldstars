#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 fragColor;
	
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_light_ambient;

uniform vec4 u_light0_diffuse;
uniform vec3 u_light0_position;
uniform float u_light0_radius;


uniform vec4 u_light1_diffuse;
uniform vec3 u_light1_position;
uniform float u_light1_radius;

uniform vec4 u_light2_diffuse;
uniform vec3 u_light2_position;
uniform float u_light2_radius;

in vec2 v_texCoord;

float attenuationFactor(float distance, float radius)
{
    return max(1.0-pow(distance/radius, 2), 0.0);
}

float diffuse_factor(vec3 light_pos, float radius, vec3 normal) 
{
	float ratio = 768.0/1024;
	//light_pos.y /= ratio;
	vec2 light_dir2 = light_pos.xy - (v_texCoord.st - vec2(0.5, 0.5));
	light_dir2.y *= ratio;
	vec3 light_dir = vec3(light_dir2, 0.1);
	
	float distance = length(light_dir);
	//return distance;
		
	float diffuse = dot(normal, normalize(light_dir));
	diffuse = max(diffuse, 0.0);
	diffuse *= attenuationFactor(distance, radius);
	return diffuse;
}
	
void main (void)
{
	bool debug = false;
	
	if (!debug) {
		// Extract color from color map  	  
		vec4 texel = texture2D(u_texture, v_texCoord.st); 
		
		// Extract the normal from the normal map 
		vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
		
		// apply ambient component
		vec4 color = texel*u_light_ambient;

		// apply diffuse components
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
		color += factor0*texel*u_light0_diffuse;

		float factor1 = diffuse_factor(u_light1_position, u_light1_radius, normal);
		color += factor1*texel*u_light1_diffuse;

		float factor2 = diffuse_factor(u_light2_position, u_light2_radius, normal);
		color += factor2*texel*u_light2_diffuse;
		
		// Set the output color of our current pixel  	
		color.a = texel.a;

		fragColor = color;
	} else {
		vec3 normal = vec3(0.0, 0.0, 1.0);
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
		
		fragColor = vec4(factor0);
		fragColor.a = 1.0;
	}
	

}	
