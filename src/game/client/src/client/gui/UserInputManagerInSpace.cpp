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
#include <common/Global.hpp>
#include <common/Config.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>

#include <core/part/WeaponComplex.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <client/pilot/Player.hpp>
#include <client/gui/GuiManager.hpp>
#include <client/session/Shortcuts.hpp>

namespace gui {

UserInputInSpace::UserInputInSpace()
    :
      m_nextTurnReady(false)
{
    m_scrollStep = core::global::get().config().SCROLL_VELOCITY_STEP;
}

UserInputInSpace::~UserInputInSpace()
{}

void UserInputInSpace::update(client::Player* player)
{
    __reset(player);

    UserInput::get().update();

    __manageInputsInSpace(player);
    __manageRealTimeInputsInSpace(player);
    __mouseButtonPressed(player);
}


void UserInputInSpace::__manageInputsInSpace(client::Player* player)
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
            
        case sf::Keyboard::Space: {
            player->endTurnEvent();
            break;
        }

            //DRIVE SLOT
        case sf::Keyboard::F: { Manager::get().pressEventMBL_onGuiElement(gui::type::DRIVE_SLOT_SELECTOR); break; }

            // WEAPON SLOTS
        case sf::Keyboard::Num1: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT1_SELECTOR); break; }
        case sf::Keyboard::Num2: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT2_SELECTOR); break; }
        case sf::Keyboard::Num3: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT3_SELECTOR); break; }
        case sf::Keyboard::Num4: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT4_SELECTOR); break; }
        case sf::Keyboard::Num5: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT5_SELECTOR); break; }
        case sf::Keyboard::Num6: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT6_SELECTOR); break; }
        case sf::Keyboard::Num7: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT7_SELECTOR); break; }
        case sf::Keyboard::Num8: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT8_SELECTOR); break; }
        case sf::Keyboard::Num9: { Manager::get().pressEventMBL_onGuiElement(gui::type::WEAPON_SLOT9_SELECTOR); break; }
            
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

        case sf::Keyboard::C: {
            client::shortcuts::camera()->setTargetPosition(player->position());
            break;
        }
        case sf::Keyboard::G: { Manager::get().pressEventMBL_onGuiElement(gui::type::GRAPPLE_SLOT_SELECTOR); break; }
            
        case sf::Keyboard::M: { Manager::get().pressEventMBL_onGuiElement(gui::type::GALAXYMAP); break; }
            
        case sf::Keyboard::R: // RADAR
        {
            //player->show().InverseRangeRadar();
            break;
        }

        case sf::Keyboard::O: // Orbits
        {
            //player->show().InverseAllOrbits();
            break;
        }

        case sf::Keyboard::P: // Path
        {
            //player->show().InverseAllPath();
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

        case sf::Keyboard::F5: { Manager::get().pressEventMBL_onGuiElement(gui::type::SAVE); break; }
            
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
            
        case sf::Keyboard::F9: { Manager::get().pressEventMBL_onGuiElement(gui::type::LOAD); break; }

        case sf::Keyboard::K: { client::shortcuts::render()->increaseScale(); break; }
        case sf::Keyboard::L: { client::shortcuts::render()->decreaseScale(); break; }

            //            case sf::Keyboard::X: { client::global::get().render().increaseLightPos(); break; }
            //            case sf::Keyboard::Z: { client::global::get().render().decreaseLightPos(); break; }

        case sf::Keyboard::X: { player->show().setAxis(true); break; }
        case sf::Keyboard::Z: { player->show().setAxis(false); break; }

        case sf::Keyboard::B: { player->show().setCollisionRadius(true); break; }
        case sf::Keyboard::N: { player->show().setCollisionRadius(false); break; }
        }
    }
}

void UserInputInSpace::__mouseButtonPressed(client::Player* player)
{
    for (const auto & key_code : UserInput::get().mousePressedCodes()) {
        switch (key_code) {
        case sf::Mouse::Left: { player->pressLeftMouseButtonEvent(); break; }
        case sf::Mouse::Right: { player->pressRightMouseButtonEvent(); break;
        }
        } // case
    }
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(client::shortcuts::screen()->window());
    m_mouseClickPos = glm::vec3(mouse_pos.x, client::shortcuts::render()->height() - mouse_pos.y, 0.0f);
}

void UserInputInSpace::__reset(client::Player* player)
{       
    player->cursor().mouseData().reset();
    m_nextTurnReady = false;
    m_scrollAccel = glm::vec3(0);
}

void UserInputInSpace::__manageRealTimeInputsInSpace(client::Player* player)
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

} // namespace gui

