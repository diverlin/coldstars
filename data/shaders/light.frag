
uniform sampler2D iTexture_0;
uniform vec4 iDiffColor;
uniform vec4 iAmbientColor;

varying vec3 vVert2light_n; 
varying vec3 vVert2eye_n; 
varying vec3 vNormal_n;
 
void main (void)
{  	
    	//vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0); 
	//float specPower = 30.0;
	    	
    	//vec3 r    = reflect(-vVert2eye_n, vNormal_n);
    	
    	vec4 diff = iDiffColor * max(0.0, dot(vNormal_n, vVert2light_n));
    	//vec4 spec = specColor * pow(max(dot(vVert2light_n, r), 0.0), specPower);
    	 
    	vec4 color = texture2D(iTexture_0, gl_TexCoord[0].xy);
 
   	gl_FragColor = (diff + iAmbientColor) * color;
}
