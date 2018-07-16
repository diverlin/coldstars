#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;
	
uniform mat4 u_modelMatrix;
uniform mat4 u_projectionViewMatrix;
	
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_color;

uniform float u_time;

in vec2 v_texCoord;

void main (void)
{
	float dist = 0.5;
	float speed = 10.5;

	float lx = 1.0;
	float ly = 0.0;
	float lz = 1.0;
	//lx = dist*sin(speed*u_time); // [-dist, dist]
	//ly = dist*cos(speed*u_time); // [-dist, dist]
	
	// Extract color from color map  	  
	vec3 texel = texture2D(u_texture, v_texCoord.st).rgb; 
	
	// Extract the normal from the normal map 
	vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);  
	  
	// Determine where the light is positioned (this can be set however you like)  
	vec3 light_pos = normalize(vec3(lx, ly, lz));  
	  
	// Calculate the lighting diffuse value  
	float diffuse = max(dot(normal, light_pos), 0.0);  

	float avr = (texel.r+texel.g+texel.b)/3;
	diffuse *= (10*avr);

	// apply ambient component
	vec3 color3 = 0.4*texel;

	// apply diffuse
	color3 += diffuse*texel;

	// Set the output color of our current pixel  	
	float a = texture2D(u_texture, v_texCoord.st).a;
	color = vec4(color3, a);
}	
