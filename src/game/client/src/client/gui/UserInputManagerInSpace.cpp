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
#include <client/common/global.hpp>
#include <common/Global.hpp>
#include <common/Config.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>

#include <parts/WeaponComplex.hpp>
#include <pilots/Npc.hpp>
#include <client/pilots/Player.hpp>

#include <spaceobjects/Vehicle.hpp>

#include <client/gui/GuiManager.hpp>

UserInputInSpace::UserInputInSpace()
:
m_nextTurnReady(false),
m_cameraMoveAxisX(CAMERADIRECTION::NONE),
m_cameraMoveAxisY(CAMERADIRECTION::NONE)
{}

UserInputInSpace::~UserInputInSpace()
{}
        
void UserInputInSpace::update(Player* player)
{
    UserInput::get().update();

    __reset();
    
    __manageInputsInSpace(player);
    __manageRealTimeInputsInSpace(player);
    __mouseButtonPressed(player);
    __scrollCamera(player);
}


void UserInputInSpace::__manageInputsInSpace(Player* player)
{  
    for (const auto & key_code : UserInput::get().m_keyboardPressedCodes)   
    {
        switch (key_code) 
        {    
            case sf::Keyboard::Escape:
            {        
                if (player->GetNpc()->scanTarget()) {
                    //player->GetNpc()->ResetScanTarget();
                } else {
                    m_runSession = false;
                }
                
                break;
            }
            
            case sf::Keyboard::Space:
            {
                if (!m_nextTurnReady) {
                    m_nextTurnReady = true;
                }
    
                break;
            } 
    
            //DRIVE SLOT
            case sf::Keyboard::F: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::DRIVE_SLOT_SELECTOR_ID); break; }
            
            case sf::Keyboard::N: { player->GetShow().InverseCollisionRadius(); break; }
            
            // WEAPON SLOTS
            case sf::Keyboard::Num1: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT1_SELECTOR_ID); break; }
            case sf::Keyboard::Num2: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT2_SELECTOR_ID); break; }
            case sf::Keyboard::Num3: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT3_SELECTOR_ID); break; }
            case sf::Keyboard::Num4: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT4_SELECTOR_ID); break; }
            case sf::Keyboard::Num5: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT5_SELECTOR_ID); break; }
            case sf::Keyboard::Num6: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT6_SELECTOR_ID); break; }
            case sf::Keyboard::Num7: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT7_SELECTOR_ID); break; }
            case sf::Keyboard::Num8: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT8_SELECTOR_ID); break; }
            case sf::Keyboard::Num9: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT9_SELECTOR_ID); break; }
            
            case sf::Keyboard::A:
            { 
//                if (player->GetNpc()->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                {
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT1_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT2_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT3_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT4_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT5_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT6_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT7_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT8_SELECTOR_ID);
//                    GuiManager::Instance().ResetEventOnGuiElement(type::GUI::WEAPON_SLOT9_SELECTOR_ID);
//                }
//                else
//                {
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT1_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT2_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT3_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT4_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT5_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT6_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT7_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT8_SELECTOR_ID);
//                    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::WEAPON_SLOT9_SELECTOR_ID);
//                }
                
                break;
            }
    
            case sf::Keyboard::C: 
            { 
                glm::vec3 player_pos3 = player->GetNpc()->vehicle()->position();
                glm::vec2 player_pos2(player_pos3.x, player_pos3.y);
                client::global::get().screen().initiateScrollTo(player_pos2);
                break; 
            }
            case sf::Keyboard::G: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::GRAPPLE_SLOT_SELECTOR_ID); break; }
            
            case sf::Keyboard::M: {    GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::GALAXYMAP_ID); break; }
            
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
                std::cout<<"god_mode ="<<!player->GetNpc()->vehicle()->godMode()<<std::endl;
                player->GetNpc()->vehicle()->setGodMode(!player->GetNpc()->vehicle()->godMode());
                break;
            }
    
            case sf::Keyboard::F3: // auto save mode
            {        
                //global::get().config().SetAutoSaveMode(!global::get().config().GetAutoSaveMode());
                break;
            }
            
            case sf::Keyboard::F4: // auto load mode
            {        
                //global::get().config().SetAutoLoadMode(!global::get().config().GetAutoLoadMode());
                break;
            }
                    
            case sf::Keyboard::F5: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::SAVE_ID); break; }
            
            case sf::Keyboard::F6: // slow down GAME SPEED 
            {
//                if (core::global::get().config().GAME_SPEED > 1)
//                {
//                   core::global::get().config().GAME_SPEED--;
//                }
                break;
            }
    
            case sf::Keyboard::F7: // speed up GAME SPEED 
            {
//                if (core::global::get().config().GAME_SPEED < 10)
//                {
//                   core::global::get().config().GAME_SPEED++;
//                }
                break;
            }
            
            case sf::Keyboard::F8: // AutoTurn
            {
                //global::get().config().AUTO_TURN_MODE = !global::get().config().AUTO_TURN_MODE;
                break;
            }
            
            case sf::Keyboard::F9: { GuiManager::Instance().PressEventMBL_onGuiElement(type::GUI::LOAD_ID); break; }
    
            case sf::Keyboard::K: { client::global::get().screen().increaseScale(); break; }
            case sf::Keyboard::L: { client::global::get().screen().decreaseScale(); break; }

            case sf::Keyboard::X: { client::global::get().render().showAxis(true); break; }
            case sf::Keyboard::Z: { client::global::get().render().showAxis(false); break; }

        }
    }
}
        
