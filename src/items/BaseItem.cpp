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



BaseItem::BaseItem()
{
        slot = NULL;
        price = 0;
}

/* virtual */
BaseItem::~BaseItem ()
{}

void BaseItem::BindSlot(ItemSlot* slot)    { this->slot = slot; }


void BaseItem::Deterioration()
{
    	condition -= data_item.deterioration_rate;
    	if (condition <= 0)
    	{
       		is_DAMAGED = true;
       		if (slot->getOwnerVehicle() != NULL) 
       		{  
           		UpdateOwnerAbilities();
           	}
    	}
}

void BaseItem::Repair()
{
    	condition = data_item.condition_max;
    	if (is_DAMAGED == true)
    	{
        	is_DAMAGED = false;
        	if (slot->getOwnerVehicle() != NULL)   
        	{
           		UpdateOwnerAbilities();
           	}
    	}
}

void BaseItem::UpdateInfo()
{
	info.clear();

	AddUniqueInfo();
    	AddCommonInfo();
}

void BaseItem::RenderInfo(Rect slot_rect, float offset_x, float offset_y)
{  
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}

/* virtual */
void BaseItem::Render(Rect slot_rect)
{
    	drawTexturedRect(texOb, slot_rect, -1.0);
}

