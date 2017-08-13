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

#include "lazerTrace.hpp"

#include <meti/VectorUtils.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>
#include <jeti/Render.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace effect {

Beam::Beam(jeti::control::Material* material)
    :
      m_material(material)
{}

Beam::~Beam()
{
    //    delete m_particleSystem;
    //    m_particleSystem = nullptr;
}

void Beam::update()
{
    if (!m_isAlive) {
        return;
    }

    __updateModelMatrix();
    if (m_liveTime < 0) {
        m_isAlive = false;
        if (m_particleSystem) {
            //m_particleSystem->StartDying();
        }
    }
    m_liveTime -= 1;
}

void Beam::__updateModelMatrix()
{
    m_matrixTranslate = glm::translate(m_from);

    const glm::vec3& origin_dir = glm::vec3(1.0f, 0.0f, 0.0f);
    float angle = glm::orientedAngle(origin_dir, glm::normalize(m_to-m_from), meti::OZ);
    m_matrixRotate = glm::rotate(angle, meti::OZ);

    float length = glm::length(m_to - m_from);
    m_matrixScale = glm::scale(glm::vec3(length, 6.0, 0.0f));

    m_matrixModel = m_matrixTranslate * m_matrixRotate * m_matrixScale;
}


void Beam::draw(const jeti::Render& render) const
{
    if (!m_isAlive) {
        return;
    }
    render.drawQuadAdditive(*m_material, m_matrixModel);
}

} // namespace effect
