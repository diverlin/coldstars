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


#include "scanerModule.h"


ScanerModule :: ScanerModule(TextureOb* _pTo_texOb)
{
    CommonForModules_init(_pTo_texOb);
    subtype_id = SCANER_MODULE_ID;

    scan_add = 0;
}


ScanerModule :: ~ScanerModule ()
{}

void ScanerModule :: activation(ScanerItem* _pTo_scaner_item)
{
    _pTo_scaner_item->scan_add += scan_add;
    _pTo_scaner_item->updatePropetries();
}

void ScanerModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "scaner module";
    info_title_1 = "scan_add:";       info_value_1 = int2str(scan_add);
    info_title_2 = "mass:";           info_value_2 = int2str(mass);


    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
}


ScanerModule* scanerModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    ScanerModule* pTo_scaner_module = new ScanerModule(pTo_texOb);
    pTo_scaner_module->scan_add = randIntInRange(SCANER_MODULE_SCAN_MIN, SCANER_MODULE_SCAN_MAX);

    pTo_scaner_module->updateInfo();
    return pTo_scaner_module;
}
