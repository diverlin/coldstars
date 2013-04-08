
uniform sampler2D Scene;
 
uniform sampler2D Pass0_tex1;
uniform sampler2D Pass0_tex2;
uniform sampler2D Pass0_tex3;
uniform sampler2D Pass0_tex4;
 
uniform sampler2D Pass1_tex1;
uniform sampler2D Pass1_tex2;
uniform sampler2D Pass1_tex3;
uniform sampler2D Pass1_tex4;
 
uniform sampler2D Pass2_tex1;
uniform sampler2D Pass2_tex2;
uniform sampler2D Pass2_tex3;
uniform sampler2D Pass2_tex4;
 
void main(void)
{
    	vec4 t0 = texture2D(Scene, gl_TexCoord[0].st);
 
    	vec4 p0t1 = texture2D(Pass0_tex1, gl_TexCoord[0].st);
    	vec4 p0t2 = texture2D(Pass0_tex2, gl_TexCoord[0].st);
    	vec4 p0t3 = texture2D(Pass0_tex3, gl_TexCoord[0].st);
    	vec4 p0t4 = texture2D(Pass0_tex4, gl_TexCoord[0].st);
 
    	vec4 p1t1 = texture2D(Pass1_tex1, gl_TexCoord[0].st);
    	vec4 p1t2 = texture2D(Pass1_tex2, gl_TexCoord[0].st);
    	vec4 p1t3 = texture2D(Pass1_tex3, gl_TexCoord[0].st);
    	vec4 p1t4 = texture2D(Pass1_tex4, gl_TexCoord[0].st);
 
    	vec4 p2t1 = texture2D(Pass2_tex1, gl_TexCoord[0].st);
    	vec4 p2t2 = texture2D(Pass2_tex2, gl_TexCoord[0].st);
    	vec4 p2t3 = texture2D(Pass2_tex3, gl_TexCoord[0].st);
    	vec4 p2t4 = texture2D(Pass2_tex4, gl_TexCoord[0].st);
  
   	gl_FragColor = t0 + p0t1 + p0t2 + p0t3 + p0t4 + p1t1 + p1t2 + p1t3 + p1t4 + p2t1 + p2t2 + p2t3 + p2t4;
}
