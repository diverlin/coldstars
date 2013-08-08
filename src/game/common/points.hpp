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
        const Vec3<float>& GetBottomLeft()  const { return bottomLeft; };  
        const Vec3<float>& GetBottomRight() const { return bottomRight; }; 
        const Vec3<float>& GetTopRight()    const { return topRight; };    
        const Vec3<float>& GetTopLeft()     const { return topLeft; };
        
        const Vec3<float>& GetMidLeftOrig()    { return midLeft_origin; };    // used in path calc              
        const Vec3<float>& GetMidLeft()    { return midLeft; };                    // used in path calc                
        Vec3<float>* GetpMidLeft()    { return &midLeft; };                     // used in drive jet
        Vec3<float>* GetpMidFarLeft() { return &midFarLeft; };
        
        Points();
        ~Points();
        
        void Add(Vec3<float>* const, const Vec3<float>* const);
        
        void addMidLeftPoint();
        void addMidFarLeftPoint();
        
        void Update(const Vec3<float>& center, const Vec3<float>& angle, const Vec3<float>& scale, const Vec3<float>& uOrient);              
                
    private:
        std::vector<const Vec3<float>*> vector_orig;
        std::vector<Vec3<float>*> vector;
        
        // Origin entity rect (for rotation only transformation)
        Vec3<float> bottomLeft_origin;  
        Vec3<float> bottomRight_origin; 
        Vec3<float> topRight_origin;    
        Vec3<float> topLeft_origin;    
        
        // jet normilized
        Vec3<float> midLeft_origin;
        Vec3<float> midFarLeft_origin;
        
        // Actual entity rect                       
        Vec3<float> bottomLeft;  
        Vec3<float> bottomRight; 
        Vec3<float> topRight;    
        Vec3<float> topLeft;
        
        // jet actual
        Vec3<float> midLeft;
        Vec3<float> midFarLeft;
};

#endif 

 
