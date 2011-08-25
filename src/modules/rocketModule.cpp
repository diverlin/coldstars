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


#include "rocketModule.h"

RocketModule :: RocketModule(TextureOb* _pTo_texOb, int _ammo_max_add, int _damage_add, int _radius_add)
{
     	CommonForModules_init(ROCKET_ID, _pTo_texOb);

     	ammo_max_add = _ammo_max_add;
     	damage_add   = _damage_add;
     	radius_add   = _radius_add;
}
       
RocketModule :: ~RocketModule()
{}


int RocketModule :: getAmmoMaxAdd() const { return ammo_max_add; }
int RocketModule :: getDamageAdd()  const { return damage_add; }
int RocketModule :: getRadiusAdd()  const { return radius_add; }
		

void RocketModule :: updateInfo()
{
    	info_title_pList.clear();
    	info_value_pList.clear();

    	info_title_0 = "rocket module";
    	info_title_1 = "ammo_max_add:";   info_value_1 = int2str(ammo_max_add);
    	info_title_2 = "damage_add:";     info_value_2 = int2str(damage_add);
    	info_title_3 = "radius_add:";     info_value_3 = int2str(radius_add);
    	info_title_4 = "mass:";           info_value_4 = int2str(mass);


    	info_title_pList.push_back(&info_title_0);  
    	if (ammo_max_add != 0)
    	{
    		info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    	}
    	if (damage_add != 0)
    	{
        	info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    	}
    	if (radius_add != 0)
    	{
        	info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    	} 
    	info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
}


RocketModule* rocketModuleGenerator()
{
    	TextureOb* _texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    	int _ammo_max_add = randIntInRange(ROCKET_MODULE_AMMO_MIN, ROCKET_MODULE_AMMO_MAX);
    	int _damage_add = randIntInRange(ROCKET_MODULE_DAMAGE_MIN, ROCKET_MODULE_DAMAGE_MAX);
    	int _radius_add = randIntInRange(ROCKET_MODULE_RADIUS_MIN, ROCKET_MODULE_RADIUS_MAX);

    	RocketModule* _rocket_module = new RocketModule(_texOb, _ammo_max_add, _damage_add, _radius_add);
    	return _rocket_module;
}
