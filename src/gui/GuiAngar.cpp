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
#include "../slots/ItemSlot.hpp"
#include "../items/BaseItem.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"

#include "../pilots/Npc.hpp"
#include "../builder/ItemSlotBuilder.hpp"

GuiAngar::GuiAngar():angar(NULL)
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

	repair_slot = GetNewItemSlotWithoutSaveAbility(ENTITY::REPAIR_SLOT_ID);
}


GuiAngar::~GuiAngar()
{
	delete repair_slot;
}	
	
void GuiAngar::BindAngar(Angar* angar)
{
	this->angar = angar;
	
	rect_vehicleslot_vec.clear();
	rect_itemslot_vec.clear();
	
        int column_counter = 1;
        int row_counter = 0;
        for (int i=0; i<angar->vehicle_visitors_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        	rect_vehicleslot_vec.push_back(GuiPair<Rect, VehicleSlot*>(_rect, angar->vehicle_visitors_slot_vec[i]));
                
                column_counter++;                
	}
        
        column_counter = 1;
        row_counter = 2;
        for (int i=0; i<angar->vehicle_military_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        	rect_vehicleslot_vec.push_back(GuiPair<Rect, VehicleSlot*>(_rect, angar->vehicle_military_slot_vec[i]));
                
                column_counter++;                
	}
	
	column_counter = 0;
        row_counter = 0;
        for (int i=0; i<angar->item_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::ITEMSLOT::WIDTH_FOR_ANGAR, row_counter*GUI::ITEMSLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        	rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(_rect, angar->item_slot_vec[i]));
                
                row_counter++;                
	}
	
		
   	Rect rect(GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		   3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        			   
	rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, repair_slot));    

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
	   					
	   					player->GetNpc()->GetVehicle()->BuyKorpusRepair();
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
       					player->GetNpc()->GetVehicle()->LaunchingEvent();
       		   			return; 
       		   				      		   			
       		   			break;
       		   		}
       			}
        	}
        }
}

bool GuiAngar::UpdateMouseVehicleSlotsInteraction(const MouseData& data_mouse)
{	
        for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        { 
                if (rect_vehicleslot_vec[i].first.CheckInteraction(data_mouse.mx, data_mouse.my) == true)
                {         
                       	if (data_mouse.right_click == true)
                       	{
                 		player->GetNpc()->SetScanTarget(rect_vehicleslot_vec[i].second->GetVehicle());
                                player->GetGuiManager().GetGuiVehicleScan().BindVehicle(rect_vehicleslot_vec[i].second->GetVehicle());
                                return true;
                        }
                        
                        if (rect_vehicleslot_vec[i].second->GetVehicle() != NULL)
                        {       
                        	player->GetCursor().SetFocusedObject(rect_vehicleslot_vec[i].second->GetVehicle());
                        }           
                                   
                }
        }

        for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        { 
                if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.mx, data_mouse.my) == true)
                {
                	if (data_mouse.left_click == true)
                        {
                		if (rect_itemslot_vec[i].second->GetSubTypeId() != ENTITY::REPAIR_SLOT_ID)
				{	
  					player->GetCursor().GetItemSlot()->SwapItem(rect_itemslot_vec[i].second);
                        	}
                        	else
                        	{
                        		angar->RepairItem(player->GetNpc(), player->GetCursor().GetItemSlot()->GetItem());
                        	}
                        	
                        }
                        	
                        if (rect_itemslot_vec[i].second->GetItem() != NULL)
                        {                         
                		player->GetCursor().SetFocusedObject(rect_itemslot_vec[i].second->GetItem());
                	}
                }
        }
                
        return false;
}


void GuiAngar::RenderVehicleSlots() const
{
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
        	for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        	{
                	rect_vehicleslot_vec[i].second->Render(rect_vehicleslot_vec[i].first);
        	}
        	for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        	{
                	rect_itemslot_vec[i].second->Render(rect_itemslot_vec[i].first, offset);
        	}
        glPopMatrix();
}

           
