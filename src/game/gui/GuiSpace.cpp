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
#include "UserInput.hpp"
#include "GuiActions.hpp"

#include "ButtonTrigger.hpp"
#include "ButtonSingle.hpp"

#include "GuiManager.hpp"

#include "GuiBar.hpp"

#include "../common/myStr.hpp"
#include "../common/constants.hpp"
#include "../common/GameDate.hpp"
#include "../common/Logger.hpp"

#include "../resources/GuiTextureObCollector.hpp"

#include "../render/Screen.hpp"
#include "../render/Render.hpp"

#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../world/starsystem.hpp"
#include "../world/Sector.hpp"

#include "../slots/ItemSlot.hpp"

#include "../spaceobjects/Vehicle.hpp"

GuiSpace::GuiSpace():
gui_galaxymap_shared(nullptr),
gui_vehicle_scan_shared(nullptr),
gui_skills_shared(nullptr),
slider_shared(nullptr),
init_done(false)
{   	
	int screen_w = Screen::Instance().GetWidth();
	int screen_h = Screen::Instance().GetHeight();
	
	{
		Vec2<float> size(screen_w, screen_h);
		SetSize(size);
		
		SetOffset(Vec2<float>(screen_w/2, screen_h/2));
	}
	
	/** Top bar */
	{
        TextureOb* textureOb_bar_top = GuiTextureObCollector::Instance().bar_top;	
        GuiBar* bar_top = new GuiBar(textureOb_bar_top);
    
        Vec2<float> size(screen_w, GUI::BAR_HEIGHT);
        bar_top->SetSize(size);

        Vec2<float> offset(0, screen_h/2-GUI::BAR_HEIGHT/2);
        AddChild(bar_top, offset);	

		{
			TextureOb* texOb = GuiTextureObCollector::Instance().icon_map;  
			ButtonTrigger* galaxymap_button = new ButtonTrigger(GUI::TYPE::GALAXYMAP_ID, "galaxy map", GuiActions::GalaxyMapGuiTransition, texOb);
			
            Vec2<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE); 	
			galaxymap_button->SetSize(size);		
            
			Vec3<float> offset(screen_w/2-1*1.1*GUI::ICON_SIZE, 0, 0);
			bar_top->AddChild(galaxymap_button, offset);
		}
		
		{
			TextureOb* texOb = GuiTextureObCollector::Instance().icon_plus;
			ButtonSingle* load_button = new ButtonSingle(GUI::TYPE::LOAD_ID, "load", GuiActions::LoadEvent, texOb);    
			
            Vec2<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE);	
			load_button->SetSize(size);
			
			Vec2<float> offset(screen_w/2-2*1.1*GUI::ICON_SIZE, 0);
			bar_top->AddChild(load_button, offset);				     
		}
		
		{
			TextureOb* texOb = GuiTextureObCollector::Instance().icon_minus;
			ButtonSingle* save_button = new ButtonSingle(GUI::TYPE::SAVE_ID, "save", GuiActions::SaveEvent, texOb);    

			Vec2<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE);	
			save_button->SetSize(size);	
			
			Vec2<float> offset(screen_w/2-3*1.1*GUI::ICON_SIZE, 0);				     
			bar_top->AddChild(save_button, offset);	
		}
	}
	/** */
	
	/** Bottom bar */
	{
		TextureOb* textureOb_bar_bottom = GuiTextureObCollector::Instance().bar_bottom;	
		GuiBar* bar_bottom = new GuiBar(textureOb_bar_bottom);

        Vec2<float> size(screen_w, GUI::BAR_HEIGHT);
        bar_bottom->SetSize(size);

        Vec2<float> offset(0, -screen_h/2+GUI::BAR_HEIGHT/2);
        AddChild(bar_bottom, offset);	
	}
		
	{
		GuiRadar* gui_radar = new GuiRadar();
		
        Vec2<float> size(250, 250);	
		gui_radar->SetSize(size);
	
        Vec2<float> offset(0, -screen_h/2+GUI::BAR_HEIGHT/2);
		AddChild(gui_radar, offset);	
	}
    
    {
		GuiVehicle2* gui_vehicle_player = new GuiVehicle2(GUI::TYPE::PLAYER_VEHICLE_ID);
		
        Vec2<float> size(250, 250);	
		gui_vehicle_player->SetSize(size);
    
        Vec2<float> offset(-screen_w/2+125, -screen_h/2+125);
		AddChild(gui_vehicle_player, offset);	
	}      

    {
		GuiVehicle* gui_scan = new GuiVehicle(GUI::TYPE::SCAN_VEHICLE_ID);

		Vec2<float> size(250, 250);	
		gui_scan->SetSize(size);
    
        Vec2<float> offset(screen_w/2, screen_h/2);
		AddChild(gui_scan, offset);	
	} 
}

/*virtual*/
GuiSpace::~GuiSpace()
{}

void GuiSpace::SetPlayer(Player* player)
{	
	m_Player = player;
        
	GetGuiElement(GUI::TYPE::GUI_RADAR_ID)->SetPlayer(player); 
}

void GuiSpace::BindSharedGuis(GuiGalaxyMap* gui_galaxymap_shared, GuiVehicle* gui_vehicle_scan_shared, GuiSkills* gui_skills_shared, Slider* slider_shared)
{
	this->gui_galaxymap_shared    = gui_galaxymap_shared;
	this->gui_vehicle_scan_shared = gui_vehicle_scan_shared;
	this->gui_skills_shared       = gui_skills_shared;
	this->slider_shared           = slider_shared;
	
	init_done = true;
}

