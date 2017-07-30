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

#include "BaseBackGroundEffect.hpp"
#include "../resources/TextureCollector.hpp"
#include <jeti/Material.hpp>
#include <jeti/Render.hpp>

#include <glm/gtx/transform.hpp>


unsigned long int BaseBackGroundEffect::counter;

BaseBackGroundEffect::BaseBackGroundEffect()
:
m_textureOb(nullptr),
m_angle(0.0f),
m_deltaAngle(0.0f)
{
    counter++;
    id = counter;
}

BaseBackGroundEffect::~BaseBackGroundEffect()
{}

void BaseBackGroundEffect::validateResources() const
{
    assert(m_textureOb);
    if (!m_textureOb->isLoaded()) {
        m_textureOb->load();
    }
}

const glm::mat4& BaseBackGroundEffect::actualModelMatrix()
{
    m_Tm = glm::translate(m_center);
    m_Rm = glm::rotate(m_angle, glm::vec3(0.0, 0.0, 1.0));
    m_Sm = glm::scale(m_size);
      
    m_Mm = m_Tm * m_Rm * m_Sm;
    
    return m_Mm;
}
        
void BaseBackGroundEffect::setTextureOb(jeti::control::Material* textureOb, const glm::vec3& scale_factor)
{
    m_textureOb = textureOb;
};
            

