
uniform sampler2D iTexture_0;
uniform float iTime;
 
void main (void)
{  	 
	vec2 pos = gl_TexCoord[0].xy;
    	vec4 texColor0 = texture2D(iTexture_0, pos);
 
  	gl_FragColor = (1.0+0.025*sin(iTime))*texColor0;
}
