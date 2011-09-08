#include "vector.h"
                
vec2f :: vec2f()
{
        x = 0;
        y = 0;
}
    
vec2f :: vec2f(float _x, float _y)
{
        x = _x; 
        y = _y; 
}
            
void vec2f :: set(float _x, float _y) 
{ 
        x = _x; 
        y = _y; 
}





vec3f :: vec3f()
{
        x = 0;
        y = 0;
        y = 0;
}
    
vec3f :: vec3f(float _x, float _y, float _z)
{
        x = _x; 
        y = _y; 
        z = _z; 
}
            
void vec3f :: set(float _x, float _y, float _z) 
{ 
        x = _x; 
        y = _y; 
        z = _z; 
}
