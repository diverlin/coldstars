#ifndef MYVECTOR_H
#define VMYECTOR_H

class vec2f
{
        public:
                float x; 
                float y;
                
                vec2f();
                vec2f(float _x, float _y);
                
                void set(float _x, float _y);
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

vec2f getRandomVec(vec2f center, int radius_min, int radius_max);

#endif
