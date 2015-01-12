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

#include <meti/VectorUtils.hpp>

namespace ceti {

class Rect
{  
    public:
        Rect();
        Rect(float, float, float, float);
        Rect(const glm::vec2&, float, float);
        Rect(const Rect&);
        ~Rect();
        
        void Scale(float);
        void Scale(const glm::vec2&);
        
        bool CheckInteraction(float, float) const;
        bool CheckInteraction(const glm::vec2&) const;
        bool CheckRoundInteraction(const glm::vec2&, float) const;
                            
        void Set(float, float, float, float);
        void Set(const glm::vec2&, float, float);
        void Set(const Rect&);
            
        void setCenter(const glm::vec2&);
        void setCenter(float, float);
        void SetBottomLeftX(float);
        void SetBottomLeft(const glm::vec2&);
        void SetBottomLeft(float, float);
                    
        const glm::vec2& center() const     { return m_center; }
        const glm::vec2& GetBottomLeft() const { return m_bottomLeft; }
        const glm::vec2& GetTopRight() const { return m_topRight; }
        float GetWidth() const         { return m_width; }
        float GetHeight() const     { return m_height; }
        
        void setSize(float, float);
        void MovingBy(const glm::vec2&);
                            
    private:
        glm::vec2 m_bottomLeft;
        glm::vec2 m_center;
        glm::vec2 m_topRight;
        
        float m_width, m_height;
        
        void UpdateCenter();
        void UpdateTopRight();
};

} // namespace ceti

