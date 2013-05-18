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
#include "ButtonTrigger.hpp"
#include "../common/myStr.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../spaceobjects/Vehicle.hpp"

#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../render/Screen.hpp"

GuiVehicle2::GuiVehicle2():vehicle(NULL)
{}

GuiVehicle2::~GuiVehicle2()
{}

void GuiVehicle2::Reset()
{
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		delete button_slot_vec[i].first;
	}
	button_slot_vec.clear();
	button_map.clear();
	
	vehicle = NULL;
}

void GuiVehicle2::BindVehicle(Vehicle* vehicle, float scale)
{
	CreateFunctionalItemSlotsCircleGeometry(vehicle, scale);
	
	this->vehicle = vehicle;
}	
	
void GuiVehicle2::CreateFunctionalItemSlotsCircleGeometry(Vehicle* vehicle, float scale)
{        
	Reset();
	
        for (unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
        {	
        	int slot_subtype_id = vehicle->slot_total_vec[i]->GetSubTypeId();
                if ( (slot_subtype_id != ENTITY::CARGO_SLOT_ID) and (slot_subtype_id != ENTITY::ARTEFACT_SLOT_ID) )
        	{  
        		int button_subtype_id = slot_subtype_id;
        		if (slot_subtype_id == ENTITY::WEAPON_SLOT_ID)
        		{
        			button_subtype_id = vehicle->slot_total_vec[i]->GetSubSubTypeId();
        		}
			           			  
          		ButtonTrigger* button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_purple, button_subtype_id, getTypeStr(button_subtype_id));  
			button_slot_vec.push_back(GuiPair<BaseButton*, ItemSlot*>(button, vehicle->slot_total_vec[i]));
			button_map.insert(std::make_pair(button->GetSubTypeId(), button));
		}
        }    	
        
        int angle = 0;
        for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
        	Vec2<float> center = getVec2f(160, angle);
		Vec2<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		Quad quad(center*scale, size*scale);
   		iterator->second->SetQuad(quad);

		//angle += 360/button_map.size();
		angle += 20;
	}
}	

void GuiVehicle2::UpdateEquipmentIcons() const
{
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		if (button_slot_vec[i].second->GetItem() != NULL)
		{
			button_slot_vec[i].first->SetTextureObAdditional(button_slot_vec[i].second->GetItem()->GetTextureOb());
			button_slot_vec[i].first->SetTextureObMask(NULL);
			if (button_slot_vec[i].second->GetItem()->GetCondition() == 0)
			{
				button_slot_vec[i].first->SetTextureObMask(GuiTextureObCollector::Instance().slot_mark_reject);
				button_slot_vec[i].first->Reset();
			}
			if (button_slot_vec[i].second->GetItem()->GetLocked())
			{
				button_slot_vec[i].first->SetTextureObMask(GuiTextureObCollector::Instance().slot_mark_accept);
				button_slot_vec[i].first->Reset();
			}
		}
		else
		{
			button_slot_vec[i].first->SetTextureObAdditional(NULL);
			button_slot_vec[i].first->SetTextureObMask(NULL);
			button_slot_vec[i].first->Reset();
		}
	}
}

void GuiVehicle2::ButtonsAction(Player* player) const
{
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		if (button_slot_vec[i].first->GetPressed() == true)
		{
			if (button_slot_vec[i].second->GetSelected() == false)
			{
				button_slot_vec[i].second->SelectEvent();
			}
		}
		else
		{
			if (button_slot_vec[i].second->GetSelected() == true)
			{
				button_slot_vec[i].second->DeselectEvent();
			}
		}       		
	}
}

ItemSlot* GuiVehicle2::GetInreactedItemSlot(const MouseData& data_mouse)
{
	for(unsigned int i=0; i<button_slot_vec.size(); i++)
	{ 
		if (button_slot_vec[i].first->GetQuad().CheckInteraction(data_mouse.mx - GetGuiOffset().x, data_mouse.my - GetGuiOffset().y))
		{  
			if (data_mouse.left_click == true)
			{
				return button_slot_vec[i].second;
			}
       		}
        }  
        
        return NULL;                     
}

void GuiVehicle2::UpdateOffset()
{
	SetGuiOffset(vehicle->GetPoints().GetCenter() - Screen::Instance().GetRect().GetBottomLeft());
}
