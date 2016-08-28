#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

in vec2 v_Texcoord;

uniform sampler2D source;
uniform float threshold;
 
void main(void)
{
    vec4 c = texture2D(source, v_Texcoord.st);
    float rgb = c.r + c.g + c.b;
    if (rgb > threshold)   /* threshold ~ 1.9 */ 
        color = c;
    else
        color = vec4(0.0, 0.0, 0.0, 0.0);
}
