//http://glslsandbox.com/e#20957.1

#version 330 core

#define FRAG_OUTPUT0 0

uniform sampler2D u_texture;
uniform float u_time;
uniform vec2 u_worldPosition;
uniform vec2 u_resolution;
uniform float u_sizeFactor;

float rand(int seed, float ray) {
    return mod(sin(float(seed)*363.5346+ray*674.2454)*6743.4365, 1.0);
}

layout(location = FRAG_OUTPUT0) out vec4 color;
in vec2 v_texCoord;

void main( void ) {
    color = texture2D(u_texture, v_texCoord);

    float pi = 3.14159265359;
    vec2 position = ( gl_FragCoord.xy / u_resolution.xy ) - vec2(u_worldPosition.x, u_worldPosition.y);
    position.y *= u_resolution.y/u_resolution.x;
    float ang = atan(position.y, position.x);
    float dist = u_sizeFactor*length(position);
    color.rgb += vec3(0.8, 0.8, 0.15) * (pow(dist, -4.0) * 0.5);
    for (float ray = 0.0; ray < 2.0; ray += 0.095) {
        float rayang = rand(5, ray)*6.2+(u_time*0.1)*2.0*(rand(2546, ray))-rand(5785, ray)-(rand(3545, ray)-rand(5467, ray));
        rayang = mod(rayang, pi*2.0);
        if (rayang < ang - pi) {rayang += pi*2.0;}
        if (rayang > ang + pi) {rayang -= pi*2.0;}
        float brite = 1.0 - abs(ang - rayang);
        brite -= dist * 0.1;
        if (brite > 0.0) {
            color.rgb += vec3(0.3+0.4*rand(8644, ray), 0.25+0.4*rand(4567, ray), 0.7+0.4*rand(7354, ray)) * brite * 0.1;
        }
    }
    color.a = 1.0;
}
