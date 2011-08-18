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


#include "bakModule.h"


BakModule :: BakModule(TextureOb* _pTo_texOb)
{
    CommonForModules_init(_pTo_texOb);
    subtype_id = BAK_ID;

    fuel_max_add = 0;
}

BakModule :: ~BakModule()
{}

void BakModule :: activation(BakEquipment* _pTo_bak_item)
{
    _pTo_bak_item->fuel_max_add += fuel_max_add;
    _pTo_bak_item->updatePropetries();
}

void BakModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "bak module";
    info_title_1 = "fuel_max_add:";     info_value_1 = int2str(fuel_max_add);

    info_title_2 = "mass:";     info_value_2 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
}



BakModule* bakModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    BakModule* pTo_bak_module = new BakModule(pTo_texOb);
    pTo_bak_module->fuel_max_add = randIntInRange(BAK_MODULE_FUEL_MIN, BAK_MODULE_FUEL_MAX);

    pTo_bak_module->updateInfo();
    return pTo_bak_module;
}
