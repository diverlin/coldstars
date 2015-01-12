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
        
        void Set(const Box2D&);
        
        void setCenter(const glm::vec2& center)    { m_Center = center; } 
        void setCenter(float x, float y)           { m_Center = glm::vec2(x, y); } 
        void setSize(const glm::vec2& size)        { m_Size = size; } 
        void setSize(float x, float y)             { m_Size = glm::vec2(x, y); } 
        void SetScale(const glm::vec2& scale)      { m_Scale = scale; }
        void SetScale(float x, float y)            { m_Scale = glm::vec2(x, y); }
        void SetAngle(float angle)                 { m_Angle = angle; }
                
        const glm::vec2& center() const    { return m_Center; }                    
        const glm::vec2& size() const        { return m_Size; }
        const glm::vec2& GetScale() const        { return m_Scale; }
        float GetAngle() const        { return m_Angle; }
                
        const glm::vec2 GetMiddleTop() const { return m_Center + glm::vec2(0, m_Size.y/2); }
        
        bool CheckInteraction(const glm::vec2&) const;    
                                          
    private:
        glm::vec2 m_Center;
        glm::vec2 m_Size;
        glm::vec2 m_Scale;
        
        float m_Angle;
};

} // namespace ceti
