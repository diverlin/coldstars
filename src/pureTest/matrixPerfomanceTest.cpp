
#include <iostream>
#include <ctime>
#include <cmath>
#include <glm/glm.hpp> // glm::vec
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

const int NUM3 = 1000000;

void runMatrixMath_GLM1()
{
    glm::vec3 v(2.0);
    
    glm::mat4 Tm;
    glm::mat4 Sm;
    glm::mat4 Rxm;
    glm::mat4 Rym;
    glm::mat4 Rzm;
    
    glm::mat4 PVm;
    glm::mat4 Mm;
    glm::mat4 PVMm;
        
    for (int i=0; i<NUM3; i++)
    {
        Tm = glm::translate(Tm, v);
        Sm = glm::scale(Sm, v);
        Rxm = glm::rotate(glm::mat4(1.0), v.x, v);
        Rym = glm::rotate(glm::mat4(1.0), v.y, v);
        Rzm = glm::rotate(glm::mat4(1.0), v.z, v);
            
        Mm = Tm*Sm*(Rxm*Rym*Rzm);
        PVMm = PVm*Mm;
        glLoadMatrixf(&PVMm[0][0]); 
    }
}

void runMatrixMath_GLM2()
{
    glm::vec3 v(2.0);
    
    glm::mat4 Tm;
    glm::mat4 Sm;
    glm::mat4 Rxm;
    glm::mat4 Rym;
    glm::mat4 Rzm;
            
    glm::mat4 PVm;
    glm::mat4 Mm;
    glm::mat4 PVMm;
        
    for (int i=0; i<NUM3; i++)
    {
        Tm = glm::translate(v);
        Sm = glm::scale(v);
        Rxm = glm::rotate(v.x, v);
        Rym = glm::rotate(v.y, v);
        Rzm = glm::rotate(v.z, v);
        
        Mm = Tm*Sm*(Rxm*Rym*Rzm);
        PVMm = PVm*Mm;
        glLoadMatrixf(&PVMm[0][0]); 
    }
}

void runMatrixMath_GLM3()
{
    glm::vec3 v(2.0);
    
    glm::mat4 PVTm;
    glm::mat4 PVTSm;
    glm::mat4 PVTSRxm;
    glm::mat4 PVTSRxRym;
    glm::mat4 PVTSRxRyRzm;
            
    glm::mat4 PVm;
    glm::mat4 Mm;
    glm::mat4 PVMm;
        
    for (int i=0; i<NUM3; i++)
    {
        PVTm = glm::translate(PVm, v);
        PVTSm = glm::scale(PVTm, v);
        PVTSRxm = glm::rotate(PVTSm, v.x, v);
        PVTSRxRym = glm::rotate(PVTSRxm, v.x, v);
        PVTSRxRyRzm = glm::rotate(PVTSRxRym, v.x, v);
                
        glLoadMatrixf(&PVTSRxRyRzm[0][0]); 
    }
}

void runMatrixMath_GLM_QUATERNIONS()
{
    glm::vec3 v(2.0);
    
    glm::mat4 Tm;
    glm::mat4 Sm;
    glm::mat4 Rm;

    glm::quat Q;    
    glm::quat Qf;
    glm::quat Ql; 
    glm::quat Qu;
      
    glm::mat4 PVm;
    glm::mat4 Mm;
    glm::mat4 PVMm;
        
    for (int i=0; i<NUM3; i++)
    {
        Tm = glm::translate(v);
        Sm = glm::scale(v);
        
        v = glm::cross(v, v);
        v = glm::cross(v, v);
        
        Qf = glm::quat(30.0, v);
        Ql = glm::quat(10.0, v);
        Qu = glm::quat(20.0, v);
                        
        Q = Qf*Ql*Qu;
        Rm = glm::toMat4(Q);
        Mm = Tm*Sm*Rm;
        PVMm = PVm*Mm;
        glLoadMatrixf(&PVMm[0][0]); 
    }
}

void runMatrixMath_GL()
{
    glm::vec3 v(2.0);

    for (int i=0; i<NUM3; i++)
    {
        glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glScalef(v.x, v.y, v.z);
            glRotatef(v.x, 1, 0, 0);
            glRotatef(v.y, 0, 1, 0);
            glRotatef(v.z, 0, 0, 1);                        
        glPopMatrix();
    }
}

void runMatrixPerfomanceTest()
{
    {
        clock_t begin = clock();
        runMatrixMath_GLM1();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GLM1 time in sec: "<<elapsed_secs<<std::endl;
    }

    {
        clock_t begin = clock();
        runMatrixMath_GLM2();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GLM2 time in sec: "<<elapsed_secs<<std::endl;
    }

    {
        clock_t begin = clock();
        runMatrixMath_GLM3();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GLM3 time in sec: "<<elapsed_secs<<std::endl;
    }

    {
        clock_t begin = clock();
        runMatrixMath_GLM_QUATERNIONS();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GLM_QUATERNIONS time in sec: "<<elapsed_secs<<std::endl;
    }
                
    {
        clock_t begin = clock();
        runMatrixMath_GL();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"GL time in sec: "<<elapsed_secs<<std::endl;
    }		
	exit(0);
}     	

//const int NUM3 = 1000000; 

//standart
// athlon x4 2.4Ghz
//GLM1 time in sec: 10.4
//GLM2 time in sec: 10.74
//GLM3 time in sec: 4.6
//GLM_QUATERNIONS time in sec: 5.06
//GL time in sec: 0.35

//Trinity x4 3.4Ghz
//GLM1 time in sec: 5.27
//GLM2 time in sec: 5.47
//GLM3 time in sec: 2.42
//GLM_QUATERNIONS time in sec: 2.49
//GL time in sec: 0.2


// O2,-native
//GLM1 time in sec: 0.46
//GLM2 time in sec: 0.48
//GLM3 time in sec: 0.16
//GLM_QUATERNIONS time in sec: 0.28
//GL time in sec: 0.33


// O3,-native
// athlon x4 2.4Ghz
//GLM1 time in sec: 0.17
//GLM2 time in sec: 0.08
//GLM3 time in sec: 0.12
//GLM_QUATERNIONS time in sec: 0.12
//GL time in sec: 0.33
   
//Trinity x4 3.4Ghz   
//GLM1 time in sec: 0.09
//GLM2 time in sec: 0.06
//GLM3 time in sec: 0.06
//GLM_QUATERNIONS time in sec: 0.08
//GL time in sec: 0.2


// Ofast,-native
//Athlon x4 2.4Ghz
//GLM1 time in sec: 0.16
//GLM2 time in sec: 0.08
//GLM3 time in sec: 0.12
//GLM_QUATERNIONS time in sec: 0.06
//GL time in sec: 0.32

//Trinity x4 3.4Ghz 
//GLM1 time in sec: 0.09
//GLM2 time in sec: 0.05
//GLM3 time in sec: 0.06
//GLM_QUATERNIONS time in sec: 0.05
//GL time in sec: 0.2

