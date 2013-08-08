#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <math/Vec3.hpp>

template<typename VARTYPE>
class Vec2
{
    public:
        VARTYPE x; 
        VARTYPE y;
        
        Vec2():x(0), y(0) {};
        Vec2(VARTYPE x, VARTYPE y)   { Set(x, y); }
        Vec2(const Vec2<VARTYPE>& v) { Set(v.x, v.y); }
        Vec2(const Vec3<VARTYPE>& v) { Set(v.x, v.y); }
        ~Vec2() {};
        
        bool IsNull() const 
        {
            if ((x == 0) and (y == 0))    return true;
            else                        return false;
        }
        
        float GetLength() const { return sqrt(x*x+y*y); }
        
        Vec2<VARTYPE> GetNormalized() const 
        {
            float length = GetLength();
            if (length > 0)
            {
                return Vec2<VARTYPE>(x/length, y/length);
            }
            else
            {
                return *this;
            }
        }
        
        void Set(VARTYPE x, VARTYPE y)             { this->x = x; this->y = y; }
        void Set(const Vec2<VARTYPE>& v)        { *this = v; }
                
        Vec2<VARTYPE>& operator+=(const Vec2<VARTYPE>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            
            return *this;
        }
        
        Vec2<VARTYPE>& operator-=(const Vec2<VARTYPE>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            
            return *this;
        }
        
        Vec2<VARTYPE>& operator+=(VARTYPE val)
        {
            x += val;
            y += val;
            
            return *this;
        } 
        
        Vec2<VARTYPE>& operator*=(VARTYPE val)
        {
            x *= val;
            y *= val;
        
            return *this;
        } 
    
        Vec2<VARTYPE>& operator/=(VARTYPE val)
        {
            x /= val;
            y /= val;
        
            return *this;
        } 
            
        Vec2<VARTYPE> operator+(const Vec2<VARTYPE>& rhs) const
        {
            Vec2<VARTYPE> result(x+rhs.x, y+rhs.y);    
            return result;
        }
        
        Vec2<VARTYPE> operator-(const Vec2<VARTYPE>& rhs) const
        {
            Vec2<VARTYPE> result(x-rhs.x, y-rhs.y);    
            return result;
        }
        
        Vec2<VARTYPE> operator*(VARTYPE val) const
        {
            Vec2<VARTYPE> result(x*val, y*val);
            return result;
        }

        Vec2<VARTYPE> operator*(const Vec2<VARTYPE>& rhs) const
        {
            Vec2<VARTYPE> result(x*rhs.x, y*rhs.y);
            return result;
        }
                
        Vec2<VARTYPE> operator/(VARTYPE val) const
        {
            Vec2<VARTYPE> result(x/val, y/val);    
            return result;
        }
        
        //void operator()(const Vec2<VARTYPE>& v)
        //{
            //Set(v);
        //}

};

template<typename VARTYPE>
std::string str(Vec2<VARTYPE> v)
{
    std::stringstream ss;
    ss<<v.x<<","<<v.y<<".";
    return ss.str();
}

#endif
