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

#include "Shield.hpp"

#include <jeti/Render.hpp>
#include <jeti/Material.hpp>

#include <glm/gtx/transform.hpp>

namespace view {
namespace effect {

Shield::Shield()
{       
    m_color.r = 1.0;
    m_color.g = 1.0;
    m_color.b = 1.0;
    m_color.a = m_opacityMin;

    m_scaleMatrix = glm::scale(glm::vec3(1.4f, 1.4f, 1.0f));
}

Shield::~Shield()
{}

void Shield::dissipate()
{
    m_move = up;
}

void Shield::update()
{      
    if (m_move == stop) {
        if (m_cyclic) {
            dissipate();
        }
        return;
    }

    if (m_move == up) {
        m_color.a *= m_opacityUpFactor;
    } else if (m_move == down) {
        m_color.a *= m_opacityDownFactor;
    }

    if (m_color.a > m_opacityMax) {
        m_move = down;
        m_color.a = m_opacityMax;
    } else if (m_color.a < m_opacityMin) {
        m_color.a = m_opacityMin;
        if (m_cyclic) {
            dissipate();
        } else {
            m_move = stop;
        }
    }
}

void Shield::draw(const glm::mat4& parentModelMatrix, const jeti::Render& render) const
{
    render.drawQuad(*m_material, parentModelMatrix*m_scaleMatrix, m_color.a);
}

} // namespace effect
} // namespace view

