#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D Texture_0;    
uniform sampler2D Texture_1;

uniform vec2 displ;

in vec2 v_Texcoord;
 
void main (void)
{
	vec2 uv = v_Texcoord;
	vec2 texCoord0 = uv - displ;
	vec2 texCoord1 = uv + displ;

	vec4 color0 = texture2D(Texture_0, texCoord0);
	vec4 color1 = texture2D(Texture_1, texCoord1);

	color = mix(color0, color1, 0.5);
}
