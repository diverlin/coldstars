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

#include <client/session/Shortcuts.hpp>

#include <client/gui/UserInput.hpp>

#include <jeti/Screen.hpp>

#include <iostream>

namespace gui {

UserInput& UserInput::get()
{
    static UserInput instance;
    return instance;
}

void UserInput::update()
{    
    m_keyboardPressedCodes.clear();
    m_mousePressedCodes.clear();
    m_mouseReleasedCodes.clear();

    sf::Event event;
    while(client::shortcuts::screen()->window().pollEvent(event)) {
        switch(event.type)  {
        case sf::Event::Closed:     {
            client::shortcuts::screen()->window().close();
            break;
        }
        case sf::Event::KeyPressed: {
            m_keyboardPressedCodes.push_back(event.key.code);
            break;
        }
            //case sf::Event::Resized:            { Screen::Instance().Resize(event.size.x, event.size.y); break; }
            //case sf::Event::MouseButtonPressed: { MouseButtonPressed(player); break; }
        case sf::Event::MouseButtonPressed: {
            //std::cout<<"--mb press..."<<std::endl;
            m_mousePressedCodes.push_back(event.key.code);
            break;
        }
        case sf::Event::MouseButtonReleased: {
            //std::cout<<"--mb release..."<<std::endl;
            m_mouseReleasedCodes.push_back(event.key.code);
            break;
        }

        }
        // share events with gui
        if (m_desktop) {
            // in some reason event handler wants to be inside the pollEvent
            m_desktop->HandleEvent(event);
        }
    }
}

} // namespace gui



