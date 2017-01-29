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

#include "GuiKosmoport.hpp"
#include "ButtonSingle.hpp"
#include "UserInput.hpp"

#include <client/resources/GuiTextureObCollector.hpp>
#include <jeti/Screen.hpp>

#include <common/constants.hpp>
#include <client/common/global.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <client/pilots/Player.hpp>
#include <pilots/Npc.hpp>

#include <spaceobjects/Vehicle.hpp>
#include <world/starsystem.hpp>
#include <world/Sector.hpp>

#include <dock/Kosmoport.hpp>
#include <slots/ItemSlot.hpp>
#include <item/BaseItem.hpp>

#include <jeti/Render.hpp>

#include <dock/Angar.hpp>
#include <dock/Goverment.hpp>

#include <client/gui/GuiManager.hpp>
#include <client/gui/GuiVehicle.hpp>
#include <client/gui/GuiSkills.hpp>
#include <client/gui/GuiGalaxyMap.hpp>
#include <client/gui/Slider.hpp>

GuiKosmoport::GuiKosmoport():
init_done(false), 
kosmoport(nullptr),
gui_galaxymap_shared(nullptr),
gui_vehicle_scan_shared(nullptr),
gui_skills_shared(nullptr),
slider_shared(nullptr)
{
    //int screen_w = Screen::Instance().GetWidth();
    //int screen_h = Screen::Instance().GetHeight();
    
    //TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake
    
    //float zpos = -1;
    //float zsize = 1;
    
    {
        //ButtonSingle* angar_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::ANGAR_ID, "angar"); 
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);   
        //Box box(center, size);        
        //angar_screen_button->SetBox(box);                         
        //button_map.insert(std::make_pair(GUI::BUTTON::ANGAR_ID, angar_screen_button));
    }
    
    {
        //ButtonSingle* store_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::STORE_ID, "store");
        //glm::vec3 center(screen_w - 2 * (GUI::ICON_SIZE + 5), GUI::ICON_SIZE, zpos); 
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);    
        //Box box(center, size);        
        //store_screen_button->SetBox(box);         
        //button_map.insert(std::make_pair(GUI::BUTTON::STORE_ID, store_screen_button));
    }
        
    {                        
        //ButtonSingle* shop_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::SHOP_ID, "shop");
        //glm::vec3 center(screen_w - 3 * (GUI::ICON_SIZE + 5), GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //shop_screen_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::SHOP_ID, shop_screen_button));
    }
    
    {                     
        //ButtonSingle* galaxymap_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GALAXYMAP_ID, "galaxymap");
        //glm::vec3 center(screen_w - 4 * (GUI::ICON_SIZE + 5), GUI::ICON_SIZE, zpos); 
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //galaxymap_screen_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::GALAXYMAP_ID, galaxymap_screen_button));
    }
    
    {                     
        //ButtonSingle* goverment_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GOVERMENT_ID, "goverment");
        //glm::vec3 center(screen_w - 5 * (GUI::ICON_SIZE + 5), GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //goverment_screen_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::GOVERMENT_ID, goverment_screen_button));
    }
}


GuiKosmoport::~GuiKosmoport()
{}
    
void GuiKosmoport::SetPlayer(Player* player)
{    
    SetPlayer(player);
    
    //gui_angar.SetPlayer(player);
    //gui_store.SetPlayer(player);
}    

void GuiKosmoport::BindKosmoport(Kosmoport* kosmoport)
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::BindKosmoport", GUI_LOG_DIP);
    #endif    
    
        this->kosmoport = kosmoport;     
                
    gui_angar.BindAngar(kosmoport->GetAngar());
        gui_store.bindStore(kosmoport->GetStore());
        gui_shop.BindShop(kosmoport->GetShop()); 
        gui_goverment.BindGoverment(kosmoport->GetGoverment());
        
        EnterGuiAngarScreen();
        
        init_done     = true;
}

void GuiKosmoport::UnbindKosmoport()
{
        ExitCurrentScreen();
        
        kosmoport = nullptr;
        
        gui_angar.UnbindAngar();
        gui_store.UnbindStore();
        gui_shop.UnbindShop();
        gui_goverment.UnbindGoverment();
        
        init_done = false;
}


