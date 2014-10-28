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

#include <glm/gtx/quaternion.hpp>

namespace jeti {

class BaseAnimationRotation
{  
    public:
        BaseAnimationRotation(float delta_angle)
        :
        m_Angle(0.0f),
        m_DeltaAngle(delta_angle) 
        {}
        
        virtual ~BaseAnimationRotation() {}

        virtual void Update(glm::quat&, const glm::vec3&) = 0;
    
    protected:
        float GetDeltaAngle() const { return m_DeltaAngle; }
        float m_Angle;
            
    private:
        float m_DeltaAngle;   
        
};

}



