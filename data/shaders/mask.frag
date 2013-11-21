
uniform sampler2D u_TextureMask; 
uniform sampler2D u_TextureTarget;

uniform float u_Threshold; // ranged [0.0 - 1.0]
 
void main(void)
{
	gl_FragColor.rgb = vec3(1.0, 0.0, 0.0);
	gl_FragColor.a = texture2D(u_TextureMask, gl_TexCoord[0].st).r;
}
