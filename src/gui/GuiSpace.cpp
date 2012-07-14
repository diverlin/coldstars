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

GuiSpace::GuiSpace(Player* player)
{
	this->player = player;
    	
    	int screen_w = Screen::Instance().GetWindow().GetWidth();
    	int screen_h = Screen::Instance().GetWindow().GetHeight();
    	
    	Button* galaxymap_screen_button = new Button(	g_GUI_TEXTUREOB_COLLECTOR.icon_map, 
        				     		GUI::SCREEN::GALAXYMAP_ID,
    					     		screen_w - (GUI::ICON_SIZE + 5),
    					     		screen_h - (GUI::ICON_SIZE + 5), 
    					     		GUI::ICON_SIZE,  
    					     		GUI::ICON_SIZE, 
    					     		"galaxy map");    					     
    	button_vec.push_back(galaxymap_screen_button);
	
       	textureOb_bar_top 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;
       	textureOb_bar_bottom 	= g_GUI_TEXTUREOB_COLLECTOR.bar_bottom;
       	textureOb_bar_radar 	= g_GUI_TEXTUREOB_COLLECTOR.bar_radar;

       	Resize(screen_w, screen_h);
       	
	int angle = 0;
	int subtype_id = GUI::BUTTON::WEAPON1_ACTIVATOR_ID;
	for (int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		vec2i pos = getVec2i(rect_bar_radar.GetWidth()/2.5, angle);
    		Button* button = new Button(	g_GUI_TEXTUREOB_COLLECTOR.dot_purple, 
        					subtype_id,
    						rect_bar_radar.GetCenter().x+pos.x-GUI::ICON_SIZE/2,
    						rect_bar_radar.GetCenter().y+pos.y-GUI::ICON_SIZE/2, 
    					     	GUI::ICON_SIZE,  
    					     	GUI::ICON_SIZE, 
    					     	"weapon_"+int2str(i+1));    					     
    		button_vec.push_back(button);
    		
		angle += 20;
		subtype_id++;
    	}
}


GuiSpace::~GuiSpace()
{}

void GuiSpace::Resize(int screen_w, int screen_h)
{
	rect_bar_bottom.Set(0, 0, screen_w, GUI::BAR_HEIGHT);
	rect_bar_top.Set(0, screen_h, screen_w, -GUI::BAR_HEIGHT);
	rect_bar_radar.Set(0, 0, 250, 250);
}

bool GuiSpace::UpdateMouseInteraction(int mxvp, int myvp, int lmb, int rmb)
{
	for (unsigned int i=0; i<button_vec.size(); i++)
     	{ 
        	if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
        	{
           		if (lmb == true)
           		{
           			if (button_vec[i]->GetSubTypeId() == GUI::SCREEN::GALAXYMAP_ID)
              			{
              				button_vec[i]->TriggerEvent();
                 		}
           		}
           		return true;
        	}
     	}
     	
     	return false;
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

