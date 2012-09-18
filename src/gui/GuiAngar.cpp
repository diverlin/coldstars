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

#include "GuiAngar.hpp"
#include "ButtonSingle.hpp"
#include "../config/config.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"

GuiAngar::GuiAngar()
{	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
        TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake

    	ButtonSingle* repair_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYARMOR_ID, "buy_repair");
        repair_button->SetRect(Rect(screen_w - 1 * (GUI::ICON_SIZE + 5),
    				    screen_h - 2 * GUI::ICON_SIZE, 
    				    GUI::ICON_SIZE,  
    				    GUI::ICON_SIZE));
    	button_map.insert(std::make_pair(GUI::BUTTON::BUYARMOR_ID, repair_button));
    				   
    	ButtonSingle* fuel_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYFUEL_ID, "buy fuel");  
        fuel_button->SetRect(Rect(screen_w - 1 * (GUI::ICON_SIZE + 5),
    	 			  screen_h - 3*GUI::ICON_SIZE, 
    	 			  GUI::ICON_SIZE,  
    	 			  GUI::ICON_SIZE));
    	button_map.insert(std::make_pair(GUI::BUTTON::BUYFUEL_ID, fuel_button));
    	 			   
    	ButtonSingle* launch_button = new ButtonSingle(texOb_button, GUI::BUTTON::GETLAUNCH_ID, "launch");
        launch_button->SetRect(Rect(screen_w - 1 * (GUI::ICON_SIZE + 5), 
    				    screen_h - 4*GUI::ICON_SIZE, 
    				    GUI::ICON_SIZE,  
    				    GUI::ICON_SIZE));
    	button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH_ID, launch_button));
}


GuiAngar::~GuiAngar()
{}	
	
void GuiAngar::BindAngar(Angar* angar)
{
	rect_slot_vec.clear();

	for (int i=0; i<angar->vehicleslot_vec.size(); i++)
 	{
 		Rect _rect(i*GUI::ITEMSLOT::WIDTH_FOR_ANGAR, 0, 
 			   GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        	rect_slot_vec.push_back(GuiPair<Rect, VehicleSlot*>(_rect, angar->vehicleslot_vec[i]));
	}
}

void GuiAngar::CheckButtonsLock()
{    	   	
	if (player->GetNpc()->GetVehicle()->IsFuelFull() == true) 	{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOn(); }
	else								{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOff(); }

	if (player->GetNpc()->GetVehicle()->IsArmorFull() == true) 	{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOn(); }
	else								{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOff(); }
}

void GuiAngar::ButtonsAction() const     
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
		if (button->GetPressed() == true)
		{
			switch(button->GetSubTypeId())
	   		{
	   			case GUI::BUTTON::BUYARMOR_ID: 
	   			{
	   				if (button->GetLock() == false)
	   				{  			
	   				      	button->PressEvent();
	   					
	   					player->GetNpc()->GetVehicle()->BuyArmorAsMuchAsPossible();
	   					return; 
	   				}
	   						
	   				break;
	  	 		}
	   		
	   			case GUI::BUTTON::BUYFUEL_ID:
	   			{
	   				if (button->GetLock() == false)
	   				{
	   		       			button->PressEvent();
	   		        		
	   		        		player->GetNpc()->GetVehicle()->BuyFuelAsMuchAsPossible();
	   					return; 
	   				}	   				
	   					
	   				break;
	   			}
	   			
	   			case GUI::BUTTON::GETLAUNCH_ID:
	   			{
	   				//MicroTask* microtask = new MicroTask(MICROSCENARIO::LAUNCHING_ID);
       					//player->GetNpc()->GetStateMachine()->SetCurrentMicroTask(microtask);
       					
       					player->GetNpc()->GetVehicle()->LaunchingEvent();
       					player->GetNpc()->GetVehicle()->SetSpecialActionId(SPECIAL_ACTION::INITIATE_LAUNCHING_ID);
       		   			return; 
       		   				      		   			
       		   			break;
       		   		}
       			}
        	}
        }
}

bool GuiAngar::UpdateMouseVehicleSlotsInteraction(const MouseData& data_mouse)
{	
        for (unsigned int i=0; i<rect_slot_vec.size(); i++)
        { 
                if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx, data_mouse.my) == true)
                {
                        if (data_mouse.right_click == true)
                        {
                                if (rect_slot_vec[i].second->GetVehicle() != NULL)
                                {
                                        player->GetNpc()->SetScanTarget(rect_slot_vec[i].second->GetVehicle());
                                        player->GetGuiManager().GetGuiVehicle().BindVehicle(rect_slot_vec[i].second->GetVehicle());
                                        return true;
                                }
                        }
                }
        }
        
        return false;
}


void GuiAngar::RenderVehicleSlots(Angar* angar) const
{
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
        	for (unsigned int i=0; i<rect_slot_vec.size(); i++)
        	{
                	rect_slot_vec[i].second->Render(rect_slot_vec[i].first);
        	}
        glPopMatrix();
}

void GuiAngar::RenderFocusedItemInfo(const MouseData& data_mouse, Angar* angar) const
{
        for (unsigned int i=0; i<angar->vehicleslot_vec.size(); i++)
        { 
		if (rect_slot_vec[i].second->GetVehicle() != NULL)
                {
                       	if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
                	{
		                rect_slot_vec[i].second->RenderItemInfo(rect_slot_vec[i].first, -offset.x, -offset.y);
		                return;
                	}
                }
        }
}
            