void GuiKosmoport::BindSharedGuis(GuiGalaxyMap* gui_galaxymap_shared, GuiVehicle* gui_vehicle_scan_shared, GuiSkills* gui_skills_shared, Slider* slider_shared)
{
        this->gui_galaxymap_shared    = gui_galaxymap_shared;
        this->gui_vehicle_scan_shared = gui_vehicle_scan_shared;
        this->gui_skills_shared       = gui_skills_shared;
        this->slider_shared           = slider_shared;
}

void GuiKosmoport::UnbindSharedGuis()
{
        gui_galaxymap_shared    = nullptr;
        gui_vehicle_scan_shared = nullptr;
        gui_skills_shared       = nullptr;
        slider_shared           = nullptr;
}

void GuiKosmoport::EnterGuiScanInAngar()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiScanInAngar", GUI_LOG_DIP);
    #endif    

    int screen_w = client::global::get().screen().width();
    int screen_h = client::global::get().screen().height();
    glm::vec2 center_screen(screen_w/2, screen_h/2);
    
    //bool allow_full_control = m_Player->IsAbleToGetFullControlOnScanedVehicle();
    //gui_vehicle_scan_shared->BindVehicle(m_Player->GetNpc()->scanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET, allow_full_control);
    //gui_skills_shared->SetOffset(center_screen + GUI_SKILLS_INSPACE_OFFSET);
}

void GuiKosmoport::ExitGuiScan()
{       
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiScan", GUI_LOG_DIP);
    #endif    
    
        //if (gui_vehicle_scan_shared->vehicle() == m_Player->GetNpc()->vehicle())
           //{
                //gui_skills_shared->Acknowledge();
           //}
        //gui_vehicle_scan_shared->UnbindVehicle();

        //m_Player->GetNpc()->ResetScanTarget();
}
               
void GuiKosmoport::EnterGuiAngarScreen()
{      
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiAngarScreen", GUI_LOG_DIP);
    #endif    
      
        active_screen_id = GUI::SCREEN::ANGAR_ID;
}

void GuiKosmoport::ExitGuiAngarScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiAngarScreen", GUI_LOG_DIP);
    #endif    
    
    if (gui_vehicle_scan_shared->vehicle() != nullptr)
    {
        ExitGuiScan();
    }
}


void GuiKosmoport::EnterGuiStoreScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiStoreScreen", GUI_LOG_DIP);
    #endif    
    
    int screen_w = client::global::get().screen().width();
    int screen_h = client::global::get().screen().height();
    glm::vec2 center_screen(screen_w/2, screen_h/2);
    
    //gui_store.SetOffset(center_screen + GUI_STORE_OFFSET);
    
    //m_Player->GetNpc()->SetScanTarget(m_Player->GetNpc()->vehicle()); //??
    //bool lock_gui_scan_vehicle = true;
    //gui_vehicle_scan_shared->BindVehicle(m_Player->GetNpc()->vehicle(), center_screen + GUI_VEHICLE_INSTORE_OFFSET, lock_gui_scan_vehicle);
    
    //active_screen_id = GUI::SCREEN::STORE_ID;
}

void GuiKosmoport::ExitGuiStoreScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiStoreScreen", GUI_LOG_DIP);
    #endif    
    
        ExitGuiScan();
}

void GuiKosmoport::EnterGuiShopScreen()
{     
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiShopScreen", GUI_LOG_DIP);
    #endif    
      
        active_screen_id = GUI::SCREEN::SHOP_ID;
}

void GuiKosmoport::ExitGuiShopScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiShopScreen", GUI_LOG_DIP);
    #endif    
}

void GuiKosmoport::EnterGuiGalaxyMapScreen()
{       
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiGalaxyMapScreen", GUI_LOG_DIP);
    #endif    
    
        //active_screen_id = GUI::SCREEN::GALAXYMAP_ID;        
        //gui_galaxymap_shared->BindGalaxy(m_Player->GetNpc()->vehicle()->starsystem()->GetSector()->GetGalaxy());
}

