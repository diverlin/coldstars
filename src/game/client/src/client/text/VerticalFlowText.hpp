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

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <glm/glm.hpp>

#include <string>

namespace effect {

class Text
{
public:
    Text(sf::Font&,
         const std::string&, int,
         const glm::vec2&,
         const glm::ivec4&);
    ~Text();

    bool isAlive() const { return m_isAlive; }
    const glm::vec2& center() const { return m_center; }

    void update();
    void draw(sf::RenderWindow&, const glm::vec3&, float scale = 1.0f);
    
private:
    sf::Text m_sfText;
    bool m_isAlive = true;
    int m_liveTime = 70;

    int m_fontSize = 12;

    std::string m_text;
    glm::ivec4 m_color;

    glm::vec2 m_center;

    float m_speed = 2.0f;
};

} // namespace effect
