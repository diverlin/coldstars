
uniform vec3 u_lightPos;
uniform vec3 u_eyePos;

varying float att;
varying vec2 v_texcoord;
varying vec3 v_normal_n;
varying vec3 v_vertexPos2lightPos_n; 
varying vec3 v_vertexPos2eyePos_n; 
varying vec3 v_vertexPos2lightPos_tangent_n;
varying vec3 v_vertexPos2eyePos_tangent_n;

 
void main(void)
{
    	vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed vertex to world space */ 
                
    	v_normal_n     = normalize(gl_NormalMatrix * gl_Normal);                            

   	v_vertexPos2lightPos_n = normalize(u_lightPos - vertexPos);              
    	v_vertexPos2eyePos_n   = normalize(u_eyePos   - vertexPos); 
    	    	
    	v_texcoord = gl_MultiTexCoord0;                                                         
    	 
    	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
    	
    	// tangent space
    	vec3 tangent;
        vec3 v1=cross(gl_Normal, vec3(0.0, 0.0, 1.0));
        vec3 v2=cross(gl_Normal, vec3(0.0, 1.0, 0.0));
        if(length(v1)>length(v2))
                tangent=v1;
        else
                tangent=v2;
        vec3 n=normalize(gl_NormalMatrix*gl_Normal);
        vec3 t=normalize(gl_NormalMatrix*tangent);
        vec3 b=cross(n,t);
        mat3 tangent_mat=mat3(t.x, b.x, n.x, t.y, b.y, n.y, t.z, b.z, n.z);
       
        v_vertexPos2lightPos_tangent_n = normalize(tangent_mat*v_vertexPos2lightPos_n);
       
        vec3 vector=normalize(-vertexPos);
        v_vertexPos2eyePos_tangent_n=tangent_mat*vector;
                                          
}


