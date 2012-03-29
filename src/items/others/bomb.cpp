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



Bomb :: Bomb()
{ 
        damage = 300;
    	radius = 300;
}

 /* virtual */
Bomb :: ~Bomb() {}
    

int Bomb :: getDamage() const { return damage; }
int Bomb :: getRadius() const { return radius; }
        
/* virtual */	
void Bomb :: updateOwnerAbilities() {} 
		

       
/* virtual */	     
void Bomb::addCommonInfo()
{
    	info.addNameStr("mass:");        info.addValueStr(int2str(data_item.mass));
}

/* virtual */	
void Bomb::addUniqueInfo()
{
    	info.addTitleStr("BOMB");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("damage:");      info.addValueStr(int2str(damage));
    	//info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
} 		


Bomb* getNewBomb()
{
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId();
    	data_id.type_id    = ENTITY::BOMB_ID;
    	//data_id.subtype_id = ;   
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::BOMB_ID); 
	
	Bomb* bomb = new Bomb();
	bomb->setIdData(data_id);
	bomb->setTextureOb(texOb);
	bomb->setFunctionalSlotSubTypeId(SLOT::CARGO_ID);
	
	return bomb;
}




