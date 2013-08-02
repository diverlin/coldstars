
uniform sampler2D u_TextureMask; 
uniform sampler2D u_TextureTarget;

uniform float u_Threshold; // ranged [0.0 - 1.0]
 
void main(void)
{
	vec2 texCoord = gl_TexCoord[0].st;
	vec4 colorMask = texture2D(u_TextureMask, texCoord);
	
	if (colorMask.r > u_Threshold)
	{
		gl_FragColor = texture2D(u_TextureTarget, texCoord);
	}
	else
	{
		gl_FragColor = vec4(1.0, 1.0, 1.0, 0.0);
	}	
}
