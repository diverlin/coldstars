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

#include "UserInputManagerInSpace.hpp"
#include "UserInput.hpp"
#include "../render/Screen.hpp"

UserInputManagerInSpace& UserInputManagerInSpace::Instance()
{
    static UserInputManagerInSpace instance;
    return instance;
}

UserInputManagerInSpace::UserInputManagerInSpace()
:
m_NextTurnReady(false),
m_CameraMoveAxisX(CAMERADIRECTION::NONE),
m_CameraMoveAxisY(CAMERADIRECTION::NONE)
{}

UserInputManagerInSpace::~UserInputManagerInSpace()
{}
        
void UserInputManagerInSpace::UpdateInSpace(Player* player)
{
    Reset();
    
    ManageInputsInSpace(player);
    ManageRealTimeInputsInSpace(player);
    MouseButtonPressed(player);
    ScrollCamera(player);
}


void UserInputManagerInSpace::ManageInputsInSpace(Player* player)
{  
    for (const auto & key_code : UserInput::Instance().m_KeyboardCodesPressed_vec)   
    {
        switch (key_code) 
        {    
            case sf::Keyboard::Escape:
            {        
                
                break;
            }


        }   
    }
}
        
void UserInputManagerInSpace::MouseButtonPressed(Player* player)
{
    for (const auto & key_code : UserInput::Instance().m_MouseCodesPressed_vec)   
    {
        switch (key_code) 
        {    

        }
    }
}
 
void UserInputManagerInSpace::Reset()
{       
    m_NextTurnReady = false;
    
    m_CameraMoveAxisX  = CAMERADIRECTION::NONE;
    m_CameraMoveAxisY  = CAMERADIRECTION::NONE;
}
               
void UserInputManagerInSpace::ManageRealTimeInputsInSpace(Player* player)
{                      
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
    {                
        m_CameraMoveAxisX = CAMERADIRECTION::LEFT;
    }           
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
    {                
        m_CameraMoveAxisX = CAMERADIRECTION::RIGHT;
    }   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
    {                
        m_CameraMoveAxisY = CAMERADIRECTION::UP;
    }   
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true)
    {                
        m_CameraMoveAxisY = CAMERADIRECTION::DOWN;
    }   
                         

}

void UserInputManagerInSpace::ScrollCamera(Player* player)
{
    int SCROLL_VELOCITY_STEP = 1.0;

    Camera& camera = Screen::Instance().GetCamera();
    
    
    // SCROLLING X AXIS         
    switch (m_CameraMoveAxisX)
    {
        case CAMERADIRECTION::LEFT:
        {
            camera.AddMoveSpeed(glm::vec3(-SCROLL_VELOCITY_STEP, 0.0f, 0.0f));
            
            break;
        }
        
        case CAMERADIRECTION::RIGHT:
        {
            camera.AddMoveSpeed(glm::vec3(SCROLL_VELOCITY_STEP, 0.0f, 0.0f));
            
            break;
        }       
    }

    switch(m_CameraMoveAxisY)
    {
        case CAMERADIRECTION::UP:
        {
            camera.AddMoveSpeed(glm::vec3(0.0f, SCROLL_VELOCITY_STEP, 0.0f));
                
            break;
        }
            
        case CAMERADIRECTION::DOWN:
        {
            camera.AddMoveSpeed(glm::vec3(0.0f, -SCROLL_VELOCITY_STEP, 0.0f));
                
            break;
        }
    }
     
    Screen::Instance().MovingBy(m_ScrollAccel);
}
