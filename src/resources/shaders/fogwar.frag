
uniform sampler2D sceneTex;     /* texture unit 0 */
uniform float radius;
uniform vec2 center;
uniform vec2 world_coord;
uniform vec2 resolution;

void main(void)
{
	vec2 pos = world_coord + gl_FragCoord.xy/resolution.xy;
	pos.x *= resolution.x/resolution.y;

	vec2 center1 = center;
	center1.x *= resolution.x/resolution.y;

 	vec4 color = texture2D(sceneTex, gl_TexCoord[0].xy);

      	float distance = distance(pos, center1);
	if (distance > radius)
	{
		color -= vec4(0.1, 0.1, 0.1, 0.0);
	}

	gl_FragColor = color;
}

