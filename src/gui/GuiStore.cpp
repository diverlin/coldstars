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
#include "../docking/Store.hpp"
#include "../pilots/Player.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../pilots/Npc.hpp"

GuiStore::GuiStore():store(NULL)
{}

GuiStore::~GuiStore()
{}

void GuiStore::BindStore(Store* store)
{
        this->store = store;
        
        int clm = 0;
        int row = 0;
        for (unsigned int i=0; i<store->item_slot_vec.size(); i++)
        {	                     
	        Rect rect(clm * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE, 
        	       	  -row * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                          GUI::ITEMSLOT::WIDTH_FOR_STORE,
                          GUI::ITEMSLOT::HEIGHT_FOR_STORE);
                                                        
       		rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, store->item_slot_vec[i]));
       		
       		clm++;
        	if (clm > GUI::STORE_SLOTS_INROW)
        	{
        		clm = 0;
        		row++;
        	}
        }


        for (unsigned int i=0; i<store->vehicle_slot_vec.size(); i++)
        {	                     
	        Rect rect(clm * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE, 
        	       	  -row * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                          GUI::ITEMSLOT::WIDTH_FOR_STORE,
                          GUI::ITEMSLOT::HEIGHT_FOR_STORE);
                                                        
       		rect_vehicleslot_vec.push_back(GuiPair<Rect, VehicleSlot*>(rect, store->vehicle_slot_vec[i]));
       		
       		clm++;
        	if (clm > GUI::STORE_SLOTS_INROW)
        	{
        		clm = 0;
        		row++;
        	}
        }
}

void GuiStore::UnbindStore()
{
        store = NULL;
                
        rect_itemslot_vec.clear();
	rect_vehicleslot_vec.clear();
}
        
bool GuiStore::UpdateMouseInteraction(const MouseData& data_mouse)
{
        for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        { 
                if (rect_itemslot_vec[i].second->GetItem() != NULL)
                {
                	if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.mx - GetGuiOffset().x, data_mouse.my - GetGuiOffset().y) == true)
                	{
				player->GetCursor().SetFocusedObject(rect_itemslot_vec[i].second->GetItem());
                	
                        	if (data_mouse.left_click == true)
                        	{
                        		if (player->GetNpc()->GetCredits() >= rect_itemslot_vec[i].second->GetItem()->GetPrice())
                              		{
                        			player->GetNpc()->GetVehicle()->BuyItem(rect_itemslot_vec[i].second->GetItem());
                        		}
                        	} 
                        	return true; 
                	} 
        	}
        }

        for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        { 
                if (rect_vehicleslot_vec[i].second->GetVehicle() != NULL)
                {
                	if (rect_vehicleslot_vec[i].first.CheckInteraction(data_mouse.mx - GetGuiOffset().x, data_mouse.my - GetGuiOffset().y) == true)
                	{
				player->GetCursor().SetFocusedObject(rect_vehicleslot_vec[i].second->GetVehicle());
                	
                        	if (data_mouse.left_click == true)
                        	{
                        		int price = rect_vehicleslot_vec[i].second->GetVehicle()->GetKorpusData().price;
                        		if (player->GetNpc()->GetCredits() >= price)
                              		{
                              			store->SellVehicle(player->GetNpc(), rect_vehicleslot_vec[i].second, price);
                                                player->GetGuiManager().GetGuiKosmoport().ExitGuiStoreScreen();                                                
                                                player->GetGuiManager().GetGuiKosmoport().EnterGuiStoreScreen();
                        		}
                        	} 
                        	return true; 
                	} 
        	}
        }
                
        return false;
}

void GuiStore::RenderSlots(int credits) const
{      
	glPushMatrix();
		glTranslatef(GetGuiOffset().x, GetGuiOffset().y, 0);
        	for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        	{
                	rect_itemslot_vec[i].second->Render(rect_itemslot_vec[i].first, GetGuiOffset());
                	if (rect_itemslot_vec[i].second->GetItem() != NULL)
                	{
                		if (rect_itemslot_vec[i].second->GetItem()->GetPrice() > credits)
                		{
                			rect_itemslot_vec[i].second->RenderMark(rect_itemslot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
               			}
               		}                	
        	}

        	for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        	{
                	rect_vehicleslot_vec[i].second->Render(rect_vehicleslot_vec[i].first);
                	if (rect_vehicleslot_vec[i].second->GetVehicle() != NULL)
                	{
                		//if (rect_vehicleslot_vec[i].second->GetItem()->GetPrice() > credits)
                		//{
                			//rect_vehicleslot_vec[i].second->RenderMark(rect_vehicleslot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
               			//}
               		}                	
        	}
	glPopMatrix();
}
