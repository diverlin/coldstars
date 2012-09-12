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

#include "GuiVehicle2.hpp"

GuiVehicle2::GuiVehicle2()
{}

GuiVehicle2::~GuiVehicle2()
{}

void GuiVehicle2::BindVehicle(Vehicle* vehicle, float scale)
{
	CreateFunctionalItemSlotsCircleGeometry(vehicle, scale);
}	
	
void GuiVehicle2::CreateFunctionalItemSlotsCircleGeometry(Vehicle* vehicle, float scale)
{        
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		delete button_slot_vec[i].first;
	}
	button_slot_vec.clear();
	button_map.clear();

        Rect rect;
        		
	int angle_layer1 = 0;
	int angle_layer2 = 0;
	int angle_layer3 = 0;
        for (unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
        {	
        	int slot_subtype_id = vehicle->slot_total_vec[i]->GetSubTypeId();
		int button_subtype_id = slot_subtype_id;
		//if (slot_subtype_id == ENTITY::ARTEFACT_SLOT_ID)
		//{
		        //vec2f pos = getVec2f(100*scale, angle_layer1);	
			//rect.SetCenter(pos);
			//rect.SetSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP/2, GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2);		    			   		
           		//rect.Scale(scale);		     	
           		
       			//GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
			//rect_slot_vec.push_back(gui_pair);
		
			//angle_layer1 += 90;
		//}

                if ( (slot_subtype_id != ENTITY::CARGO_SLOT_ID) and (slot_subtype_id != ENTITY::ARTEFACT_SLOT_ID) )
        	{  
        		if (slot_subtype_id == ENTITY::WEAPON_SLOT_ID)
        		{
        			button_subtype_id = vehicle->slot_total_vec[i]->GetSubSubTypeId();
        		}
        		
        		vec2f pos = getVec2f(260*scale, angle_layer2);	
			rect.SetCenter(pos);
			rect.SetSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		    			   
           		rect.Scale(scale);	
           			  
          		ButtonTrigger* button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_purple, button_subtype_id, getEntityStr(button_subtype_id));  
    			button->SetRect(rect);  	
    				        	
			button_slot_vec.push_back(GuiPair<BaseButton*, ItemSlot*>(button, vehicle->slot_total_vec[i]));
			button_map.insert(std::make_pair(button->GetSubTypeId(), button));
		
			angle_layer2 += 20;
		}

		//if (slot_subtype_id == ENTITY::CARGO_SLOT_ID)
		//{
		        //vec2f pos = getVec2f(220*scale, angle_layer3);	
			//rect.SetCenter(pos);
			//rect.SetSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		    			   		
           		//rect.Scale(scale);		     	
       			
       			//GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
			//rect_slot_vec.push_back(gui_pair);
		
			//angle_layer3 += 15*scale;
		//}
        }    	
}	

void GuiVehicle2::UpdateEquipmentIcons() const
{
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		if (button_slot_vec[i].second->GetEquiped() == true)
		{
			button_slot_vec[i].first->SetAdditionalTextureOb(button_slot_vec[i].second->GetItem()->GetTextureOb());
		}
		else
		{
			button_slot_vec[i].first->SetAdditionalTextureOb(NULL);
		}
	}
}

void GuiVehicle2::ButtonsAction(Player* player) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
       		switch(button->GetSubTypeId())
       		{	
        		case ENTITY::WEAPON_SLOT1_ID: { player->GetWeaponsSelector().SetSingle(1, button->GetPressed()); break; }
        		case ENTITY::WEAPON_SLOT2_ID: { player->GetWeaponsSelector().SetSingle(2, button->GetPressed()); break; }      		
        		case ENTITY::WEAPON_SLOT3_ID: { player->GetWeaponsSelector().SetSingle(3, button->GetPressed()); break; }     
          		case ENTITY::WEAPON_SLOT4_ID: { player->GetWeaponsSelector().SetSingle(4, button->GetPressed()); break; }     
        		case ENTITY::WEAPON_SLOT5_ID: { player->GetWeaponsSelector().SetSingle(5, button->GetPressed()); break; }         		           		   	      	
                	case ENTITY::WEAPON_SLOT6_ID: { player->GetWeaponsSelector().SetSingle(6, button->GetPressed()); break; }          		
        		case ENTITY::WEAPON_SLOT7_ID: { player->GetWeaponsSelector().SetSingle(7, button->GetPressed()); break; }          		
        		case ENTITY::WEAPON_SLOT8_ID: { player->GetWeaponsSelector().SetSingle(8, button->GetPressed()); break; }          		
        		case ENTITY::WEAPON_SLOT9_ID: { player->GetWeaponsSelector().SetSingle(9, button->GetPressed()); break; }     
		}
	}
}
