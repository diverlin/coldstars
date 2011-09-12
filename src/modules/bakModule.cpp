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


#include "bakModule.hpp"


BakModule :: BakModule(TextureOb* _texOb, int _fuel_max_add)
{
    	CommonForModules_init(BAK_ID, _texOb);

    	fuel_max_add = _fuel_max_add;
}

BakModule :: ~BakModule()
{}

int BakModule :: getFuelMaxAdd() const { return fuel_max_add; }
 	

void BakModule :: addUniqueInfo()
{
    	info.addTitleStr("bak module");
    	info.addNameStr("fuel_max_add:"); info.addValueStr( int2str(fuel_max_add) );
}



BakModule* bakModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);     	
    	int fuel_max_add = randIntInRange(BAK_MODULE_FUEL_MIN, BAK_MODULE_FUEL_MAX);
    	
    	BakModule* bak_module = new BakModule(texOb, fuel_max_add);
    	
    	return bak_module;
}
