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

#include "Point.hpp"
#include <jeti/Base.hpp>

namespace jeti {

Point::Point(int id, Base* parent, const meti::vec3& positionOrigin)
    :
      m_id(id)
    , m_parent(parent)
    , m_positionOrigin(positionOrigin)
{

}

void Point::update()
{
    m_position = m_parent->matrixRotate() * m_parent->matrixScale() * glm::vec4(m_positionOrigin, 1.0f); // parent rotation offset position
    m_position += m_parent->position();
}

} // namespace jeti

