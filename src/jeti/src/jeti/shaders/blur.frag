#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D sceneTex;  /* 0 */
 
uniform float rt_w;    /* render target width  */
uniform float rt_h;    /* render target height */
uniform float vx_offset;
 
in vec2 v_Texcoord;

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );
 
void main()
{
  	vec3 tc = vec3(0.0, 0.0, 0.0);
  	if (v_Texcoord.x<(vx_offset-0.01))
  	{
   		vec2 uv = v_Texcoord.xy;
        tc = texture2D(sceneTex, uv).rgb * weight[0];

        for (int i=1; i<3; i++)
        {
            tc += texture2D(sceneTex, uv + vec2(offset[i])/rt_w, 0.0).rgb * weight[i];
            tc += texture2D(sceneTex, uv - vec2(offset[i])/rt_w, 0.0).rgb * weight[i];
        }
  	}
  	else if (v_Texcoord.x>=(vx_offset+0.01))
  	{
        tc = texture2D(sceneTex, v_Texcoord.xy).rgb;
  	}
  
	color = vec4(tc, 1.0);
}
