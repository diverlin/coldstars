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

uniform vec4 u_light1_diffuse;
uniform vec3 u_light1_position;
uniform float u_light1_radius;

uniform vec4 u_light2_diffuse;
uniform vec3 u_light2_position;
uniform float u_light2_radius;

uniform vec4 u_light3_diffuse;
uniform vec3 u_light3_position;
uniform float u_light3_radius;

uniform vec4 u_light4_diffuse;
uniform vec3 u_light4_position;
uniform float u_light4_radius;

uniform vec4 u_light5_diffuse;
uniform vec3 u_light5_position;
uniform float u_light5_radius;

uniform vec4 u_light6_diffuse;
uniform vec3 u_light6_position;
uniform float u_light6_radius;

uniform vec4 u_light7_diffuse;
uniform vec3 u_light7_position;
uniform float u_light7_radius;

uniform vec4 u_light8_diffuse;
uniform vec3 u_light8_position;
uniform float u_light8_radius;

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
		mat3 nm = transpose(inverse(mat3(u_modelMatrix)));
		vec3 n = normalize(vec3(0.0, 1.0, 0.0));

		vec3 Normal = normalize(nm * n);
		vec3 Tangent = normalize(nm[0]); 
		vec3 Binormal = normalize(nm[1]);
		mat3 tangentToWorld = mat3(Tangent.x, Binormal.x, Normal.x,
				           Tangent.y, Binormal.y, Normal.y,
				           Tangent.z, Binormal.z, Normal.z);

		//vec3 Normal = normalize(gl_NormalMatrix * gl_Normal);
		//vec3 Tangent = normalize(gl_NormalMatrix[0]); 
		//vec3 Binormal = normalize(gl_NormalMatrix[1]);
		//mat3 tangentToWorld = mat3(Tangent.x, Binormal.x, Normal.x,
		//		           Tangent.y, Binormal.y, Normal.y,
		//		           Tangent.z, Binormal.z, Normal.z);

		// Extract color from color map  	  
		vec4 texel = texture2D(u_texture, v_texCoord.st); 
		
		// Extract the normal from the normal map 
		//vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0);
		vec3 normal = normalize(texture2D(u_normalmap, v_texCoord.st).rgb * 2.0 - 1.0) * tangentToWorld;

		// apply ambient component
		vec3 lcolor = u_light_ambient.rgb;

		// apply diffuse components
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
		float factor1 = diffuse_factor(u_light1_position, u_light1_radius, normal);
		float factor2 = diffuse_factor(u_light2_position, u_light2_radius, normal);
		float factor3 = diffuse_factor(u_light3_position, u_light3_radius, normal);
		float factor4 = diffuse_factor(u_light4_position, u_light4_radius, normal);
		float factor5 = diffuse_factor(u_light5_position, u_light5_radius, normal);
		float factor6 = diffuse_factor(u_light6_position, u_light6_radius, normal);
		float factor7 = diffuse_factor(u_light7_position, u_light7_radius, normal);
		float factor8 = diffuse_factor(u_light8_position, u_light8_radius, normal);
																
		lcolor += factor0*u_light0_diffuse.rgb;
		lcolor += factor1*u_light1_diffuse.rgb;
		lcolor += factor2*u_light2_diffuse.rgb;
		lcolor += factor3*u_light3_diffuse.rgb;
		lcolor += factor4*u_light4_diffuse.rgb;
		lcolor += factor5*u_light5_diffuse.rgb;
		lcolor += factor6*u_light6_diffuse.rgb;
		lcolor += factor7*u_light7_diffuse.rgb;
		lcolor += factor8*u_light8_diffuse.rgb;
				
		lcolor *= texel.rgb;
												
		fragColor = vec4(lcolor, texel.a);

	} else {
		vec3 normal = normalize(vec3(0.0, 0.0, 1.0));
		
		vec3 lcolor = vec3(0.0, 0.0, 0.0);
		
		float factor0 = diffuse_factor(u_light0_position, u_light0_radius, normal);
		float factor1 = diffuse_factor(u_light1_position, u_light1_radius, normal);
		float factor2 = diffuse_factor(u_light2_position, u_light2_radius, normal);
		float factor3 = diffuse_factor(u_light3_position, u_light3_radius, normal);
		float factor4 = diffuse_factor(u_light4_position, u_light4_radius, normal);
		float factor5 = diffuse_factor(u_light5_position, u_light5_radius, normal);
		float factor6 = diffuse_factor(u_light6_position, u_light6_radius, normal);
		float factor7 = diffuse_factor(u_light7_position, u_light7_radius, normal);									
		float factor8 = diffuse_factor(u_light8_position, u_light8_radius, normal);
		
		lcolor += factor0*u_light0_diffuse.rgb;
		lcolor += factor1*u_light1_diffuse.rgb;
		lcolor += factor2*u_light2_diffuse.rgb;
		lcolor += factor3*u_light3_diffuse.rgb;
		lcolor += factor4*u_light4_diffuse.rgb;
		lcolor += factor5*u_light5_diffuse.rgb;
		lcolor += factor6*u_light6_diffuse.rgb;
		lcolor += factor7*u_light7_diffuse.rgb;
		lcolor += factor8*u_light8_diffuse.rgb;
																
		fragColor = vec4(lcolor, 1.0);
	}	

}	
