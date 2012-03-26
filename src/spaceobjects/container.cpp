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



Container :: Container()
{
    	mass = 1;

    	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);
    	item_slot = new ItemSlot();
    	item_slot->SetSubTypeId(SLOT::CARGO);
    	item_slot->SetTextureOb(texOb_slot);
    	
    	velocity = getRandInt(40, 42) / 100.0;
}


Container :: ~Container()
{
	delete item_slot;
}


ItemSlot* Container :: getItemSlot() { return item_slot; }
        	
        	
void Container :: updateInfo()  
{}        	 
       	
void Container :: renderInfo_inSpace(vec2f scroll_coords)
{
	updateInfo();
     	item_slot->getRect().setCenter(points.getCenter());	
     	item_slot->renderItemInfo(scroll_coords.x, scroll_coords.y);
}
 
 /* virtual */    
void Container :: postDeathUniqueEvent(bool show_effect)
{
        if (item_slot->getItem()->getTypeId() == BOMB_ID)
        {
        	starsystem->bombExplosionEvent(this, show_effect);  
        }
        else
        {
        	if (show_effect == true)
        	{
        		createExplosion(starsystem, points.getCenter(), texOb->size_id);  
        	}
        }
}




Container* getNewContainer()
{
        IdData data_id;
        data_id.id = g_ID_GENERATOR.getNextId(); 
        data_id.type_id = ENTITY::CONTAINER;
        
        LifeData data_life;
        data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;
        
        vec3f d_angle;
        d_angle.z      = -getRandInt(10, 100)*0.01; 
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(CONTAINER_TEXTURE_ID); 
	
	Container* container = new Container();
	container->setIdData(data_id);
	container->setLifeData(data_life);
	container->setTextureOb(texOb);
	container->setDeltaAngle(d_angle);

	
	container->postCreateInit();
	
	return container;
}
