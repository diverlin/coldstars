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



#ifndef POINTS_H
#define POINTS_H

class Points
{
  public:
    std::vector<float*> vector_orig_x;
    std::vector<float*> vector_orig_y;
    std::vector<float*> vector_x;
    std::vector<float*> vector_y;
    
    float angle_inD;
    int w, h;
    
    bool is_updated;
            
    // Origin entity rect (for rotation only transformation)
    float center_origin_x;    
    float center_origin_y;    
      
    float bottomLeft_origin_x;  
    float bottomLeft_origin_y;  

    float bottomRight_origin_x; 
    float bottomRight_origin_y; 

    float topRight_origin_x;    
    float topRight_origin_y;    
                
    float topLeft_origin_x;    
    float topLeft_origin_y;     
      
    // Actual entity rect
    float center_x;     
    float center_y;     
      
    float bottomLeft_x;  
    float bottomLeft_y;  
      
    float bottomRight_x; 
    float bottomRight_y; 
      
    float topRight_x;    
    float topRight_y;   
                 
    float topLeft_x;    
    float topLeft_y;     
      

    //////////////////////////////////
    // center coordinates for weapons
    /////////////////////////////////
    // weapon 1
    float weapon1_origin_center_x;      
    float weapon1_origin_center_y;
    float weapon1_center_x;      
    float weapon1_center_y;

    // weapon 2
    float weapon2_origin_center_x;      
    float weapon2_origin_center_y;
    float weapon2_center_x;      
    float weapon2_center_y;

    // weapon 3
    float weapon3_origin_center_x;      
    float weapon3_origin_center_y;
    float weapon3_center_x;      
    float weapon3_center_y;

    // weapon 4
    float weapon4_origin_center_x;      
    float weapon4_origin_center_y;
    float weapon4_center_x;      
    float weapon4_center_y;

    // weapon 5
    float weapon5_origin_center_x;      
    float weapon5_origin_center_y;
    float weapon5_center_x;      
    float weapon5_center_y;
    ////////////////////////////////////



    // Origin entity rect (for rotation only transformation)
    float bottomLeftShield_origin_x;
    float bottomLeftShield_origin_y;

    float bottomRightShield_origin_x;
    float bottomRightShield_origin_y;

    float topRightShield_origin_x;
    float topRightShield_origin_y;

    float topLeftShield_origin_x;
    float topLeftShield_origin_y;


    // Actual entity rect
    float bottomLeftShield_x;
    float bottomLeftShield_y;

    float bottomRightShield_x;
    float bottomRightShield_y;

    float topRightShield_x;
    float topRightShield_y;

    float topLeftShield_x;
    float topLeftShield_y;

    // jet
    float midLeft_origin_x;
    float midLeft_origin_y;

    float midFarLeft_origin_x;
    float midFarLeft_origin_y;

    float midLeft_x;
    float midLeft_y;

    float midFarLeft_x;
    float midFarLeft_y;



    Points();
    ~Points();

    void initCenterPoint();
    void addCenterPoint();


    void initMainQuadPoints(int _w, int _h);
    void addMainQuadPoints();

    void initWeapon1CenterPoint(float _pos_x, float _pos_y);
    void addWeapon1CenterPoint();

    void initWeapon2CenterPoint(float _pos_x, float _pos_y);
    void addWeapon2CenterPoint();

    void initWeapon3CenterPoint(float _pos_x, float _pos_y);
    void addWeapon3CenterPoint();

    void initWeapon4CenterPoint(float _pos_x, float _pos_y);
    void addWeapon4CenterPoint();

    void initWeapon5CenterPoint(float _pos_x, float _pos_y);
    void addWeapon5CenterPoint();

    void initShieldQuadPoints();
    void addShieldQuadPoints();


    void initMidLeftPoint();
    void addMidLeftPoint();
    void initMidFarLeftPoint();
    void addMidFarLeftPoint();


    void setCenter(float _centerx, float _centery);
    void setAngle(float _angle);

    void update();
};

#endif /* POINTS_H */

 

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
     

      //def addMidLeftPoint(self):
          //self.midLeft_origin       = [-self.w/2, 0]
          //self.midLeft              = [-self.w/2, 0]
          
          //self.points.append((self.midLeft_origin, self.midLeft))


      //def addMidFarLeftPoint(self):
          //self.midFarLeft_origin       = [-self.w, 0]
          //self.midFarLeft              = [-self.w, 0]
          
          //self.points.append((self.midFarLeft_origin, self.midFarLeft))

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


      //def update(self):   # will be moved plain C in future
          //if self.updated == False:
             //pos_x = self.center[0]
             //pos_y = self.center[1]

             //self.angle_degree = self.angle  # depr

             //self.angle_radian = self.angle_degree/57.295779
             //cosa = cos(self.angle_radian)
             //sina = sin(self.angle_radian)

             //for (p_origin, p) in self.points:
                 //# rotation around center
                 //p[0] = (p_origin[0])*cosa - (p_origin[1])*sina
                 //p[1] = (p_origin[0])*sina + (p_origin[1])*cosa
                 //# moving to position
                 //p[0] += pos_x
                 //p[1] += pos_y
     
             //self.updated = True
          





       




