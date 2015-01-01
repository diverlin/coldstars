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
    Set(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(float _bottomLeft_x, float _bottomLeft_y, float _w, float _h)
{
    Set(_bottomLeft_x, _bottomLeft_y, _w, _h);
}

Rect::Rect(const glm::vec2& _bottomLeft, float _w, float _h)
{
    Set(_bottomLeft.x, _bottomLeft.y, _w, _h);
}

Rect::Rect(const Rect& rhs)
{
    Set(rhs.GetBottomLeft(), rhs.GetWidth(), rhs.GetHeight());
}

Rect::~Rect()
{}
         
void Rect::Scale(float scale)
{
    w *= scale;
    h *= scale;
    center *= scale;
    bottomLeft.x = center.x - w/2; 
    bottomLeft.y = center.y - h/2; 
}
         
void Rect::Scale(const glm::vec2& scale)
{
          w *= scale.x;
          h *= scale.y; 
    bottomLeft.x = center.x - w/2;    
    bottomLeft.y = center.y - h/2; 
}

bool Rect::CheckInteraction(const glm::vec2& point) const
{
    return CheckInteraction(point.x, point.y);
}
    
bool Rect::CheckInteraction(float x, float y) const
{           
    if (x < bottomLeft.x)
        return false;
    if (x > bottomLeft.x + w)
        return false;
    if (y < bottomLeft.y)
    return false;
        if (y > bottomLeft.y + h)
    return false;
    
    return true;
}

bool Rect::CheckRoundInteraction(const glm::vec2& p, float radius) const
{           
    float dist = glm::length((p-center));
    if (dist < radius)
    {
         return true;
    }
         
    return false;
}
        
void Rect::Set(float _bottomLeft_x, float _bottomLeft_y, float _w, float _h)
{
    bottomLeft.x = _bottomLeft_x;
    bottomLeft.y = _bottomLeft_y;

    w = _w;
    h = _h;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::Set(const glm::vec2& vbl, float _w, float _h)
{
    Set(vbl.x, vbl.y, _w , _h);
}
          
void Rect::Set(const Rect& rect)
{
    Set(rect.GetBottomLeft(), rect.GetWidth(), rect.GetHeight());
}
    
void Rect::SetCenter(const glm::vec2& _center)
{
    SetCenter(_center.x, _center.y);
}

void Rect::SetCenter(float _center_x, float _center_y)
{
    float dx = center.x - _center_x;
    float dy = center.y - _center_y;

    bottomLeft.x -= dx;
    bottomLeft.y -= dy; 

    center.x = _center_x;
    center.y = _center_y;
    
    UpdateTopRight();
}

void Rect::SetBottomLeft(const glm::vec2& _bottomLeft)
{
    SetBottomLeft(_bottomLeft.x, _bottomLeft.y);
}

void Rect::SetBottomLeft(float _pos_x, float _pos_y)
{
    bottomLeft.x = _pos_x;
    bottomLeft.y = _pos_y;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::SetBottomLeftX(float _pos_x)
{
    bottomLeft.x = _pos_x;

    UpdateCenter();
    UpdateTopRight();
}

void Rect::SetSize(float w, float h)
{
    this->w = w;
    this->h = h;

    bottomLeft.x = center.x - w/2;
    bottomLeft.y = center.y - h/2;
    
    UpdateTopRight();
}

void Rect::MovingBy(const glm::vec2& d_pos)
{
    bottomLeft += d_pos;
    UpdateCenter();
    UpdateTopRight();
}

void Rect::UpdateCenter()
{
    center.x = bottomLeft.x + w/2;
    center.y = bottomLeft.y + h/2;
}

void Rect::UpdateTopRight()
{
    topRight.x = bottomLeft.x + w;
    topRight.y = bottomLeft.y + h;    
}

} // namespace ceti
