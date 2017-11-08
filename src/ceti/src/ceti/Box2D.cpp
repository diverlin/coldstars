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

#include "Box2D.hpp"
#include <ceti/Collision.hpp>
#include <ceti/rect.hpp>

namespace ceti {

Box2D::Box2D()
{
}

Box2D::Box2D(const glm::vec2& size)
    :
      m_size(size)
{
}

Box2D::Box2D(const glm::vec2& center, const glm::vec2& size)
    :
      m_size(size)
    , m_center(center)
{
}

Box2D::Box2D(const Box2D& rhs)
{
    set(rhs);
}

Box2D::Box2D(const Rect& rect)
{
    setCenter(glm::vec2(rect.center().x, rect.center().y));
    setSize(glm::vec2(rect.width(), rect.height()));
}

Box2D::~Box2D()
{}

bool Box2D::checkInteraction(const glm::vec2& point) const
{           
    return isPointInRectangle(point, m_center, m_scale*m_size);
}
               
void Box2D::set(const Box2D& box)
{
    setSize(box.size());
    setScale(box.scale());
    setCenter(box.center());
    setAngle(box.angle());
}

} // namespace ceti
