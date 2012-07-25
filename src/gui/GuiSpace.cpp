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

    	ButtonSingle* load_button = new ButtonSingle(	g_GUI_TEXTUREOB_COLLECTOR.icon_plus, 
        				     			GUI::BUTTON::LOAD_ID,
    					     			screen_w - 2*(GUI::ICON_SIZE + 5),
    					     			screen_h - (GUI::ICON_SIZE + 5), 
    					     			GUI::ICON_SIZE,  
    					     			GUI::ICON_SIZE, 
    					     			"load");    					     
    	button_map.insert(std::make_pair(GUI::BUTTON::LOAD_ID, load_button));
    	
    	ButtonSingle* save_button = new ButtonSingle(	g_GUI_TEXTUREOB_COLLECTOR.icon_minus, 
        				     			GUI::BUTTON::SAVE_ID,
    					     			screen_w - 3*(GUI::ICON_SIZE + 5),
    					     			screen_h - (GUI::ICON_SIZE + 5), 
    					     			GUI::ICON_SIZE,  
    					     			GUI::ICON_SIZE, 
    					     			"save");    					     
    	button_map.insert(std::make_pair(GUI::BUTTON::SAVE_ID, save_button));
    	    		
       	textureOb_bar_top 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;
       	textureOb_bar_bottom 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;

       	Resize(screen_w, screen_h);
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

     			case GUI::BUTTON::SAVE_ID:   
       			{
       				if (button->GetPressed() == true) 
       				{
       					std::cout<<"save"<<std::endl; 
       					break;
       				} 
       			}   

     			case GUI::BUTTON::LOAD_ID:   
       			{ 
       			       	if (button->GetPressed() == true) 
       				{
       					std::cout<<"load"<<std::endl; 
       					break;
       				} 
       			}   
       		}
	}
}

void GuiSpace::Resize(int screen_w, int screen_h)
{
	rect_bar_bottom.Set(0, 0, screen_w, GUI::BAR_HEIGHT);
	rect_bar_top.Set(0, screen_h, screen_w, -GUI::BAR_HEIGHT);
}


void GuiSpace::RenderBar() const
{	
	drawTexturedRect(textureOb_bar_bottom, rect_bar_bottom, -1.5);
	drawTexturedRect(textureOb_bar_top, rect_bar_top, -1.5);
}


void GuiSpace::RenderText(const vec2f& scroll_coords) const
{
	std::string _coord_str = "world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);

	sf::String _str(_coord_str, Screen::Instance().GetFont(), 12);
	_str.SetColor(sf::Color(255, 255, 255));
	_str.SetPosition(Screen::Instance().GetWindow().GetWidth() - 200, 5); 

	Screen::Instance().GetWindow().Draw(_str);    
}

