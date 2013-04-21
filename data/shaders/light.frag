/* http://www.gamedev.ru/code/forum/?id=90743 */

uniform sampler2D Texture_0;
uniform vec4 diffColor, ambientColor;
varying vec3 vertex2light_n, vertex2eye_n, normal_n;
 
void main (void)
{
    	/*const vec4 diffColor    = vec4(1.0, 1.0, 1.0, 1.0);*/
    	/*const vec4 ambientColor = vec4(0.2, 0.2, 0.2, 1.0); */
    	/*const vec4 specColor    = vec4(0.7, 0.7, 0.0, 1.0); */
    	/*const float specPower    = 30.0;*/
    	
    	vec3 r    = reflect(-vertex2eye_n, normal_n);
    	vec4 diff = diffColor * max(dot(normal_n, vertex2light_n), 0.0);
    	/*vec4 spec = specColor * pow(max(dot(vertex2light_n, r), 0.0), specPower); */
    	vec4 texColor0 = texture2D(Texture_0, gl_TexCoord[0].xy);
 
   	gl_FragColor = (diff + ambientColor) * texColor0;
}
