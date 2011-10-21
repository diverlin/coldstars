/*
Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/



#include "points.hpp"


Points :: Points()
{
        is_updated = false;  
        pos_z = -500.0;           
}

Points :: ~Points()
{}
  
void Points :: setPosZ(float _pos_z) { pos_z = _pos_z; }
    
int Points :: getWidth()  const { return w; }
int Points :: getHeight() const { return h; }
                
float Points :: getAngleDegree() const { return angle_inD; }   	
float* Points :: getpAngleDegree() { return &angle_inD; }
        
float Points :: getPosZ() const { return pos_z; }
                	
vec2f Points :: getCenter()      const { return center; }     
vec2f* Points :: getpCenter()    { return &center; }  
      
vec2f Points :: getBottomLeft()  const { return bottomLeft; }
vec2f Points :: getBottomRight() const { return bottomRight; }
vec2f Points :: getTopRight()    const { return topRight; }    
vec2f Points :: getTopLeft()     const { return topLeft; }
    
    
vec2f Points :: getBottomLeftShield()  const { return bottomLeftShield; }
vec2f Points :: getBottomRightShield() const { return bottomRightShield; }
vec2f Points :: getTopRightShield()    const { return topRightShield; }
vec2f Points :: getTopLeftShield()     const { return topLeftShield; }
                
vec2f* Points :: getpMidLeft()    { return &midLeft; }
vec2f* Points :: getpMidFarLeft() { return &midFarLeft; }
          
vec2f* Points :: getpWeapon1Center() { return &weapon_1_center; }
vec2f* Points :: getpWeapon2Center() { return &weapon_2_center; }
vec2f* Points :: getpWeapon3Center() { return &weapon_3_center; }
vec2f* Points :: getpWeapon4Center() { return &weapon_4_center; }
vec2f* Points :: getpWeapon5Center() { return &weapon_5_center; }
                   
                

void Points :: initCenterPoint()
{ 
        center_origin.set(0, 0);
        center.set(0, 0);
}  

void Points :: addCenterPoint()
{ 
        vector_orig_x.push_back(&center_origin.x);
        vector_orig_y.push_back(&center_origin.y);

        vector_x.push_back(&center.x);
        vector_y.push_back(&center.y);
}
     




void Points :: initWeapon1CenterPoint(float _pos_x, float _pos_y)
{ 
        weapon_1_origin_center.set(_pos_x, _pos_y);
        weapon_1_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon1CenterPoint()
{ 
        vector_orig_x.push_back(&weapon_1_origin_center.x);
        vector_orig_y.push_back(&weapon_1_origin_center.y);

        vector_x.push_back(&weapon_1_center.x);
        vector_y.push_back(&weapon_1_center.y);
}




void Points :: initWeapon2CenterPoint(float _pos_x, float _pos_y)
{
        weapon_2_origin_center.set(_pos_x, _pos_y);
        weapon_2_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon2CenterPoint()
{
        vector_orig_x.push_back(&weapon_2_origin_center.x);
        vector_orig_y.push_back(&weapon_2_origin_center.y);

        vector_x.push_back(&weapon_2_center.x);
        vector_y.push_back(&weapon_2_center.y);
}






void Points :: initWeapon3CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_3_origin_center.set(_pos_x, _pos_y);
     	weapon_3_center.set(_pos_x, _pos_y);
}
  
void Points :: addWeapon3CenterPoint()
{
     	vector_orig_x.push_back(&weapon_3_origin_center.x);
     	vector_orig_y.push_back(&weapon_3_origin_center.y);

     	vector_x.push_back(&weapon_3_center.x);
     	vector_y.push_back(&weapon_3_center.y);
}




void Points :: initWeapon4CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_4_origin_center.set(_pos_x, _pos_y);
     	weapon_4_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon4CenterPoint()
{
     	vector_orig_x.push_back(&weapon_4_origin_center.x);
     	vector_orig_y.push_back(&weapon_4_origin_center.y);

     	vector_x.push_back(&weapon_4_center.x);
     	vector_y.push_back(&weapon_4_center.y);
}





    
void Points :: initWeapon5CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_5_origin_center.set(_pos_x, _pos_y);
     	weapon_5_center.set(_pos_x, _pos_y);
}
   
void Points :: addWeapon5CenterPoint()
{
     	vector_orig_x.push_back(&weapon_5_origin_center.x);
     	vector_orig_y.push_back(&weapon_5_origin_center.y);

     	vector_x.push_back(&weapon_5_center.x);
     	vector_y.push_back(&weapon_5_center.y);
}
   



void Points :: initMainQuadPoints(int _w, int _h)
{ 
        setWidthHeight(_w, _h);  

        ////// Origin entity rect (for rotation only transformation)
        bottomLeft_origin.set(-w/2, -h/2);
        bottomRight_origin.set(+w/2, -h/2);
        topRight_origin.set(+w/2, +h/2);
        topLeft_origin.set(-w/2, +h/2);
      
        ///////////////////////////////////////////
        ////// Actual entity rect
        bottomLeft.set(-w/2, -h/2);
        bottomRight.set(+w/2, -h/2);
        topRight.set(+w/2, +h/2);
        topLeft.set(-w/2, +h/2);
}





          
void Points :: addMainQuadPoints()
{ 
      	/////////////////////////////////////////////////////////////
      	////// Origin entity rect (for rotation only transformation)
      	vector_orig_x.push_back(&bottomLeft_origin.x);
      	vector_orig_y.push_back(&bottomLeft_origin.y);
      
      	vector_orig_x.push_back(&bottomRight_origin.x);
      	vector_orig_y.push_back(&bottomRight_origin.y);
      
      	vector_orig_x.push_back(&topRight_origin.x);
      	vector_orig_y.push_back(&topRight_origin.y);
                
      	vector_orig_x.push_back(&topLeft_origin.x);
      	vector_orig_y.push_back(&topLeft_origin.y);
      
      	///////////////////////////////////////////
      	////// Actual entity rect
      	vector_x.push_back(&bottomLeft.x);
      	vector_y.push_back(&bottomLeft.y);
      
      	vector_x.push_back(&bottomRight.x);
      	vector_y.push_back(&bottomRight.y);
      
      	vector_x.push_back(&topRight.x);
      	vector_y.push_back(&topRight.y);
                 
      	vector_x.push_back(&topLeft.x);
      	vector_y.push_back(&topLeft.y);
}



void Points :: initShieldQuadPoints()
{ 
     	float factor = 1.6;
     
     	// Origin entity rect (for rotation only transformation)
     	bottomLeftShield_origin.set(-w/factor, -h/factor);
     	bottomRightShield_origin.set(+w/factor, -h/factor);
     	topRightShield_origin.set(+w/factor, +h/factor);
     	topLeftShield_origin.set(-w/factor, +h/factor);


     	// Actual entity rect
     	bottomLeftShield.set(-w/factor, -h/factor);
     	bottomRightShield.set(+w/factor, -h/factor);
     	topRightShield.set(+w/factor, +h/factor);
     	topLeftShield.set(-w/factor, +h/factor);
}





void Points :: addShieldQuadPoints()
{ 
     	// Origin entity rect (for rotation only transformation)
     	vector_orig_x.push_back(&bottomLeftShield_origin.x);
     	vector_orig_y.push_back(&bottomLeftShield_origin.y);

     	vector_orig_x.push_back(&bottomRightShield_origin.x);
     	vector_orig_y.push_back(&bottomRightShield_origin.y);

     	vector_orig_x.push_back(&topRightShield_origin.x);
     	vector_orig_y.push_back(&topRightShield_origin.y);

     	vector_orig_x.push_back(&topLeftShield_origin.x);
     	vector_orig_y.push_back(&topLeftShield_origin.y);


     	// Actual entity rect
     	vector_x.push_back(&bottomLeftShield.x);
     	vector_y.push_back(&bottomLeftShield.y);

     	vector_x.push_back(&bottomRightShield.x);
     	vector_y.push_back(&bottomRightShield.y);

     	vector_x.push_back(&topRightShield.x);
     	vector_y.push_back(&topRightShield.y);

     	vector_x.push_back(&topLeftShield.x);
     	vector_y.push_back(&topLeftShield.y);
}




void Points :: initMidLeftPoint()
{
     	midLeft_origin.set(-w/2, 0);
     	midLeft.set(-w/2, 0);
}

void Points :: addMidLeftPoint()
{
     	vector_orig_x.push_back(&midLeft_origin.x);
     	vector_orig_y.push_back(&midLeft_origin.y);

     	vector_x.push_back(&midLeft.x);
     	vector_y.push_back(&midLeft.y);
}




void Points :: initMidFarLeftPoint()
{
     	midFarLeft_origin.set(-w, 0);
     	midFarLeft.set(-w, 0);
}

void Points :: addMidFarLeftPoint()
{
     	vector_orig_x.push_back(&midFarLeft_origin.x);
     	vector_orig_y.push_back(&midFarLeft_origin.y);

     	vector_x.push_back(&midFarLeft.x);
     	vector_y.push_back(&midFarLeft.y);
}



void Points :: setWidthHeight(int _w, int _h)
{
        w = _w;
        h = _h;
}  



void Points :: setCenter(float _centerx, float _centery) 
{
    	center.set(_centerx, _centery);
      
    	is_updated = false;       
}
       

void  Points :: setCenter(vec2f _center)
{
    	center.set(_center.x, _center.y);
      
    	is_updated = false;   
}
                       
    
void Points :: setAngle(float _angle_inD)
{ 
    	angle_inD = _angle_inD;
    
    	is_updated = false; 
}  


void Points :: update()
{
    	if (is_updated == false)
    	{   
        	float pos_x = center.x;
        	float pos_y = center.y;

        	float angle_degree = angle_inD;
       		float angle_radian = angle_degree/57.295779;
         
        	float cosa = cos(angle_radian);
        	float sina = sin(angle_radian);
 
        	for (unsigned int i = 0; i < vector_x.size(); i++)
        	{   
           		////// rotation around center
            		(*vector_x[i]) = (*vector_orig_x[i]) * cosa - (*vector_orig_y[i]) * sina;
            		(*vector_y[i]) = (*vector_orig_x[i]) * sina + (*vector_orig_y[i]) * cosa;  
            		////// moving to position
            		(*vector_x[i]) += pos_x;
            		(*vector_y[i]) += pos_y;
        	}   
        	is_updated = true;
    	}
}        


 
          





       




