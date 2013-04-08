/* http://www.gamedev.ru/code/forum/?id=90743 */

uniform vec4 lightPos, eyePos;
varying vec3 l, v, n;
 
void main(void)
{
    	vec3 p = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed point to world space */ 
   	l = normalize(vec3(lightPos) - p);                  /* vector to light source */           
    	v = normalize(vec3(eyePos)   - p);                  /* vector to the eye */                
    	n = normalize(gl_NormalMatrix * gl_Normal);         /* transformed n */                    
    	gl_TexCoord[0] = gl_MultiTexCoord0;                                                         
 
    	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;                                    
}


