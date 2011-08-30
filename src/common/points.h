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
        /*****************************************
        The class holds points(verticles) collection relevant for game entity, 
        and provides the transformation methodsin 2D (rotation, moving).  
        If entity is rotated/moved then all relevant points are passing the same transformation (rotation and moving).
        The numbers relevant points can be varry and it depends on game entity type. 
        All relevant points for particular entity placed to the STL vector were 
        they are updated rely on game entity angle value and center position 
        (the points outside the STL are not relevant and are not dated).
        The points with prefix <<_origin>> are used internally in the class for rotation calculation.
        ******************************************/
        
        public:
        	int getWidth() const;
        	int getHeight() const;
        
                float getAngleDegree() const;
                float* getpAngleDegree();
                        
                vec2f getCenter()      const;   
                vec2f* getpCenter();   // used inturrels(for target)
      
                vec2f getBottomLeft()  const;  
                vec2f getBottomRight() const; 
                vec2f getTopRight()    const;    
                vec2f getTopLeft()     const;
                
                vec2f getBottomLeftShield()  const;
                vec2f getBottomRightShield() const;
                vec2f getTopRightShield()    const;
                vec2f getTopLeftShield()     const;
                
                vec2f* getpMidLeft();	     // used in drive jet
                vec2f* getpMidFarLeft();
                
                vec2f* getpWeapon1Center();  // used in turrels
        	vec2f* getpWeapon2Center();
        	vec2f* getpWeapon3Center();
        	vec2f* getpWeapon4Center();
        	vec2f* getpWeapon5Center();
    
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

                void setWidthHeight(int _w, int _h);  
                void setCenter(float _centerx, float _centery);
                void setAngle(float _angle);

                void update();
                
        private:
                bool is_updated;
                        
                std::vector<float*> vector_orig_x;
                std::vector<float*> vector_orig_y;
                std::vector<float*> vector_x;
                std::vector<float*> vector_y;
        
                                              
                // Origin entity rect (for rotation only transformation)
                vec2f center_origin;    
     
                vec2f bottomLeft_origin;  
                vec2f bottomRight_origin; 
                vec2f topRight_origin;    
                vec2f topLeft_origin;    
                
                // Actual entity rect
                int w, h; 		// used for collisions
                float angle_inD;
                
                vec2f center;     
      
                vec2f bottomLeft;  
                vec2f bottomRight; 
                vec2f topRight;    
                vec2f topLeft;
                
            
                // Origin shield quad (for rotation only transformation)
                vec2f bottomLeftShield_origin;
                vec2f bottomRightShield_origin;
                vec2f topRightShield_origin;
                vec2f topLeftShield_origin;
                
                // Actual shield quad
                vec2f bottomLeftShield;
                vec2f bottomRightShield;
                vec2f topRightShield;
                vec2f topLeftShield;
                
                      
                // jet origin
                vec2f midLeft_origin;
                vec2f midFarLeft_origin;
                // jet actual
                vec2f midLeft;
                vec2f midFarLeft;
                
                
                //////////////////////////////////
                // center coordinates for weapons
                /////////////////////////////////
                // weapon 1
                vec2f weapon_1_origin_center;      
                vec2f weapon_1_center;      

                // weapon 2
                vec2f weapon_2_origin_center;
                vec2f weapon_2_center;      
                
                // weapon 3
                vec2f weapon_3_origin_center;      
                vec2f weapon_3_center;      
                
                // weapon 4
                vec2f weapon_4_origin_center;      
                vec2f weapon_4_center;      
                
                // weapon 5
                vec2f weapon_5_origin_center;      
                vec2f weapon_5_center;    
                ////////////////////////////////////
                 
};

#endif 

 
