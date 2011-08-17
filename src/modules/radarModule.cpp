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


#include "radarModule.h"

RadarModule :: RadarModule(TextureOb* _pTo_texOb)
{
     CommonForModules_init(_pTo_texOb);
     subtype_id = RADAR_MODULE_ID;

     radius_add = 0;
}

RadarModule :: ~RadarModule()
{}

void RadarModule :: activation(RadarItem* _pTo_radar_item)
{
     _pTo_radar_item->radius_add += radius_add;
     _pTo_radar_item->updatePropetries();
}

void RadarModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "radar module";
    info_title_1 = "radius_add:";     info_value_1 = int2str(radius_add);
    info_title_2 = "mass:";           info_value_2 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
}


RadarModule* radarModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    RadarModule* pTo_radar_module = new RadarModule(pTo_texOb);
    pTo_radar_module->radius_add  = randIntInRange(RADAR_MODULE_RADIUS_MIN, RADAR_MODULE_RADIUS_MAX);

    pTo_radar_module->updateInfo();
    return pTo_radar_module;
}














