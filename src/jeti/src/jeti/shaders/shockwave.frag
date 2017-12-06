/* shaders are taken from www.geeks3d.com/20091116/shader-library-2d-shockwave-post-processing-filter-glsl/ */

#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

in vec2 v_Texcoord;
                            
uniform sampler2D u_Texture;
uniform vec2 center[10];        
uniform vec3 shockParams[10];   /* 10.0, 0.8, 0.1 */ 
uniform float time[10];         /* effect elapsed time */
uniform int distortion_num;     /* how many shaders */
 
void main()
{
	float diffTime = 0.0;
	vec2 diffUV;
	
   	for(int i=0; i<distortion_num; i++) {
		float dist = distance(v_Texcoord, center[i]);
		if ( (dist <= (time[i] + shockParams[i].z)) && (dist >= (time[i] - shockParams[i].z)) ) {
			float diff = dist - time[i];
			float powDiff = 1.0 - pow(abs(diff*shockParams[i].x), shockParams[i].y);
			diffTime += diff  * powDiff;
			diffUV += normalize(v_Texcoord - center[i]);
		}  	
	}

  	vec2 uv = v_Texcoord + (diffTime * diffUV);	
	color = texture2D(u_Texture, uv);
}
