#ifndef VECTOR_H
#define VECTOR_H

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

float distBetweenCenters(vec2f, vec2f);
float distBetweenCenters(vec2f center1, float x2, float y2);
float distBetweenCenters(float x1, float y1, float x2, float y2);

#endif
