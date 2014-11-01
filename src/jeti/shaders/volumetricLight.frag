#version 330 core

#define FRAG_OUTPUT0 0

layout(location = FRAG_OUTPUT0) out vec4 color;

in vec2 v_Texcoord;

uniform sampler2D FullSampler;
uniform sampler2D BlurSampler;
uniform vec4 sun_pos;
 
const vec4 ShaftParams	= vec4(0.05, 1.0, 0.05, 1.0);
const vec4 sunColor	= vec4(0.9, 0.8, 0.6, 1.0);
 
float saturate(float val)
{
	return clamp(val,0.0,1.0);
}
 
void main(void)
{ 
	vec2  sunPosProj = sun_pos.xy;
	float sign = sun_pos.w;
 
	vec2  tc = v_Texcoord;
 
	vec2  sunVec = sunPosProj.xy - tc; /* + vec2(0.5,0.5); */
	float sunDist = saturate(sign) * (1.0 - saturate(dot(sunVec,sunVec) * ShaftParams.y));
 
	sunVec *= ShaftParams.x * sign;
 
	tc += sunVec;
	vec4 accum = texture2D(BlurSampler, tc);
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.875;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.75;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.625;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.5;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.375;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.25;
	tc += sunVec;
	accum += texture2D(BlurSampler, tc) * 0.125;
 
	accum  *= 1.65 * sunDist;
 
	vec4 cScreen = texture2D(FullSampler, v_Texcoord);
	accum = cScreen + accum * ShaftParams.w * sunColor * ( 1.0 - cScreen );
 
    color = accum;
}
