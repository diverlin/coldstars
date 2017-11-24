#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_Texture0;
uniform float u_time;

in vec4 vColor; 

void main (void)
{  	 
    vec4 texel = texture2D(u_Texture0, gl_PointCoord);
    color = vColor*texel;
}
