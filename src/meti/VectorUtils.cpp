#include "VectorUtils.hpp"
#include <RandUtils.hpp>
#include <sstream>
      
namespace meti {

float distance(const glm::vec3& center1, const glm::vec3& center2)
{
    float lx = (center2.x - center1.x);
    float ly = (center2.y - center1.y);
    float lz = (center2.z - center1.z);
        
    return sqrt(lx*lx + ly*ly + lz*lz); 
}

float distance(const glm::vec3& center1, const glm::vec2& center2)
{
    float lx = (center2.x - center1.x);
    float ly = (center2.y - center1.y);
        
    return sqrt(lx*lx + ly*ly); 
}

float distance(const glm::vec3& center1, float x2, float y2, float z2)
{
    float lx = (x2 - center1.x);
    float ly = (y2 - center1.y);
    float lz = (z2 - center1.z);
        
    return sqrt(lx*lx + ly*ly + lz*lz);    
}

float distance(const glm::vec2& center1, const glm::vec2& center2)
{
    float xl = center2.x - center1.x;
    float yl = center2.y - center1.y;
    
    return sqrt(xl*xl + yl*yl);
}

float distance(const glm::vec2& center1, const glm::vec3& center2)
{
    float xl = center2.x - center1.x;
    float yl = center2.y - center1.y;
    
    return sqrt(xl*xl + yl*yl);
}

float distance(const glm::vec2& center1, float x2, float y2)
{
    float xl = (x2 - center1.x);
    float yl = (y2 - center1.y);
    
    return sqrt(xl*xl + yl*yl);    
}

float distance(const glm::vec3& center1, float x2, float y2)  
{
    float xl = (x2 - center1.x);
    float yl = (y2 - center1.y);
    
    return sqrt(xl*xl + yl*yl);  
}

float distance(float x1, float y1, float x2, float y2)
{
    float xl = (x2 - x1);
    float yl = (y2 - y1);
    
    return sqrt(xl*xl + yl*yl);
}


glm::vec2 genVec2f(float length, float angle)
{
    angle = glm::radians(angle);
    return length * glm::vec2(sin(angle), cos(angle));
}

glm::vec3 genVec3f(float length, float angle, float pos_z)
{
    return glm::vec3(length*sin(angle), length*cos(angle), pos_z);
}

float getAngleInD(const glm::vec2& v_start, const glm::vec2 v_end)  // depr
{
    return glm::degrees(atan2(v_start.y - v_end.y, v_start.x - v_end.x));
}

float getAngle(const glm::vec2& v_start, const glm::vec2 v_end)
{
    return atan2(v_start.y - v_end.y, v_start.x - v_end.x);
}

float getAngleBetweenUnits(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::degrees(acos(dotUnits(v1, v2)));
}

float dotUnits(const glm::vec3& v1, const glm::vec3& v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}


glm::vec2 vec2(const glm::vec3& v3)
{
    return glm::vec2(v3.x, v3.y);
}

std::string str(const glm::vec2& v)
{
    return std::to_string(v.x)+","+std::to_string(v.y);
}

std::string str(const glm::vec3& v)
{
    return std::to_string(v.x)+","+std::to_string(v.y)+","+std::to_string(v.z);
}

} // namespace meti