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
#include "BaseButton.hpp"
#include "../world/EntityManager.hpp"
#include "../config/config.hpp"
#include "../render/Screen.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../pilots/Npc.hpp"
#include "../pilots/Player.hpp"

#include "../spaceobjects/Vehicle.hpp"

#include "../gui/GuiManager.hpp"

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
                if (player->GetNpc()->GetScanTarget() != nullptr)
                {
                    player->GetNpc()->ResetScanTarget();
                }
                
                break;
            }
            
            case sf::Keyboard::Space:
            {
                if (m_NextTurnReady == false)
                {
                    m_NextTurnReady = true;
                }
    
                break;
            } 
    
            //DRIVE SLOT
            case sf::Keyboard::F: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::DRIVE_SLOT_SELECTOR_ID); break; }    
            
            case sf::Keyboard::N: { player->GetShow().InverseCollisionRadius(); break; }
            
            // WEAPON SLOTS
            case sf::Keyboard::Num1: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID); break; }        
            case sf::Keyboard::Num2: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID); break; }
            case sf::Keyboard::Num3: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID); break; } 
            case sf::Keyboard::Num4: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID); break; } 
            case sf::Keyboard::Num5: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID); break; }
            case sf::Keyboard::Num6: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID); break; }
            case sf::Keyboard::Num7: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID); break; }
            case sf::Keyboard::Num8: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID); break; }                
            case sf::Keyboard::Num9: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID); break; } 
            
            case sf::Keyboard::A:
            { 
                if (player->GetNpc()->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                {
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID);
                    GuiManager::Instance().ResetEventOnGuiElement(TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID);    
                }
                else
                {        
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID);
                    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID);                
                }
                
                break;
            }
    
            case sf::Keyboard::C: 
            { 
                glm::vec3 player_pos3 = player->GetNpc()->GetVehicle()->GetCenter();
                glm::vec2 player_pos2(player_pos3.x, player_pos3.y);
                Screen::Instance().InitiateScrollTo(player_pos2); 
                break; 
            }
            case sf::Keyboard::G: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::GRAPPLE_SLOT_SELECTOR_ID); break; }    
            
            case sf::Keyboard::M: {    GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::GALAXYMAP_ID); break; }
            
            case sf::Keyboard::R: // RADAR
            {
                player->GetShow().InverseRangeRadar();
                break;
            }
    
            case sf::Keyboard::O: // Orbits
            {
                player->GetShow().InverseAllOrbits();
                break;
            }
    
            case sf::Keyboard::P: // Path
            {
                player->GetShow().InverseAllPath();
                break;
            }
    
            case sf::Keyboard::F1: // god mode on/off
            {    
                std::cout<<"god_mode ="<<!player->GetNpc()->GetVehicle()->GetGodMode()<<std::endl;
                player->GetNpc()->GetVehicle()->SetGodMode(!player->GetNpc()->GetVehicle()->GetGodMode());            
                break;
            }
    
            case sf::Keyboard::F3: // auto save mode
            {        
                Config::Instance().SetAutoSaveMode(!Config::Instance().GetAutoSaveMode());            
                break;
            }
            
            case sf::Keyboard::F4: // auto load mode
            {        
                Config::Instance().SetAutoLoadMode(!Config::Instance().GetAutoLoadMode());        
                break;
            }
                    
            case sf::Keyboard::F5: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::SAVE_ID); break; }
            
            case sf::Keyboard::F6: // slow down GAME SPEED 
            {
                if (Config::Instance().GAME_SPEED > 1)
                {
                    Config::Instance().GAME_SPEED--;
                }
                break;
            }
    
            case sf::Keyboard::F7: // speed up GAME SPEED 
            {
                if (Config::Instance().GAME_SPEED < 10)
                {
                    Config::Instance().GAME_SPEED++;
                }                             
                break;
            }
            
            case sf::Keyboard::F8: // AutoTurn
            {
                Config::Instance().AUTO_TURN_MODE = !Config::Instance().AUTO_TURN_MODE;
                break;
            }
            
            case sf::Keyboard::F9: { GuiManager::Instance().PressEventMBL_onGuiElement(TYPE::GUI::LOAD_ID); break; }        
    
            case sf::Keyboard::K: { Screen::Instance().IncreaseScale(); break; }    
            case sf::Keyboard::L: { Screen::Instance().DecreaseScale(); break; }    
        }   
    }
}
        
void UserInputManagerInSpace::MouseButtonPressed(Player* player)
{
    for (const auto & key_code : UserInput::Instance().m_MouseCodesPressed_vec)   
    {
        switch (key_code) 
        {    
            case sf::Mouse::Left:  { player->GetCursor().SetLeftMouseButtonClick(true); break; } 
            case sf::Mouse::Right: { player->GetCursor().SetRightMouseButtonClick(true); break; }
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
    //sf::Vector2i mouse_pos = sf::Mouse::getPosition(Screen::Instance().GetWindow());
       
    int mx = player->GetCursor().GetMouseData().pos_screencoord.x;
    int my = player->GetCursor().GetMouseData().pos_screencoord.y;
    
    int screen_w = Screen::Instance().GetWidth();
    int screen_h = Screen::Instance().GetHeight();
    
    bool mouse_camera_scroll = Config::Instance().GetMouseCameraScroll();
                 
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
                         
    if ((mouse_camera_scroll)and(mx < SCROLL_BORDER_OFFSET)) 
    {
        m_CameraMoveAxisX = CAMERADIRECTION::LEFT;
    }   
    if ((mouse_camera_scroll)and(mx > (screen_w - SCROLL_BORDER_OFFSET)))
    {
        m_CameraMoveAxisX = CAMERADIRECTION::RIGHT;
    }   
    if ((mouse_camera_scroll)and(my > (screen_h - SCROLL_BORDER_OFFSET)))
    {
        m_CameraMoveAxisY = CAMERADIRECTION::UP;
    }   
    if ((mouse_camera_scroll)and(my < SCROLL_BORDER_OFFSET)) 
    {
        m_CameraMoveAxisY = CAMERADIRECTION::DOWN;
    }   
}

void UserInputManagerInSpace::ScrollCamera(Player* player)
{
    int SCROLL_VELOCITY_STEP = Config::Instance().SCROLL_VELOCITY_STEP; 

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
