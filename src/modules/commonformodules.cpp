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


#include "commonformodules.hpp"


CommonForModules :: CommonForModules()
{}

void CommonForModules :: CommonForModules_init(int _subtype_id, TextureOb* _texOb)
{
     	id = g_MODULE_ID_GENERATOR.getNextId(); 
     	type_id = MODULE_ID;
     	subtype_id = _subtype_id;
     	
     	texOb = _texOb;

     	w = texOb->w;
     	h = texOb->h;
         
     	mass = 1;
}


CommonForModules :: ~CommonForModules ()
{}


unsigned int CommonForModules :: getId()      const { return id; }
unsigned int CommonForModules :: getTypeId()    const { return type_id; }
unsigned int CommonForModules :: getSubTypeId() const { return subtype_id; }
unsigned int CommonForModules :: getMass()    const { return mass; }
TextureOb* CommonForModules :: getTexOb()     const { return texOb; }
      		

// not relevant for this cals but is needed for interface
int CommonForModules :: getFunctionalSlotSubTypeId() { return NONE_SLOT_ID; }
void CommonForModules :: bindSlot(ItemSlot* _slot)   { /* do nothing*/ }
void CommonForModules :: updateOwnerPropetries()     { /* do nothing*/ } 
//
      		

void CommonForModules :: updateInfo()
{
	info.clear();

	addUniqueInfo();
    	addCommonInfo();
}

void CommonForModules :: addUniqueInfo() { /* virtual */ }
 		
void CommonForModules :: addCommonInfo()
{
    	//info.addNameStr("modules:");   info.addValueStr( int2str(common_data.modules_num_max) );
    	//info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	//info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(common_data.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(mass) );
    	//info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

void CommonForModules :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
{  
	updateInfo();
        drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}



void CommonForModules :: render(Rect slot_rect)
{
        drawTexturedRect(texOb, slot_rect, -1);   
}


