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
#include "../slots/ItemSlot.hpp"
#include "../dock/Kosmoport.hpp"

#include <world/Sector.hpp>
#include "../world/starsystem.hpp"

#include "../common/myStr.hpp"
#include "../render/Screen.hpp"
#include "../render/Render.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../items/BaseItem.hpp"

#include "../pilots/Npc.hpp"
#include "../pilots/Player.hpp"

#include "../spaceobjects/Vehicle.hpp"

#include "../gui/GuiSkills.hpp"
#include "../gui/GuiGalaxyMap.hpp"


GuiManager& GuiManager::Instance()
{
    static GuiManager instance;
    return instance;
}

GuiManager::GuiManager()
:
player(nullptr),
gui_vehicle_scan(nullptr)
{   
    int screen_w = Screen::Instance().GetWidth();
    int screen_h = Screen::Instance().GetHeight();
    
    /* shared gui */
    {
        gui_vehicle_scan = new GuiVehicle();

        glm::vec2 size(250, 250);    
        gui_vehicle_scan->SetSize(size);
    
        glm::vec2 offset(screen_w/2, screen_h/2);
        gui_space.AddChild(gui_vehicle_scan, offset);    
    } 
    
    {
        gui_galaxymap    = new GuiGalaxyMap();
        
        glm::vec2 offset(screen_w/2, screen_h/2);
        gui_space.AddChild(gui_galaxymap, offset);
    }
    
    gui_skills       = new GuiSkills();
    slider           = new Slider();  
}

GuiManager::~GuiManager()
{
    //delete gui_vehicle_scan;
    delete gui_skills;
    delete gui_galaxymap;
    delete slider;  
}
        
void GuiManager::SetPlayer(Player* player)
{    
    this->player = player;
}

bool GuiManager::UpdateMouseInteractionWithScanVehicle(const MouseData& data_mouse)
{
    //bool interaction = gui_vehicle_scan->UpdateMouseInteraction(data_mouse);        
    //if ( (interaction == true) and (gui_vehicle_scan->GetAllowFullControl() == true) )
    //{
        //interaction = gui_skills->UpdateMouseInteraction(data_mouse.pos_screencoord);
        //gui_skills->ButtonsAction(gui_vehicle_scan->GetVehicle()->GetOwnerNpc()->GetSkills());
    //}

    //return interaction;
    return false;
}

void GuiManager::RenderScanVehicle(const MouseData& data_mouse, bool show_skill) const
{    
    //if (player->GetCursor().GetItemSlot()->GetItem() != nullptr)
    {
        //gui_vehicle_scan->RenderVehicle(data_mouse, player->GetCursor().GetItemSlot()->GetItem()->GetParentSubTypeId());
        //player->GetCursor().GetItemSlot()->GetItem()->Render(player->GetCursor().GetRect(), glm::vec2(0, 0));        
    }
    //else
    {
        //gui_vehicle_scan->RenderVehicle(data_mouse);
    }
                    
    //if ( (show_skill == true) and (gui_vehicle_scan->GetVehicle()->GetOwnerNpc() != nullptr) )
    {
        //gui_skills->RenderButtons();
        //gui_skills->RenderSkills(gui_vehicle_scan->GetVehicle()->GetOwnerNpc()->GetSkills());
        //gui_skills->RenderFocusedButtonInfo(data_mouse);
    }                                        
}

void GuiManager::EnterGuiKosmoport()
{
    //gui_kosmoport.BindKosmoport((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand());
    //gui_kosmoport.BindSharedGuis(gui_galaxymap, gui_vehicle_scan, gui_skills, slider);
}
        
void GuiManager::ExitGuiKosmoport()
{    
    //gui_kosmoport.UnbindKosmoport();
    //gui_kosmoport.UnbindSharedGuis();
}

void GuiManager::EnterGuiSpace()
{
    //gui_space.BindSharedGuis(gui_galaxymap, gui_vehicle_scan, gui_skills, slider);
}

