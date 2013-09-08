
#include <vector>
#include <iostream>
#include <thread>
#include <ctime>
#include <cmath>
#include <glm/glm.hpp> // glm::vec
#include <math/Vec3.hpp>

const int NUM2 = 100000000;

void runVecMath_GLM()
{
glm::vec3 t;
std::cout<<t.x<<" "<<t.y<<" "<<t.z;

    glm::vec3 v1(2.0, 1.0, 3.0);
    glm::vec3 v2(2.0);
    glm::vec3 v3(0.0);
    for (int i=0; i<NUM2; i++)
    {
        v3 += glm::normalize(v1) + glm::normalize(v2) + v1 + v2*v1;
        v3 *= v1*glm::length(v3);
    }
}

void runVecMath_CUSTOM()
{
    Vec3<float> v1(2.0, 1.0, 3.0);
    Vec3<float> v2(2.0);
    Vec3<float> v3(0.0);
    for (int i=0; i<NUM2; i++)
    {  
        v3 += v1.GetNormalized() + v2.GetNormalized() + v1 + v2*v1;
        v3 *= v1*v3.GetLength();            
    }
}

void runVectorPerfomanceTest()
{
    {
        clock_t begin = clock();
        runVecMath_GLM();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GLM time in sec: "<<elapsed_secs<<std::endl;
    }
    
    {
        clock_t begin = clock();
        runVecMath_CUSTOM();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"CUSTOM time in sec: "<<elapsed_secs<<std::endl;
    }		
	exit(0);
}
	
