
uniform sampler2D source;
uniform float threshold;
 
void main(void)
{
    	vec4 c = texture2D(source, gl_TexCoord[0].st);
    	float rgb = c.r + c.g + c.b;
    	if (rgb > threshold)   /* threshold ~ 1.9 */ 
       		gl_FragColor = c;
    	else
       		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
}