void GuiManager::ExitGuiSpace()
{
    //gui_space.UnbindSharedGuis();
}
             
void GuiManager::UpdateSessionInSpace()
{
    GuiVehicle* gui_scan_vehicle     = (GuiVehicle*)GetGuiElement(TYPE::GUI::SCAN_VEHICLE_ID);     
    GuiVehicle2* gui_player_vehicle = (GuiVehicle2*)GetGuiElement(TYPE::GUI::PLAYER_VEHICLE_ID);
    GuiRadar* gui_radar             = (GuiRadar*)GetGuiElement(TYPE::GUI::GUI_RADAR_ID);
    GuiGalaxyMap* gui_galaxymap     = (GuiGalaxyMap*)GetGuiElement(TYPE::GUI::GALAXYMAP_ID);

    assert(gui_scan_vehicle);
    assert(gui_player_vehicle);
    assert(gui_radar);
    assert(gui_galaxymap);
                
    const BaseSpaceEntity* scan_target = player->GetNpc()->GetScanTarget();    
      
    if (scan_target != nullptr)
    {       
        if (gui_scan_vehicle->GetVehicle() == nullptr)
        {               
            if (scan_target->GetTypeId() == TYPE::ENTITY::VEHICLE_ID)
            {
                gui_scan_vehicle->BindVehicle((Vehicle*)scan_target, /*offset=*/glm::vec2(0, 0), /*full_control_on*/true);
                gui_scan_vehicle->Show();  
                
                gui_player_vehicle->Hide(); 
                gui_radar->Hide();                       
            }
        }
    }
    else
    {
        gui_scan_vehicle->UnbindVehicle();
        gui_scan_vehicle->Hide();
        
        gui_player_vehicle->Show(); 
        gui_radar->Show();        
    }

    BaseGuiElement* button = GetGuiElement(TYPE::GUI::BUTTON_GALAXYMAP_ID);
    if (button->GetPressed())
    {
        player->GetNpc()->ResetScanTarget();

        gui_radar->Hide(); 
        gui_player_vehicle->Hide(); 
        
        gui_galaxymap->Show();
        gui_galaxymap->BindGalaxy(player->GetNpc()->GetStarSystem()->GetSector()->GetGalaxy());
    }
    else
    {
        gui_galaxymap->UnbindGalaxy();
        gui_galaxymap->Hide();
    }

    //gui_space.Update(data_mouse);
    //gui_space.Render();
    //gui_space.RenderInfo(data_mouse);
}

void GuiManager::RunSessionInKosmoport(const MouseData& data_mouse)
{
    gui_kosmoport.Update(data_mouse);
    gui_kosmoport.Render(data_mouse);
}

void GuiManager::RunSessionInNatureLand(const MouseData& data_mouse)
{   
    /*     
    Rect screen_rect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());   
    glm::vec2 center_screen(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2);                   
                    
     //UserInputManager::Instance().UpdateInKosmoport(player);
    //player->GetCursor().Update(); 
                            
    //bool interaction = gui_kosmoport.UpdateMouseInteractionWithButtons(data_mouse);
    //gui_kosmoport.ButtonsAction();
    
                                    
    NatureLand* natureland = (NatureLand*)player->GetNpc()->GetVehicle()->GetLand();
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


void GuiManager::PressEventMBL_onGuiElement(TYPE::GUI subtype_id)
{
    gui_space.PressEventMBL_onGuiElement(subtype_id, player); 
}    

void GuiManager::ResetEventOnGuiElement(TYPE::GUI subtype_id)
{
    gui_space.ResetStateEventOnGuiElement(subtype_id);
}    

BaseGuiElement* GuiManager::GetGuiElement(TYPE::GUI request_subtype_id) const
{
    return gui_space.GetGuiElement(request_subtype_id);
}
        
