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


#include "GuiSpace.hpp"
#include "GuiGalaxyMap.hpp"
#include "GuiSkills.hpp"
#include "UserInputManagerInSpace.hpp"
#include "GuiActions.hpp"

#include "ButtonTrigger.hpp"
#include "ButtonSingle.hpp"

#include "GuiManager.hpp"

#include "GuiBar.hpp"

//#include <ceti/StringUtils.hpp>
#include <common/constants.hpp>
#include <common/GameDate.hpp>

#include <ceti/Logger.hpp>

#include <client/resources/GuiTextureObCollector.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Render.hpp>

#include <client/session/Shortcuts.hpp>
#include <client/pilot/Player.hpp>
#include <core/pilot/Npc.hpp>

#include <world/starsystem.hpp>
#include <world/Sector.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/spaceobject/Vehicle.hpp>

namespace gui {

Space::Space()
{       
    int screen_w = client::shortcuts::screen()->width();
    int screen_h = client::shortcuts::screen()->height();
    
    {
        glm::vec2 size(screen_w, screen_h);
        setSize(size);
    }
    
    /** Top bar */
    {
        GuiBar* bar_top = new GuiBar(MaterialCollector::get().bar_top);

        glm::vec2 size(screen_w, GUI::BAR_HEIGHT);
        bar_top->setSize(size);

        glm::vec2 offset(screen_w/2, screen_h-GUI::BAR_HEIGHT/2);
        add(bar_top, offset);

        {
            ButtonTrigger* galaxymap_button = new ButtonTrigger(gui::type::BUTTON_GALAXYMAP,
                                                                "galaxy map",
                                                                GuiActions::GalaxyMapGuiTransition,
                                                                MaterialCollector::get().icon_map);
            
            glm::vec2 size(GUI::ICON_SIZE, GUI::ICON_SIZE);
            galaxymap_button->setSize(size);
            
            glm::vec2 offset(screen_w/2-1*1.1*GUI::ICON_SIZE, 0);
            bar_top->add(galaxymap_button, offset);
        }
        
        {
            ButtonSingle* load_button = new ButtonSingle(gui::type::LOAD,
                                                         "load",
                                                         GuiActions::LoadEvent,
                                                         MaterialCollector::get().icon_plus);
            
            glm::vec2 size(GUI::ICON_SIZE, GUI::ICON_SIZE);
            load_button->setSize(size);
            
            glm::vec2 offset(screen_w/2-2*1.1*GUI::ICON_SIZE, 0);
            bar_top->add(load_button, offset);
        }
        
        {
            ButtonSingle* save_button = new ButtonSingle(gui::type::SAVE,
                                                         "save",
                                                         GuiActions::SaveEvent,
                                                         MaterialCollector::get().icon_minus);

            glm::vec2 size(GUI::ICON_SIZE, GUI::ICON_SIZE);
            save_button->setSize(size);
            
            glm::vec2 offset(screen_w/2-3*1.1*GUI::ICON_SIZE, 0);
            bar_top->add(save_button, offset);
        }
    }
    /** */
    
    /** Bottom bar */
    {
        GuiBar* bar_bottom = new GuiBar(MaterialCollector::get().bar_bottom);

        glm::vec2 size(screen_w, GUI::BAR_HEIGHT);
        bar_bottom->setSize(size);

        glm::vec2 offset(screen_w/2, GUI::BAR_HEIGHT/2);
        add(bar_bottom, offset);
    }

    {
        gui::Radar* gui_radar = new gui::Radar();
        
        glm::vec2 size(250, 250);
        gui_radar->setSize(size);

        glm::vec2 offset(0, -screen_h/2+GUI::BAR_HEIGHT/2);
        add(gui_radar, offset);
    }
    
    {
        GuiVehicle2* gui_vehicle_player = new GuiVehicle2();
        
        glm::vec2 size(250, 250);
        gui_vehicle_player->setSize(size);

        glm::vec2 offset(125, 125);
        add(gui_vehicle_player, offset);
    }
}

/* virtual */
Space::~Space()
{}

void Space::bindSharedGuis(GuiGalaxyMap* gui_galaxymap_shared, Vehicle* gui_vehicle_scan_shared, GuiSkills* gui_skills_shared, Slider* slider_shared)
{
    m_galaxymapShared = gui_galaxymap_shared;
    //this->gui_vehicle_scan_shared = gui_vehicle_scan_shared;
    m_skillsShared = gui_skills_shared;
    m_sliderShared = slider_shared;
    
    m_initialized = true;
}

void Space::unbindSharedGuis()
{
    m_galaxymapShared = nullptr;
    //gui_vehicle_scan_shared = nullptr;
    m_skillsShared = nullptr;
    m_sliderShared = nullptr;
    
    m_initialized = false;
}

bool Space::updateMouseInteractionWithPreciseWeaponTarget(const MouseData& data_mouse)
{
    //ItemSlot* selected_item_slot = gui_vehicle_target.GetInreactedItemSlot(data_mouse);
    //if (selected_item_slot != nullptr)
    //{
    //if (selected_item_slot->item() != nullptr)
    //{
    //player->GetNpc()->vehicle()->GetWeaponComplex().SetTarget(selected_item_slot->GetOwnerVehicle(), selected_item_slot);
    //gui_vehicle_target.Reset();
    //return true;
    //}
    //}

    return false;
}

void Space::enterGalaxyMap()
{        
#if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiSpace::EnterGalaxyMap", GUI_LOG_DIP);
#endif
    
    //if (gui_vehicle_scan_shared->vehicle() != nullptr)
    //{
    //ExitGuiScan();
    //}
    
    //GetGuiElement(gui::type::GUI_RADAR)->Hide();

    //gui_galaxymap_shared->BindGalaxy(GetPlayer()->GetNpc()->starsystem()->GetSector()->GetGalaxy());
}

void Space::exitGalaxyMap()
{
#if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiSpace::ExitGalaxyMap", GUI_LOG_DIP);
#endif
    
    //GetGuiElement(gui::type::GUI_RADAR)->Show();
    //gui_galaxymap_shared->UnbindGalaxy();
}

void Space::enterGuiScan()
{
#if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiSpace::EnterGuiScan", GUI_LOG_DIP);
#endif
    
    //int screen_w = Screen::Instance().GetWidth();
    //int screen_h = Screen::Instance().GetHeight();
    //glm::vec2 center_screen(screen_w/2, screen_h/2);
    
    //bool allow_full_control = m_Player->IsAbleToGetFullControlOnScanedVehicle();
    //gui_vehicle_scan_shared->BindVehicle(m_Player->GetNpc()->scanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET, allow_full_control);
    //gui_skills_shared->SetOffset(center_screen + GUI_SKILLS_INSPACE_OFFSET);

    //GetGuiElement(gui::type::PLAYER_VEHICLE)->Hide();
    //GetGuiElement(gui::type::GUI_RADAR)->Hide();
}

void Space::exitGuiScan()
{       
#if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiSpace::ExitGuiScan", GUI_LOG_DIP);
#endif
    
    //if (gui_vehicle_scan_shared->vehicle() == m_Player->GetNpc()->vehicle())
    //{
    //gui_skills_shared->Acknowledge();
    //}
    //gui_vehicle_scan_shared->UnbindVehicle();
    
    //m_Player->GetNpc()->ResetScanTarget();
    
    //GetGuiElement(gui::type::GUI_RADAR)->Show();
    //GetGuiElement(gui::type::PLAYER_VEHICLE)->Show();
}

void Space::buttonsAction(client::Player* player) const
{}

void Space::resize(int screen_w, int screen_h)
{

}


void Space::renderText(const glm::vec2& scroll_coords) const
{
    //    const std::string _coord_str = "date:"+ GameDate::Instance().GetDate().GetStr()+" world coord: " + std::to_string(scroll_coords.x) + "," + std::to_string(scroll_coords.y);
    //    glm::vec2 pos(client::shortcuts::screen()->GetWidth() - 400, client::shortcuts::screen()->GetHeight() - 5);

    //    client::shortcuts::screen()->DrawText(_coord_str, 12, pos);
}

/* virtual override final */
void Space::_updateUnique(client::Player* player)
{ 
    int screen_w = client::shortcuts::screen()->width();
    int screen_h = client::shortcuts::screen()->height();
    ceti::Rect screen_rect(0, 0, screen_w, screen_h);
    glm::vec2 center_screen(screen_w/2, screen_h/2);
}

//BaseGuiElement* GuiSpace::CheckInteraction(const MouseData& data_mouse)
//{
//if (gui_vehicle_target.GetVehicle() != nullptr)
//{
//gui_vehicle_target.UpdateOffset();
//}

//update
//BaseGuiElement* gui_element = nullptr;
//gui_element = UpdateMouseInteraction(data_mouse.pos_screencoord);

//ButtonsAction(player);

//if (gui_galaxymap_shared->GetGalaxy() != nullptr)
//{
//if (gui_element == nullptr)
//{
//gui_element = gui_galaxymap_shared->UpdateMouseInteraction(data_mouse);
//}
//}

//if (gui_vehicle_scan_shared->vehicle() != nullptr)
//{
//if (gui_element == nullptr)
//{
//gui_element = GuiManager::Instance().UpdateMouseInteractionWithScanVehicle(data_mouse);
//}
//}


//gui_radar.Update();
//if (gui_element == nullptr)
//{
//gui_element = gui_radar.UpdateMouseInteraction(data_mouse);
//}
//}

//if (gui_vehicle_target.GetVehicle() != nullptr)
//{
//if (gui_element == nullptr)
//{
//gui_element = UpdateMouseInteractionWithPreciseWeaponTarget(data_mouse);
//}
//}

//return gui_element;
//}

/* virtual final */
void Space::_renderUnique(const jeti::Render&, client::Player* player) const
{
    //if (show_gui_radar == true)
    //{
    //gui_radar->Render();
    //gui_vehicle_player.Render();
    //gui_vehicle_player.RenderInfo(data_mouse);
    //}
    
    //if (gui_galaxymap_shared->GetGalaxy() != nullptr)
    {
        //gui_galaxymap_shared->Render(player);
    }

    //if (gui_vehicle_scan_shared->vehicle() != nullptr)
    //{
    //GuiManager::Instance().RenderScanVehicle(data_mouse, player->GetNpc()->scanTarget());
    //}
    
    //if (gui_vehicle_target.GetVehicle() != nullptr)
    //{
    //gui_vehicle_target.Render();
    //gui_vehicle_target.RenderInfo(data_mouse);
    //}

    //RenderChildInfo(data_mouse);
    
    //RenderText(client::shortcuts::screen()->bottomLeftScreenWC());
}

} // namespace gui
