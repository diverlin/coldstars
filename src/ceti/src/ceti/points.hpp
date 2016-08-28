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


#pragma once

#include <vector>
#include <cmath>
#include <meti/VectorUtils.hpp>

namespace ceti {

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
        const glm::vec3& GetBottomLeft()  const { return bottomLeft; };  
        const glm::vec3& GetBottomRight() const { return bottomRight; }; 
        const glm::vec3& GetTopRight()    const { return topRight; };    
        const glm::vec3& GetTopLeft()     const { return topLeft; };
        
        const glm::vec3& GetMidLeftOrig()    { return midLeft_origin; };    // used in path calc              
        const glm::vec3& GetMidLeft()    { return midLeft; };                    // used in path calc                
        glm::vec3* GetpMidLeft()    { return &midLeft; };                     // used in drive jet
        glm::vec3* GetpMidFarLeft() { return &midFarLeft; };
        
        Points();
        ~Points();
        
        void Add(glm::vec3* const, const glm::vec3* const);
        
        void addMidLeftPoint();
        void addMidFarLeftPoint();
        
        void Update(const glm::vec3& center, const glm::vec3& angle, const glm::vec3& scale, const glm::vec3& uOrient);              
                
    private:
        std::vector<const glm::vec3*> vector_orig;
        std::vector<glm::vec3*> vector;
        
        // Origin entity rect (for rotation only transformation)
        glm::vec3 bottomLeft_origin;  
        glm::vec3 bottomRight_origin; 
        glm::vec3 topRight_origin;    
        glm::vec3 topLeft_origin;    
        
        // jet normilized
        glm::vec3 midLeft_origin;
        glm::vec3 midFarLeft_origin;
        
        // Actual entity rect                       
        glm::vec3 bottomLeft;  
        glm::vec3 bottomRight; 
        glm::vec3 topRight;    
        glm::vec3 topLeft;
        
        // jet actual
        glm::vec3 midLeft;
        glm::vec3 midFarLeft;
};

} // namespace ceti
 
