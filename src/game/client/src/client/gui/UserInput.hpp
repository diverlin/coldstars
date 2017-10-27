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

#include <SFML/Window.hpp>

#include <SFGUI/Desktop.hpp>

class UserInputInSpace;

class UserInput
{
public:
    static UserInput& get();
    ~UserInput() {}

    //void update();
    void setDesktop(sfg::Desktop* desktop) { m_desktop = desktop; }
    void update();
    //    const std::vector<sf::Event>& events() const { return m_events; }

    const std::vector<sf::Keyboard::Key>& mousePressedCodes() { return m_mousePressedCodes; }
    const std::vector<sf::Keyboard::Key>& mouseReleasedCodes() { return m_mouseReleasedCodes; }

private:
    UserInput() {}
    UserInput(const UserInput&) = delete;
    UserInput& operator=(const UserInput&) = delete;

//    std::vector<sf::Event> m_events;

    std::vector<sf::Keyboard::Key> m_keyboardPressedCodes;
    std::vector<sf::Keyboard::Key> m_mousePressedCodes;
    std::vector<sf::Keyboard::Key> m_mouseReleasedCodes;

    sfg::Desktop* m_desktop = nullptr;
    friend class UserInputInSpace;
};

