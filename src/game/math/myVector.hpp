#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cmath>
float const RADIAN_TO_DEGREE_RATE = 180.0/M_PI;
float const DEGREE_TO_RADIAN_RATE = M_PI/180.0;

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Color4.hpp"

float distBetweenPoints(const Vec2<float>& center1, const Vec2<float>& center2);
float distBetweenPoints(const Vec2<float>& center1, float x2, float y2);
float distBetweenPoints(float x1, float y1, float x2, float y2);
Vec2<float> getVec2f(float length, float angle);
float getAngleInD(const Vec2<float>& v_start, const Vec2<float> v_end);


class Vector2f
{
	public:
		Vector2f(const Vec2<float>& p0, const Vec2<float>& p):p0(p0), p(p) {};
		~Vector2f() {};
		
		Vec2<float> p0;
		Vec2<float> p;
		

		float GetLength() const
		{
			return sqrt((p.x-p0.x)*(p.x-p0.x) + (p.y-p0.y)*(p.y-p0.y));
		}		
};

float getAngle(const Vector2f& v1, const Vector2f& v2);

#endif