void UserInputInSpace::__mouseButtonPressed(Player* player)
{
    for (const auto & key_code : UserInput::get().m_mousePressedCodes)   
    {
        switch (key_code) {
            case sf::Mouse::Left:  { player->GetCursor().SetLeftMouseButtonClick(true); break; } 
            case sf::Mouse::Right: { player->GetCursor().SetRightMouseButtonClick(true); break; }
        }
    }
}
 
void UserInputInSpace::__reset()
{       
    m_nextTurnReady = false;
    
    m_cameraMoveAxisX  = CAMERADIRECTION::NONE;
    m_cameraMoveAxisY  = CAMERADIRECTION::NONE;
}
               
void UserInputInSpace::__manageRealTimeInputsInSpace(Player* player)
{ 
    //sf::Vector2i mouse_pos = sf::Mouse::getPosition(Screen::Instance().GetWindow());
       
    int mx = player->GetCursor().GetMouseData().pos_screencoord.x;
    int my = player->GetCursor().GetMouseData().pos_screencoord.y;
    
    int screen_w = client::global::get().screen().width();
    int screen_h = client::global::get().screen().height();
    
    //bool mouse_camera_scroll = core::global::get().config().GetMouseCameraScroll();
                 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_cameraMoveAxisX = CAMERADIRECTION::LEFT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_cameraMoveAxisX = CAMERADIRECTION::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_cameraMoveAxisY = CAMERADIRECTION::UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_cameraMoveAxisY = CAMERADIRECTION::DOWN;
    }   
                         
//    if ((mouse_camera_scroll)and(mx < SCROLL_BORDER_OFFSET))
//    {
//        m_CameraMoveAxisX = CAMERADIRECTION::LEFT;
//    }
//    if ((mouse_camera_scroll)and(mx > (screen_w - SCROLL_BORDER_OFFSET)))
//    {
//        m_CameraMoveAxisX = CAMERADIRECTION::RIGHT;
//    }
//    if ((mouse_camera_scroll)and(my > (screen_h - SCROLL_BORDER_OFFSET)))
//    {
//        m_CameraMoveAxisY = CAMERADIRECTION::UP;
//    }
//    if ((mouse_camera_scroll)and(my < SCROLL_BORDER_OFFSET))
//    {
//        m_CameraMoveAxisY = CAMERADIRECTION::DOWN;
//    }
}

void UserInputInSpace::__scrollCamera(Player* player)
{
    int SCROLL_VELOCITY_STEP = core::global::get().config().SCROLL_VELOCITY_STEP;

    jeti::Camera& camera = client::global::get().camera();
    
    // SCROLLING X AXIS
    switch (m_cameraMoveAxisX)
    {
    case CAMERADIRECTION::LEFT:
        camera.appendSpeed(glm::vec3(-SCROLL_VELOCITY_STEP, 0.0f, 0.0f));
        break;
    case CAMERADIRECTION::RIGHT:
        camera.appendSpeed(glm::vec3(SCROLL_VELOCITY_STEP, 0.0f, 0.0f));
        break;
    }

    switch(m_cameraMoveAxisY)
    {
    case CAMERADIRECTION::UP:
        camera.appendSpeed(glm::vec3(0.0f, SCROLL_VELOCITY_STEP, 0.0f));
        break;
    case CAMERADIRECTION::DOWN:
        camera.appendSpeed(glm::vec3(0.0f, -SCROLL_VELOCITY_STEP, 0.0f));
        break;
    }

    client::global::get().screen().move(m_scrollAccel);
}
