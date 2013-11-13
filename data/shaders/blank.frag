
uniform sampler2D Texture_0;   

void main() 
{
	vec4 c = texture2D(Texture_0, gl_TexCoord[0].st);
	if (c.a > 0.0) 
	{ 
		c = vec4(0.0, 0.0, 0.0, 1.0); 
	}

	gl_FragColor = c;
}

