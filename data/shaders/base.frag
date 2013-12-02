#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_Texture;

in vec2 v_Texcoord;
 
void main (void)
{
    color = texture2D(u_Texture, v_Texcoord);
}
