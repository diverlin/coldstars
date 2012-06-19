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

        
void GuiStore::Update(Store* store)
{
         bool lmb = player->GetCursor()->GetMouseLeftButton();; 
        //bool rmb = player->GetCursor()->GetMouseRightButton();; 

        for (unsigned int i = 0; i < store->slot_total_vec.size(); i++)
        { 
                if (store->slot_total_vec[i]->GetEquipedStatus() == true)
                {                                
                	float dist = distBetweenPoints(store->slot_total_vec[i]->GetRect().GetCenter(), player->GetCursor()->GetMousePos().x, player->GetScreen()->GetHeight() - player->GetCursor()->GetMousePos().y);
                                                       				
                	if (dist < store->slot_total_vec[i]->GetRect().GetWidth()/2)
                	{
                        	if (lmb == true)
                        	{
                        		store->SellItemFromSlot(player->GetNpc(), store->slot_total_vec[i]);
                        	} 
                        	break;
                	} 
        	}
        }
}

void GuiStore::RenderBackground(Store* store, const Rect& rect)
{
	store->RenderBackground(rect);                
}

void GuiStore::RenderSlots(Store* store) const
{      
        for (unsigned int i = 0; i < store->slot_total_vec.size(); i ++)
        {
                store->slot_total_vec[i]->Render(-1);
        }
}

void GuiStore::RenderFocusedItemInfo(Store* store)
{	
        for (unsigned int i = 0; i < store->slot_total_vec.size(); i++)
        { 
                float dist = distBetweenPoints(store->slot_total_vec[i]->GetRect().GetCenter(), player->GetCursor()->GetMousePos().x, player->GetScreen()->GetHeight() - player->GetCursor()->GetMousePos().y);
                                                       				
                if (dist < store->slot_total_vec[i]->GetRect().GetWidth()/2)
                {
                        store->slot_total_vec[i]->RenderItemInfo();                    
                } 
        }
}


