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

#include <glm/glm.hpp>

namespace ceti {

class Rect; // tmp  hack

class Box2D
{  
public:
    Box2D();
    Box2D(const glm::vec2&);
    Box2D(const glm::vec2&, const glm::vec2&);
    Box2D(const Box2D&);
    Box2D(const Rect&); // depr
    ~Box2D();

    void set(const Box2D&);

    void setCenter(const glm::vec2& center)    { m_center = center; }
    void setCenter(float x, float y)           { m_center = glm::vec2(x, y); }
    void setSize(const glm::vec2& size)        { m_size = size; }
    void setSize(float x, float y)             { m_size = glm::vec2(x, y); }
    void setScale(const glm::vec2& scale)      { m_scale = scale; }
    void setScale(float x, float y)            { m_scale = glm::vec2(x, y); }
    void setAngle(float angle)                 { m_angle = angle; }

    const glm::vec2& center() const    { return m_center; }
    const glm::vec2& size() const        { return m_size; }
    const glm::vec2& scale() const        { return m_scale; }
    float angle() const { return m_angle; }

    const glm::vec2 middleTop() const { return m_center + glm::vec2(0, m_size.y/2); }

    bool checkInteraction(const glm::vec2&) const;

private:
    glm::vec2 m_center;
    glm::vec2 m_size;
    glm::vec2 m_scale;

    float m_angle;
};

} // namespace ceti
