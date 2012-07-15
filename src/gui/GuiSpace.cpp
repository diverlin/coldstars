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

#include "GuiSpace.hpp"

GuiSpace::GuiSpace()
{   	
    	int screen_w = Screen::Instance().GetWindow().GetWidth();
    	int screen_h = Screen::Instance().GetWindow().GetHeight();
    	
    	ButtonTrigger* galaxymap_button = new ButtonTrigger(	g_GUI_TEXTUREOB_COLLECTOR.icon_map, 
        				     			GUI::BUTTON::GALAXYMAP_ID,
    					     			screen_w - (GUI::ICON_SIZE + 5),
    					     			screen_h - (GUI::ICON_SIZE + 5), 
    					     			GUI::ICON_SIZE,  
    					     			GUI::ICON_SIZE, 
    					     			"galaxy map");    					     
    	button_map.insert(std::make_pair(GUI::BUTTON::GALAXYMAP_ID, galaxymap_button));
	
       	textureOb_bar_top 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;
       	textureOb_bar_bottom 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;
       	textureOb_bar_radar 	= g_GUI_TEXTUREOB_COLLECTOR.bar_radar;

       	Resize(screen_w, screen_h);
       	
	int angle = 0;
	int subtype_id = GUI::BUTTON::WEAPON1_ACTIVATOR_ID;
	for (int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		vec2i pos = getVec2i(rect_bar_radar.GetWidth()/2.5, angle);
    		ButtonTrigger* button = new ButtonTrigger(	g_GUI_TEXTUREOB_COLLECTOR.dot_purple, 
        					subtype_id,
    						rect_bar_radar.GetCenter().x+pos.x-GUI::ICON_SIZE/2,
    						rect_bar_radar.GetCenter().y+pos.y-GUI::ICON_SIZE/2, 
    					     	GUI::ICON_SIZE*1.5,  
    					     	GUI::ICON_SIZE*1.5, 
    					     	"weapon_"+int2str(i+1));    					     
    		button_map.insert(std::make_pair(subtype_id, button));
    		
		angle += 20;
		subtype_id++;
    	}
}

/*virtual*/
GuiSpace::~GuiSpace()
{}

void GuiSpace::ButtonsAction(Player* player) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
       		switch(button->GetSubTypeId())
       		{
       			case GUI::BUTTON::GALAXYMAP_ID:   
       			{ 
       				player->GetControlFlags().SetShowGalaxyMapFlag(button->GetPressed()); 
       				break; 
       			}
        		
        		case GUI::BUTTON::WEAPON1_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(1, button->GetPressed()); break; }
        		case GUI::BUTTON::WEAPON2_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(2, button->GetPressed()); break; }      		
        		case GUI::BUTTON::WEAPON3_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(3, button->GetPressed()); break; }     
          		case GUI::BUTTON::WEAPON4_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(4, button->GetPressed()); break; }     
        		case GUI::BUTTON::WEAPON5_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(5, button->GetPressed()); break; }         		           		   	      	
                	case GUI::BUTTON::WEAPON6_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(6, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON7_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(7, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON8_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(8, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON9_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(9, button->GetPressed()); break; }     
		}
	}
	
	UpdateEquipmentIcons(player);
}

void GuiSpace::Resize(int screen_w, int screen_h)
{
	rect_bar_bottom.Set(0, 0, screen_w, GUI::BAR_HEIGHT);
	rect_bar_top.Set(0, screen_h, screen_w, -GUI::BAR_HEIGHT);
	rect_bar_radar.Set(0, 0, 250, 250);
}

void GuiSpace::UpdateEquipmentIcons(Player* player) const
{
       	WeaponComplex* weapon_complex = player->GetNpc()->GetVehicle()->GetWeaponComplex();
       	GetButton(GUI::BUTTON::WEAPON1_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(1));
       	GetButton(GUI::BUTTON::WEAPON2_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(2));
       	GetButton(GUI::BUTTON::WEAPON3_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(3));
       	GetButton(GUI::BUTTON::WEAPON4_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(4));
       	GetButton(GUI::BUTTON::WEAPON5_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(5));
       	GetButton(GUI::BUTTON::WEAPON6_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(6));
       	GetButton(GUI::BUTTON::WEAPON7_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(7));       	       	       	
       	GetButton(GUI::BUTTON::WEAPON8_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(8)); 
       	GetButton(GUI::BUTTON::WEAPON9_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(9)); 
}

void GuiSpace::RenderBar() const
{	
	drawTexturedRect(textureOb_bar_bottom, rect_bar_bottom, -1.5);
	drawTexturedRect(textureOb_bar_top, rect_bar_top, -1.5);
	drawTexturedRect(textureOb_bar_radar, rect_bar_radar, -1.5);
}


void GuiSpace::RenderText(const vec2f& scroll_coords) const
{
	std::string _coord_str = "world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);

	sf::String _str(_coord_str, Screen::Instance().GetFont(), 12);
	_str.SetColor(sf::Color(255, 255, 255));
	_str.SetPosition(Screen::Instance().GetWindow().GetWidth() - 200, 5); 

	Screen::Instance().GetWindow().Draw(_str);    
}

