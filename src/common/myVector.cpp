                
vec2f :: vec2f()
{
        x = 0;
        y = 0;
}
    
vec2f :: vec2f(float _x, float _y)
{
        x = _x; 
        y = _y; 
}
            
void vec2f :: set(float _x, float _y) 
{ 
        x = _x; 
        y = _y; 
}





vec3f :: vec3f()
{
        x = 0;
        y = 0;
        y = 0;
}
    
vec3f :: vec3f(float _x, float _y, float _z)
{
        x = _x; 
        y = _y; 
        z = _z; 
}
            
void vec3f :: set(float _x, float _y, float _z) 
{ 
        x = _x; 
        y = _y; 
        z = _z; 
}




float distBetweenCenters(vec2f center1, vec2f center2)
{
        float xl = center2.x - center1.x;
        float yl = center2.y - center1.y;
    
        return sqrt(xl*xl + yl*yl);
}

float distBetweenCenters(vec2f center1, float x2, float y2)
{
        float xl = (x2 - center1.x);
        float yl = (y2 - center1.y);
    
        return sqrt(xl*xl + yl*yl);    
}

float distBetweenCenters(float x1, float y1, float x2, float y2)
{
        float xl = (x2 - x1);
        float yl = (y2 - y1);
        
        return sqrt(xl*xl + yl*yl);
}



vec2f getRandomVec(vec2f center, int radius_min, int radius_max)
{
	vec2f target;
	
    	float alpha = (float)getRandInt(0, 360) / 57.0;
    	int len = getRandInt(radius_min, radius_max);
   
    	target.x = center.x + sin(alpha) * len;
    	target.y = center.y + cos(alpha) * len;
    	
    	return target;
}
