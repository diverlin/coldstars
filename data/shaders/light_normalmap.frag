
uniform sampler2D u_texture;
uniform sampler2D u_normalmap;

uniform vec4 u_diffColor;
uniform vec4 u_ambientColor;

varying vec2 v_texcoord;
varying vec3 v_normal_n;
varying vec3 v_vertexPos2lightPos_n; 
varying vec3 v_vertexPos2eyePos_n; 
varying vec3 v_vertexPos2lightPos_tangent_n;
varying vec3 v_vertexPos2eyePos_tangent_n;
 
void main(void)
{  	
    	vec4 texColor = texture2D(u_texture, v_texcoord.xy);
    	
	vec3 normaltex_n = normalize(texture2D(u_normalmap, v_texcoord.xy).rgb * 2.0 - 1.0); // Extract the normal from the normal map  

    	//vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    	//vec3 r    = reflect(-v_vertex2eye_n, v_normal_n);
    	
    	vec4 diff = u_diffColor * max(0.0, dot(normaltex_n, v_vertexPos2lightPos_tangent_n));
    	//vec4 spec = specColor * pow(0.0, max(0.0, dot(v_vertexPos2lightPos_n, r)), specPower);
 
   	gl_FragColor = (diff + u_ambientColor) * texColor;
}