void GuiKosmoport::ExitGuiGalaxyMapScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiGalaxyMapScreen", GUI_LOG_DIP);
    #endif    
    
        gui_galaxymap_shared->UnbindGalaxy(); 
}

void GuiKosmoport::EnterGuiGovermentScreen()
{        
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::EnterGuiGovermentScreen", GUI_LOG_DIP);
    #endif
    
        active_screen_id = GUI::SCREEN::GOVERMENT_ID;
}

void GuiKosmoport::ExitGuiGovermentScreen()
{
    #if GUI_LOG_ENABLED == 1
    Logger::Instance().Log("GuiKosmoport::ExitGuiGovermentScreen", GUI_LOG_DIP);
    #endif
}    

void GuiKosmoport::ExitCurrentScreen()
{
    switch (active_screen_id)
    {
        case GUI::SCREEN::ANGAR_ID: { ExitGuiAngarScreen(); break; }
        case GUI::SCREEN::STORE_ID: { ExitGuiStoreScreen(); break; }
        case GUI::SCREEN::SHOP_ID:  { ExitGuiShopScreen(); break; }
        case GUI::SCREEN::GALAXYMAP_ID: { ExitGuiGalaxyMapScreen(); break; }
        case GUI::SCREEN::GOVERMENT_ID: { ExitGuiGovermentScreen(); break; }
    }
}


void GuiKosmoport::ButtonsAction()
{
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
        //BaseButton* button = iterator->second;
        //if (button->GetPressed() == true)
        //{
            //switch(button->subTypeId())
               //{
                   //case GUI::BUTTON::ANGAR_ID: 
                   //{
                             ////button->OnPressEventMBL(player);   
                                        ////ExitCurrentScreen();
                                        ////EnterGuiAngarScreen();
                                        
                       //return; break;
                   //}

                   //case GUI::BUTTON::STORE_ID: 
                   //{
                             ////button->OnPressEventMBL(player);
                                        ////ExitCurrentScreen();
                                        ////EnterGuiStoreScreen();
                                        
                       //return; break;
                   //}

                   //case GUI::BUTTON::SHOP_ID: 
                   //{
                             ////button->OnPressEventMBL(player);
                                        ////ExitCurrentScreen();
                                        ////EnterGuiShopScreen();
                                        
                       //return; break;
                   //}

                   //case GUI::BUTTON::GALAXYMAP_ID: 
                   //{
                             ////button->OnPressEventMBL(player);
                                        ////ExitCurrentScreen();                                                                                
                                        ////EnterGuiGalaxyMapScreen();
                                        
                       //return; break;
                   //}

                   //case GUI::BUTTON::GOVERMENT_ID: 
                   //{
                             ////button->OnPressEventMBL(player);
                                        ////ExitCurrentScreen();
                                        ////EnterGuiGovermentScreen();
                                        
                       //return; break;
                   //}
               //}
           //}
      //}
}


