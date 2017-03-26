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


#ifndef VERTICALFLOWTEXT_HPP
#define VERTICALFLOWTEXT_HPP

#include <string>

#include <glm/glm.hpp>


class VerticalFlowText
{
    public:
        VerticalFlowText(const std::string&, int, const glm::vec2&, const glm::ivec4&, float);                                   
        ~VerticalFlowText();
        
        bool isAlive() const { return m_IsAlive; }
        
        const glm::vec2& center() const { return m_Center; }
        
        void Update();
        void Render(const glm::vec2&, float) const;
    
    private:
        bool m_IsAlive;
        int m_LiveTime;
        
        int m_FontSize;
        
        std::string m_Text;
        glm::ivec4 m_Color;
        
        glm::vec2 m_Center;
        
        float m_Speed;
};

#endif 
