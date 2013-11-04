#version 330 core

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionViewMatrix;
uniform mat3 u_NormalModelMatrix;

uniform vec3 u_LightPos;
uniform vec3 u_EyePos;

in vec3 position;
in vec3 normal;

out vec3 vVert2light_n; 
out vec3 vVert2eye_n; 
out vec3 vNormal_n;
out vec2 vTexcoord;
 
void main(void)
{
    vec4 vertexPos = u_ModelMatrix * position;      /* transformed vertex to world space */ 
    gl_Position = u_ProjectionViewMatrix * vertexPos; 
        
    vVert2light_n = normalize(u_LightPos - vertexPos.xyz);              
    vVert2eye_n   = normalize(u_EyePos   - vertexPos.xyz);                              
    vNormal_n     = normalize(u_NormalModelMatrix * normal);   

    vTexcoord = gl_MultiTexCoord0;                                                         
}


