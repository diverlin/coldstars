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


#include "commonforslot.h"

CommonForSlot :: CommonForSlot()
{}


void CommonForSlot :: CommonForSlot_init(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
     pTo_ship  = _pTo_ship; 

     pTo_texOb = _pTo_texOb;
     w = pTo_texOb->w;
     h = pTo_texOb->h;
     
     rect = Rect(_pos_x, _pos_y, w, h);         // create rect with size of the texture

     item_type_id    = -1;
     item_subtype_id = -1;
     
     is_EQUIPED       = false;
     is_FLASHING      = false;
     is_CURSORED      = false; 
}


bool CommonForSlot :: interaction(int _x, int _y)
{        
    float dist = lengthBetweenPoints(rect.center_x, rect.center_y, _x, _y);
    if (dist < rect.w/2)
        return true;
    else
        return false;    
}





