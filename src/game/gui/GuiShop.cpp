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
#include "../docking/Shop.hpp"

#include "../common/rect.hpp"
#include "../gui/Cursor.hpp"
#include "../render/Screen.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../gui/ButtonSingle.hpp"
#include "../common/myStr.hpp"
#include "../common/constants.hpp"

GuiShop::GuiShop():shop(nullptr)
{
	Vec2<float> center(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2);
			
	TextureOb* _texOb = GuiTextureObCollector::Instance().text_background; 
	
	float zpos = -1;
	float zsize = 1;
	{
		//ButtonSingle* minerals_button = new ButtonSingle(_texOb, GUI::BUTTON::MINERALS_ID, "minerals");  
		//Vec3<float> center(center.x, center.y - 1*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//minerals_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::MINERALS_ID, minerals_button));
	}
	
	{
		//ButtonSingle* food_button = new ButtonSingle(_texOb, GUI::BUTTON::FOOD_ID, "food");  
		//Vec3<float> center(center.x, center.y - 2*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//food_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::FOOD_ID, food_button));
	}
	
	{
		//ButtonSingle* medicine_button = new ButtonSingle(_texOb, GUI::BUTTON::MEDICINE_ID, "medicine");  
		//Vec3<float> center(center.x, center.y - 3*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//medicine_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::MEDICINE_ID, medicine_button));
	}
	
	{
		//ButtonSingle* military_button = new ButtonSingle(_texOb, GUI::BUTTON::MILITARY_ID, "military");  
		//Vec3<float> center(center.x, center.y - 4*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//military_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::MILITARY_ID, military_button));
	}
			
	{
		//ButtonSingle* drug_button = new ButtonSingle(_texOb, GUI::BUTTON::DRUG_ID, "drug");  
		//Vec3<float> center(center.x, center.y - 5*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//drug_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::DRUG_ID, drug_button));  
	}
	
	{
		//ButtonSingle* exclusive_button = new ButtonSingle(_texOb, GUI::BUTTON::EXCLUSIVE_ID, "exclusive");  
		//Vec3<float> center(center.x, center.y - 6*(GUI::ICON_SIZE + 5), zpos);
		//Vec3<float> size(10*GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//exclusive_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::EXCLUSIVE_ID, exclusive_button));  
	}
}

GuiShop::~GuiShop()
{}

void GuiShop::BindShop(Shop* shop)
{
        this->shop = shop;
}

void GuiShop::UnbindShop()
{
        shop = nullptr;
}
        
void GuiShop::UpdateLables() const
{   /*
	for (auto &gui_element : m_Child_vec)
	{	
		switch(gui_element->GetSubTypeId())
		{
			case GUI::BUTTON::MINERALS_ID:
			{
	                	gui_element->SetLabel("mineral:" + int2str(shop->GetMineralsAmount()) + " price:" + int2str(shop->GetMineralsPrice()));	                
	                	break;
        		}
        	
			case GUI::BUTTON::FOOD_ID:
			{
	                	gui_element->SetLabel("food:" + int2str(shop->GetFoodAmount()) + " price:" + int2str(shop->GetFoodPrice()));	                
	                	break;
        		}

			case GUI::BUTTON::MEDICINE_ID:
			{
	                	gui_element->SetLabel("medicine:" + int2str(shop->GetMedicineAmount()) + " price:" + int2str(shop->GetMedicinePrice()));	                
	                	break;
        		}

			case GUI::BUTTON::MILITARY_ID:
			{
	                	gui_element->SetLabel("military:" + int2str(shop->GetMilitaryAmount()) + " price:" + int2str(shop->GetMilitaryPrice()));	                
	                	break;
        		}

			case GUI::BUTTON::DRUG_ID:
			{
	                	gui_element->SetLabel("drug:" + int2str(shop->GetDrugAmount()) + " price:" + int2str(shop->GetDrugPrice()));	                
	                	break;
        		}
        		
        		case GUI::BUTTON::EXCLUSIVE_ID:
			{
	                	gui_element->SetLabel("exclusive:" + int2str(shop->GetExclusiveAmount()) + " price:" + int2str(shop->GetExclusivePrice()));	                
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
		       	//slider.SetSubTypeId(button->GetSubTypeId());
        		//switch(button->GetSubTypeId())
        		//{
        			//case GUI::BUTTON::MINERALS_ID: 		{ slider.Configure(shop->GetMineralsAmount(), shop->GetMineralsPrice()); break; }
        			//case GUI::BUTTON::FOOD_ID: 		{ slider.Configure(shop->GetFoodAmount(), shop->GetFoodPrice()); break; }
        			//case GUI::BUTTON::MEDICINE_ID: 		{ slider.Configure(shop->GetMedicineAmount(), shop->GetMedicinePrice()); break; }
        			//case GUI::BUTTON::MILITARY_ID: 		{ slider.Configure(shop->GetMilitaryAmount(), shop->GetMilitaryPrice()); break; }
        			//case GUI::BUTTON::DRUG_ID: 		{ slider.Configure(shop->GetDrugAmount(), shop->GetDrugPrice()); break; }
        			//case GUI::BUTTON::EXCLUSIVE_ID: 	{ slider.Configure(shop->GetExclusiveAmount(), shop->GetExclusivePrice()); break; }
           		//}  		   	
		//}
	//}
}	

