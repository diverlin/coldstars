#ifndef MYVECTOR_H
#define MYVECTOR_H

class vec2f
{
        public:
                float x; 
                float y;
                
                vec2f():x(0), y(0) {};
                vec2f(float x, float y) { this->x = x; this->y = y; };
                vec2f(const vec2f& v) { *this = v; } ;
                                
                bool IsNull() const;
                
                float GetLen() const;
                vec2f GetNorm() const;
                
		void Set(float x, float y) 	{ this->x = x; this->y = y; }
                void Set(const vec2f& v)    	{ *this = v; };
                
                vec2f operator+=(const vec2f&);                
                vec2f operator+=(float);  
                
                vec2f operator+(const vec2f&) const;
                vec2f operator-(const vec2f&) const;
                vec2f operator*(const float) const;
                vec2f operator/(const float) const;
};

class vec3f
{
        public:
                float x;
                float y;
                float z;
                
                vec3f();
                vec3f(float _x, float _y, float _z);
                
                void set(float _x, float _y, float _z);
};

float distBetweenPoints(vec2f, vec2f);
float distBetweenPoints(vec2f center1, float x2, float y2);
float distBetweenPoints(float x1, float y1, float x2, float y2);

vec2f getRandVec(int radius_min, int radius_max);
#endif
