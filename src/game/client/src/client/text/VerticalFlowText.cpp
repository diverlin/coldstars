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

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

#include <meti/RandUtils.hpp>

namespace effect {

Text::Text(const std::string& text,
           int font_size,
           const glm::vec2& center,
           const glm::ivec4& color)
    :
      m_fontSize(font_size)
    , m_text(text)
    , m_color(color)
{
//    float kof1 = 0.1f * meti::getRandInt(3, 18);
//    float kof2 = 0.1f * meti::getRandInt(5, 15);
    
//    m_center.x = center.x - collision_radius * kof1;
//    m_center.y = center.y + collision_radius * kof2;

    m_center = glm::vec2(0.0f); //= center;

    m_sfText.setString(text);
    int scale = 24;
    m_sfText.setScale(scale, scale);
    //sf::Color sfColor(color.r*255, color.g*255, color.b*255, color.a*255);
    sf::Color sfColor(255, 255, 255, 255);
    m_sfText.setColor(sfColor);
}

Text::~Text()
{}

void Text::update()
{
    if (!m_isAlive) {
        return;
    }

    m_center.y += m_speed;
    if (m_speed > 0.5f) {
        m_speed -= 0.1;
    }

    m_liveTime -= 1;
    if (m_liveTime < 0) {
        m_isAlive = false;
    }
}

void Text::draw(sf::RenderWindow& window, const glm::vec3& scroll_coords, float scale)
{
    if (!m_isAlive) {
        return;
    }

    m_sfText.setPosition(m_center.x-scroll_coords.x, m_center.y-scroll_coords.y);
    window.draw(m_sfText);
}

} // namepsace effect
