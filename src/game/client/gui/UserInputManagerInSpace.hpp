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

#include <glm/glm.hpp>
#include <common/constants.hpp>

class Player;
class GuiManager;

class UserInputInSpace
{
    public:
        static UserInputInSpace& get();
        ~UserInputInSpace();
        
        bool nextTurnReady() const { return m_nextTurnReady; }
        bool runSession() const { return m_runSession; }

        void update(Player*);
        
    private:
        UserInputInSpace();
        UserInputInSpace(const UserInputInSpace&) = delete;
        UserInputInSpace& operator=(const UserInputInSpace&) = delete;

        bool m_nextTurnReady = false;
        bool m_runSession = true;

        CAMERADIRECTION m_cameraMoveAxisX;
        CAMERADIRECTION m_cameraMoveAxisY;
            
        glm::vec2 m_scrollAccel;
                
        void __reset();
    
        void __manageInputsInSpace(Player*);
        
        void __mouseButtonPressed(Player*);
                    
        void __manageRealTimeInputsInSpace(Player*);
        void __scrollCamera(Player*);
};


