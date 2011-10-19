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


#include "rocketModule.hpp"

RocketModule :: RocketModule(TextureOb* _texOb, int _ammo_max_add, int _damage_add, int _radius_add)
{
     	CommonForModules_init(ROCKET_ID, _texOb);

     	ammo_max_add = _ammo_max_add;
     	damage_add   = _damage_add;
     	radius_add   = _radius_add;
}
       
RocketModule :: ~RocketModule()
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


RocketModule* rocketModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int ammo_max_add = getRandInt(ROCKET_MODULE_AMMO_MIN, ROCKET_MODULE_AMMO_MAX);
    	int damage_add = getRandInt(ROCKET_MODULE_DAMAGE_MIN, ROCKET_MODULE_DAMAGE_MAX);
    	int radius_add = getRandInt(ROCKET_MODULE_RADIUS_MIN, ROCKET_MODULE_RADIUS_MAX);

    	RocketModule* rocket_module = new RocketModule(texOb, ammo_max_add, damage_add, radius_add);    	
    	return rocket_module;
}
