#include "myVector.hpp"
#include "../common/rand.hpp"
#include <sstream>
      
float distanceBetween(const glm::vec3& center1, const glm::vec3& center2)
{
    float lx = (center2.x - center1.x);
    float ly = (center2.y - center1.y);
    float lz = (center2.z - center1.z);
        
    return sqrt(lx*lx + ly*ly + lz*lz); 
}

float distanceBetween(const glm::vec3& center1, const glm::vec2& center2)
{
    float lx = (center2.x - center1.x);
    float ly = (center2.y - center1.y);
        
    return sqrt(lx*lx + ly*ly); 
}

float distanceBetween(const glm::vec3& center1, float x2, float y2, float z2)
{
    float lx = (x2 - center1.x);
    float ly = (y2 - center1.y);
    float lz = (z2 - center1.z);
        
    return sqrt(lx*lx + ly*ly + lz*lz);    
}

float distanceBetween(const glm::vec2& center1, const glm::vec2& center2)
{
    float xl = center2.x - center1.x;
    float yl = center2.y - center1.y;
    
    return sqrt(xl*xl + yl*yl);
}

float distanceBetween(const glm::vec2& center1, const glm::vec3& center2)
{
    float xl = center2.x - center1.x;
    float yl = center2.y - center1.y;
    
    return sqrt(xl*xl + yl*yl);
}

float distanceBetween(const glm::vec2& center1, float x2, float y2)
{
    float xl = (x2 - center1.x);
    float yl = (y2 - center1.y);
    
    return sqrt(xl*xl + yl*yl);    
}

float distanceBetween(const glm::vec3& center1, float x2, float y2)  
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


glm::vec2 getVec2f(float length, float angle)
{
    angle *= DEGREE_TO_RADIAN_RATE;    
    glm::vec2 vec(length*sin(angle), length*cos(angle));
    
    return vec;
}

glm::vec3 getVec3f(float length, float angle, float pos_z)
{
    glm::vec3 vec(length*sin(angle), length*cos(angle), pos_z);
    
    return vec;
}

float getAngleInD(const glm::vec2& v_start, const glm::vec2 v_end)  // depr
{
    return atan2(v_start.y - v_end.y, v_start.x - v_end.x) * RADIAN_TO_DEGREE_RATE;
}

float getAngle(const glm::vec2& v_start, const glm::vec2 v_end)
{
    return atan2(v_start.y - v_end.y, v_start.x - v_end.x);
}

float getAngleBetweenUnits(const glm::vec3& v1, const glm::vec3& v2)
{
    return acos(dotUnits(v1, v2)) * RADIAN_TO_DEGREE_RATE;
}

float dotUnits(const glm::vec3& v1, const glm::vec3& v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

glm::vec2 getRandVec2f(int radius_min, int radius_max)
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    int len = getRandInt(radius_min, radius_max);
    
    glm::vec2 v(sin(alpha) * len, cos(alpha) * len);
    
    return v;
}

glm::vec3 getRandXYVec3f(int radius_min, int radius_max, float z)
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    int len = getRandInt(radius_min, radius_max);
    
    glm::vec3 v(sin(alpha)*len, cos(alpha)*len, z);
    
    return v;
}

glm::vec3 getRandXYVec3Unit()
{
    float alpha = (float)getRandInt(0, 360) * DEGREE_TO_RADIAN_RATE;
    glm::vec3 v(sin(alpha), cos(alpha), 0.0);
    
    return v;
}

glm::vec3 getXYVec3Unit(float alpha)
{
    alpha *= DEGREE_TO_RADIAN_RATE;
    glm::vec3 v(sin(alpha), cos(alpha), 0.0);
    
    return v;
}


glm::vec2 vec3ToVec2(const glm::vec3& v3)
{
    return glm::vec2(v3.x, v3.y);
}

std::string str(const glm::vec3& v)
{
    std::stringstream ss;
    ss<<v.x<<","<<v.y<<","<<v.z<<".";
    return ss.str();
}

