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

#include "Beam.hpp"

#include <meti/VectorUtils.hpp>
#include <meti/RandUtils.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>
#include <jeti/Render.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace effect {

Beam::Beam(jeti::control::Material* material)
    :
      m_material(material)
{
    //m_color = glm::vec4(1.0f, 0.8f, 0.6f, 0.4f);
    float r = meti::rand::get_float(0.6f, 1.0f);
    float g = meti::rand::get_float(0.6f, 1.0f);
    float b = meti::rand::get_float(0.6f, 1.0f);
    m_color = glm::vec4(r, g, b, 0.4f);

//    r = meti::getRandFloat(0.6f, 1.0f);
//    g = meti::getRandFloat(0.6f, 1.0f);
//    b = meti::getRandFloat(0.6f, 1.0f);
//    m_overlayColor = glm::vec4(r, g, b, 0.2f);

    m_overlayColor = m_color;
    m_overlayColor.a = 0.2f;

    m_size = 1.0f;
    m_deltaSize = 0.1f;
    m_sizeMax = 6.0f;
}

Beam::~Beam()
{
    if (m_particleSystem) {
        delete m_particleSystem;
        m_particleSystem = nullptr;
    }
}

void Beam::update()
{
    if (!m_isAlive) {
        return;
    }

    if (m_liveTime > 30) {
        if (m_size < m_sizeMax) {
            m_size += 6*m_deltaSize;
        }
    } else {
        m_size -= m_deltaSize;
    }

    __updateModelMatrix();

    if (m_particleSystem) {
        m_particleSystem->setCenter(m_to);
        m_particleSystem->update();
    }

    if (m_liveTime < 0) {
        m_isAlive = false;
        if (m_particleSystem) {
            m_particleSystem->setDying();
        }
    }
    m_liveTime -= 1;
}

void Beam::__updateModelMatrix()
{
    glm::vec3 diff(m_to-m_from);
    glm::vec3 direction(glm::normalize(diff));
    float length = glm::length(diff);

    m_matrixTranslate = glm::translate(m_from+(0.5f*length)*direction);

    const glm::vec3& origin_dir = glm::vec3(1.0f, 0.0f, 0.0f);
    float angle = glm::orientedAngle(origin_dir, direction, meti::OZ);
    m_matrixRotate = glm::rotate(angle, meti::OZ);

    m_matrixScale = glm::scale(glm::vec3(length/2, m_size, 0.0f));
    m_matrixScaleOverlay = glm::scale(glm::vec3(length/2, m_size*4.0f, 0.0f));

    m_matrixModel = m_matrixTranslate * m_matrixRotate * m_matrixScale;

    m_matrixModelOverlay = m_matrixTranslate * m_matrixRotate * m_matrixScaleOverlay;
}


void Beam::draw(const jeti::Render& render) const
{
    if (!m_isAlive) {
        return;
    }
    render.drawQuadAdditive(*m_material, m_matrixModel, m_color);
    render.drawQuadAdditive(*m_material, m_matrixModelOverlay, m_overlayColor);

    if (m_particleSystem) {
        m_particleSystem->draw(render);
    }
}

} // namespace effect
