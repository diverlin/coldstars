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

#include <math/myVector.hpp>

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
            
        void SetCenter(const glm::vec2&);
        void SetCenter(float, float);
        void SetBottomLeftX(float);
        void SetBottomLeft(const glm::vec2&);
        void SetBottomLeft(float, float);
                    
        const glm::vec2& GetCenter() const     { return center; }
        const glm::vec2& GetBottomLeft() const { return bottomLeft; }
        const glm::vec2& GetTopRight() const { return topRight; }
        float GetWidth() const         { return w; }
        float GetHeight() const     { return h; }  
        
        void SetSize(float, float);
        void MovingBy(const glm::vec2&);
                            
    private:
        glm::vec2 bottomLeft;    
        glm::vec2 center;  
        glm::vec2 topRight;
        
        float w, h;
        
        void UpdateCenter();
        void UpdateTopRight();
};


