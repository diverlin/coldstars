          /*
        Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
        
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.
        
        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
        
        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
       
#include "myVector.hpp"
#include <cmath>
#include "../common/constants.hpp"
#include "../common/rand.hpp"


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

vec2f& vec2f::operator+=(float rhs)
{
	x += rhs;
	y += rhs;
	
	return *this;
}

vec2f& vec2f::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	
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


//vec2i vec2i::operator+(const vec2i& rhs) const
//{
	//vec2i result(x+rhs.x, y+rhs.y);	
	//return result;
//}

const vec3f& vec3f::operator+=(const vec3f& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
	z+=rhs.z;	
	
	return *this;
}

float Vector2f::GetLen() const
{
	float len = sqrt((p.x-p0.x)*(p.x-p0.x) + (p.y-p0.y)*(p.y-p0.y));
	return len;
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


//vec2i getVec2i(int len, int angle)
//{
    	//float alpha = (float)angle * DEGREE_TO_RADIAN_RATE;	
    	//vec2i request(sin(alpha) * len, cos(alpha) * len);
    	
    	//return request;
//}

vec2f getVec2f(float len, float angle)
{
    	angle *= DEGREE_TO_RADIAN_RATE;	
    	vec2f vec(sin(angle) * len, cos(angle) * len);
    	
    	return vec;
}

float getAngleInD(const vec2f& v_start, const vec2f& v_end)
{
	return atan2(v_start.y - v_end.y, v_start.x - v_end.x) * RADIAN_TO_DEGREE_RATE;
}

vec2f getRandVec2f(int radius_min, int radius_max)
{
    	float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    	int len = getRandInt(radius_min, radius_max);
   
 	vec2f vec(sin(alpha) * len, cos(alpha) * len);
    	
    	return vec;
}

float getAngle(const Vector2f& v1, const Vector2f& v2)
{
	float angle = acos( ((v1.p.x-v1.p0.x)*(v2.p.x-v2.p0.x) + (v1.p.y-v1.p0.y)*(v2.p.y-v2.p0.y))/(v1.GetLen()*v2.GetLen()) ) * RADIAN_TO_DEGREE_RATE;
    	return angle;
}
