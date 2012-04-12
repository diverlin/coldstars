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


#include "Goverment.hpp"


Goverment::Goverment(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::GOVERMENT_ID;
	data_id.subtype_id = NONE_ID;
			
        textureOb_background   = NULL;
        textureOb_face         = NULL;   
}

Goverment::~Goverment()
{}

void Goverment::Update()
{}

void Goverment::RenderBackground(Player* player) const
{
     	Rect screen_rect = Rect(0, 0, player->GetScreen()->getWidth(), player->GetScreen()->getHeight());
     	drawTexturedRect(textureOb_background, screen_rect, -1);  
}

void Goverment::RenderInternals() const
{}
            
void Goverment::Render(Player* player) const
{
        clearScreen();
        resetRenderTransformation();
                                                        
        RenderBackground(player);
        RenderInternals();
}

