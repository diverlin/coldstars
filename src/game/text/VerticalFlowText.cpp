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

#include "VerticalFlowText.hpp"
#include "../common/rand.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"

VerticalFlowText::VerticalFlowText(const std::string& text, 
                                    int font_size,
                                    const glm::vec2& center, 
                                    const glm::ivec4& color, 
                                    float collision_radius)
:
m_IsAlive(true),
m_LiveTime(70), //TEXT_EXISTANCE_TIME
m_FontSize(font_size),
m_Text(text),
m_Color(color),
m_Speed(2.0)
{
    float kof1 = 0.1 * getRandInt(3, 18);
    float kof2 = 0.1 * getRandInt(5, 15);
    
    m_Center.x = center.x - collision_radius * kof1;
    m_Center.y = center.y + collision_radius * kof2;
}

VerticalFlowText::~VerticalFlowText()
{}

void VerticalFlowText::Update()
{
    if (m_IsAlive == true)
    {
        m_Center.y += m_Speed;
        if (m_Speed > 0.5)
        {
            m_Speed -= 0.1;
        }
        
        m_LiveTime -= 1;
        if (m_LiveTime < 0)
        {
            m_IsAlive = false;
        }
    }
}
                
void VerticalFlowText::Render(const glm::vec2& scroll_coords, float scale) const
{
    if (m_IsAlive == true)
    {
        drawColoredText(m_Text, m_FontSize, (m_Center-scroll_coords)*scale, m_Color);
    }
}
 

