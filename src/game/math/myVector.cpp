#include "myVector.hpp"

float distBetweenPoints(const Vec2<float>& center1, const Vec2<float>& center2)
{
        float xl = center2.x - center1.x;
        float yl = center2.y - center1.y;
    
        return sqrt(xl*xl + yl*yl);
}


float distBetweenPoints(const Vec2<float>& center1, float x2, float y2)
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


Vec2<float> getVec2f(float length, float angle)
{
    	angle *= DEGREE_TO_RADIAN_RATE;	
    	Vec2<float> vec(length*sin(angle), length*cos(angle));
    	
    	return vec;
}

float getAngleInD(const Vec2<float>& v_start, const Vec2<float> v_end)
{
	return atan2(v_start.y - v_end.y, v_start.x - v_end.x) * RADIAN_TO_DEGREE_RATE;
}

float getAngle(const Vector2f& v1, const Vector2f& v2)
{
	float angle = acos( ((v1.p.x-v1.p0.x)*(v2.p.x-v2.p0.x) + (v1.p.y-v1.p0.y)*(v2.p.y-v2.p0.y))/(v1.GetLength()*v2.GetLength()) ) * RADIAN_TO_DEGREE_RATE;
    	return angle;
}

