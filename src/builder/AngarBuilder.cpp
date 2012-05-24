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

#include "AngarBuilder.hpp"

AngarBuilder& AngarBuilder::Instance()
{
	static AngarBuilder instance;
	return instance;
}

AngarBuilder::~AngarBuilder()
{}

void AngarBuilder::CreateNewAngar(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        angar = new Angar(id);
        EntityManager::Instance().RegisterEntity(angar);
} 
        	
void AngarBuilder::CreateNewInternals()
{
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;	
	
	TextureOb* texOb_platform = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::LANDINGAREA_ID);
 	
        angar->AddPlatform(new Platform(texOb_platform, screen_w/2,       screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR));
        angar->AddPlatform(new Platform(texOb_platform, screen_w/2 + 150, screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR));
        angar->AddPlatform(new Platform(texOb_platform, screen_w/2 - 150, screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR));
        angar->AddPlatform(new Platform(texOb_platform, screen_w/2,       screen_h/2 + 150, GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR));
	angar->AddPlatform(new Platform(texOb_platform, screen_w/2,       screen_h/2 - 150, GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR));
		
	TextureOb* texOb_bg  = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::ANGAR_BACKGROUND_ID); 
	angar->SetTextureObBackground(texOb_bg);
}

  	
