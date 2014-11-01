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


#include <gui/UserInput.hpp>

#include <jeti/Screen.hpp>
#include <iostream>

UserInput& UserInput::Instance()
{
    static UserInput instance;
    return instance;
}

void UserInput::Update()
{    
    m_KeyboardCodesPressed_vec.clear();
    m_MouseCodesPressed_vec.clear();
        
    while (jeti::Screen::Instance().GetWindow().pollEvent(m_Event))
    {
        switch(m_Event.type)
        {
            case sf::Event::Closed:             { jeti::Screen::Instance().GetWindow().close(); break; }
            case sf::Event::KeyPressed:         { m_KeyboardCodesPressed_vec.push_back(m_Event.key.code); break; }
            //case sf::Event::Resized:            { Screen::Instance().Resize(event.size.x, event.size.y); break; }
            //case sf::Event::MouseButtonPressed: { MouseButtonPressed(player); break; }
            case sf::Event::MouseButtonPressed: { m_MouseCodesPressed_vec.push_back(m_Event.key.code); break; }
        } 
   }    
}
     

       
