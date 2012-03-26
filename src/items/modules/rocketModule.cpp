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


RocketModule :: RocketModule(int ammo_max_add, 
                             int damage_add, 
                             int radius_add)
{
     	this->ammo_max_add = ammo_max_add;
     	this->damage_add   = damage_add;
     	this->radius_add   = radius_add;
}
       
RocketModule :: ~RocketModule() /* virtual */
{}


int RocketModule :: getAmmoMaxAdd() const { return ammo_max_add; }
int RocketModule :: getDamageAdd()  const { return damage_add; }
int RocketModule :: getRadiusAdd()  const { return radius_add; }
		

void RocketModule :: addUniqueInfo()
{
    	info.addTitleStr("rocket module"); 
    	if (ammo_max_add != 0)
    	{
    		info.addNameStr("ammo_max_add:");   info.addValueStr(int2str(ammo_max_add));
    	}
    	if (damage_add != 0)
    	{
    		info.addNameStr("damage_add:");     info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{
    		info.addNameStr("radius_add:");     info.addValueStr(int2str(radius_add));
    	} 
}


RocketModule* getNewRocketModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int ammo_max_add = getRandInt(ROCKET_MODULE_AMMO_MIN, ROCKET_MODULE_AMMO_MAX);
    	int damage_add = getRandInt(ROCKET_MODULE_DAMAGE_MIN, ROCKET_MODULE_DAMAGE_MAX);
    	int radius_add = getRandInt(ROCKET_MODULE_RADIUS_MIN, ROCKET_MODULE_RADIUS_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE;
        data_id.subtype_id = MODULE::ROCKET;  
        
    	RocketModule* rocket_module = new RocketModule(ammo_max_add, damage_add, radius_add);
        rocket_module->setTextureOb(texOb);
        rocket_module->setIdData(data_id);
                
    	return rocket_module;
}
