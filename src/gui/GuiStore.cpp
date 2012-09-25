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

#include "GuiStore.hpp"
#include "../pilots/Player.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../pilots/Npc.hpp"

GuiStore::GuiStore()
{}

GuiStore::~GuiStore()
{}

void GuiStore::BindStore(Store* store)
{
	rect_slot_vec.clear();

        int clm = 0;
        int row = 0;
        for (unsigned int i=0; i<store->slot_total_vec.size(); i++)
        {	                     
	        Rect rect(clm * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE, 
        	       	  -row * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                          GUI::ITEMSLOT::WIDTH_FOR_STORE,
                          GUI::ITEMSLOT::HEIGHT_FOR_STORE);
                                                        
       		rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, store->slot_total_vec[i]));
       		
       		clm++;
        	if (clm > GUI::STORE_SLOTS_INROW)
        	{
        		clm = 0;
        		row++;
        	}
        }
}
        
bool GuiStore::UpdateMouseInteraction(const MouseData& data_mouse, Store* store)
{
        for (unsigned int i=0; i<rect_slot_vec.size(); i++)
        { 
                if (rect_slot_vec[i].second->GetEquiped() == true)
                {
                	if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
                	{
                        	if (data_mouse.left_click == true)
                        	{
                        		if (player->GetNpc()->GetCredits() >= rect_slot_vec[i].second->GetItem()->GetPrice())
                              		{
                        			store->SellItemFromSlot(player->GetNpc(), rect_slot_vec[i].second);
                        		}
                        	} 
                        	return true; break;
                	} 
        	}
        }
        
        return false;
}

void GuiStore::RenderSlots(int credits) const
{      
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
        	for (unsigned int i=0; i<rect_slot_vec.size(); i++)
        	{
                	rect_slot_vec[i].second->Render(rect_slot_vec[i].first, offset);
                	if (rect_slot_vec[i].second->GetEquiped() == true)
                	{
                		if (rect_slot_vec[i].second->GetItem()->GetPrice() > credits)
                		{
                			rect_slot_vec[i].second->RenderMark(rect_slot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
               			}
               		}                	
        	}
	glPopMatrix();
}

void GuiStore::RenderFocusedItemInfo(const MouseData& data_mouse)
{	
        for (unsigned int i=0; i<rect_slot_vec.size(); i++)
        {                              				
                if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
                {
                        rect_slot_vec[i].second->RenderItemInfo(rect_slot_vec[i].first.GetCenter(), -offset.x, -offset.y);                    
                } 
        }
}

