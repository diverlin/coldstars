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
#include "../math/myVector.hpp"

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
                void SetParentCenter(Vec2<float> parent_center) { this->parent_center.Set(parent_center); };
                
                void SetCenter(float x, float y)	{ center.Set(x, y); 		is_updated = false; };
                void SetCenter(const Vec2<float>& center) { this->center = center;  	is_updated = false; };
                void SetAngle(float angle_inD) 	{ this->angle_inD = angle_inD; 	is_updated = false; };

                void SetPosZ(float pos_z) { this->pos_z = pos_z; }
                
                void SetScale(float x, float y, float z) { scale.Set(x,y,z); };
                void SetScale(const Vec3<float> scale) { this->scale = scale; };
                                        
        	float GetWidth() const  { return scale.x; };
        	float GetHeight() const { return scale.y; };
        
                float GetAngleDegree() const { return angle_inD; }  ;
                float* GetpAngleDegree() { return &angle_inD; };
                        
                float GetPosZ() const { return pos_z; };
                        
                const Vec2<float>& GetCenter()  const { return center; };   
                const Vec3<float> GetCenter3f() const { return Vec3<float>(center.x, center.y, pos_z); }; 
                const Vec3<float> GetScale() 	  const { return scale; }; 
                
                Vec2<float>* GetpCenter() { return &center; };  
                Vec2<float>* GetpParentCenter() { return &parent_center; };   
                      
                const Vec2<float>& GetBottomLeft()  const { return bottomLeft; };  
                const Vec2<float>& GetBottomRight() const { return bottomRight; }; 
                const Vec2<float>& GetTopRight()    const { return topRight; };    
                const Vec2<float>& GetTopLeft()     const { return topLeft; };

                const Vec2<float>& GetMidLeftOrig()    { return midLeft_origin; };	// used in path calc              
                const Vec2<float>& GetMidLeft()    { return midLeft; };	// used in path calc                
                Vec2<float>* GetpMidLeft()    { return &midLeft; };	     	// used in drive jet
                Vec2<float>* GetpMidFarLeft() { return &midFarLeft; };
                   
                Points();
                ~Points();

                void addMainQuadPoints();

                void Add(Vec2<float>*, Vec2<float>*);

                void addMidLeftPoint();
                void addMidFarLeftPoint();

                void Update();                
                
        private:
                bool is_updated;
                
                Vec3<float> scale;
                float angle_inD;
                float pos_z;
            
                Vec2<float> center;     
                Vec2<float> parent_center; 
              
                std::vector<Vec2<float>*> vector_orig;
                std::vector<Vec2<float>*> vector;
                                             
                // Origin entity rect (for rotation only transformation)
                Vec2<float> bottomLeft_origin;  
                Vec2<float> bottomRight_origin; 
                Vec2<float> topRight_origin;    
                Vec2<float> topLeft_origin;    

		// jet normilized
		Vec2<float> midLeft_origin;
		Vec2<float> midFarLeft_origin;
                
                // Actual entity rect                       
                Vec2<float> bottomLeft;  
                Vec2<float> bottomRight; 
                Vec2<float> topRight;    
                Vec2<float> topLeft;
                
                // jet actual
                Vec2<float> midLeft;
                Vec2<float> midFarLeft;
};

#endif 

 
