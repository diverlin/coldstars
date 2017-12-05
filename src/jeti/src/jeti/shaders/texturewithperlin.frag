#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

uniform sampler2D u_texture;
uniform sampler2D u_texturePerlin;

uniform float u_scale;
uniform vec2 u_resolution;
uniform vec2 u_cameraPos;
uniform vec4 u_color;
uniform float u_time;

in vec2 v_texCoord;
  
 float noise( vec2 uv ){
	return texture(u_texturePerlin, uv).r;
}

float perlin_noise(vec2 uv, float t){
	float res = noise(uv     +t*vec2(.5,  .5))*64.0
		      + noise(uv*2.0 +t*vec2(-.7, .2))*32.0
			  + noise(uv*4.0 +t*vec2( 0,   1))*16.0
		  	  + noise(uv*8.0 +t*vec2(1,    0))*8.0
			  + noise(uv*16.0+t*vec2(-.5,-.5))*4.0
		   	  + noise(uv*32.0+t*vec2(.1,  .1))*2.0
			  + noise(uv*64.0+t*vec2(.9,  .9))*1.0;
	
	return res / (1.0+2.0+4.0+8.0+16.0+32.0+64.0);
}

void main (void)
{
    color = texture2D(u_texture, v_texCoord);
    color *= u_color;
    
	vec2 uv = (gl_FragCoord.xy + u_cameraPos/u_scale) / u_resolution;
    float p1 = perlin_noise(uv.xy * 0.25, u_time/100.0);
    p1 = perlin_noise(uv.xy, p1);
	color.a *= p1;
}
