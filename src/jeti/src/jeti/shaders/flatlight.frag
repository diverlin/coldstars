#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;
	
uniform mat4 u_modelMatrix;
uniform mat4 u_projectionViewMatrix;
uniform mat3 u_normalMatrix;
	
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;

uniform float u_time;

in vec2 v_texCoord;
in mat2 v_rotateMat2;

void main (void)
{
	float dist = 0.5;
	float speed = 10.5;

	float lx = 1.0;
	float ly = 0.0;
	float lz = 0.0;
	//lx = dist*sin(speed*u_time); // [-dist, dist]
	//ly = dist*cos(speed*u_time); // [-dist, dist]
	
	// Extract color from color map  	  
	vec4 texel = texture2D(u_texture, v_texCoord.st); 
	
	// Extract the normal from the normal map 
	//vec3 normal = vec3(0.0, 0.0, 1.0);
	vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
	vec2 normal2 = v_rotateMat2 * normal.xy;
	normal = vec3(normal2, normal.z);	  

	// Determine where the light is positioned (this can be set however you like)  
	vec3 light_pos = normalize(vec3(lx, ly, lz));
	
	// Calculate the lighting diffuse value  
	float diffuse = max(dot(normal, light_pos), 0.0);  

	float avr = (texel.r+texel.g+texel.b)/3.0;
	avr += 0.5;
	float shiniess_factor = 4.0;
	diffuse *= (shiniess_factor*avr*avr*avr);

	// apply ambient component
	color = texel*u_ambientColor;

	// apply diffuse
	color += diffuse*texel*u_diffuseColor;

	// Set the output color of our current pixel  	
	color.a = texel.a;
}	
