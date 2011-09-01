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


#include "container.h"

Container :: Container(TextureOb* _pTo_texOb, vec2f _start_pos)
{
    	CommonForSpaceItems_init(_pTo_texOb, _start_pos);
    
    	id = g_ENTITY_ID_GENERATOR.returnNextId(); 
    	type_id = CONTAINER_ID;

    	mass = 1;

    	TextureOb* pTo_slotTexOb   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);
    	otsec_slot = new ItemSlot(UNIVERSAL_SLOT_ID, NULL, pTo_slotTexOb, 0, 0);
     
    
    	armor = randIntInRange(1,6);

    	speed = randIntInRange(40, 42);
    	stepCalculation();

    	size = returnObjectSize(w, h);
}


Container :: ~Container()
{
	delete otsec_slot;
}


void Container :: renderInfo()
{
     	otsec_slot->getRect().setNewCenter(points.getCenter().x, points.getCenter().y);	
     	otsec_slot->renderItemInfo(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);
}

 


Container* createContainer(vec2f _start_pos)
{
	TextureOb* _containerTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.container_texOb_pList); 
	Container* _container = new Container(_containerTexOb, _start_pos);

	return _container;
}
