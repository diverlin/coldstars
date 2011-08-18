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


#include "freezerModule.h"

FreezerModule :: FreezerModule(TextureOb* _pTo_texOb)
{
     CommonForModules_init(_pTo_texOb);
     subtype_id = FREEZER_ID;

     freeze_add = 0;
}

void FreezerModule :: activation(FreezerItem* _pTo_freezer_item)
{
     _pTo_freezer_item->freeze_add += freeze_add;
     _pTo_freezer_item->updatePropetries();
}

void FreezerModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "freezer module";
    info_title_1 = "freeze_add:";     info_value_1 = int2str(freeze_add);
    info_title_2 = "mass:";           info_value_2 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
}

FreezerModule* freezerModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    FreezerModule* pTo_freezer_module = new FreezerModule(pTo_texOb);
    pTo_freezer_module->freeze_add = randIntInRange(FREEZER_MODULE_FREEZE_MIN, FREEZER_MODULE_FREEZE_MAX);

    pTo_freezer_module->updateInfo();
    return pTo_freezer_module;
}
