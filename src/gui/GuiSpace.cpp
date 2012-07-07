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
    	
    	Button* galaxymap_screen_button = new Button(g_GUI_TEXTUREOB_COLLECTOR.icon_map, 
        				     GUI::SCREEN::GALAXYMAP_ID,
    					     Screen::Instance().GetWindow().GetWidth() - (GUI::ICON_SIZE + 5),
    					     Screen::Instance().GetWindow().GetHeight() - (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "galaxy map");
    					     
    	button_vec.push_back(galaxymap_screen_button);
}


GuiSpace::~GuiSpace()
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
		delete button_vec[i];
	}
}

void GuiSpace::UpdateMouseInteraction(int mxvp, int myvp, int lmb, int rmb)
{
	for (unsigned int i = 0; i < button_vec.size(); i++)
     	{ 
        	if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
        	{
           		if (lmb == true)
           		{
           			if (button_vec[i]->GetSubTypeId() == GUI::SCREEN::GALAXYMAP_ID)
              			{
              				player->SetWorldMapShowFlag(!player->GetWorldMapShowFlag());
                 		}
           		}
        	}
     	}
}

void GuiSpace::RenderBar() const
{
	int screen_w = Screen::Instance().GetWindow().GetWidth();
	int screen_h = Screen::Instance().GetWindow().GetHeight();
	
	Rect rect1(0, 0, screen_w, GUI::BAR_HEIGHT);
	drawTexturedRect(g_GUI_TEXTUREOB_COLLECTOR.bar_bottom, rect1, -1.5);

	Rect rect2(0, screen_h, screen_w, -GUI::BAR_HEIGHT);
	drawTexturedRect(g_GUI_TEXTUREOB_COLLECTOR.bar_bottom, rect2, -1.5);
}

void GuiSpace::RenderButtons() const
{
	for (unsigned int i = 0; i < button_vec.size(); i++)
	{ 
		button_vec[i]->Render();
	}
}

void GuiSpace::RenderFocusedButtonInfo(int mxvp, int myvp) const
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
		if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
		{
			button_vec[i]->RenderInfo();
			break;
		}
	}       
}

void GuiSpace::RenderText(const vec2f& scroll_coords) const
{
	std::string _coord_str = "world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);

	sf::String _str(_coord_str, Screen::Instance().GetFont(), 12);
	_str.SetColor(sf::Color(255, 255, 255));
	_str.SetPosition(Screen::Instance().GetWindow().GetWidth() - 200, 5); 

	Screen::Instance().GetWindow().Draw(_str);    
}

