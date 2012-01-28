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



Container :: Container(IdData _data_id, LifeData _data_life, TextureOb* _texOb)
{
    	CommonForSpaceItems_init(_data_id, _data_life, _texOb);
        
    	mass = 1;

    	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);
    	item_slot = new ItemSlot(CARGO_SLOT_ID, NULL, texOb_slot, 0, 0, 0, 0);
    	
    	velocity = getRandInt(40, 42) / 100.0;
}


Container :: ~Container()
{
	delete item_slot;
}


ItemSlot* Container :: getItemSlot() { return item_slot; }
        	
void Container :: renderInfo()
{
	//printf("id = %i\n", data_id.id);
     	item_slot->getRect().setNewCenter(points.getCenter());	
     	item_slot->renderItemInfo(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);
}

 


Container* createContainer()
{
        IdData data_id;
        data_id.id = g_CONTAINER_ID_GENERATOR.getNextId(); 
        data_id.type_id = CONTAINER_ID;
        
        LifeData data_life;
        data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;
        
        
	TextureOb* texOb_container = g_TEXTURE_MANAGER.getRandomTexOb(CONTAINER_TEXTURE_ID); 
	Container* container = new Container(data_id, data_life, texOb_container);
	
	return container;
}
