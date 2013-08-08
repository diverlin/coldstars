#include "myVector.hpp"
#include "..//common/rand.hpp"

float distanceBetween(const Vec3<float>& center1, const Vec3<float>& center2)
{
        float lx = (center2.x - center1.x);
        float ly = (center2.y - center1.y);
        float lz = (center2.z - center1.z);
            
        return sqrt(lx*lx + ly*ly + lz*lz); 
}


float distanceBetween(const Vec3<float>& center1, float x2, float y2, float z2)
{
        float lx = (x2 - center1.x);
        float ly = (y2 - center1.y);
        float lz = (z2 - center1.z);
            
        return sqrt(lx*lx + ly*ly + lz*lz);    
}

float distanceBetween(const Vec2<float>& center1, const Vec2<float>& center2)
{
        float xl = center2.x - center1.x;
        float yl = center2.y - center1.y;
    
        return sqrt(xl*xl + yl*yl);
}


float distanceBetween(const Vec2<float>& center1, float x2, float y2)
{
        float xl = (x2 - center1.x);
        float yl = (y2 - center1.y);
    
        return sqrt(xl*xl + yl*yl);    
}

float distanceBetween(float x1, float y1, float x2, float y2)
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

Vec3<float> getVec3f(float length, float angle, float pos_z)
{
    	angle *= DEGREE_TO_RADIAN_RATE;	
    	Vec3<float> vec(length*sin(angle), length*cos(angle), pos_z);
    	
    	return vec;
}

float getAngleInD(const Vec2<float>& v_start, const Vec2<float> v_end)
{
	return atan2(v_start.y - v_end.y, v_start.x - v_end.x) * RADIAN_TO_DEGREE_RATE;
}

float getAngleBetweenUnits(const Vec3<float>& v1, const Vec3<float>& v2)
{
	return acos(dotUnits(v1, v2)) * RADIAN_TO_DEGREE_RATE;
}

float dotUnits(const Vec3<float>& v1, const Vec3<float>& v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vec2<float> getRandVec2f(int radius_min, int radius_max)
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    int len = getRandInt(radius_min, radius_max);
    
    Vec2<float> v(sin(alpha) * len, cos(alpha) * len);
    
    return v;
}

Vec3<float> getRandXYVec3f(int radius_min, int radius_max, float z)
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    int len = getRandInt(radius_min, radius_max);
    
    Vec3<float> v(sin(alpha)*len, cos(alpha)*len, z);
    
    return v;
}

Vec3<float> getRandXYVec3Unit()
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    Vec3<float> v(sin(alpha), cos(alpha), 0.0);
    
    return v;
}

Vec3<float> getXYVec3Unit(float alpha)
{
    alpha *= DEGREE_TO_RADIAN_RATE;
    Vec3<float> v(sin(alpha), cos(alpha), 0.0);
    
    return v;
}
