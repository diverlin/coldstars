#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform mat4 u_modelMatrix;
uniform mat4 u_projectionViewMatrix;

uniform float u_angle;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texCoord;

out vec2 v_texCoord;
out mat2 v_rotateMat2;
 
mat2 rotateMat2(float angle) {
	float s = sin(angle);
	float c = cos(angle);
	return mat2(c, -s, s, c);
}

void main(void)
{
    vec4 vertexPos = u_modelMatrix * vec4(position, 1.0f);
    gl_Position = u_projectionViewMatrix * vertexPos;

    v_texCoord = texCoord;
    v_rotateMat2 = rotateMat2(u_angle);
}


