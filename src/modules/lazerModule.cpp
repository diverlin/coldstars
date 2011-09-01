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


#include "lazerModule.h"

LazerModule :: LazerModule(TextureOb* _pTo_texOb, int _damage_add, int _radius_add)
{
     	CommonForModules_init(LAZER_ID, _pTo_texOb);

     	damage_add = _damage_add;
     	radius_add = _radius_add;
}


LazerModule :: ~LazerModule()
{}


int LazerModule :: getDamageAdd() const { return damage_add; }
int LazerModule :: getRadiusAdd() const { return radius_add; }


void LazerModule :: updateInfo()
{
	info.clear();

    	info.addTitleStr("lazer module");
    	if (damage_add != 0) 
    	{
    		info.addNameStr("damage_add:");   info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
    	}
    	info.addNameStr("mass:");         info.addValueStr(int2str(mass));
}


LazerModule* lazerModuleGenerator()
{
    	TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int _damage_add = randIntInRange(LAZER_MODULE_DAMAGE_MIN, LAZER_MODULE_DAMAGE_MAX);
    	int _radius_add = randIntInRange(LAZER_MODULE_RADIUS_MIN, LAZER_MODULE_RADIUS_MAX);

    	LazerModule* _lazer_module = new LazerModule(pTo_texOb, _damage_add, _radius_add);
    	return _lazer_module;
}
