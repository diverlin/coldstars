                
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
          
       
bool vec2f :: isNull() const
{
	if ( (x == 0) and ( y == 0 ) )
		return true;
	else
		return false;
}

  
float vec2f :: getLen() const
{
	return sqrt(x*x+y*y);
}                
         
vec2f vec2f :: getNorm() const
{
	float len = getLen();

	return vec2f(x/len, y/len);
}	
                
                         
void vec2f :: set(float _x, float _y) 
{ 
        x = _x; 
        y = _y; 
}


vec2f vec2f :: operator+=(const vec2f& _vec_add)
{
	x += _vec_add.x;
	y += _vec_add.y;
	
	return *this;
}


vec2f vec2f :: operator+(const vec2f& _vec_add) const
{
	vec2f result;
	
	result.x = x + _vec_add.x;
	result.y = y + _vec_add.y;
	
	return result;
}

vec2f vec2f :: operator-(const vec2f& _vec_add) const
{
	vec2f result;
	
	result.x = x - _vec_add.x;
	result.y = y - _vec_add.y;
	
	return result;
}

vec2f vec2f :: operator*(const float _val) const
{
	vec2f result;
	
	result.x = x * _val;
	result.y = y * _val;
	
	return result;
}

vec2f vec2f :: operator/(const float _val) const
{
	vec2f result;
	
	result.x = x / _val;
	result.y = y / _val;
	
	return result;
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




float distBetweenPoints(vec2f center1, vec2f center2)
{
        float xl = center2.x - center1.x;
        float yl = center2.y - center1.y;
    
        return sqrt(xl*xl + yl*yl);
}

float distBetweenPoints(vec2f center1, float x2, float y2)
{
        float xl = (x2 - center1.x);
        float yl = (y2 - center1.y);
    
        return sqrt(xl*xl + yl*yl);    
}

float distBetweenPoints(float x1, float y1, float x2, float y2)
{
        float xl = (x2 - x1);
        float yl = (y2 - y1);
        
        return sqrt(xl*xl + yl*yl);
}



vec2f getRandVec(int radius_min, int radius_max)
{
    	float alpha = (float)getRandInt(0, 360) / 57.0;
    	int len = getRandInt(radius_min, radius_max);
   
 	vec2f target(sin(alpha) * len, cos(alpha) * len) ;
    	
    	return target;
}
