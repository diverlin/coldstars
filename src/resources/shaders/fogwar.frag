
uniform sampler2D sceneTex;     /* texture unit 0 */
uniform vec2 center;
uniform float radius;
uniform vec2 pos;

void main(void)
{
	vec2 texCoord = gl_TexCoord[0].xy;
	vec4 color = texture2D(sceneTex, texCoord);

	vec2 global_texCoord = texCoord + pos;
      	float distance = distance(global_texCoord, center);
	if (distance > radius)
	{
		color = color - vec4(0.1f, 0.1f, 0.1f, 0.0f);
	}

	gl_FragColor = color;
}

