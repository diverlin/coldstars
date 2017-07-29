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

#include <core/part/WeaponComplex.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <client/pilots/Player.hpp>
#include <client/gui/GuiManager.hpp>

UserInputInSpace::UserInputInSpace()
    :
      m_nextTurnReady(false)
{
    m_scrollStep = core::global::get().config().SCROLL_VELOCITY_STEP;
}

UserInputInSpace::~UserInputInSpace()
{}

void UserInputInSpace::update(Player* player)
{
    UserInput::get().update();

    __reset();
    
    __manageInputsInSpace(player);
    __manageRealTimeInputsInSpace(player);
    __mouseButtonPressed(player);
}


void UserInputInSpace::__manageInputsInSpace(Player* player)
{  
    for (const auto & key_code : UserInput::get().m_keyboardPressedCodes)
    {
        switch (key_code)
        {
        case sf::Keyboard::Escape:
        {
            assert(false);
            //                if (player->GetNpc()->scanTarget()) {
            //                    //player->GetNpc()->ResetScanTarget();
            //                } else {
            //                    m_runSession = false;
            //                }

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
        case sf::Keyboard::F: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::DRIVE_SLOT_SELECTOR); break; }

            // WEAPON SLOTS
        case sf::Keyboard::Num1: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT1_SELECTOR); break; }
        case sf::Keyboard::Num2: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT2_SELECTOR); break; }
        case sf::Keyboard::Num3: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT3_SELECTOR); break; }
        case sf::Keyboard::Num4: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT4_SELECTOR); break; }
        case sf::Keyboard::Num5: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT5_SELECTOR); break; }
        case sf::Keyboard::Num6: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT6_SELECTOR); break; }
        case sf::Keyboard::Num7: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT7_SELECTOR); break; }
        case sf::Keyboard::Num8: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT8_SELECTOR); break; }
        case sf::Keyboard::Num9: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT9_SELECTOR); break; }
            
        case sf::Keyboard::A:
        {
            //                if (player->GetNpc()->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
            //                {
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT1_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT2_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT3_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT4_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT5_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT6_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT7_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT8_SELECTOR);
            //                    GuiManager::Instance().ResetEventOnGuiElement(gui::type::WEAPON_SLOT9_SELECTOR);
            //                }
            //                else
            //                {
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT1_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT2_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT3_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT4_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT5_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT6_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT7_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT8_SELECTOR);
            //                    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::WEAPON_SLOT9_SELECTOR);
            //                }

            break;
        }

        case sf::Keyboard::C:
        {
            assert(false);
            //                glm::vec3 player_pos3 = player->GetNpc()->vehicle()->position();
            //                glm::vec2 player_pos2(player_pos3.x, player_pos3.y);
            //                client::global::get().screen().initiateScrollTo(player_pos2);
            break;
        }
        case sf::Keyboard::G: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::GRAPPLE_SLOT_SELECTOR); break; }
            
        case sf::Keyboard::M: {    GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::GALAXYMAP); break; }
            
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
            assert(false);
            //                std::cout<<"god_mode ="<<!player->GetNpc()->vehicle()->godMode()<<std::endl;
            //                player->GetNpc()->vehicle()->setGodMode(!player->GetNpc()->vehicle()->godMode());
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

        case sf::Keyboard::F5: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::SAVE); break; }
            
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
            
        case sf::Keyboard::F9: { GuiManager::Instance().PressEventMBL_onGuiElement(gui::type::LOAD); break; }

        case sf::Keyboard::K: { client::global::get().render().increaseScale(); break; }
        case sf::Keyboard::L: { client::global::get().render().decreaseScale(); break; }

            //            case sf::Keyboard::X: { client::global::get().render().increaseLightPos(); break; }
            //            case sf::Keyboard::Z: { client::global::get().render().decreaseLightPos(); break; }

        case sf::Keyboard::X: { client::global::get().render().setAllowDrawAxis(true); break; }
        case sf::Keyboard::Z: { client::global::get().render().setAllowDrawAxis(false); break; }

        case sf::Keyboard::B: { client::global::get().render().setAllowDrawCollisionRadius(true); break; }
        case sf::Keyboard::N: { client::global::get().render().setAllowDrawCollisionRadius(false); break; }
        }
    }
}

void UserInputInSpace::__mouseButtonPressed(Player* player)
{
    for (const auto & key_code : UserInput::get().m_mousePressedCodes)
    {
        switch (key_code) {
        case sf::Mouse::Left:
        {
            //            sf::Vector2i mouse_pos = sf::Mouse::getPosition(client::global::get().screen().window());
            //            client::global::get().render().setLightPos(mouse_pos.x, client::global::get().screen().height() - mouse_pos.y);

            player->cursor().setLeftMouseButtonClick(true);
            break;
        }
        case sf::Mouse::Right: { player->cursor().setRightMouseButtonClick(true); break; }
        }
    }
}

void UserInputInSpace::__reset()
{       
    m_nextTurnReady = false;
    m_scrollAccel = glm::vec3(0);
}

void UserInputInSpace::__manageRealTimeInputsInSpace(Player* player)
{ 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_scrollAccel.x -= m_scrollStep;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_scrollAccel.x += m_scrollStep;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_scrollAccel.y += m_scrollStep;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_scrollAccel.y -= m_scrollStep;
    }
}

