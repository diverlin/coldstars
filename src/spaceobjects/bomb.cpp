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



Bomb :: Bomb(IdData _data_id, LifeData _data_life, TextureOb* _texOb)
{        
    	CommonForSpaceItems_init(_data_id, _data_life, _texOb);

    	mass = getRandInt(1, 4);
    	velocity = getRandInt(40, 42) / 100.0;
    	
    	damage = 300;
    	radius = 300;
}

Bomb :: ~Bomb() {}
    
    
    
int Bomb :: getFunctionalSlotSubTypeId() const { return NONE_SLOT_ID; }
TextureOb* Bomb :: getTexOb() const { return texOb; }

int Bomb :: getDamage() const { return damage; }
int Bomb :: getRadius() const { return radius; }
        	
void Bomb :: bindSlot(ItemSlot* slot) {}

void Bomb :: updateOwnerPropetries() {}
		
void Bomb :: updateInfo()
{
	info.clear();

    	info.addTitleStr("BOMB");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("damage:");          info.addValueStr(int2str(damage));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void Bomb :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}

void Bomb :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}



Bomb* getNewBomb()
{
        IdData data_id;
        data_id.id         = g_BOMB_ID_GENERATOR.getNextId();
    	data_id.type_id    = BOMB_ID;
    	//data_id.subtype_id = ; 
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = getRandInt(1,6);
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(BOMB_TEXTURE_ID); 
	Bomb* bomb = new Bomb(data_id, data_life, texOb);

	return bomb;
}




