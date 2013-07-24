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

#include "Slider.hpp"
#include "../render/Render.hpp"
#include "../common/constants.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../common/myStr.hpp"
#include "../gui/ButtonSingle.hpp"
#include "../gui/ButtonTrigger.hpp"
#include "../gui/MouseData.hpp"
#include "../pilots/Player.hpp"
#include "../resources/TextureManager.hpp"
#include "../render/Screen.hpp"

#include "../items/others/GoodsPack.hpp"

#include "../pilots/Npc.hpp"

Slider::Slider()
{
	//type_id = GUI::TYPE::SLIDER_ID;
	//subtype_id = GUI::TYPE::NONE_ID;
	
	textureOb = GuiTextureObCollector::Instance().text_background;
	textureOb_scale = TextureManager::Instance().GetRandomTextureOb(TEXTURE::LAZER_EFFECT_ID);
	
	//BaseButton* slide_button = new BaseButton(GuiTextureObCollector::Instance().dot_purple, GUI::BUTTON::SLIDE_ID, "slide");  
	//button_map.insert(std::make_pair(GUI::BUTTON::SLIDE_ID, slide_button));
	
	//ButtonTrigger* accept_button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_green, GUI::BUTTON::ACCEPT_ID, "accept");  
	//button_map.insert(std::make_pair(GUI::BUTTON::ACCEPT_ID, accept_button));
	
	//ButtonTrigger* decline_button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_red, GUI::BUTTON::DECLINE_ID, "decline");  
	//button_map.insert(std::make_pair(GUI::BUTTON::DECLINE_ID, decline_button));
}

Slider::~Slider()
{}
        
void Slider::Configure(int ammount_total, int price_for_one)
{
	this->ammount_total = ammount_total;
	this->price_for_one  = price_for_one;

	SetOffset(Vec2<float>(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2));

	ammount_selected = 0;
	price_selected = 0;
	
	rect.Set(0, 0, GUI::SLIDER_WIDTH, 3*GUI::ICON_SIZE);
	rect_slide.Set(0, rect.GetCenter().y - GUI::ICON_SIZE/2, GUI::SLIDER_WIDTH, GUI::ICON_SIZE);
	
	//GetButton(GUI::BUTTON::SLIDE_ID)->GetRect().Set(0, rect_slide.GetBottomLeft().y, GUI::ICON_SIZE, GUI::ICON_SIZE);
	//GetButton(GUI::BUTTON::ACCEPT_ID)->GetRect().Set(0, 0, 20, 20);
	//GetButton(GUI::BUTTON::DECLINE_ID)->GetRect().Set(rect.GetWidth() - GUI::ICON_SIZE, 0, GUI::ICON_SIZE, GUI::ICON_SIZE);
}

void Slider::UpdateSlidePosition(const MouseData& data_mouse)
{      /*
	ButtonSingle* slide_button = (ButtonSingle*)GetGuiElement(GUI::TYPE::SLIDER_ID);
	if (rect_slide.CheckInteraction(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y) == true)
	{
		if (data_mouse.left_press == true)
		{
			//slide_button->GetRect().SetBottomLeftX(data_mouse.mx - slide_button->GetRect().GetWidth()/2 - GetOffset().x);
		}
	}
	
	//ammount_selected = ammount_total * slide_button->GetRect().GetCenter().x / (float)rect.GetWidth();
	price_selected = price_for_one * ammount_selected; */
}
		
void Slider::ButtonsAction(Shop* shop)
{
	//for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	//{
		//BaseButton* button = iterator->second;
		//if (button->GetLock() == false)
		//{
			//if (button->GetPressed() == true)
			//{
        			//switch(button->GetSubTypeId())
        			//{
        				//case GUI::BUTTON::ACCEPT_ID: 
        				//{ 
        					//int goods_subtype_id;
        					//switch(subtype_id)
        					//{
        						//case GUI::BUTTON::MINERALS_ID: 		{ goods_subtype_id = ENTITY::MINERALS_ID; break; }
        						//case GUI::BUTTON::FOOD_ID: 		{ goods_subtype_id = ENTITY::FOOD_ID; break; }
        						//case GUI::BUTTON::MEDICINE_ID: 		{ goods_subtype_id = ENTITY::MEDICINE_ID; break; }
        						//case GUI::BUTTON::MILITARY_ID: 		{ goods_subtype_id = ENTITY::MILITARY_ID; break; }
        						//case GUI::BUTTON::DRUG_ID: 		{ goods_subtype_id = ENTITY::DRUG_ID; break; }
        						//case GUI::BUTTON::EXCLUSIVE_ID: 	{ goods_subtype_id = ENTITY::EXCLUSIVE_ID; break; }
        					//}
        					
        					
						//shop->SellGoods(player->GetNpc(), goods_subtype_id, ammount_selected);
						
        					//SetSubTypeId(NONE_ID);
        					//button->Reset(); //untrigger        				
        					//break; 
        				//}

        				//case GUI::BUTTON::DECLINE_ID: 
        				//{	 
        					//SetSubTypeId(NONE_ID);  
        					//button->Reset(); //untrigger        				
        					//break; 
        				//}
           			//}
           		//}  		   	
		//}
	//}
}
       	
void Slider::CheckButtonsLock()
{    	   	
	//if (player->GetNpc()->GetCredits() < price_selected) 	{ GetButton(GUI::BUTTON::ACCEPT_ID)->LockOn(); }
	//else							{ GetButton(GUI::BUTTON::ACCEPT_ID)->LockOff(); }
}
	  		
void Slider::Render() const
{
	glPushMatrix();
	{
		//glTranslatef(GetOffset().x, GetOffset().y, 0);
		drawTexturedRect(textureOb, rect, -1);
		drawTexturedRect(textureOb_scale, rect_slide, -1);
	}
	glPopMatrix();
	
	{
		//Vec2<float> pos(rect.GetBottomLeft().x + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
		//Screen::Instance().DrawText("0", 12, pos);
	}

	{
		//Vec2<float> pos(rect.GetBottomLeft().x + rect.GetWidth()/2 - 20 + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
		//Screen::Instance().DrawText(int2str(ammount_selected)+" :"+int2str(price_selected) + "$", 12, pos);		
	}

	{
		//Vec2<float> pos(rect.GetBottomLeft().x + rect.GetWidth() - 20 + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
		//Screen::Instance().DrawText(int2str(ammount_total), 12, pos);	
	}	
	
	//RenderButtons();
}

