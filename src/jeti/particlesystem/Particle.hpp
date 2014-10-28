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
 
#include <particlesystem/ParticleData.hpp>
#include <glm/glm.hpp>

namespace jeti {

class Particle
{
    public:
        Particle(const ParticleData&);       
        ~Particle();
        
        void SetPosition(const glm::vec3& position) { m_Position = position; };              
        void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; };
        
        bool GetIsAlive()     const { return m_IsAlive; };
        float GetAlpha()      const { return m_Color.a; };
        
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec4& GetColor() const { return m_Color; }
        
        float GetSize() const { return m_Size; }

        void Reborn();      
        
        void RandomizeLifeTime(float, float);
        void Randomize_d_alpha(float, float);        
        
        void CalcRandomVelocity();            
        void CalcRandomAccurateVelocity();
        void CalcRandomDirtyVelocity();
        
        void Update();
                
    private:
        bool m_IsAlive;
        
        glm::vec3 m_Position;
        glm::vec3 m_Velocity;
        glm::vec3 m_Force;
        
        glm::vec4 m_Color;
        
        float m_Size;
        
        ParticleData m_DataParticle;
};
  
}
