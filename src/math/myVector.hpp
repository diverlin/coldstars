#pragma once

#include <glm/glm.hpp>
#include <string>

float const RADIAN_TO_DEGREE_RATE = 180.0/M_PI;
float const DEGREE_TO_RADIAN_RATE = M_PI/180.0;

float distanceBetween(const glm::vec3& center1, const glm::vec3& center2);
float distanceBetween(const glm::vec3& center1, const glm::vec2& center2);
float distanceBetween(const glm::vec2& center1, const glm::vec3& center2);
float distanceBetween(const glm::vec3& center1, float x2, float y2, float z2);
float distanceBetween(const glm::vec2& center1, const glm::vec2& center2);
float distanceBetween(const glm::vec2& center1, float x2, float y2);
float distanceBetween(const glm::vec3& center1, float x2, float y2);  
float distanceBetween(float x1, float y1, float x2, float y2);

glm::vec2 getVec2f(float length, float angle);
glm::vec3 getVec3f(float length, float angle, float);
float getAngleInD(const glm::vec2& v_start, const glm::vec2 v_end);

float getAngle(const glm::vec2&, const glm::vec2);

float getAngleBetweenUnits(const glm::vec3&, const glm::vec3&);
float dotUnits(const glm::vec3& v1, const glm::vec3& v2);

glm::vec3 getXYVec3Unit(float);


glm::vec2 vec3ToVec2(const glm::vec3&);

std::string str(const glm::vec3&);

