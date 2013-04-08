
uniform sampler2D Texture_0;     /* texture unit 0 */
uniform sampler2D Texture_1;

uniform vec2 displ;

void main() 
{
	vec2 uv = gl_TexCoord[0].xy;
	vec2 texCoord0 = uv - displ;
	vec2 texCoord1 = uv + displ;

	vec4 color0 = texture2D(Texture_0, texCoord0);
	vec4 color1 = texture2D(Texture_1, texCoord1);
	/*vec4 color3 = vec4(1.0, 1.0, 0.0, 1.0);*/
	vec4 tmp = mix(color0, color1, 0.5);

	/*gl_FragColor = mix(tmp, color3, 0.4);*/
	gl_FragColor = tmp;
}

