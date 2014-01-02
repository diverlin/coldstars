#version 330 core

#define VERTEX_POSITION_LOCATION 0
#define VERTEX_TEXCOORD_LOCATION 1
#define VERTEX_NORMAL_LOCATION   2
#define VERTEX_COLOR_LOCATION    3

uniform struct Matrices
{
    mat4 model;
    mat4 projectionView;
    mat3 normal;
} u_Matrices;

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
    vec4 vertexPos = u_Matrices.model * vec4(position, 1.0f);      
    gl_Position = u_Matrices.projectionView * vertexPos;      
      
    v_Normal_n = normalize(u_Matrices.normal * normal);                            

   	v_VertPos2lightPos_n = normalize(u_LightPos - vertexPos.xyz);              
    v_VertPos2eyePos_n   = normalize(u_EyePos   - vertexPos.xyz); 

    v_Texcoord = texcoord;                                                       

    // tangent space
    vec3 tangent;
    vec3 v1 = cross(normal, vec3(0.0, 0.0, 1.0));
    vec3 v2 = cross(normal, vec3(0.0, 1.0, 0.0));
    
    if(length(v1)>length(v2)) tangent=v1;
    else                      tangent=v2;
    
    vec3 n = normalize(u_Matrices.normal * normal);
    vec3 t = normalize(u_Matrices.normal * tangent);
    vec3 b = cross(n,t);
    mat3 tangent_mat = mat3(t.x, b.x, n.x, t.y, b.y, n.y, t.z, b.z, n.z);
    
    v_VertPos2lightPos_ts_n = normalize(tangent_mat * v_VertPos2lightPos_n);
    
    vec3 vector = normalize(-vertexPos.xyz);

    //v_VertPos2eyePos_ts_n = vec3(1.0);//tangent_mat*vector;  
    v_VertPos2eyePos_ts_n = tangent_mat * vector; 
}


