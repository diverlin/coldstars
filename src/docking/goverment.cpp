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


#include "goverment.hpp"


Goverment :: Goverment(TextureOb* _texOb_background, TextureOb* _texOb_face)
{
        texOb_background   = _texOb_background;
        texOb_face         = _texOb_face;   
}


void Goverment :: update()
{}


void Goverment :: renderBackground(Player* player) const
{
     	Rect screen_rect = Rect(0, 0, player->getScreen()->getWidth(), player->getScreen()->getHeight());
     	drawTexturedRect(texOb_background, screen_rect, -1);  
}

void Goverment :: renderInternals() const
{}
            
void Goverment :: Render(Player* player) const
{
        clearScreen();
        resetRenderTransformation();
                                                        
        renderBackground(player);
        renderInternals();
}

