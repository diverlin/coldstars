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

EnergizerModule :: EnergizerModule(TextureOb* pTo_texOb)
{
     CommonForModules_init(pTo_texOb);
     subtype_id = ENERGIZER_ID;

     energy_max_add = 0;
     restoration_add = 0;
}

void EnergizerModule :: activation(EnergizerEquipment* pTo_energizer_item)
{
     pTo_energizer_item->energy_max_add  += energy_max_add;
     pTo_energizer_item->restoration_add += restoration_add;
     pTo_energizer_item->updatePropetries();
}

void EnergizerModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "energizer module";
    info_title_1 = "energy_max_add:";  info_value_1 = int2str(energy_max_add);
    info_title_2 = "restoration_add:"; info_value_2 = int2str(restoration_add);
    info_title_3 = "mass:";            info_value_3 = int2str(mass);

    info_title_pList.push_back(&info_title_0); 
    if (energy_max_add != 0)
    { 
        info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    }
    if (restoration_add != 0)
    {
        info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    } 
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);

}


EnergizerModule* energizerModuleGenerator()
{
     TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

     EnergizerModule* pTo_energizer_module = new EnergizerModule(pTo_texOb);
     pTo_energizer_module->energy_max_add  = randIntInRange(ENERGIZER_MODULE_ENERGY_MIN, ENERGIZER_MODULE_ENERGY_MAX);
     pTo_energizer_module->restoration_add = randIntInRange(ENERGIZER_MODULE_RESTORATION_MIN, ENERGIZER_MODULE_RESTORATION_MAX); 

     pTo_energizer_module->updateInfo();
     return pTo_energizer_module; 
}
