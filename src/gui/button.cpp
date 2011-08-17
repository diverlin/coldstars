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


#include "button.h"

Button :: Button(TextureOb* _pTo_texOb, float _pos_x, float _pos_y, int _w, int _h, std::string _info_str)
{
    pTo_texOb = _pTo_texOb;
    rect = Rect(_pos_x, _pos_y, _w, _h);
    info_str = _info_str; 
    show_info = false; 
}

Button :: ~Button()
{}


bool Button :: interaction(int _x, int _y)
{        
    float dist = lengthBetweenPoints(rect.center_x, rect.center_y, _x, _y);
    if (dist < rect.w/2)
        return true;
    else
        return false;    
}
    
void Button :: setCenter(int _x, int _y)
{        
     rect.setNewCenter((float)_x, (float)_y);
}
   
void Button :: render()
{
   drawTexturedRect(pTo_texOb->texture, rect, -1);
}

void Button :: renderInfo()
{
     drawSimpleText(info_str, 12, rect.bottomLeft_x - 50, rect.bottomLeft_y + 30);
}
