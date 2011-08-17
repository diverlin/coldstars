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



#include "points.h"

Points :: Points()
{
   is_updated = false;             
}

Points :: ~Points()
{}
  


void Points :: initCenterPoint()
{ 
      center_origin_x    = 0;
      center_origin_y    = 0;

      center_x    = 0;
      center_y    = 0;
}  

void Points :: addCenterPoint()
{ 
      vector_orig_x.push_back(&center_origin_x);
      vector_orig_y.push_back(&center_origin_y);

      vector_x.push_back(&center_x);
      vector_y.push_back(&center_y);
}
     




void Points :: initWeapon1CenterPoint(float _pos_x, float _pos_y)
{ 
     weapon1_origin_center_x = _pos_x;      
     weapon1_origin_center_y = _pos_y;

     weapon1_center_x = _pos_x;      
     weapon1_center_y = _pos_y;
}

void Points :: addWeapon1CenterPoint()
{ 
     vector_orig_x.push_back(&weapon1_origin_center_x);
     vector_orig_y.push_back(&weapon1_origin_center_y);

     vector_x.push_back(&weapon1_center_x);
     vector_y.push_back(&weapon1_center_y);
}




void Points :: initWeapon2CenterPoint(float _pos_x, float _pos_y)
{
     weapon2_origin_center_x = _pos_x;      
     weapon2_origin_center_y = _pos_y;

     weapon2_center_x = _pos_x;      
     weapon2_center_y = _pos_y;
}

void Points :: addWeapon2CenterPoint()
{
     vector_orig_x.push_back(&weapon2_origin_center_x);
     vector_orig_y.push_back(&weapon2_origin_center_y);

     vector_x.push_back(&weapon2_center_x);
     vector_y.push_back(&weapon2_center_y);
}






void Points :: initWeapon3CenterPoint(float _pos_x, float _pos_y)
{
     weapon3_origin_center_x = _pos_x;      
     weapon3_origin_center_y = _pos_y;

     weapon3_center_x = _pos_x;      
     weapon3_center_y = _pos_y;
}
  
void Points :: addWeapon3CenterPoint()
{
     vector_orig_x.push_back(&weapon3_origin_center_x);
     vector_orig_y.push_back(&weapon3_origin_center_y);

     vector_x.push_back(&weapon3_center_x);
     vector_y.push_back(&weapon3_center_y);
}




void Points :: initWeapon4CenterPoint(float _pos_x, float _pos_y)
{
     weapon4_origin_center_x = _pos_x;      
     weapon4_origin_center_y = _pos_y;

     weapon4_center_x = _pos_x;      
     weapon4_center_y = _pos_y;
}

void Points :: addWeapon4CenterPoint()
{
     vector_orig_x.push_back(&weapon4_origin_center_x);
     vector_orig_y.push_back(&weapon4_origin_center_y);

     vector_x.push_back(&weapon4_center_x);
     vector_y.push_back(&weapon4_center_y);
}





    
void Points :: initWeapon5CenterPoint(float _pos_x, float _pos_y)
{
     weapon5_origin_center_x = _pos_x;      
     weapon5_origin_center_y = _pos_y;

     weapon5_center_x = _pos_x;      
     weapon5_center_y = _pos_y;
}
   
void Points :: addWeapon5CenterPoint()
{
     vector_orig_x.push_back(&weapon5_origin_center_x);
     vector_orig_y.push_back(&weapon5_origin_center_y);

     vector_x.push_back(&weapon5_center_x);
     vector_y.push_back(&weapon5_center_y);
}
   



void Points :: initMainQuadPoints(int _w, int _h)
{ 
      w = _w;
      h = _h;

      ////// Origin entity rect (for rotation only transformation)
      bottomLeft_origin_x  = -w/2;
      bottomLeft_origin_y  = -h/2;
      
      bottomRight_origin_x = +w/2;
      bottomRight_origin_y = -h/2;
      
      topRight_origin_x    = +w/2;
      topRight_origin_y    = +h/2;
                
      topLeft_origin_x     = -w/2;
      topLeft_origin_y     = +h/2;
      
      ///////////////////////////////////////////
      ////// Actual entity rect
      bottomLeft_x  = -w/2;
      bottomLeft_y  = -h/2;
      
      bottomRight_x = +w/2;
      bottomRight_y = -h/2;
      
      topRight_x    = +w/2;
      topRight_y    = +h/2;
                 
      topLeft_x     = -w/2;
      topLeft_y     = +h/2;
}





          
void Points :: addMainQuadPoints()
{ 
      /////////////////////////////////////////////////////////////
      ////// Origin entity rect (for rotation only transformation)
      vector_orig_x.push_back(&bottomLeft_origin_x);
      vector_orig_y.push_back(&bottomLeft_origin_y);
      
      vector_orig_x.push_back(&bottomRight_origin_x);
      vector_orig_y.push_back(&bottomRight_origin_y);
      
      vector_orig_x.push_back(&topRight_origin_x);
      vector_orig_y.push_back(&topRight_origin_y);
                
      vector_orig_x.push_back(&topLeft_origin_x);
      vector_orig_y.push_back(&topLeft_origin_y);
      
      ///////////////////////////////////////////
      ////// Actual entity rect
      vector_x.push_back(&bottomLeft_x);
      vector_y.push_back(&bottomLeft_y);
      
      vector_x.push_back(&bottomRight_x);
      vector_y.push_back(&bottomRight_y);
      
      vector_x.push_back(&topRight_x);
      vector_y.push_back(&topRight_y);
                 
      vector_x.push_back(&topLeft_x);
      vector_y.push_back(&topLeft_y);
}



