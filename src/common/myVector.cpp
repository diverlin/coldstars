          
       
bool vec2f::IsNull() const
{
	if ( (x == 0) and ( y == 0 ) )
		return true;
	else
		return false;
}
  
float vec2f::GetLen() const
{
	return sqrt(x*x+y*y);
}                
         
vec2f vec2f::GetNorm() const
{
	float len = GetLen();
	return vec2f(x/len, y/len);
}	
                

vec2f& vec2f::operator+=(const vec2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	
	return *this;
}

vec2f& vec2f::operator+=(float offset)
{
	x += offset;
	y += offset;
	
	return *this;
}


vec2f vec2f::operator+(const vec2f& rhs) const
{
	vec2f result(x+rhs.x, y+rhs.y);	
	return result;
}

vec2f vec2f::operator-(const vec2f& rhs) const
{
	vec2f result(x-rhs.x, y-rhs.y);	
	return result;
}

vec2f vec2f::operator*(float val) const
{
	vec2f result(x*val, y*val);
	return result;
}

vec2f vec2f::operator/(float val) const
{
	vec2f result(x/val, y/val);	
	return result;
}



const vec3f& vec3f::operator+=(const vec3f& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
	z+=rhs.z;	
	
	return *this;
}










float distBetweenPoints(const vec2f& center1, const vec2f& center2)
{
        float xl = center2.x - center1.x;
        float yl = center2.y - center1.y;
    
        return sqrt(xl*xl + yl*yl);
}

float distBetweenPoints(const vec2f& center1, float x2, float y2)
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



vec2f getRandVec2f(int radius_min, int radius_max)
{
    	float alpha = (float)getRandInt(0, 360) / 57.0;
    	int len = getRandInt(radius_min, radius_max);
   
 	vec2f target(sin(alpha) * len, cos(alpha) * len) ;
    	
    	return target;
}
