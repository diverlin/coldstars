#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 fragColor;
	
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_light_ambient;
uniform float u_screenRatio;

uniform vec4 u_light0_diffuse;
uniform vec3 u_light0_position;
uniform float u_light0_radius;

uniform mat4 u_modelMatrix;

in vec2 v_texCoord;

float attenuationFactor(float distance, float radius)
{
    return max(1.0-pow(distance/radius, 2), 0.0);
}

float diffuse_factor(vec3 light_pos, float radius, vec3 normal) 
{
	vec2 light_dir2 = light_pos.xy - (v_texCoord.st - vec2(0.5, 0.5));
	light_dir2.y *= u_screenRatio;
	vec3 light_dir = vec3(light_dir2, 0.0);
	
	float distance = length(light_dir);
		
	float diffuse = dot(normal, normalize(light_dir));
	diffuse = max(diffuse, 0.0);
	diffuse *= attenuationFactor(distance, radius);
	return diffuse;
}
	
void main (void)
{
	bool debug = false;
	
	if (!debug) {
		//mat3 nm = transpose(inverse(mat3(u_modelMatrix)));
		//vec3 n = normalize(vec3(0.0, 1.0, 0.0));

		//vec3 Normal = normalize(nm * n);
		//vec3 Tangent = normalize(nm[0]); 
		//vec3 Binormal = normalize(nm[1]);
		//mat3 tangentToWorld = mat3(Tangent.x, Binormal.x, Normal.x,
				           //Tangent.y, Binormal.y, Normal.y,
				           //Tangent.z, Binormal.z, Normal.z);

		//vec3 Normal = normalize(gl_NormalMatrix * gl_Normal);
		//vec3 Tangent = normalize(gl_NormalMatrix[0]); 
		//vec3 Binormal = normalize(gl_NormalMatrix[1]);
		//mat3 tangentToWorld = mat3(Tangent.x, Binormal.x, Normal.x,
		//		           Tangent.y, Binormal.y, Normal.y,
		//		           Tangent.z, Binormal.z, Normal.z);

		// Extract color from color map  	  
		vec4 texel = texture2D(u_texture, v_texCoord.st); 
		
		// Extract the normal from the normal map 
		vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
		//vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0) * tangentToWorld;
		//normal.y *= -1;

		// apply ambient component
		vec3 lcolor = vec3(0.1, 0.1, 0.1); //u_light_ambient.rgb;

		// apply diffuse components
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
																
		lcolor += factor0*u_light0_diffuse.rgb;
				
		lcolor *= texel.rgb;
												
		fragColor = vec4(lcolor, texel.a);

	} else {
		vec3 normal = normalize(vec3(0.0, 0.0, 1.0));
		
		vec3 lcolor = vec3(0.0, 0.0, 0.0);
		
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
		
		lcolor += factor0*u_light0_diffuse.rgb;
																
		fragColor = vec4(lcolor, 1.0);
	}	

}	
