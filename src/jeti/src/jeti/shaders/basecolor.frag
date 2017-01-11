#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

in vec4 v_color;
 
void main (void)
{
    color = v_color;
}
