#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionViewMatrix;
uniform mat3 u_NormalModelMatrix;

uniform vec3 u_LightPos;
uniform vec3 u_EyePos;

layout(location = VERTEX_POSITION_LOCATION) in vec3 position;
layout(location = VERTEX_TEXCOORD_LOCATION) in vec2 texcoord;
layout(location = VERTEX_NORMAL_LOCATION)   in vec3 normal;

out vec2 v_Texcoord;
out vec3 v_Normal_n;
out vec3 v_VertPos2lightPos_n; 
out vec3 v_VertPos2eyePos_n; 

out vec3 v_VertPos2lightPos_ts_n;
out vec3 v_VertPos2eyePos_ts_n;

 
void main(void)
{
    vec4 vertexPos = u_ModelMatrix * vec4(position, 1.0f);      
    gl_Position = u_ProjectionViewMatrix * vertexPos;      
      
    v_Normal_n = normalize(gl_NormalMatrix * normal);                            

   	v_VertPos2lightPos_n = normalize(u_LightPos - vertexPos);              
    v_VertPos2eyePos_n   = normalize(u_EyePos   - vertexPos); 

    v_Texcoord = texcoord;                                                       

    // tangent space
    vec3 tangent;
    vec3 v1 = cross(normal, vec3(0.0, 0.0, 1.0));
    vec3 v2 = cross(normal, vec3(0.0, 1.0, 0.0));
    
    if(length(v1)>length(v2)) tangent=v1;
    else                      tangent=v2;
    
    vec3 n = normalize(gl_NormalMatrix * normal);
    vec3 t = normalize(gl_NormalMatrix * tangent);
    vec3 b = cross(n,t);
    mat3 tangent_mat = mat3(t.x, b.x, n.x, t.y, b.y, n.y, t.z, b.z, n.z);
    
    v_VertPos2lightPos_ts_n = normalize(tangent_mat*v_VertPos2lightPos_n);
    
    vec3 vector = normalize(-vertexPos);

    //v_VertPos2eyePos_ts_n = vec3(1.0);//tangent_mat*vector;  
    v_VertPos2eyePos_ts_n = tangent_mat*vector; 
}


