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


#ifndef BAKSLOT_H
#define BAKSLOT_H


class BakSlot : public CommonForSlot
{   
    public:
       BakItem*         pTo_bakItem;

       BakSlot();
       BakSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y);

       void insertBakItem(BakItem* pTo_item);
       void removeBakItem();

       void renderFrame(GLuint flash_tex);
       void renderFrames(GLuint flash_tex);

       void renderItemInfo();
}; 

#endif
