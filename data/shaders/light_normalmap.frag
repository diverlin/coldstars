#version 330 core

#define FRAG_OUTPUT0 0

uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform vec4 u_diffColor;
uniform vec4 u_ambientColor;

in vec2 v_Texcoord;
in vec3 v_Normal_n;
in vec3 v_VertPos2lightPos_n; 
in vec3 v_VertPos2eyePos_n; 

in vec3 v_VertPos2lightPos_ts_n;
in vec3 v_VertPos2eyePos_ts_n;
 
void main(void)
{  	
    vec4 texColor = texture2D(u_texture, v_Texcoord);
    
	vec3 normaltex_n = normalize(texture2D(u_normalmap, v_Texcoord).rgb * 2.0 - 1.0); // Extract the normal from the normal map  

    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	
    //vec3 r    = reflect(-v_VertPos2eyePos_n, v_Normal_n);
    	
    vec3 diff = u_diffColor.xyz * max(0.0, dot(normaltex_n, v_VertPos2lightPos_ts_n));
    //vec4 spec = specColor * pow(0.0, max(0.0, dot(v_VertPos2lightPos_n, r)), specPower);
 
   	color = (vec4(diff, 1.0f) + u_ambientColor) * texColor;
}
