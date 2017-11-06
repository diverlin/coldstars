#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_texture;
uniform vec4 u_color;

in vec2 v_texCoord;
 
void main (void)
{
    color = texture2D(u_texture, v_texCoord);
    color *= u_color;
}
