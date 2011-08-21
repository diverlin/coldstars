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


#ifndef COMMONFOREQUIPMENT_H
#define COMMONFOREQUIPMENT_H


class CommonForEquipment
{
        public:
                int type_id, subtype_id;

     ItemSlot* slot;
     bool update_info_request;

     VEC_pString_type info_title_pList;  
     VEC_pString_type info_value_pList;  

     TextureOb* pTo_itemTexOb;

     VEC_pTexOb_type texOb_modules_pList;    // needs for inserted modules drawing

     int w, h;
          
     bool in_SPACE;                 // this flag is needed for grap function to check if the item was already collected or not
     bool is_DAMAGED;

     int id;

     int race_id;
     int mass;
     int modules_num_max;

     int condition_max;
     int condition;

     int deterioration_rate;

     int price;

     CommonForEquipment();
     
     void bindSlot(ItemSlot* _slot);
     void CommonForEquipment_init(TextureOb* _pTo_itemTexOb, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
     void deterioration();
     void repair();

     void render(Rect slot_rect);
          void (CommonForEquipment::*pToFunc_render)(Rect slot_rect);
          void _renderFrame(Rect slot_rect);
          void _renderFrames(Rect slot_rect);
     void renderInfo(Rect slot_rect); 
};

#endif 
