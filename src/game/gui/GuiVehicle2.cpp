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

GuiVehicle2::GuiVehicle2():vehicle(nullptr)
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
	child_vec.clear();
	
	vehicle = nullptr;
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
						  
			TextureOb* textureOb = GuiTextureObCollector::Instance().dot_purple;
			//ButtonTrigger* button = new ButtonTrigger(textureOb, button_subtype_id, getTypeStr(button_subtype_id));  
			//button_slot_vec.push_back(GuiPair<BaseButton*, ItemSlot*>(button, vehicle->slot_total_vec[i]));
			//button_map.insert(std::make_pair(button->GetSubTypeId(), button));
		}
	}    	
        
	int angle = 0;
	for (auto &button : child_vec)
	{
		Vec2<float> center = getVec2f(160, angle);
		float zpos = -1;
		float zsize = 1;
		Vec3<float> center3(center.x, center.y, zpos);
		Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
		Box box(center3*scale, size*scale);
		button->SetBox(box);
		
		//angle += 360/button_map.size();
		angle += 20;
	}
}	

void GuiVehicle2::UpdateEquipmentIcons() const
{
	for (unsigned int i=0; i<button_slot_vec.size(); i++)
	{
		if (button_slot_vec[i].second->GetItem() != nullptr)
		{
			button_slot_vec[i].first->SetTextureObAdditional(button_slot_vec[i].second->GetItem()->GetTextureOb());
			button_slot_vec[i].first->SetTextureObMask(nullptr);
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
			button_slot_vec[i].first->SetTextureObAdditional(nullptr);
			button_slot_vec[i].first->SetTextureObMask(nullptr);
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
		if (button_slot_vec[i].first->GetBox().CheckInteraction(data_mouse.pos))
		{  
			if (data_mouse.left_click == true)
			{
				return button_slot_vec[i].second;
			}
		}
	}  
        
	return nullptr;                     
}

void GuiVehicle2::UpdateOffset()
{
	Vec3<float> offset(Screen::Instance().GetRect().GetBottomLeft().x, Screen::Instance().GetRect().GetBottomLeft().y, 0.0);
	SetOffset(vehicle->GetCenter() - offset);
}
