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


#ifndef RESOURCES_H
#define RESOURCES_H


class GuiTextureObCollector
{
	public:
		TextureOb* starsystem_mark_enemy;	
		TextureOb* starsystem_mark_player;
	
		TextureOb* icon_minus;
		TextureOb* icon_plus;
		TextureOb* skill;	
		TextureOb* skill_transparent;	
	
		TextureOb* icon_map;
        	TextureOb* grapple_trail;	

        	TextureOb* dot_blue;
        	TextureOb* dot_red;
        	TextureOb* dot_green;
        	TextureOb* dot_black;
        	TextureOb* dot_yellow;
        	TextureOb* dot_purple;

		TextureOb* screenrect;
        	TextureOb* background_radar;                
        	TextureOb* bar_radar;
        	TextureOb* bar_bottom;
        	TextureOb* bar_left;
        	TextureOb* bar_top;
        	TextureOb* bar_right;        
        
        	TextureOb* text_background;

        	TextureOb* slot_mark_accept;
        	TextureOb* slot_mark_reject;
        	
        	static GuiTextureObCollector& Instance();
        	
        private:
        	GuiTextureObCollector() {};
        	~GuiTextureObCollector() {};
        	
        	GuiTextureObCollector(const GuiTextureObCollector&) = delete;
        	GuiTextureObCollector& operator=(const GuiTextureObCollector&) = delete;
};

void loadGameData();

void load3DModels();
void loadShaders();
void loadImages();

#endif
