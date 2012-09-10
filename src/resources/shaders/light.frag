/* http://www.gamedev.ru/code/forum/?id=90743 */

uniform sampler2D Texture_0;
varying vec3 l, v, n;
 
void main (void)
{
    	const vec4  diffColor = vec4(1.0, 1.0, 1.0, 1.0);
    	const vec4  ambientColor = vec4(0.1, 0.1, 0.1, 1.0);
    	const vec4  specColor = vec4(0.7, 0.7, 0.0, 0.0);
    	const float specPower = 30.0;
 
    	vec3 n2   = normalize(n);
    	vec3 l2   = normalize(l);
    	vec3 v2   = normalize(v);
    	vec3 r    = reflect(-v2, n2);
    	vec4 diff = diffColor * max(dot(n2, l2), 0.0);
    	vec4 spec = specColor * pow(max(dot(l2, r), 0.0), specPower);
    	vec2 texCoord0 = gl_TexCoord[0].xy;
    	vec4 texColor0 = texture2D(Texture_0, texCoord0);
 
   	 gl_FragColor = (diff + ambientColor) * texColor0;
}
