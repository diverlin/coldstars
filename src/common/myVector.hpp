#ifndef MYVECTOR_H
#define MYVECTOR_H


class vec2f
{
        public:
                float x; 
                float y;
                
                vec2f():x(0.0), y(0.0) {};
                vec2f(float x, float y) { this->x = x; this->y = y; };
                vec2f(const vec2f& v) { *this = v; };
                ~vec2f() {};
                                                
                bool IsNull() const;
                
                float GetLen() const;
                vec2f GetNorm() const;
                
		void Set(float x, float y) 	{ this->x = x; this->y = y; }
                void Set(const vec2f& v)    	{ *this = v; };
                
                vec2f& operator+=(const vec2f&);                
                vec2f& operator+=(float);  
                
                vec2f operator+(const vec2f&) const;
                vec2f operator-(const vec2f&) const;
                vec2f operator*(float) const;
                vec2f operator/(float) const;
                
                void operator()(const vec2f&);
};


class Vector2f
{
	public:
		Vector2f(const vec2f& p0, const vec2f& p):p0(p0), p(p) {};
		~Vector2f() {};
		
		vec2f p0;
		vec2f p;
		
		float GetLen() const;
		
		
};

float getAngle(const Vector2f&, const Vector2f&);



class vec2i
{
	public:
	        int x; 
                int y;
                
                vec2i():x(0), y(0) {};
                vec2i(int x, int y) { this->x = x; this->y = y; };
                vec2i(const vec2i& v) { *this = v; } ;
                ~vec2i() {};
                		
};

class vec3f
{
        public:
                float x;
                float y;
                float z;
                
                vec3f():x(0.0), y(0.0), z(0.0) {};
                vec3f(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
                vec3f(const vec3f& v) { *this = v; };
                ~vec3f() {};
                
                void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
                const vec3f& operator+=(const vec3f&);     
};



struct Color4f
{
	float r;
	float g;
	float b;
	float a;

	Color4f(): r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	Color4f(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {}
};


struct Color4i
{
	int r;
	int g;
	int b;
	int a;
	
	Color4i(): r(255), g(255), b(255), a(255) {}
	Color4i(int r, int g, int b, int a): r(r), g(g), b(b), a(a) {}
};



float distBetweenPoints(const vec2f&, const vec2f&);
float distBetweenPoints(const vec2f& center1, float x2, float y2);
float distBetweenPoints(float x1, float y1, float x2, float y2);

vec2i getVec2i(int len, int angle);

vec2f getRandVec2f(int radius_min, int radius_max);
#endif
