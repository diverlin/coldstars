#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <sstream>
#include "Vec2.hpp"

template<typename VARTYPE>
class Vec3
{
        public:
                VARTYPE x;
                VARTYPE y;
                VARTYPE z;
                
                Vec3():x(0), y(0), z(0) {}
                Vec3(float val):x(val), y(val), z(val) {}
                Vec3(VARTYPE x, VARTYPE y, VARTYPE z):x(x), y(y), z(z) {}
                Vec3(const Vec3<VARTYPE>& v) { *this = v; }
                ~Vec3() {};
                
                void Set(VARTYPE x, VARTYPE y, VARTYPE z) 
                { 
                	this->x = x; 
                	this->y = y; 
                	this->z = z; 
                }
		
		void Set(const Vec3<VARTYPE>& v) { *this = v; };
		                
		bool IsNull() const 
                {
			if ((x == 0) and (y == 0) and (z == 0)) return true;
			else    		   		return false;
		}
                
                float GetLength() const { return sqrt(x*x+y*y+z*z); }
                
                Vec3<VARTYPE> GetNormalized() const 
                {
                	float length = GetLength();
                	if (length > 0)
                	{
				return Vec3<VARTYPE>(x/length, y/length, z/length);
                	}
                	else
                	{
                		return *this;
                	}
                }

                void Normalize() 
                {
                	float length = GetLength();
                	if (length > 0)
                	{
				x /= length;
				y /= length;
				z /= length;
			}
                }
                                
		const Vec3<VARTYPE>& operator+=(const Vec3<VARTYPE>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;	
			
			return *this;
		}
		
		const Vec3<VARTYPE>& operator*=(VARTYPE val)
		{
			x *= val;
			y *= val;
			z *= val;	
			
			return *this;
		}

		const Vec3<VARTYPE>& operator/=(VARTYPE val)
		{
			x /= val;
			y /= val;
			z /= val;	
			
			return *this;
		}
		
		Vec3<VARTYPE> operator*(VARTYPE val) const
                {
                	Vec3<VARTYPE> result(x*val, y*val, z*val);
			return result;
                }
                
                Vec3<VARTYPE> operator+(const Vec3<VARTYPE>& rhs) const
                {
                	Vec3<VARTYPE> result(x+rhs.x, y+rhs.y, z+rhs.z);	
			return result;
                }

                Vec3<VARTYPE> operator-(const Vec3<VARTYPE>& rhs) const
                {
                	Vec3<VARTYPE> result(x-rhs.x, y-rhs.y, z-rhs.z);	
			return result;
                }                
	
                //Vec3<VARTYPE> operator+(const Vec2<VARTYPE>& rhs) const
                //{
                	//Vec3<VARTYPE> result(x+rhs.x, y+rhs.y, z);	
			//return result;
                //}
                                
                //float GetDistanceTo(const Vec3<VARTYPE> v) const
                //{
                        //float lx = v.x - x;
        		//float ly = v.y - y;
        		//float lz = v.z - z;
        		    
        		//return sqrt(lx*lx + ly*ly + lz*lz);
                //}

                //float GetDistanceTo(float x, float y, float z) const
                //{
                        //float lx = x - this->x;
        		//float ly = y - this->y;
        		//float lz = z - this->z;
        		    
        		//return sqrt(lx*lx + ly*ly + lz*lz);
                //}
                                
                //Vec2<VARTYPE> GetXY() const
                //{
                	//Vec2<VARTYPE> result(x, y);
                	//return result;
                //}
  
};

template<typename VARTYPE>
std::string str(Vec3<VARTYPE> v)
{
	std::stringstream ss;
	ss<<v.x<<","<<v.y<<","<<v.z<<".";
	return ss.str();
}

#endif
