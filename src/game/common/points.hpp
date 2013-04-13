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

#include <vector>
#include <cmath>
#include "myVector.hpp"

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
                void SetParentCenter(vec2f parent_center) { this->parent_center.Set(parent_center); };
                
                void SetCenter(float x, float y)	{ center.Set(x, y); 		is_updated = false; };
                void SetCenter(vec2f center)		{ this->center = center;  	is_updated = false; };
                void SetAngle(float angle_inD) 	{ this->angle_inD = angle_inD; 	is_updated = false; };

                void SetPosZ(float pos_z) { this->pos_z = pos_z; }
                
                void SetWidthHeight(int w, int h) { this->w = w; this->h = h; };
                        
        	int GetWidth() const  { return w; };
        	int GetHeight() const { return h; };
        
                float GetAngleDegree() const { return angle_inD; }  ;
                float* GetpAngleDegree() { return &angle_inD; };
                        
                float GetPosZ() const { return pos_z; };
                        
                const vec2f& GetCenter()  const { return center; };   
                const vec3f GetCenter3f() const { return vec3f(center.x, center.y, pos_z); }; 
                vec2f* GetpCenter() { return &center; };  
                vec2f* GetpParentCenter() { return &parent_center; };   
                      
                const vec2f& GetBottomLeft()  const { return bottomLeft; };  
                const vec2f& GetBottomRight() const { return bottomRight; }; 
                const vec2f& GetTopRight()    const { return topRight; };    
                const vec2f& GetTopLeft()     const { return topLeft; };

                const vec2f& GetMidLeftOrig()    { return midLeft_origin; };	// used in path calc              
                const vec2f& GetMidLeft()    { return midLeft; };	// used in path calc                
                vec2f* GetpMidLeft()    { return &midLeft; };	     	// used in drive jet
                vec2f* GetpMidFarLeft() { return &midFarLeft; };
                   
                Points();
                ~Points();

                void initMainQuadPoints(int, int);
                void addMainQuadPoints();

                void Add(vec2f*, vec2f*);

                void initMidLeftPoint();
                void addMidLeftPoint();
                void initMidFarLeftPoint();
                void addMidFarLeftPoint();

                void Update();                
                
        private:
                bool is_updated;
                        
                std::vector<vec2f*> vector_orig;
                std::vector<vec2f*> vector;
                                              
                // Origin entity rect (for rotation only transformation)
                vec2f bottomLeft_origin;  
                vec2f bottomRight_origin; 
                vec2f topRight_origin;    
                vec2f topLeft_origin;    
                
                // Actual entity rect
                int w, h; 		// used for collisions
                float angle_inD;
                float pos_z;
                
                vec2f center;     
                vec2f parent_center; 
                    
                vec2f bottomLeft;  
                vec2f bottomRight; 
                vec2f topRight;    
                vec2f topLeft;
                
            
                // Origin shield quad (for rotation only transformation)
                vec2f bottomLeftShield_origin;
                vec2f bottomRightShield_origin;
                vec2f topRightShield_origin;
                vec2f topLeftShield_origin;
                      
                // jet origin
                vec2f midLeft_origin;
                vec2f midFarLeft_origin;
                // jet actual
                vec2f midLeft;
                vec2f midFarLeft;
};

#endif 

 
