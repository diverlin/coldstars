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


Goverment :: Goverment(TextureOb* _pTo_bg_texOb, TextureOb* _pTo_face_texOb)
{
    pTo_bg_texOb   = _pTo_bg_texOb;
    pTo_face_texOb = _pTo_face_texOb;   
}

void Goverment :: linkTexture()
{
    //background_tex = pTo_bg_texOb->texture
}

void Goverment :: unlinkTexture()
{
     //background_tex = -1; ???
}



void Goverment :: renderBackground()
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(pTo_bg_texOb->texture, screen_rect, -1);  
}

void Goverment :: renderInternals()
{
}
            
void Goverment :: render()
{
     renderBackground();
     renderInternals();
}

