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

LazerModule :: LazerModule(TextureOb* _pTo_texOb)
{
     CommonForModules_init(_pTo_texOb);
     subtype_id = LAZER_ID;

     damage_add = 0;
     radius_add = 0;
}


LazerModule :: ~LazerModule()
{
}


void LazerModule :: activation(LazerEquipment* _pTo_lazer_item)
{
     _pTo_lazer_item->damage_add += damage_add;
     _pTo_lazer_item->radius_add += radius_add;
     _pTo_lazer_item->updatePropetries();
}

void LazerModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "lazer module";
    info_title_1 = "damage_add:";      info_value_1 = int2str(damage_add);
    info_title_2 = "radius_add:";      info_value_2 = int2str(radius_add);
    info_title_3 = "mass:";            info_value_3 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    if (damage_add != 0) 
    {
        info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    }
    if (radius_add != 0)
    { 
        info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    }
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
}


LazerModule* lazerModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    LazerModule* pTo_lazer_module = new LazerModule(pTo_texOb);

    pTo_lazer_module->damage_add = randIntInRange(LAZER_MODULE_DAMAGE_MIN, LAZER_MODULE_DAMAGE_MAX);
    pTo_lazer_module->radius_add = randIntInRange(LAZER_MODULE_RADIUS_MIN, LAZER_MODULE_RADIUS_MAX);

    pTo_lazer_module->updateInfo();
    return pTo_lazer_module;
}
