#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

in vec2 v_Texcoord;

uniform sampler2D sceneTex;     /* texture unit 0 */
uniform float radius;
uniform vec2 center;
uniform vec2 world_coord;
uniform vec2 resolution;
uniform float dcolor;

void main(void)
{
	vec2 pos = world_coord + gl_FragCoord.xy/resolution.xy;
	pos.x *= resolution.x/resolution.y;

	vec2 center1 = center;
	center1.x *= resolution.x/resolution.y;

 	color = texture2D(sceneTex, v_Texcoord);

    float distance = distance(pos, center1);
	if (distance > radius)
	{
		color -= vec4(0.1, 0.1, 0.1, 0.0);
	}

	color += dcolor;
}

