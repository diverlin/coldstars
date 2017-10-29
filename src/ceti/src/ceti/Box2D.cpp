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
:
m_angle(0.0)
{
    setScale(1.0, 1.0);
}

Box2D::Box2D(const glm::vec2& size)
:
m_angle(0.0)
{
    setSize(size);
    setScale(1.0, 1.0);
}

Box2D::Box2D(const glm::vec2& center, const glm::vec2& size)
:
m_angle(0.0)
{
    setCenter(center);
    setSize(size);    
    setScale(1.0, 1.0);
}

Box2D::Box2D(const Box2D& rhs)
:
m_angle(0.0)
{
    set(rhs);
}

Box2D::Box2D(const Rect& rect)
:
m_angle(0.0)
{
    setCenter(glm::vec2(rect.center().x, rect.center().y));
    setSize(glm::vec2(rect.width(), rect.height()));
    setScale(1.0, 1.0);
}

Box2D::~Box2D()
{}

bool Box2D::checkInteraction(const glm::vec2& point) const
{           
    return checkCollisionDotWithRectangle(point, m_center, m_size*m_scale);
}
               
void Box2D::set(const Box2D& box)
{
    setSize(box.size());
    setScale(box.scale());
    setCenter(box.center());
    m_angle = box.angle();
}

} // namespace ceti
