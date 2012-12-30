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

#include "GuiKosmoport.hpp"
#include "ButtonSingle.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../render/Screen.hpp"
#include "../common/constants.hpp"
#include "../pilots/Player.hpp"

GuiKosmoport::GuiKosmoport()
{
	int screen_w = Screen::Instance().GetWindow().GetWidth();
	int screen_h = Screen::Instance().GetWindow().GetHeight();
	
        TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake

    	ButtonSingle* angar_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::ANGAR_ID, "angar"); 
    	angar_screen_button->SetRect(Rect(screen_w - 1 * (GUI::ICON_SIZE + 5), 
    					  GUI::ICON_SIZE, 
    					  GUI::ICON_SIZE,  
    					  GUI::ICON_SIZE));   					     
    	button_map.insert(std::make_pair(GUI::BUTTON::ANGAR_ID, angar_screen_button));
    	
    	ButtonSingle* store_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::STORE_ID, "store");
    	store_screen_button->SetRect(Rect(screen_w - 2 * (GUI::ICON_SIZE + 5),
    					  GUI::ICON_SIZE, 
    					  GUI::ICON_SIZE,  
    					  GUI::ICON_SIZE));		     
    	button_map.insert(std::make_pair(GUI::BUTTON::STORE_ID, store_screen_button));
    					        	
    	ButtonSingle* shop_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::SHOP_ID, "shop");
    	shop_screen_button->SetRect(Rect(screen_w - 3 * (GUI::ICON_SIZE + 5), 
    					 GUI::ICON_SIZE, 
    					 GUI::ICON_SIZE,  
    					 GUI::ICON_SIZE));
    	button_map.insert(std::make_pair(GUI::BUTTON::SHOP_ID, shop_screen_button));
    					     
    	ButtonSingle* galaxymap_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GALAXYMAP_ID, "galaxymap");
   	galaxymap_screen_button->SetRect(Rect(screen_w - 4 * (GUI::ICON_SIZE + 5), 
    					      GUI::ICON_SIZE, 
    					      GUI::ICON_SIZE,  
    					      GUI::ICON_SIZE));
   	button_map.insert(std::make_pair(GUI::BUTTON::GALAXYMAP_ID, galaxymap_screen_button));
    					     
    	ButtonSingle* goverment_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GOVERMENT_ID, "goverment");
    	goverment_screen_button->SetRect(Rect(screen_w - 5 * (GUI::ICON_SIZE + 5), 
    					      GUI::ICON_SIZE,
    					      GUI::ICON_SIZE,  
    					      GUI::ICON_SIZE));
   	button_map.insert(std::make_pair(GUI::BUTTON::GOVERMENT_ID, goverment_screen_button));

	active_screen_id = GUI::SCREEN::ANGAR_ID;
}


GuiKosmoport::~GuiKosmoport()
{}
		
void GuiKosmoport::ButtonsAction()
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
		if (button->GetPressed() == true)
		{
			switch(button->GetSubTypeId())
	   		{
	   			case GUI::BUTTON::ANGAR_ID: 
	   			{
   				      	button->PressEvent();   
                                        player->GetGuiManager().ExitCurrentScreen();
   					active_screen_id = GUI::SCREEN::ANGAR_ID;
                                        player->GetGuiManager().EnterGuiAngarScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::STORE_ID: 
	   			{
   				      	button->PressEvent();
                                        player->GetGuiManager().ExitCurrentScreen();
                                        active_screen_id = GUI::SCREEN::STORE_ID;
                                        player->GetGuiManager().EnterGuiStoreScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::SHOP_ID: 
	   			{
   				      	button->PressEvent();
                                        player->GetGuiManager().ExitCurrentScreen();
   					active_screen_id = GUI::SCREEN::SHOP_ID;
                                        player->GetGuiManager().EnterGuiShopScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::GALAXYMAP_ID: 
	   			{
   				      	button->PressEvent();
                                        player->GetGuiManager().ExitCurrentScreen();                                                                                
   					active_screen_id = GUI::SCREEN::GALAXYMAP_ID;
                                        player->GetGuiManager().EnterGuiGalaxyMapScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::GOVERMENT_ID: 
	   			{
   				      	button->PressEvent();
                                        player->GetGuiManager().ExitCurrentScreen();
   					active_screen_id = GUI::SCREEN::GOVERMENT_ID;
                                        player->GetGuiManager().EnterGuiGovermentScreen();
                                        
   					return; break;
	  	 		}
	  	 	}
	  	 }
	  }
}

                
