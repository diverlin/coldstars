#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

template<typename VARTYPE>
class Vec3
{
        public:
                VARTYPE x;
                VARTYPE y;
                VARTYPE z;
                
                Vec3():x(0), y(0), z(0) {}
                Vec3(VARTYPE x, VARTYPE y, VARTYPE z):x(x), y(y), z(z) {}
                Vec3(const Vec3<VARTYPE>& v) { *this = v; }
                ~Vec3() {};
                
                void Set(VARTYPE x, VARTYPE y, VARTYPE z) 
                { 
                	this->x = x; 
                	this->y = y; 
                	this->z = z; 
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
  
};

#endif
