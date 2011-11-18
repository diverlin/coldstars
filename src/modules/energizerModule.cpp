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


#include "energizerModule.hpp"

EnergizerModule :: EnergizerModule(TextureOb* _texOb, int _energy_max_add, int _restoration_add)
{
     	CommonForModules_init(ENERGIZER_MODULE_ID, _texOb);

     	energy_max_add  = _energy_max_add;
     	restoration_add = _restoration_add;
}


EnergizerModule :: ~EnergizerModule()
{}
      		

int EnergizerModule :: getEnergyMaxAdd()   const { return energy_max_add; }
int EnergizerModule :: getRestorationAdd() const { return restoration_add; }
		
		
void EnergizerModule :: addUniqueInfo()
{
    	info.addTitleStr("energizer module");
    	if (energy_max_add != 0)
    	{ 
    		info.addNameStr("energy_max_add:");  info.addValueStr( int2str(energy_max_add) );
    	}
    	if (restoration_add != 0)
    	{
    		info.addNameStr("restoration_add:"); info.addValueStr( int2str(restoration_add) );
    	} 
}


EnergizerModule* energizerModuleGenerator()
{
     	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);      	
     	int energy_max_add  = getRandInt(ENERGIZER_MODULE_ENERGY_MIN, ENERGIZER_MODULE_ENERGY_MAX);
     	int restoration_add = getRandInt(ENERGIZER_MODULE_RESTORATION_MIN, ENERGIZER_MODULE_RESTORATION_MAX);
     	
     	EnergizerModule* energizer_module = new EnergizerModule(texOb, energy_max_add, restoration_add);
	return energizer_module; 
}
