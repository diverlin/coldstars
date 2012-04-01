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



GuiStore :: GuiStore(Player* player)
{
	this->player = player;
}


GuiStore :: ~GuiStore()
{}

        
void GuiStore :: update()
{
 	Store* store = ((Kosmoport*)player->getNpc()->GetLand())->getStore();
 
        bool lmb = player->getCursor()->getMouseLeftButton();; 
        //bool rmb = player->getCursor()->getMouseRightButton();; 

        for (unsigned int i = 0; i < store->slot_vec.size(); i++)
        { 
                if (store->slot_vec[i]->GetEquipedStatus() == true)
                {                                
                	float dist = distBetweenPoints(store->slot_vec[i]->GetRect().getCenter(), player->getCursor()->getMousePos().x, player->getScreen()->getHeight() - player->getCursor()->getMousePos().y);
                                                       				
                	if (dist < store->slot_vec[i]->GetRect().getWidth()/2)
                	{
                        	if (lmb == true)
                        	{
                        		store->sellItemFromSlot(player->getNpc(), store->slot_vec[i]);
                        	} 
                        	break;
                	} 
        	}
        }
}


void GuiStore :: Render() const
{            
	Store* store = ((Kosmoport*)player->getNpc()->GetLand())->getStore();
	         
        for (unsigned int i = 0; i < store->slot_vec.size(); i ++)
        {
                store->slot_vec[i]->Render(-1);
        }
}


void GuiStore :: renderFocusedItemInfo()
{
	Store* store = ((Kosmoport*)player->getNpc()->GetLand())->getStore();
        for (unsigned int i = 0; i < store->slot_vec.size(); i++)
        { 
                float dist = distBetweenPoints(store->slot_vec[i]->GetRect().getCenter(), player->getCursor()->getMousePos().x, player->getScreen()->getHeight() - player->getCursor()->getMousePos().y);
                                                       				
                if (dist < store->slot_vec[i]->GetRect().getWidth()/2)
                {
                        store->slot_vec[i]->RenderItemInfo();                    
                } 
        }
}


void GuiStore :: renderBackground() const
{
	Store* store = ((Kosmoport*)player->getNpc()->GetLand())->getStore();

     	Rect screen_rect = Rect(0, 0, player->getScreen()->getWidth(), player->getScreen()->getHeight());
     	drawTexturedRect(store->texOb_background, screen_rect, -1);  
}
