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

#include "rect.hpp"

namespace ceti {

Rect::Rect()
{
    set(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(float bottomLeft_x, float bottomLeft_y, float width, float height)
{
    set(bottomLeft_x, bottomLeft_y, width, height);
}

Rect::Rect(const glm::vec2& bottomLeft, float width, float height)
{
    set(bottomLeft.x, bottomLeft.y, width, height);
}

Rect::Rect(const Rect& rhs)
{
    set(rhs.bottomLeft(), rhs.width(), rhs.height());
}

Rect::~Rect()
{}

void Rect::scale(float scale)
{
    m_width *= scale;
    m_height *= scale;
    m_center *= scale;
    m_bottomLeft.x = m_center.x - m_width/2;
    m_bottomLeft.y = m_center.y - m_height/2;
}

void Rect::scale(const glm::vec2& scale)
{
    m_width *= scale.x;
    m_height *= scale.y;
    m_bottomLeft.x = m_center.x - m_width/2;
    m_bottomLeft.y = m_center.y - m_height/2;
}

bool Rect::checkInteraction(const glm::vec2& point) const
{
    return checkInteraction(point.x, point.y);
}

bool Rect::checkInteraction(float x, float y) const
{           
    if (x < m_bottomLeft.x)
        return false;
    if (x > m_bottomLeft.x + m_width)
        return false;
    if (y < m_bottomLeft.y)
        return false;
    if (y > m_bottomLeft.y + m_height)
        return false;
    
    return true;
}

bool Rect::checkRoundInteraction(const glm::vec2& p, float radius) const
{           
    float dist = glm::length((p-m_center));
    if (dist < radius)
    {
        return true;
    }

    return false;
}

void Rect::set(float bottomLeft_x, float bottomLeft_y, float width, float height)
{
    m_bottomLeft.x = bottomLeft_x;
    m_bottomLeft.y = bottomLeft_y;

    m_width = width;
    m_height = height;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::set(const glm::vec2& vbl, float width, float height)
{
    set(vbl.x, vbl.y, width, height);
}

void Rect::set(const Rect& rect)
{
    set(rect.bottomLeft(), rect.width(), rect.height());
}

void Rect::setCenter(const glm::vec2& center)
{
    setCenter(center.x, center.y);
}

void Rect::setCenter(float center_x, float center_y)
{
    float dx = m_center.x - center_x;
    float dy = m_center.y - center_y;

    m_bottomLeft.x -= dx;
    m_bottomLeft.y -= dy;

    m_center.x = center_x;
    m_center.y = center_y;
    
    UpdateTopRight();
}

void Rect::setBottomLeft(const glm::vec2& bottomLeft)
{
    setBottomLeft(bottomLeft.x, bottomLeft.y);
}

void Rect::setBottomLeft(float pos_x, float pos_y)
{
    m_bottomLeft.x = pos_x;
    m_bottomLeft.y = pos_y;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::setBottomLeftX(float pos_x)
{
    m_bottomLeft.x = pos_x;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::setSize(float width, float height)
{
    m_width = width;
    m_height = height;

    m_bottomLeft.x = m_center.x - width/2;
    m_bottomLeft.y = m_center.y - height/2;
    
    UpdateTopRight();
}

void Rect::movingBy(const glm::vec2& d_pos)
{
    m_bottomLeft += d_pos;
    UpdateCenter();
    UpdateTopRight();
}

void Rect::UpdateCenter()
{
    m_center.x = m_bottomLeft.x + m_width/2;
    m_center.y = m_bottomLeft.y + m_height/2;
}

void Rect::UpdateTopRight()
{
    m_topRight.x = m_bottomLeft.x + m_width;
    m_topRight.y = m_bottomLeft.y + m_height;
}

} // namespace ceti
