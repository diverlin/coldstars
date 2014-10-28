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

#include <common/NonCopyable.hpp>
#include <glm/glm.hpp>

namespace jeti {

const float CAMERA_SPEED_MAX = 10.0f;
const float CAMERA_INERTIA = 0.95f;

class Camera : public NonCopyable
{
    public:
        Camera();
        ~Camera();

        const glm::vec3& GetPos() const { return m_Pos; }
        const glm::vec3& GetEyePos() const { return m_EyePos; }
        const glm::mat4& GetViewMatrix() const { return m_Vm; }
         
        void AddMoveSpeed(const glm::vec3&);
        
        void Update(int, int);  
                    
    private:
        glm::vec3 m_EyePos;

        glm::vec3 m_Pos;
        glm::vec3 m_Dir;
        glm::vec3 m_Up;
        
        float m_InertiaFactor;
        glm::vec3 m_MoveSpeed;
        float m_SpeedMax;
        
        glm::mat4 m_Vm; 
};

}


