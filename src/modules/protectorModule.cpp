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


#include "protectorModule.h"



ProtectorModule :: ProtectorModule(TextureOb* _pTo_texOb)
{
     CommonForModules_init(_pTo_texOb);
     subtype_id = PROTECTOR_ID;

     protection_add = 0;
}

ProtectorModule :: ~ProtectorModule ()
{}

void ProtectorModule :: activation(ProtectorItem* _pTo_protector_item)
{
     _pTo_protector_item->protection_add += protection_add;
     _pTo_protector_item->updatePropetries();
}

void ProtectorModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "protector module";
    info_title_1 = "protection_add:";  info_value_1 = int2str(protection_add);
    info_title_2 = "mass:";            info_value_2 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
}


ProtectorModule* protectorModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    ProtectorModule* pTo_protector_module = new ProtectorModule(pTo_texOb);
    pTo_protector_module->protection_add = randIntInRange(PROTECTOR_MODULE_PROTECTION_MIN, PROTECTOR_MODULE_PROTECTION_MAX);

    pTo_protector_module->updateInfo();
    return pTo_protector_module;
}
