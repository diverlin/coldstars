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


#include "driveModule.h"

DriveModule :: DriveModule(TextureOb* _pTo_texOb)
{
     CommonForModules_init(_pTo_texOb);
     subtype_id = DRIVE_MODULE_ID;

     speed_add = 0;
     hyper_add = 0;
}

DriveModule :: ~DriveModule()
{}

void DriveModule :: activation(DriveItem* _pTo_drive_item)
{
     _pTo_drive_item->speed_add += speed_add;
     _pTo_drive_item->hyper_add += hyper_add;
     _pTo_drive_item->updatePropetries();
}

void DriveModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "drive module";
    info_title_1 = "speed_add:";       info_value_1 = int2str(speed_add);
    info_title_2 = "hyper_add:";       info_value_2 = int2str(hyper_add);
    info_title_3 = "mass:";            info_value_3 = int2str(mass);


    info_title_pList.push_back(&info_title_0);  
    if (speed_add != 0)
    { 
       info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    } 
    if (hyper_add != 0)
    { 
        info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    }
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
}


DriveModule* driveModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    DriveModule* pTo_drive_module = new DriveModule(pTo_texOb);
    pTo_drive_module->speed_add = randIntInRange(DRIVE_MODULE_SPEED_MIN, DRIVE_MODULE_SPEED_MAX);
    pTo_drive_module->hyper_add = randIntInRange(DRIVE_MODULE_HYPER_MIN, DRIVE_MODULE_HYPER_MAX);

    pTo_drive_module->updateInfo();
    return pTo_drive_module;
}


