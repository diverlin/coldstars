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
#include <jeti/Render.hpp>
#include <common/constants.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
//#include <ceti/StringUtils.hpp>
#include <client/gui/ButtonSingle.hpp>
#include <client/gui/ButtonTrigger.hpp>
#include <client/gui/MouseData.hpp>
#include <client/pilots/Player.hpp>
#include <client/resources/TextureCollector.hpp>
#include <jeti/Screen.hpp>

#include <item/others/GoodsPack.hpp>

#include <pilots/Npc.hpp>

Slider::Slider()
{
    //type_id = GUI::TYPE::SLIDER;
    //subtype_id = GUI::TYPE::NONE;
    
    textureOb = GuiTextureObCollector::Instance().text_background;
    textureOb_scale = TextureCollector::get().getTextureByTypeId(texture::Type::LAZER_EFFECT);
    
    //BaseButton* slide_button = new BaseButton(GuiTextureObCollector::Instance().dot_purple, GUI::BUTTON::SLIDE, "slide");  
    //button_map.insert(std::make_pair(GUI::BUTTON::SLIDE, slide_button));
    
    //ButtonTrigger* accept_button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_green, GUI::BUTTON::ACCEPT, "accept");  
    //button_map.insert(std::make_pair(GUI::BUTTON::ACCEPT, accept_button));
    
    //ButtonTrigger* decline_button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_red, GUI::BUTTON::DECLINE, "decline");  
    //button_map.insert(std::make_pair(GUI::BUTTON::DECLINE, decline_button));
}

Slider::~Slider()
{}
        
void Slider::Configure(int ammount_total, int price_for_one)
{
    this->ammount_total = ammount_total;
    this->price_for_one  = price_for_one;

    //SetOffset(glm::vec2(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2));

    ammount_selected = 0;
    price_selected = 0;
    
    rect.set(0, 0, GUI::SLIDER_WIDTH, 3*GUI::ICON_SIZE);
    rect_slide.set(0, rect.center().y - GUI::ICON_SIZE/2, GUI::SLIDER_WIDTH, GUI::ICON_SIZE);
    
    //GetButton(GUI::BUTTON::SLIDE)->GetRect().Set(0, rect_slide.GetBottomLeft().y, GUI::ICON_SIZE, GUI::ICON_SIZE);
    //GetButton(GUI::BUTTON::ACCEPT)->GetRect().Set(0, 0, 20, 20);
    //GetButton(GUI::BUTTON::DECLINE)->GetRect().Set(rect.GetWidth() - GUI::ICON_SIZE, 0, GUI::ICON_SIZE, GUI::ICON_SIZE);
}

void Slider::UpdateSlidePosition(const MouseData& data_mouse)
{      /*
    ButtonSingle* slide_button = (ButtonSingle*)GetGuiElement(GUI::TYPE::SLIDER);
    if (rect_slide.CheckInteraction(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y) == true)
    {
        if (data_mouse.left_press == true)
        {
            //slide_button->GetRect().SetBottomLeftX(data_mouse.mx - slide_button->GetRect().GetWidth()/2 - GetOffset().x);
        }
    }
    
    //ammount_selected = ammount_total * slide_button->GetRect().center().x / (float)rect.GetWidth();
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
                    //switch(button->subTypeId())
                    //{
                        //case GUI::BUTTON::ACCEPT: 
                        //{ 
                            //int goods_subtype_id;
                            //switch(subtype_id)
                            //{
                                //case GUI::BUTTON::MINERALS:         { goods_subtype_id = ENTITY::MINERALS; break; }
                                //case GUI::BUTTON::FOOD:         { goods_subtype_id = ENTITY::FOOD; break; }
                                //case GUI::BUTTON::MEDICINE:         { goods_subtype_id = ENTITY::MEDICINE; break; }
                                //case GUI::BUTTON::MILITARY:         { goods_subtype_id = ENTITY::MILITARY; break; }
                                //case GUI::BUTTON::DRUG:         { goods_subtype_id = ENTITY::DRUG; break; }
                                //case GUI::BUTTON::EXCLUSIVE:     { goods_subtype_id = ENTITY::EXCLUSIVE; break; }
                            //}
                            
                            
                        //shop->SellGoods(player->GetNpc(), goods_subtype_id, ammount_selected);
                        
                            //setSubTypeId(NONE);
                            //button->Reset(); //untrigger                        
                            //break; 
                        //}

                        //case GUI::BUTTON::DECLINE: 
                        //{     
                            //setSubTypeId(NONE);  
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
    //if (player->GetNpc()->GetCredits() < price_selected)     { GetButton(GUI::BUTTON::ACCEPT)->LockOn(); }
    //else                            { GetButton(GUI::BUTTON::ACCEPT)->LockOff(); }
}
              
void Slider::Render() const
{
    //glPushMatrix();
    //{
        ////glTranslatef(GetOffset().x, GetOffset().y, 0);
        //drawTexturedRect(textureOb, rect, -1);
        //drawTexturedRect(textureOb_scale, rect_slide, -1);
    //}
    //glPopMatrix();
    
    {
        //glm::vec2 pos(rect.GetBottomLeft().x + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
        //Screen::Instance().DrawText("0", 12, pos);
    }

    {
        //glm::vec2 pos(rect.GetBottomLeft().x + rect.GetWidth()/2 - 20 + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
        //Screen::Instance().DrawText(std::to_string(ammount_selected)+" :"+std::to_string(price_selected) + "$", 12, pos);
    }

    {
        //glm::vec2 pos(rect.GetBottomLeft().x + rect.GetWidth() - 20 + GetOffset().x, rect.GetBottomLeft().y + rect.GetHeight() + GetOffset().y);
        //Screen::Instance().DrawText(std::to_string(ammount_total), 12, pos);
    }    
    
    //RenderButtons();
}

