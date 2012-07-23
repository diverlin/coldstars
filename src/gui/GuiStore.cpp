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



GuiStore::GuiStore(Player* player)
{
	this->player = player;
}

GuiStore::~GuiStore()
{}

        
bool GuiStore::UpdateMouseInteraction(const MouseData& data_mouse, Store* store)
{
        for (unsigned int i = 0; i < store->slot_total_vec.size(); i++)
        { 
                if (store->slot_total_vec[i]->GetEquipedStatus() == true)
                {
                	if (store->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
                	{
                        	if (data_mouse.left_click == true)
                        	{
                        		store->SellItemFromSlot(player->GetNpc(), store->slot_total_vec[i]);
                        	} 
                        	return true; break;
                	} 
        	}
        }
        
        return false;
}

void GuiStore::RenderSlots(Store* store) const
{      
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
        	for (unsigned int i = 0; i < store->slot_total_vec.size(); i ++)
        	{
                	store->slot_total_vec[i]->Render();
                	if (store->slot_total_vec[i]->GetEquipedStatus() == true)
                	{
                		store->slot_total_vec[i]->GetItem()->Render(store->slot_total_vec[i]->GetRect());	
                	}
        	}
	glPopMatrix();
}

void GuiStore::RenderFocusedItemInfo(const MouseData& data_mouse, Store* store)
{	
        for (unsigned int i = 0; i < store->slot_total_vec.size(); i++)
        {                              				
                if (store->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
                {
                        store->slot_total_vec[i]->RenderItemInfo(-offset.x, -offset.y);                    
                } 
        }
}