bool GuiKosmoport::Update(const MouseData& data_mouse)
{    bool interaction = false;
    /*
     UserInput::Instance().UpdateInKosmoport(m_Player);
    m_Player->GetCursor().Update(); 
                            
    bool interaction = UpdateMouseInteraction(data_mouse.pos_screencoord);
    ButtonsAction();

    switch(active_screen_id)
    {
        case GUI::SCREEN::ANGAR_ID:
        {
            gui_angar.CheckButtonsLock();
            if (interaction == false)
            {                    
                interaction = gui_angar.UpdateMouseInteraction(data_mouse.pos_screencoord);
                if (interaction == false)
                {
                    interaction = gui_angar.UpdateMouseInteractionWithVehicleSlots(data_mouse);
                }

                gui_angar.ButtonsAction();
                    if (interaction == false)
                    {
                    if (gui_vehicle_scan_shared->vehicle() != nullptr)
                    { 
                        interaction = GuiManager::Instance().UpdateMouseInteractionWithScanVehicle(data_mouse);
                    }
                    } 
                }

            break;
        }

        case GUI::SCREEN::STORE_ID:
        {
            if (interaction == false)
            {
                interaction = gui_store.UpdateMouseInteraction(data_mouse);
                    if (interaction == false)
                    {
                        //interaction = gui_vehicle_scan_shared->UpdateMouseInteractionInStore(data_mouse, gui_store.GetStore());
                    }
            }

            break;
        }

        case GUI::SCREEN::SHOP_ID:
        {
            gui_shop.UpdateLables();
            gui_shop.ButtonsAction(*slider_shared);
            if (slider_shared->subTypeId() != GUI::TYPE::NONE_ID)
            {
                slider_shared->CheckButtonsLock();
                slider_shared->ButtonsAction(gui_shop.GetShop());
            }
            
            if (interaction == false)
            {
                interaction = gui_shop.UpdateMouseInteraction(data_mouse.pos_screencoord);
                if (interaction == false)
                {
                    if (slider_shared->subTypeId() != GUI::TYPE::NONE_ID)
                    {
                        slider_shared->UpdateSlidePosition(data_mouse);
                        interaction = slider_shared->UpdateMouseInteraction(data_mouse.pos_screencoord);
                    }
                }
                }

            break;
        }

        case GUI::SCREEN::GALAXYMAP_ID:
        {
            //update
            if ( interaction == false)
            {
                interaction = gui_galaxymap_shared->UpdateMouseInteraction(data_mouse);
                }                       

            break;
        }

        case GUI::SCREEN::GOVERMENT_ID:
        {
            //update
            if (interaction == false)
            {
                //interaction = gui_goverment.UpdateMouseInteraction(data_mouse);
                }

            break;
        }
    }
    */
    return interaction;
}

void GuiKosmoport::Render(const MouseData& data_mouse)
{        /*
    Rect screen_rect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());   
    glm::vec2 center_screen(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2);

    switch(active_screen_id)
    {
        case GUI::SCREEN::ANGAR_ID:
        {
            resetRenderTransformation();
            gui_angar.GetAngar()->RenderBackground(screen_rect);
            enable_BLEND();   
                    gui_angar.RenderVehicleAndItemSlots();
                    
                if (gui_vehicle_scan_shared->vehicle() != nullptr)
                { 
                    GuiManager::Instance().RenderScanVehicle(data_mouse, gui_vehicle_scan_shared); 
                }
                
                //Render(); 
                gui_angar.Render();
                //RenderInfo(data_mouse); 
                gui_angar.RenderInfo(data_mouse); 
            disable_BLEND(); 
        
            break;
        }

        case GUI::SCREEN::STORE_ID:
        {
            resetRenderTransformation();
            gui_store.GetStore()->RenderBackground(screen_rect);

            enable_BLEND();
                gui_store.RenderSlots(player->GetNpc()->GetCredits());

                bool show_skill = false;
                GuiManager::Instance().RenderScanVehicle(data_mouse, show_skill);
                
                Render(); 
                RenderChildInfo(data_mouse); 
            disable_BLEND();
            Screen::Instance().DrawText("credits:"+std::to_string(player->GetNpc()->GetCredits()), 12, glm::vec2(600, 200));

            break;
        }

        case GUI::SCREEN::SHOP_ID:
        {
            resetRenderTransformation();
            gui_shop.GetShop()->RenderBackground(screen_rect);
            enable_BLEND();   
                //gui_shop.RenderButtons();
                
                if (slider_shared->subTypeId() != NONE_ID)
                {
                    slider_shared->Render();
                }
                
                //RenderButtons(); 
                //RenderFocusedButtonInfo(data_mouse); 
                    
            disable_BLEND();  
            
            break;
        }

        case GUI::SCREEN::GALAXYMAP_ID:
        {
            clearScreen(); //becase there is no background
                resetRenderTransformation();
            enable_BLEND();   
                gui_galaxymap_shared->Render();
                
                //RenderButtons(); 
                //RenderFocusedButtonInfo(data_mouse); 
                    
            disable_BLEND();    

            break;
        }

        case GUI::SCREEN::GOVERMENT_ID:
        {
                resetRenderTransformation();
            gui_goverment.GetGoverment()->RenderBackground(screen_rect);
            enable_BLEND();   
                //gui_goverment->RenderInternals(goverment);
                
                //RenderButtons(); 
                //RenderFocusedButtonInfo(data_mouse); 
                    
            disable_BLEND(); 

            break;
        }
    }*/
}
                
