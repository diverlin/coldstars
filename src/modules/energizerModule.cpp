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


#include "energizerModule.h"

EnergizerModule :: EnergizerModule(TextureOb* pTo_texOb, int _energy_max_add, int _restoration_add)
{
     	CommonForModules_init(ENERGIZER_ID, pTo_texOb);

     	energy_max_add  = _energy_max_add;
     	restoration_add = _restoration_add;
}


int EnergizerModule :: getEnergyMaxAdd()   const { return energy_max_add; }
int EnergizerModule :: getRestorationAdd() const { return restoration_add; }
		
void EnergizerModule :: updateInfo()
{
	info.clear();

    	info.addTitleStr("energizer module");
    	if (energy_max_add != 0)
    	{ 
    		info.addNameStr("energy_max_add:");  info.addValueStr( int2str(energy_max_add) );
    	}
    	if (restoration_add != 0)
    	{
    		info.addNameStr("restoration_add:"); info.addValueStr( int2str(restoration_add) );
    	} 
    	info.addNameStr("mass:");         info.addValueStr(int2str(mass));

}


EnergizerModule* energizerModuleGenerator()
{
     	TextureOb* _texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
     	int _energy_max_add  = randIntInRange(ENERGIZER_MODULE_ENERGY_MIN, ENERGIZER_MODULE_ENERGY_MAX);
     	int _restoration_add = randIntInRange(ENERGIZER_MODULE_RESTORATION_MIN, ENERGIZER_MODULE_RESTORATION_MAX);
     	
     	EnergizerModule* _energizer_module = new EnergizerModule(_texOb, _energy_max_add, _restoration_add);


	return _energizer_module; 
}
