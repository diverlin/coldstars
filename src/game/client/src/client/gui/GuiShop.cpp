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

#include "GuiShop.hpp"
#include <dock/Shop.hpp>

#include <ceti/rect.hpp>
#include <client/gui/Cursor.hpp>
#include <jeti/Screen.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/gui/ButtonSingle.hpp>
//#include <ceti/StringUtils.hpp>
#include <common/constants.hpp>

namespace gui {

GuiShop::GuiShop()
{
    //glm::vec2 center(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2);
            
    //TextureOb* _texOb = GuiTextureObCollector::Instance().text_background; 
    
    //float zpos = -1;
    //float zsize = 1;
    {
        //ButtonSingle* minerals_button = new ButtonSingle(_texOb, GUI::BUTTON::MINERALS, "minerals");  
        //glm::vec3 center(center.x, center.y - 1*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //minerals_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::MINERALS, minerals_button));
    }
    
    {
        //ButtonSingle* food_button = new ButtonSingle(_texOb, GUI::BUTTON::FOOD, "food");  
        //glm::vec3 center(center.x, center.y - 2*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //food_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::FOOD, food_button));
    }
    
    {
        //ButtonSingle* medicine_button = new ButtonSingle(_texOb, GUI::BUTTON::MEDICINE, "medicine");  
        //glm::vec3 center(center.x, center.y - 3*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //medicine_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::MEDICINE, medicine_button));
    }
    
    {
        //ButtonSingle* military_button = new ButtonSingle(_texOb, GUI::BUTTON::MILITARY, "military");  
        //glm::vec3 center(center.x, center.y - 4*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //military_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::MILITARY, military_button));
    }
            
    {
        //ButtonSingle* drug_button = new ButtonSingle(_texOb, GUI::BUTTON::DRUG, "drug");  
        //glm::vec3 center(center.x, center.y - 5*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //drug_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DRUG, drug_button));  
    }
    
    {
        //ButtonSingle* exclusive_button = new ButtonSingle(_texOb, GUI::BUTTON::EXCLUSIVE, "exclusive");  
        //glm::vec3 center(center.x, center.y - 6*(GUI::ICON_SIZE + 5), zpos);
        //glm::vec3 size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);        
        //exclusive_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::EXCLUSIVE, exclusive_button));  
    }
}

GuiShop::~GuiShop()
{}

void GuiShop::bind(control::Shop* shop)
{
    m_shop = shop;
}

void GuiShop::release()
{
    m_shop = nullptr;
}
        
void GuiShop::UpdateLables() const
{   /*
    for (auto &gui_element : m_Child_vec)
    {    
        switch(gui_element->subTypeId())
        {
            case GUI::BUTTON::MINERALS:
            {
                        gui_element->SetLabel("mineral:" + std::to_string(shop->GetMineralsAmount()) + " price:" + std::to_string(shop->GetMineralsPrice()));
                        break;
                }
            
            case GUI::BUTTON::FOOD:
            {
                        gui_element->SetLabel("food:" + std::to_string(shop->GetFoodAmount()) + " price:" + std::to_string(shop->GetFoodPrice()));
                        break;
                }

            case GUI::BUTTON::MEDICINE:
            {
                        gui_element->SetLabel("medicine:" + std::to_string(shop->GetMedicineAmount()) + " price:" + std::to_string(shop->GetMedicinePrice()));
                        break;
                }

            case GUI::BUTTON::MILITARY:
            {
                        gui_element->SetLabel("military:" + std::to_string(shop->GetMilitaryAmount()) + " price:" + std::to_string(shop->GetMilitaryPrice()));
                        break;
                }

            case GUI::BUTTON::DRUG:
            {
                        gui_element->SetLabel("drug:" + std::to_string(shop->GetDrugAmount()) + " price:" + std::to_string(shop->GetDrugPrice()));
                        break;
                }
                
                case GUI::BUTTON::EXCLUSIVE:
            {
                        gui_element->SetLabel("exclusive:" + std::to_string(shop->GetExclusiveAmount()) + " price:" + std::to_string(shop->GetExclusivePrice()));
                        break;
                }
            }
        }  */
}
        
void GuiShop::ButtonsAction(Slider& slider)
{
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
        //BaseButton* button = iterator->second;
        //if (button->GetPressed() == true)
        //{
                   //slider.setSubTypeId(button->subTypeId());
                //switch(button->subTypeId())
                //{
                    //case GUI::BUTTON::MINERALS:         { slider.Configure(shop->GetMineralsAmount(), shop->GetMineralsPrice()); break; }
                    //case GUI::BUTTON::FOOD:         { slider.Configure(shop->GetFoodAmount(), shop->GetFoodPrice()); break; }
                    //case GUI::BUTTON::MEDICINE:         { slider.Configure(shop->GetMedicineAmount(), shop->GetMedicinePrice()); break; }
                    //case GUI::BUTTON::MILITARY:         { slider.Configure(shop->GetMilitaryAmount(), shop->GetMilitaryPrice()); break; }
                    //case GUI::BUTTON::DRUG:         { slider.Configure(shop->GetDrugAmount(), shop->GetDrugPrice()); break; }
                    //case GUI::BUTTON::EXCLUSIVE:     { slider.Configure(shop->GetExclusiveAmount(), shop->GetExclusivePrice()); break; }
                   //}                 
        //}
    //}
}    

} // namespace gui

