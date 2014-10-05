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

#include "BaseParticleSystem.hpp"
#include <effects/particlesystem/Particle.hpp>

#include <math/rand.hpp>
#include <common/constants.hpp>

#include <resources/textureOb.hpp>
#include <spaceobjects/BaseSpaceEntity.hpp>

#include <render/Mesh.hpp>

#include <glm/gtx/transform.hpp>

BaseParticleSystem::BaseParticleSystem()
:
m_TypeId(NONE_ID),
m_Mesh(nullptr),
m_Parent(nullptr),
m_IsAlive(true),
m_IsDying(false)
{
    m_Mesh = new Mesh();
}
 
/* virtual */
BaseParticleSystem::~BaseParticleSystem()
{
    //delete m_Mesh; FIXME cause bug

    for (unsigned int i=0; i<m_Particles.size(); i++) 
    {
        delete m_Particles[i];
    }
}

void BaseParticleSystem::ValidateResources() const
{
    assert(m_TextureOb);
    if (!m_TextureOb->GetIsLoaded()) {
        m_TextureOb->Load();
    }
}

void BaseParticleSystem::Update()
{  
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (unsigned int i=0; i<m_Particles.size(); i++) 
    {
        const Particle& particle = *m_Particles[i];

        positions.push_back(particle.GetPosition());
        colors.push_back(particle.GetColor());
        sizes.push_back(particle.GetSize());
    }

    m_Mesh->FillPointVerticesFast(positions, colors, sizes);
}

const glm::mat4& BaseParticleSystem::GetActualModelMatrix()
{ 
    m_MatrixModel = glm::translate(GetCenter());    
    //m_MatrixRotate    = glm::toMat4(m_QuatPosition * m_QuatAnimation); 
    //m_MatrixScale     = glm::scale(GetSize());
      
    //m_MatrixModel = m_MatrixTranslate * m_MatrixScale * m_MatrixRotate;
    
    return m_MatrixModel;
}

