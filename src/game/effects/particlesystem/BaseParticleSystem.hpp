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


#ifndef BASEPARTICLESYSTEM_HPP
#define BASEPARTICLESYSTEM_HPP

#include <vector>

#include <effects/particlesystem/Particle.hpp>
#include <resources/textureOb.hpp>
#include <spaceobjects/BaseSpaceEntity.hpp>

class BaseParticleSystem 
{
    public:
        BaseParticleSystem();
        virtual ~BaseParticleSystem();
        
        void SetDying() { m_IsDying = true; }
        void SetTextureOb(TextureOb* textureOb) { m_TextureOb = textureOb; }
        void SetParent(BaseSpaceEntity* parent) { m_Parent = parent; }
        void SetCenter(const glm::vec3& center) { m_Center = center; }
        void SetParticlesNum(unsigned int particles_num)  { m_ParticlesNum = particles_num; }
        void SetParticleData(const ParticleData& data_particle) { m_DataParticle = data_particle; }
        
        int GetTypeId() const { return m_TypeId; }
        bool GetAlive() const { return m_IsAlive; }
        const glm::vec3& GetCenter() const { return m_Center; }

        unsigned int GetParticlesNum() const { return m_ParticlesNum; }
        
        virtual void Update() = 0;
        virtual void Render(float) {}
    
    protected:
        int m_TypeId;
        unsigned int m_ParticlesNum;
        
        TextureOb* m_TextureOb;
        ParticleData m_DataParticle;

        glm::vec3 m_Center;
        glm::vec3 m_Velocity;
        glm::vec3 m_Dir; 

        BaseSpaceEntity* m_Parent;
        
        bool m_IsAlive;
        bool m_IsDying;
        
        std::vector<Particle*> m_Particles;  
};


#endif 
