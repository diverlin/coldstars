/* shaders are taken from www.geeks3d.com/20091116/shader-library-2d-shockwave-post-processing-filter-glsl/ */

uniform sampler2D sceneTex;     /* texture unit 0 */
uniform vec2 center[10];        
uniform vec3 shockParams[10];   /* 10.0, 0.8, 0.1 */ 
uniform float time[10];         /* effect elapsed time */
uniform int distortion_num;     /* how many shaders */
 
void main()
{
	float diffTime = 0;
	vec2 diffUV;
	
  	vec2 uv = gl_TexCoord[0].xy;
  	vec2 texCoord = uv; 
   	for(int i=0; i<distortion_num; i++)
  	{
		float dist = distance(uv, center[i]);
		if ( (dist <= (time[i] + shockParams[i].z)) && (dist >= (time[i] - shockParams[i].z)) )
		{
			float diff = dist - time[i];
			float powDiff = 1.0 - pow(abs(diff*shockParams[i].x), shockParams[i].y);
			diffTime += diff  * powDiff;
			diffUV += normalize(uv - center[i]);
		}  	
	}
	
	texCoord = uv + (diffTime * diffUV); 
	gl_FragColor = texture2D(sceneTex, texCoord);
}
