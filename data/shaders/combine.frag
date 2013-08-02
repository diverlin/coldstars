
uniform sampler2D u_TextureScene;
 
uniform sampler2D u_Pass0_tex1;
uniform sampler2D u_Pass0_tex2;
uniform sampler2D u_Pass0_tex3;
uniform sampler2D u_Pass0_tex4;
 
uniform sampler2D u_Pass1_tex1;
uniform sampler2D u_Pass1_tex2;
uniform sampler2D u_Pass1_tex3;
uniform sampler2D u_Pass1_tex4;
 
uniform sampler2D u_Pass2_tex1;
uniform sampler2D u_Pass2_tex2;
uniform sampler2D u_Pass2_tex3;
uniform sampler2D u_Pass2_tex4;
 
void main(void)
{
	vec2 texCoord = gl_TexCoord[0].st;

	vec4 t0 = texture2D(u_TextureScene, texCoord);

	vec4 p0t1 = texture2D(u_Pass0_tex1, texCoord);
	vec4 p0t2 = texture2D(u_Pass0_tex2, texCoord);
	vec4 p0t3 = texture2D(u_Pass0_tex3, texCoord);
	vec4 p0t4 = texture2D(u_Pass0_tex4, texCoord);

	vec4 p1t1 = texture2D(u_Pass1_tex1, texCoord);
	vec4 p1t2 = texture2D(u_Pass1_tex2, texCoord);
	vec4 p1t3 = texture2D(u_Pass1_tex3, texCoord);
	vec4 p1t4 = texture2D(u_Pass1_tex4, texCoord);

	vec4 p2t1 = texture2D(u_Pass2_tex1, texCoord);
	vec4 p2t2 = texture2D(u_Pass2_tex2, texCoord);
	vec4 p2t3 = texture2D(u_Pass2_tex3, texCoord);
	vec4 p2t4 = texture2D(u_Pass2_tex4, texCoord);
  
   	gl_FragColor = t0 + p0t1 + p0t2 + p0t3 + p0t4 + p1t1 + p1t2 + p1t3 + p1t4 + p2t1 + p2t2 + p2t3 + p2t4;
}
