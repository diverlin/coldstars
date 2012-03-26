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

#include "guiSpace.hpp"

GuiSpace :: GuiSpace(Player* player)
{
	this->player = player;

	TextureOb* texOb_icon_map = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_map;

	galaxymap_screen_button = new Button(texOb_icon_map, 
			SCREEN_GALAXYMAP_ID,
			SCREEN_WIDTH_MIN  - (INTERFACE_ICON_SIZE + 5),
			SCREEN_HEIGHT_MIN - (INTERFACE_ICON_SIZE + 5), 
			INTERFACE_ICON_SIZE,  
			INTERFACE_ICON_SIZE, 
			"galaxy map");

	button_vec.push_back(galaxymap_screen_button);
}


GuiSpace :: ~GuiSpace()
{}


void GuiSpace :: update()
{
	resetInfoFlags();
	mouseInteraction();
}


void GuiSpace :: resetInfoFlags()
{
	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
		button_vec[i]->setShowInfoFlag(false);
	}
}


void GuiSpace :: mouseInteraction()
{
	int mxvp = player->getCursor()->getMousePos().x;
	int myvp = player->getScreen()->getHeight() - player->getCursor()->getMousePos().y;         
	int lmb  = player->getCursor()->getMouseLeftButton();

	for (unsigned int i = 0; i < button_vec.size(); i++)
	{ 
		if (button_vec[i]->interaction(mxvp, myvp) == true)
		{
			if (lmb == true)
			{
				if (button_vec[i]->getSubTypeId() == SCREEN_GALAXYMAP_ID)
				{
					player->setWorldMapShowFlag(!player->getWorldMapShowFlag());
				}
			}
		}
	}
}


void GuiSpace :: render()
{
	resetRenderTransformation();

	enable_BLEND();    						
	renderInternal();
	renderInfo();
	disable_BLEND();

	renderText(player->getScreen()->getBottomLeftGlobalCoord());
}


void GuiSpace :: renderInternal() const
{
	for (unsigned int i = 0; i < button_vec.size(); i++)
	{ 
		button_vec[i]->render();
	}
}

void GuiSpace :: renderInfo() const
{

	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
		if (button_vec[i]->getShowInfoFlag() == true)
		{
			button_vec[i]->renderInfo();
			break;
		}
	}       
}

void GuiSpace :: renderText(vec2f scroll_coords) const
{
	std::string _coord_str = "world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);

	sf::String _str(_coord_str, Gui::GetFont(), 14);
	_str.SetColor(sf::Color(255, 255, 255));
	_str.SetPosition(SCREEN_WIDTH_MIN - 200, 15); 

	Gui::GetWindow().Draw(_str);    
}

