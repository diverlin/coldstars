
uniform sampler2D sceneTex;     /* texture unit 0 */

void main()
{
    	vec4 c = texture2D(sceneTex, gl_TexCoord[0].st);
    	float rgb = c.r + c.g + c.b;
    	if (c.g > 0.6)
       		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    	else
      		gl_FragColor = c;
}
