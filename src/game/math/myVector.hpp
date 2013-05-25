#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cmath>
float const RADIAN_TO_DEGREE_RATE = 180.0/M_PI;
float const DEGREE_TO_RADIAN_RATE = M_PI/180.0;

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Color4.hpp"

float distanceBetween(const Vec3<float>& center1, const Vec3<float>& center2);
float distanceBetween(const Vec3<float>& center1, float x2, float y2, float z2);
float distanceBetween(const Vec2<float>& center1, const Vec2<float>& center2);
float distanceBetween(const Vec2<float>& center1, float x2, float y2);

float distanceBetween(float x1, float y1, float x2, float y2);

Vec2<float> getVec2f(float length, float angle);
Vec3<float> getVec3f(float length, float angle, float);
float getAngleInD(const Vec2<float>& v_start, const Vec2<float> v_end);

float getAngleBetweenUnits(const Vec3<float>&, const Vec3<float>&);
float dotUnits(const Vec3<float>& v1, const Vec3<float>& v2);

Vec2<float> getRandVec2f(int radius_min, int radius_max);
Vec3<float> getRandXYVec3f(int radius_min, int radius_max, float z);
Vec3<float> getRandXYVec3Unit();

#endif
