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
#include "Collision.hpp"
#include "rect.hpp"

Box2D::Box2D()
:
m_Angle(0.0)
{
    SetScale(1.0, 1.0);
}

Box2D::Box2D(const Vec2<float>& size)
:
m_Angle(0.0)
{
    SetSize(size);
    SetScale(1.0, 1.0);
}

Box2D::Box2D(const Vec2<float>& center, const Vec2<float>& size)
:
m_Angle(0.0)
{
    SetCenter(center);
    SetSize(size);    
    SetScale(1.0, 1.0);
}

Box2D::Box2D(const Box2D& rhs)
:
m_Angle(0.0)
{
    Set(rhs);
}

Box2D::Box2D(const Rect& rect)
:
m_Angle(0.0)
{
    SetCenter(Vec2<float>(rect.GetCenter().x, rect.GetCenter().y));
    SetSize(Vec2<float>(rect.GetWidth(), rect.GetHeight()));
    SetScale(1.0, 1.0);
}

Box2D::~Box2D()
{}

bool Box2D::CheckInteraction(const Vec2<float>& point) const
{           
    return checkCollisionDotWithRectangle(point, m_Center, m_Size*m_Scale);
}
               
void Box2D::Set(const Box2D& box)
{
    SetSize(box.GetSize());
    SetScale(box.GetScale());
    SetCenter(box.GetCenter());
    m_Angle = box.GetAngle();
}

