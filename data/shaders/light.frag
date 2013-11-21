#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_Texture0;

uniform vec4 u_DiffColor;
uniform vec4 u_AmbientColor;

in vec3 vVert2light_n; 
in vec3 vVert2eye_n; 
in vec3 vNormal_n;
in vec2 vTexcoord;
 
void main (void)
{  	
    //vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    //vec3 r    = reflect(-vVert2eye_n, vNormal_n);
    	
    vec4 diff = u_DiffColor * max(0.0, dot(vNormal_n, vVert2light_n));
    //vec4 spec = specColor * pow(max(dot(vVert2light_n, r), 0.0), specPower);
    	 
    vec4 texel = texture2D(u_Texture0, vTexcoord);
 
   	color = (diff + u_AmbientColor) * texel;
}
