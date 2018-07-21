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

float diffuse_factor(vec3 light_pos, vec3 normal) 
{
	light_pos = normalize(light_pos);
	float diffuse = max(dot(normal, light_pos), 0.0);  
	return diffuse;
}
	
void main (void)
{
	float dist = 1.0;
	float speed = 2.0;
	
	float lx = 1.0;
	float ly = 0.0;
	float lz = 0.0;
	vec3 light_pos = vec3(lx, ly, lz);
	vec3 light_pos2 = vec3(lx, ly, lz);
	
	light_pos.x = dist*sin(speed*u_time); // [-dist, dist]
	light_pos.y = dist*cos(speed*u_time); // [-dist, dist]

	light_pos2.x = -dist*sin(2*speed*u_time); // [-dist, dist]
	light_pos2.y = -dist*cos(2*speed*u_time); // [-dist, dist]
		
	// Extract color from color map  	  
	vec4 texel = texture2D(u_texture, v_texCoord.st); 
	
	// Extract the normal from the normal map 
	vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
	vec2 normal2 = v_rotateMat2 * normal.xy;
	normal = vec3(normal2, normal.z);	  
	
	// apply ambient component
	color = texel*u_ambientColor;

	// apply diffuse
	float diffuse = diffuse_factor(light_pos, normal);
	vec4 diffuseColor = vec4(0.0, 0.0, 1.0, 1.0);
	color += diffuse*texel*diffuseColor;

	float diffuse2 = diffuse_factor(light_pos2, normal);
	vec4 diffuseColor2 = vec4(1.0, 0.0, 0.0, 1.0);
	color += diffuse2*texel*diffuseColor2;
	
	// Set the output color of our current pixel  	
	color.a = texel.a;
}	
