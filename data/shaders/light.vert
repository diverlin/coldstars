
uniform vec3 iLightPos;
uniform vec3 iEyePos;

varying vec3 vVert2light_n; 
varying vec3 vVert2eye_n; 
varying vec3 vNormal_n;
 
void main(void)
{
    	vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed vertex to world space */ 
   	vVert2light_n = normalize(iLightPos - vertexPos);              
    	vVert2eye_n   = normalize(iEyePos   - vertexPos);                              
    	vNormal_n      = normalize(gl_NormalMatrix * gl_Normal);                            
    	
    	gl_TexCoord[0] = gl_MultiTexCoord0;                                                         
 
    	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;                                    
}


