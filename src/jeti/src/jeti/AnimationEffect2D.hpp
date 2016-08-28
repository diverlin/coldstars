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

#include <meti/VectorUtils.hpp>

namespace ceti {
class Box2D;
}

namespace jeti {

class AnimationEffect2D
{
    public:
        AnimationEffect2D(const glm::vec3& scale_min, const glm::vec3& scale_max, const glm::vec3& d_scale, float angle_min, float angle_max, float d_angle):
        scale_min(scale_min), 
        scale_max(scale_max), 
        d_scale(d_scale), 
        angle_min(angle_min),
        angle_max(angle_max),
        d_angle(d_angle),
        scale_up(true) 
        {};
        
        ~AnimationEffect2D() {};
    
        const glm::vec3& GetScale() const { return scale; };
        float GetAngle() const { return angle; };
        
        void Update(ceti::Box2D&);
        void Reset();
        
    private:
        glm::vec3 scale;
        glm::vec3 scale_min;
        glm::vec3 scale_max;
        glm::vec3 d_scale;
        
        float angle;
        float angle_min;
        float angle_max;
        float d_angle;
        
        bool scale_up;
        
};

}


