#pragma once

#include <boost/serialization/map.hpp>

#include <glm/glm.hpp>

#include <string>

namespace meti {

class vec3 : public glm::vec3
{
public:
    vec3(float x, float y, float z):glm::vec3(x,y,z) {}
    vec3(float val):glm::vec3(val) {}
    vec3(glm::vec3 v):glm::vec3(v) {}
    vec3():glm::vec3() {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & x;
        ar & y;
        ar & z;
    }
};

vec3 normalize(const vec3&);

float distance(const glm::vec3& center1, const glm::vec3& center2);
float distance(const glm::vec3& center1, const glm::vec2& center2);
float distance(const glm::vec2& center1, const glm::vec3& center2);
float distance(const glm::vec3& center1, float x2, float y2, float z2);
float distance(const glm::vec2& center1, const glm::vec2& center2);
float distance(const glm::vec2& center1, float x2, float y2);
float distance(const glm::vec3& center1, float x2, float y2);  
float distance(float x1, float y1, float x2, float y2);

glm::vec2 genVec2f(float length, float angle);
glm::vec3 genVec3f(float length, float angle, float);
float getAngleInD(const glm::vec2& v_start, const glm::vec2 v_end);

float getAngle(const glm::vec2&, const glm::vec2);

float getAngleBetweenUnits(const glm::vec3&, const glm::vec3&);
float dotUnits(const glm::vec3& v1, const glm::vec3& v2);

glm::vec3 getXYVec3Unit(float);

glm::vec2 vec2(const glm::vec3&);

std::string str(const glm::vec2&);
std::string str(const glm::vec3&);

} // namespace meti
