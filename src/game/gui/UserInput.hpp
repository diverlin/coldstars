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


#ifndef USERINPUT_HPP
#define USERINPUT_HPP


#include <SFML/Window.hpp>

class UserInputManagerInSpace;


class UserInput
{
    public:
        static UserInput& Instance();
        ~UserInput() {};
        
        void Update();
        
    private:
        UserInput() {};
        UserInput(const UserInput&) = delete;
        UserInput& operator=(const UserInput&) = delete;
        
        sf::Event m_Event;        
        
        std::vector<sf::Keyboard::Key> m_KeyboardCodesPressed_vec;
        std::vector<sf::Keyboard::Key> m_MouseCodesPressed_vec;
    
    friend class UserInputManagerInSpace;
};

#endif 
