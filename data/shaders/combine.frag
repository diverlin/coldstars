#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_Texture;

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

in vec2 v_Texcoord;
 
void main(void)
{
	vec4 t0 = texture2D(u_TextureScene, v_Texcoord);

	vec4 p0t1 = texture2D(u_Pass0_tex1, v_Texcoord);
	vec4 p0t2 = texture2D(u_Pass0_tex2, v_Texcoord);
	vec4 p0t3 = texture2D(u_Pass0_tex3, v_Texcoord);
	vec4 p0t4 = texture2D(u_Pass0_tex4, v_Texcoord);

	vec4 p1t1 = texture2D(u_Pass1_tex1, v_Texcoord);
	vec4 p1t2 = texture2D(u_Pass1_tex2, v_Texcoord);
	vec4 p1t3 = texture2D(u_Pass1_tex3, v_Texcoord);
	vec4 p1t4 = texture2D(u_Pass1_tex4, v_Texcoord);

	vec4 p2t1 = texture2D(u_Pass2_tex1, v_Texcoord);
	vec4 p2t2 = texture2D(u_Pass2_tex2, v_Texcoord);
	vec4 p2t3 = texture2D(u_Pass2_tex3, v_Texcoord);
	vec4 p2t4 = texture2D(u_Pass2_tex4, v_Texcoord);
  
   	color = t0 + p0t1 + p0t2 + p0t3 + p0t4 + p1t1 + p1t2 + p1t3 + p1t4 + p2t1 + p2t2 + p2t3 + p2t4;
}
