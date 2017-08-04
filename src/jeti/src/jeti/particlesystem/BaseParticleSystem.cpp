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
#include <particlesystem/Particle.hpp>

//#include <spaceobjects/SpaceObject.hpp> // depr

#include <Material.hpp>
#include <Mesh.hpp>

// math
#include <glm/gtx/transform.hpp>
#include <meti/RandUtils.hpp>

namespace jeti {
namespace particlesystem {

Base::Base()
    :
      m_typeId(-1),
      m_mesh(nullptr),
//      m_Parent(nullptr),
      m_isAlive(true),
      m_isDying(false)
{
    m_mesh = new Mesh();
}

/* virtual */
Base::~Base()
{
    //delete m_Mesh; FIXME cause bug

    for (unsigned int i=0; i<m_particles.size(); i++) {
        delete m_particles[i];
    }
}

void Base::validateResources() const
{
    assert(m_material);
    if (!m_material->isLoaded()) {
        m_material->load();
    }
}

void Base::update()
{  
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (unsigned int i=0; i<m_particles.size(); i++) {
        const Particle& particle = *m_particles[i];

        positions.push_back(particle.GetPosition());
        colors.push_back(particle.color());
        sizes.push_back(particle.size());
    }

    m_mesh->fillPointVerticesFast(positions, colors, sizes);
}

const glm::mat4& Base::actualModelMatrix()
{ 
    m_matrixModel = glm::translate(center());
    //m_MatrixRotate    = glm::toMat4(m_QuatPosition * m_QuatAnimation);
    //m_MatrixScale     = glm::scale(size());

    //m_MatrixModel = m_MatrixTranslate * m_MatrixScale * m_MatrixRotate;
    
    return m_matrixModel;
}

} // namespace particlesystem
} // namespace jeti
