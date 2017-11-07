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


#include "GuiManager.hpp"
#include "UserInputManagerInSpace.hpp"
#include <core/slot/ItemSlot.hpp>
#include <core/dock/Kosmoport.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <world/Sector.hpp>
#include <world/starsystem.hpp>

//#include <ceti/StringUtils.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Render.hpp>
#include <core/part/WeaponComplex.hpp>
#include <item/Item.hpp>

#include <core/pilot/Npc.hpp>
#include <client/pilot/Player.hpp>

#include <core/spaceobject/Vehicle.hpp>

#include <client/session/Shortcuts.hpp>
#include <client/gui/GuiSkills.hpp>
#include <client/gui/GuiGalaxyMap.hpp>

#include <ceti/Logger.hpp>

namespace gui {

Manager& Manager::get()
{
    static Manager instance;
    return instance;
}

Manager::Manager()
{   
    int screen_w = client::shortcuts::screen()->width();
    int screen_h = client::shortcuts::screen()->height();
    
    /* shared gui */
    {
        m_vehicle = new Vehicle();

        glm::vec2 size(250, 250);    
        m_vehicle->setSize(size);
    
//        glm::vec2 offset(0, 0);
//        m_space.add(m_vehicle, offset);
    } 
    
    {
        m_galaxymap    = new GuiGalaxyMap();
        
        glm::vec2 offset(screen_w/2, screen_h/2);
        m_space.add(m_galaxymap, offset);
    }
    
    m_skills       = new GuiSkills();
    m_slider       = new Slider();
}

Manager::~Manager()
{
    //delete gui_vehicle_scan;
    delete m_skills;
    delete m_galaxymap;
    delete m_slider;
}
        
bool Manager::updateMouseInteractionWithScanVehicle(const MouseData& data_mouse)
{
    //bool interaction = gui_vehicle_scan->UpdateMouseInteraction(data_mouse);        
    //if ( (interaction == true) and (gui_vehicle_scan->GetAllowFullControl() == true) )
    //{
        //interaction = gui_skills->UpdateMouseInteraction(data_mouse.pos_screencoord);
        //gui_skills->ButtonsAction(gui_vehicle_scan->vehicle()->GetOwnerNpc()->GetSkills());
    //}

    //return interaction;
    return false;
}

void Manager::renderScanVehicle(const MouseData& data_mouse, bool show_skill) const
{    
    //if (player->GetCursor().GetItemSlot()->item() != nullptr)
    {
        //gui_vehicle_scan->RenderVehicle(data_mouse, player->GetCursor().GetItemSlot()->item()->GetParentSubTypeId());
        //player->GetCursor().GetItemSlot()->item()->Render(player->GetCursor().GetRect(), glm::vec2(0, 0));
    }
    //else
    {
        //gui_vehicle_scan->RenderVehicle(data_mouse);
    }
                    
    //if ( (show_skill == true) and (gui_vehicle_scan->vehicle()->GetOwnerNpc() != nullptr) )
    {
        //gui_skills->RenderButtons();
        //gui_skills->RenderSkills(gui_vehicle_scan->vehicle()->GetOwnerNpc()->GetSkills());
        //gui_skills->RenderFocusedButtonInfo(data_mouse);
    }                                        
}

void Manager::enterKosmoport()
{
    //gui_kosmoport.BindKosmoport((Kosmoport*)player->GetNpc()->vehicle()->GetLand());
    //gui_kosmoport.BindSharedGuis(gui_galaxymap, gui_vehicle_scan, gui_skills, slider);
}
        
void Manager::quitKosmoport()
{    
    //gui_kosmoport.UnbindKosmoport();
    //gui_kosmoport.UnbindSharedGuis();
}

void Manager::enterSpace()
{
    //gui_space.BindSharedGuis(gui_galaxymap, gui_vehicle_scan, gui_skills, slider);
}

void Manager::quitSpace()
{
    //gui_space.UnbindSharedGuis();
}

void Manager::enterScan(client::Player* player)
{
    Logger::get().log("gui::Manager enterScan", Logger::Code::GUI);
    VehicleSimple* gui_player_vehicle = static_cast<VehicleSimple*>(element(Type::PLAYER_VEHICLE));
    gui::Radar* gui_radar = static_cast<Radar*>(element(Type::GUI_RADAR));

    control::Vehicle* scan_target = player->npc()->scanTarget();
    assert(scan_target);
    if (m_vehicle->isActive()) {
        m_vehicle->unbindVehicle();
    }
    gui_player_vehicle->hide();
    gui_radar->hide();

    m_vehicle->bindVehicle(scan_target, /*offset=*/glm::vec2(0, 0), /*full_control_on*/true);
    m_vehicle->show();
}

void Manager::exitScan(client::Player* player)
{
    Logger::get().log("gui::Manager exitScan", Logger::Code::GUI);
    VehicleSimple* gui_player_vehicle = static_cast<VehicleSimple*>(element(Type::PLAYER_VEHICLE));
    gui::Radar* gui_radar = static_cast<Radar*>(element(Type::GUI_RADAR));

    m_vehicle->unbindVehicle();
    m_vehicle->hide();

    gui_player_vehicle->show();
    gui_radar->show();
}

void Manager::update(client::Player* player)
{
    switch(player->place()) {
    case place::Type::SPACE: __updateInSpace(player);

    }
}

void Manager::render(jeti::Render& render, client::Player* player)
{
    render.applyOrthogonalProjectionForHUD();
    switch(player->place()) {
    case place::Type::SPACE: __renderInSpace(render, player);

    }
}

void Manager::__updateInSpace(client::Player* player)
{
    VehicleSimple* gui_player_vehicle = static_cast<VehicleSimple*>(element(Type::PLAYER_VEHICLE));
    gui::Radar* gui_radar = static_cast<Radar*>(element(Type::GUI_RADAR));
    GuiGalaxyMap* gui_galaxymap = (GuiGalaxyMap*)element(Type::GALAXYMAP);

    assert(gui_player_vehicle);
    assert(gui_radar);
    assert(gui_galaxymap);

    Base* button = element(Type::BUTTON_GALAXYMAP);
    if (button->isPressed()) {
        //player->GetNpc()->ResetScanTarget();

        gui_radar->hide();
        gui_player_vehicle->hide();

        gui_galaxymap->show();
        //gui_galaxymap->BindGalaxy(player->GetNpc()->starsystem()->GetSector()->GetGalaxy());
    } else {
        gui_galaxymap->UnbindGalaxy();
        gui_galaxymap->hide();
    }

    if (m_vehicle->isActive()) {
        m_vehicle->update(player);
        m_vehicle->updateMouseInteraction(player);
    }
    //m_space.show();
}

void Manager::__renderInSpace(jeti::Render& render, client::Player* player)
{
    VehicleSimple* gui_player_vehicle = static_cast<VehicleSimple*>(element(Type::PLAYER_VEHICLE));
    gui::Radar* gui_radar = static_cast<Radar*>(element(Type::GUI_RADAR));
    GuiGalaxyMap* gui_galaxymap = (GuiGalaxyMap*)element(Type::GALAXYMAP);

    assert(gui_player_vehicle);
    assert(gui_radar);
    assert(gui_galaxymap);

    if (m_vehicle->isActive()) {
        m_vehicle->render(render, player);
    }

    //m_space.render(render, player);
    //gui_space.RenderInfo(data_mouse);
}

//void Manager::runSessionInSpace(jeti::Render& render, client::Player* player)
//{
////    VehicleSimple* gui_player_vehicle = static_cast<VehicleSimple*>(element(Type::PLAYER_VEHICLE));
////    gui::Radar* gui_radar = static_cast<Radar*>(element(Type::GUI_RADAR));
////    GuiGalaxyMap* gui_galaxymap = (GuiGalaxyMap*)element(Type::GALAXYMAP);

////    assert(m_vehicle);
////    assert(gui_player_vehicle);
////    assert(gui_radar);
////    assert(gui_galaxymap);

////    Base* button = element(Type::BUTTON_GALAXYMAP);
////    if (button->isPressed()) {
////        //player->GetNpc()->ResetScanTarget();

////        gui_radar->hide();
////        gui_player_vehicle->hide();
        
////        gui_galaxymap->show();
////        //gui_galaxymap->BindGalaxy(player->GetNpc()->starsystem()->GetSector()->GetGalaxy());
////    } else {
////        gui_galaxymap->UnbindGalaxy();
////        gui_galaxymap->hide();
////    }

////    render.applyOrthogonalProjectionForHUD();

////    if (m_vehicle->isActive()) {
////        m_vehicle->update(player);
////        m_vehicle->updateMouseInteraction(player);
////        m_vehicle->render(render, player);
////    }
////    //m_space.show();
////    //m_space.update(player);

////    //m_space.render(render, player);
////    //gui_space.RenderInfo(data_mouse);
//}

void Manager::runSessionInKosmoport(const MouseData& data_mouse)
{
    m_kosmoport.update(data_mouse);
    m_kosmoport.render(data_mouse);
}

void Manager::runSessionInNatureLand(const MouseData& data_mouse)
{   
    /*     
    Rect screen_rect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());   
    glm::vec2 center_screen(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2);                   
                    
     //UserInputManager::Instance().UpdateInKosmoport(player);
    //player->GetCursor().Update(); 
                            
    //bool interaction = gui_kosmoport.UpdateMouseInteractionWithButtons(data_mouse);
    //gui_kosmoport.ButtonsAction();
    
                                    
    NatureLand* natureland = (NatureLand*)player->GetNpc()->vehicle()->GetLand();
    gui_natureland.BindNatureLand(natureland);

    //update  
    bool interaction = gui_natureland.UpdateMouseInteraction(data_mouse.pos_screencoord);
    if (interaction == false)
    {
        interaction = gui_natureland.UpdateMouseInteractionWithEquipedItemSlots(data_mouse);
    }
    gui_natureland.ButtonsAction();
    
    //render
    resetRenderTransformation();
    gui_natureland.RenderBackground(screen_rect);
    enable_BLEND();
    {   
        gui_natureland.RenderEquipedItemSlots();
        //gui_natureland.RenderButtons();
        //gui_natureland.RenderFocusedButtonInfo(data_mouse); 
    }
    disable_BLEND(); 
    */
}


void Manager::pressEventMBL_onGuiElement(Type group)
{
    m_space._pressEventMBL_onGuiElement(group, m_player);
}    

void Manager::resetEventOnGuiElement(Type group)
{
    m_space._resetStateEventOnGuiElement(group);
}    

Base* Manager::element(Type id) const
{
    return m_space.element(id);
}
        
} // namespace gui
