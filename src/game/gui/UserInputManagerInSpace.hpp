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


#ifndef UserInputManagerInSpaceINSPACE_HPP
#define UserInputManagerInSpaceINSPACE_HPP

#include <SFML/Window.hpp> // !!!
#include <math/Vec2.hpp>
#include <common/constants.hpp>

class Player;
class GuiManager;


class UserInputManagerInSpace
{
    public:
        static UserInputManagerInSpace& Instance();
        ~UserInputManagerInSpace();
        
        bool GetNextTurnReady() const { return     m_NextTurnReady; }
        
        void UpdateInSpace(Player*);
        
    private:
        UserInputManagerInSpace();
        UserInputManagerInSpace(const UserInputManagerInSpace&) = delete;
        UserInputManagerInSpace& operator=(const UserInputManagerInSpace&) = delete;

        bool m_NextTurnReady;
                
        CAMERADIRECTION m_CameraMoveAxisX;
        CAMERADIRECTION m_CameraMoveAxisY;
            
        Vec2<float> m_ScrollAccel; 
                
        void Reset();                    
    
        void ManageInputsInSpace(Player*);
        
        void MouseButtonPressed(Player*);
                    
        void ManageRealTimeInputsInSpace(Player*);
        void ScrollCamera(Player*);
};

#endif 
