          
       
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

void vec2f::operator()(const vec2f& v)
{
	x = v.x;
	y = v.y;
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


vec2i getVec2i(int len, int angle)
{
    	float alpha = (float)angle / 57.0;	
    	vec2i request(sin(alpha) * len, cos(alpha) * len);
    	
    	return request;
}

vec2f getRandVec2f(int radius_min, int radius_max)
{
    	float alpha = (float)getRandInt(0, 360) / 57.0;
    	int len = getRandInt(radius_min, radius_max);
   
 	vec2f request(sin(alpha) * len, cos(alpha) * len);
    	
    	return request;
}

float vector2f::GetLen() const
{
	float len = sqrt((p.x-p0.x)*(p.x-p0.x) + (p.y-p0.y)*(p.y-p0.y));
	return len;
}

float getAngle(const vector2f& v1, const vector2f& v2)
{
	float angle = acos( ((v1.p.x-v1.p0.x)*(v2.p.x-v2.p0.x) + (v1.p.y-v1.p0.y)*(v2.p.y-v2.p0.y))/(v1.GetLen()*v2.GetLen()) ) * RADIAN_TO_DEGREE_RATE;
    	return angle;
}
