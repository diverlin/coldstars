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


EnergizerModule :: EnergizerModule(int energy_max_add, 
                                   int restoration_add)
{
     	this->energy_max_add  = energy_max_add;
     	this->restoration_add = restoration_add;
}


EnergizerModule :: ~EnergizerModule() /* virtual */
{}


int EnergizerModule :: getEnergyMaxAdd()   const { return energy_max_add; }
int EnergizerModule :: getRestorationAdd() const { return restoration_add; }


void EnergizerModule :: AddUniqueInfo()
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


EnergizerModule* getNewEnergizerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        	
     	int energy_max_add  = getRandInt(MODULE::ENERGIZER::ENERGY_MIN, MODULE::ENERGIZER::ENERGY_MAX);
     	int restoration_add = getRandInt(MODULE::ENERGIZER::RESTORATION_MIN, MODULE::ENERGIZER::RESTORATION_MAX);
     	
        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::ENERGIZER_ID;  
        
     	EnergizerModule* energizer_module = new EnergizerModule(energy_max_add, restoration_add);
        energizer_module->SetTextureOb(texOb);
        energizer_module->SetIdData(data_id);
        
        return energizer_module; 
}