void GuiSpace::UnbindSharedGuis()
{
	gui_galaxymap_shared    = nullptr;
	gui_vehicle_scan_shared = nullptr;
	gui_skills_shared       = nullptr;
	slider_shared           = nullptr;
	
	init_done = false;
}

bool GuiSpace::UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData& data_mouse)
{
    //ItemSlot* selected_item_slot = gui_vehicle_target.GetInreactedItemSlot(data_mouse);
	//if (selected_item_slot != nullptr)
	//{
		//if (selected_item_slot->GetItem() != nullptr)
		//{
			//player->GetNpc()->GetVehicle()->GetWeaponComplex().SetTarget(selected_item_slot->GetOwnerVehicle(), selected_item_slot);
			//gui_vehicle_target.Reset();
			//return true;
		//}
	//}

	//return false;
}

void GuiSpace::EnterGalaxyMap()
{        
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::EnterGalaxyMap", GUI_LOG_DIP);
	#endif
	
	if (gui_vehicle_scan_shared->GetVehicle() != nullptr)
	{
		ExitGuiScan();
	}
	
	GetGuiElement(GUI::TYPE::GUI_RADAR_ID)->Hide();
	      
	gui_galaxymap_shared->BindGalaxy(m_Player->GetNpc()->GetStarSystem()->GetSector()->GetGalaxy());
}

void GuiSpace::ExitGalaxyMap()
{
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::ExitGalaxyMap", GUI_LOG_DIP);
	#endif
	
	GetGuiElement(GUI::TYPE::GUI_RADAR_ID)->Show();    
	gui_galaxymap_shared->UnbindGalaxy();
}
    
void GuiSpace::EnterGuiScan()
{
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::EnterGuiScan", GUI_LOG_DIP);
	#endif
	
	//int screen_w = Screen::Instance().GetWidth();
	//int screen_h = Screen::Instance().GetHeight();
	//Vec2<float> center_screen(screen_w/2, screen_h/2);
	
	//bool allow_full_control = m_Player->IsAbleToGetFullControlOnScanedVehicle();
	//gui_vehicle_scan_shared->BindVehicle(m_Player->GetNpc()->GetScanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET, allow_full_control);
	//gui_skills_shared->SetOffset(center_screen + GUI_SKILLS_INSPACE_OFFSET);
			
    //GetGuiElement(GUI::TYPE::PLAYER_VEHICLE_ID)->Hide();		
	//GetGuiElement(GUI::TYPE::GUI_RADAR_ID)->Hide();
}

void GuiSpace::ExitGuiScan()
{       
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::ExitGuiScan", GUI_LOG_DIP);
	#endif
	
	//if (gui_vehicle_scan_shared->GetVehicle() == m_Player->GetNpc()->GetVehicle())
	//{
		//gui_skills_shared->Acknowledge();
	//}
	//gui_vehicle_scan_shared->UnbindVehicle();
	
	//m_Player->GetNpc()->ResetScanTarget();
	
	//GetGuiElement(GUI::TYPE::GUI_RADAR_ID)->Show();
    //GetGuiElement(GUI::TYPE::PLAYER_VEHICLE_ID)->Show();	
}

void GuiSpace::ButtonsAction(Player* player) const
{}

void GuiSpace::Resize(int screen_w, int screen_h)
{

}


void GuiSpace::RenderText(const Vec2<float>& scroll_coords) const
{
	const std::string _coord_str = "date:"+ GameDate::Instance().GetDate().GetStr()+" world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);
	Vec2<float> pos(Screen::Instance().GetWidth() - 400, Screen::Instance().GetHeight() - 5);

	Screen::Instance().DrawText(_coord_str, 12, pos);    
}

/*virtual override final*/
void GuiSpace::UpdateUnique(Player* player)
{ 
    int screen_w = Screen::Instance().GetWidth();
	int screen_h = Screen::Instance().GetHeight();
	Rect screen_rect(0, 0, screen_w, screen_h);   
	Vec2<float> center_screen(screen_w/2, screen_h/2);
    
    UserInput::Instance().UpdateInSpace(player);
	m_Player->GetCursor().Update(); 
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
			
	//if (gui_vehicle_scan_shared->GetVehicle() != nullptr)
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
void GuiSpace::RenderUnique(Player*) const
{
    //if (show_gui_radar == true)  
    //{
        //gui_radar->Render();
        //gui_vehicle_player.Render();
        //gui_vehicle_player.RenderInfo(data_mouse);    
    //}
    
    if (gui_galaxymap_shared->GetGalaxy() != nullptr)  
    {
        gui_galaxymap_shared->Render();    
    }
                                    
    //if (gui_vehicle_scan_shared->GetVehicle() != nullptr)
    //{
        //GuiManager::Instance().RenderScanVehicle(data_mouse, player->GetNpc()->GetScanTarget()); 				                 
    //}
    
    //if (gui_vehicle_target.GetVehicle() != nullptr)
    //{
        //gui_vehicle_target.Render();
        //gui_vehicle_target.RenderInfo(data_mouse); 
    //}

    //RenderChildInfo(data_mouse);
	
	RenderText(Screen::Instance().GetBottomLeftScreenWC());
}