void Points :: initShieldQuadPoints()
{ 
     float factor = 1.6;
     
     // Origin entity rect (for rotation only transformation)
     bottomLeftShield_origin_x = -w/factor;
     bottomLeftShield_origin_y = -h/factor;

     bottomRightShield_origin_x = +w/factor;
     bottomRightShield_origin_y = -h/factor;

     topRightShield_origin_x    = +w/factor;
     topRightShield_origin_y    = +h/factor;

     topLeftShield_origin_x     = -w/factor;
     topLeftShield_origin_y     = +h/factor;


     // Actual entity rect
     bottomLeftShield_x         = -w/factor;
     bottomLeftShield_y         = -h/factor;

     bottomRightShield_x        = +w/factor;
     bottomRightShield_y        = -h/factor;

     topRightShield_x           = +w/factor;
     topRightShield_y           = +h/factor;

     topLeftShield_x            = -w/factor;
     topLeftShield_y            = +h/factor;
}





void Points :: addShieldQuadPoints()
{ 
     // Origin entity rect (for rotation only transformation)
     vector_orig_x.push_back(&bottomLeftShield_origin_x);
     vector_orig_y.push_back(&bottomLeftShield_origin_y);

     vector_orig_x.push_back(&bottomRightShield_origin_x);
     vector_orig_y.push_back(&bottomRightShield_origin_y);

     vector_orig_x.push_back(&topRightShield_origin_x);
     vector_orig_y.push_back(&topRightShield_origin_y);

     vector_orig_x.push_back(&topLeftShield_origin_x);
     vector_orig_y.push_back(&topLeftShield_origin_y);


     // Actual entity rect
     vector_x.push_back(&bottomLeftShield_x);
     vector_y.push_back(&bottomLeftShield_y);

     vector_x.push_back(&bottomRightShield_x);
     vector_y.push_back(&bottomRightShield_y);

     vector_x.push_back(&topRightShield_x);
     vector_y.push_back(&topRightShield_y);

     vector_x.push_back(&topLeftShield_x);
     vector_y.push_back(&topLeftShield_y);
}




void Points :: initMidLeftPoint()
{
     midLeft_origin_x = -w/2;
     midLeft_origin_y = 0;

     midLeft_x        = -w/2;
     midLeft_y        = 0;
}

void Points :: addMidLeftPoint()
{
     vector_orig_x.push_back(&midLeft_origin_x);
     vector_orig_y.push_back(&midLeft_origin_y);

     vector_x.push_back(&midLeft_x);
     vector_y.push_back(&midLeft_y);
}




void Points :: initMidFarLeftPoint()
{
     midFarLeft_origin_x = -w;
     midFarLeft_origin_y = 0;

     midFarLeft_x        = -w;
     midFarLeft_y        = 0;
}

void Points :: addMidFarLeftPoint()
{
     vector_orig_x.push_back(&midFarLeft_origin_x);
     vector_orig_y.push_back(&midFarLeft_origin_y);

     vector_x.push_back(&midFarLeft_x);
     vector_y.push_back(&midFarLeft_y);
}





void Points :: setCenter(float _centerx, float _centery) 
{
    center_x = _centerx;
    center_y = _centery; 
      
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
        float pos_x = center_x;
        float pos_y = center_y;

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


 

      //def createRocketCascade(self, w, h):
          //self.angle = 0
          //self.w, self.h = w, h

          //self.addMainQuad()

          //self.addMidLeftPoint()    # trail vector
          //self.addMidFarLeftPoint() # drive trail vector

          //self.updated = False

      //def createSpaceShipCascade(self, w, h):
          //self.angle = 0
          //self.w, self.h = w, h

          //self.addMainQuad()

          //self.addMidLeftPoint()
          //self.addMidFarLeftPoint()
          //self.addShieldCascade()

          //self.updated = False
     

      //def addShieldCascade(self):
          //factor = 1.6
          //w, h = self.w, self.h

          //# Origin entity rect (for rotation only transformation)
          //self.bottomFarLeft_origin  = [-w/factor, -h/factor]
          //self.bottomFarRight_origin = [+w/factor, -h/factor]
          //self.topFarRight_origin    = [+w/factor, +h/factor]
          //self.topFarLeft_origin     = [-w/factor, +h/factor]

          //# Actual entity rect
          //self.bottomFarLeft         = [-w/factor, -h/factor]
          //self.bottomFarRight        = [+w/factor, -h/factor]
          //self.topFarRight           = [+w/factor, +h/factor]
          //self.topFarLeft            = [-w/factor, +h/factor]

          
          //self.points.append((self.bottomFarLeft_origin, self.bottomFarLeft))
          //self.points.append((self.bottomFarRight_origin, self.bottomFarRight))
          //self.points.append((self.topFarRight_origin, self.topFarRight))
          //self.points.append((self.topFarLeft_origin, self.topFarLeft))


          





       




