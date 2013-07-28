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

#include "GuiNatureLand.hpp"
#include "ButtonSingle.hpp"
#include "../config/config.hpp"
#include "../slots/ItemSlot.hpp"
#include "../items/BaseItem.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"
#include "../common/rand.hpp"

#include "../pilots/Npc.hpp"
#include "../spaceobjects/Vehicle.hpp"
//#include "../builder/ItemSlotBuilder.hpp"

#include "../dock/NatureLand.hpp"

#include "../render/Render.hpp"

GuiNatureLand::GuiNatureLand():natureland(nullptr)
{
	//int screen_w = Config::Instance().SCREEN_WIDTH;
	//int screen_h = Config::Instance().SCREEN_HEIGHT;
	
	//TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake
	
	//float zpos = -1;
	//float zsize = 1;	
	
	{		   
		//ButtonSingle* launch_button = new ButtonSingle(texOb_button, GUI::BUTTON::GETLAUNCH_ID, "launch");
		//Vec3<float> center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 4*GUI::ICON_SIZE, zpos);
		//Vec3<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);
		//launch_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH_ID, launch_button));
	}
}


GuiNatureLand::~GuiNatureLand()
{}	
	
void GuiNatureLand::BindNatureLand(NatureLand* natureland)
{
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
	this->natureland = natureland;
	
	rect_itemslot_vec.clear();

    for (unsigned int i=0; i<natureland->item_slot_vec.size(); i++)
 	{
 		Rect _rect(natureland->item_slot_vec[i]->GetPosition().x/100.f*(screen_w - GUI::ITEMSLOT::WIDTH_FOR_ANGAR), 
 			       natureland->item_slot_vec[i]->GetPosition().y/100.f*(screen_h - GUI::ITEMSLOT::HEIGHT_FOR_ANGAR), 
 			       GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(_rect, natureland->item_slot_vec[i]));
	}
}

void GuiNatureLand::ButtonsAction() const     
{
	//for (auto &button : child_vec)
	//{
		//if (button->GetPressed() == true)
		//{
			//switch(button->GetSubTypeId())	   		
			//{	   			
	   			//case GUI::BUTTON::GETLAUNCH_ID:
	   			//{      					
       					//player->GetNpc()->GetVehicle()->LaunchingEvent();
       		   			//return; 
       		   				      		   			
       		   			//break;
       		   		//}
       			//}
        	//}
        //}
}

bool GuiNatureLand::UpdateMouseInteractionWithEquipedItemSlots(const MouseData& data_mouse)
{
       	//for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
       	//{
		//BaseItem* item = rect_itemslot_vec[i].second->GetItem();
		//if (item != nullptr)
		//{	 
	                //if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y) == true)
	                //{	
                		//if (data_mouse.left_click == true)
                        	//{
                        		//m_Player->GetNpc()->GetVehicle()->AddItemToCargoSlot(item);
                        	//}
                     
               			//m_Player->GetCursor().SetFocusedObject(item);
        		//}
		//}
       	//}
                
        return false;
}

void GuiNatureLand::RenderBackground(const Rect& rect) const
{
     	drawTexturedRect(natureland->GetBackgroundTextureOb(), rect, -2);  
}
           

void GuiNatureLand::RenderEquipedItemSlots() const
{
	//glPushMatrix();
		//glTranslatef(GetGuiOffset().x, GetGuiOffset().y, 0);
        	//for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        	//{
        		//if (rect_itemslot_vec[i].second->GetItem() != nullptr)
        		//{
                		//rect_itemslot_vec[i].second->Render(rect_itemslot_vec[i].first, GetGuiOffset());
        		//}
        	//}
        //glPopMatrix();
}
