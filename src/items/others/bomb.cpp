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
void Bomb :: UpdateOwnerAbilities() {} 
		

       
/* virtual */	     
void Bomb::AddCommonInfo()
{
    	info.addNameStr("mass:");        info.addValueStr(int2str(data_item.mass));
}

/* virtual */	
void Bomb::AddUniqueInfo()
{
    	info.addTitleStr("BOMB");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("damage:");      info.addValueStr(int2str(damage));
    	//info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
} 		

/*virtual*/
void Bomb::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void Bomb::LoadData(boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void Bomb::ResolveData()
{

}


Bomb* getNewBomb()
{
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId();
    	data_id.type_id    = ENTITY::BOMB_ID;
    	//data_id.subtype_id = ;   
        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::BOMB_ID); 
	
	Bomb* bomb = new Bomb();
	bomb->SetIdData(data_id);
	bomb->SetTextureOb(texOb);
	bomb->SetFunctionalSlotSubTypeId(SLOT::CARGO_ID);
	
	return bomb;
}




