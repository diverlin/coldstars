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
                void setPosZ(float pos_z) { this->pos_z = pos_z; }
                
                void setWidthHeight(int, int);  
                void setCenter(float, float);
                void setCenter(vec2f);
                void setAngle(float);
        
        	int getWidth() const  { return w; };
        	int getHeight() const { return h; };
        
                float getAngleDegree() const { return angle_inD; }  ;
                float* getpAngleDegree() { return &angle_inD; };
                        
                float getPosZ() const { return pos_z; };
                        
                const vec2f& getCenter()  const { return center; };   
                const vec3f getCenter3f() const { return vec3f(center.x, center.y, pos_z); }; 
                vec2f* getpCenter() { return &center; };   // used inturrels(for target)
      
                const vec2f& getBottomLeft()  const { return bottomLeft; };  
                const vec2f& getBottomRight() const { return bottomRight; }; 
                const vec2f& getTopRight()    const { return topRight; };    
                const vec2f& getTopLeft()     const { return topLeft; };
                
                const vec2f& getBottomLeftShield()  const { return bottomLeftShield; };
                const vec2f& getBottomRightShield() const { return bottomRightShield; };
                const vec2f& getTopRightShield()    const { return topRightShield; };
                const vec2f& getTopLeftShield()     const { return topLeftShield; };
                
                vec2f* getpMidLeft()    { return &midLeft; };	     // used in drive jet
                vec2f* getpMidFarLeft() { return &midFarLeft; };
                
                vec2f* getpWeapon1Center() { return &weapon_1_center; };  // used in turrels
        	vec2f* getpWeapon2Center() { return &weapon_2_center; };
        	vec2f* getpWeapon3Center() { return &weapon_3_center; };
        	vec2f* getpWeapon4Center() { return &weapon_4_center; };
        	vec2f* getpWeapon5Center() { return &weapon_5_center; };
    
                Points();
                ~Points();

                void initCenterPoint();
                void addCenterPoint();

                void initMainQuadPoints(int, int);
                void addMainQuadPoints();

                void initWeapon1CenterPoint(float, float);
                void addWeapon1CenterPoint();

                void initWeapon2CenterPoint(float, float);
                void addWeapon2CenterPoint();

                void initWeapon3CenterPoint(float, float);
                void addWeapon3CenterPoint();

                void initWeapon4CenterPoint(float, float);
                void addWeapon4CenterPoint();

                void initWeapon5CenterPoint(float, float);
                void addWeapon5CenterPoint();

                void initShieldQuadPoints();
                void addShieldQuadPoints();

                void initMidLeftPoint();
                void addMidLeftPoint();
                void initMidFarLeftPoint();
                void addMidFarLeftPoint();

                void update();                
                
        private:
                bool is_updated;
                        
                std::vector<vec2f*> vector_orig;
                std::vector<vec2f*> vector;
                                              
                // Origin entity rect (for rotation only transformation)
                vec2f center_origin;    
     
                vec2f bottomLeft_origin;  
                vec2f bottomRight_origin; 
                vec2f topRight_origin;    
                vec2f topLeft_origin;    
                
                // Actual entity rect
                int w, h; 		// used for collisions
                float angle_inD;
                float pos_z;
                
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
                
                void CreateCenter();
                 
};

#endif 

 
