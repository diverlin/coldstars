#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_texture;

uniform vec4 u_color;

in vec2 v_texCoord;

void main (void)
{
    vec4 _color = texture2D(u_texture, v_texCoord);
    _color *= u_color;
    _color.r = 1.0;

    color = _color;
}
