/* http://www.gamedev.ru/code/forum/?id=90743 */

uniform vec3 lightPos, eyePos;
varying vec3 vertex2light_n, vertex2eye_n, normal_n;
 
void main(void)
{
    	vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed vertex to world space */ 
   	vertex2light_n = normalize(lightPos - vertexPos);              
    	vertex2eye_n   = normalize(eyePos   - vertexPos);                              
    	normal_n       = normalize(gl_NormalMatrix * gl_Normal);                            
    	
    	gl_TexCoord[0] = gl_MultiTexCoord0;                                                         
 
    	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;                                    
}


