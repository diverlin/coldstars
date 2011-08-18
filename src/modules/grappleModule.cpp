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


#include "grappleModule.h"


GrappleModule :: GrappleModule(TextureOb* _pTo_texOb)
{
       CommonForModules_init(_pTo_texOb);
       subtype_id = GRAPPLE_ID;

       strength_add = 0;
       radius_add = 0;
       speed_add = 0;
       maxNumItem_add = 0;
}

GrappleModule :: ~GrappleModule ()
{}

void GrappleModule :: activation(GrappleItem* _pTo_grapple_item)
{
     _pTo_grapple_item->strength_add   += strength_add;
     _pTo_grapple_item->radius_add     += radius_add;
     _pTo_grapple_item->speed_add      += speed_add;
     _pTo_grapple_item->maxNumItem_add += maxNumItem_add;
     _pTo_grapple_item->updatePropetries();
}

void GrappleModule :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "grapple module";
    info_title_1 = "strength_add:";    info_value_1 = int2str(strength_add);
    info_title_2 = "radius_add:";      info_value_2 = int2str(radius_add);
    info_title_3 = "speed_add:";       info_value_3 = int2str(speed_add);
    info_title_4 = "maxNumItem_add:";  info_value_4 = int2str(maxNumItem_add); 
    info_title_5 = "mass:";            info_value_5 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    if (strength_add != 0)
    {
        info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    }
    if (radius_add != 0)
    { 
        info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    } 
    if (speed_add != 0)
    {
        info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    }
    if (maxNumItem_add != 0)
    {
        info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    }
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
}


GrappleModule* grappleModuleGenerator()
{
    TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 

    GrappleModule* pTo_grapple_module = new GrappleModule(pTo_texOb);
    pTo_grapple_module->strength_add   = randIntInRange(GRAPPLE_MODULE_STRENGTH_MIN, GRAPPLE_MODULE_STRENGTH_MAX);
    pTo_grapple_module->radius_add     = randIntInRange(GRAPPLE_MODULE_RADIUS_MIN, GRAPPLE_MODULE_RADIUS_MAX);
    pTo_grapple_module->speed_add      = randIntInRange(GRAPPLE_MODULE_SPEED_MIN, GRAPPLE_MODULE_SPEED_MAX);
    pTo_grapple_module->maxNumItem_add = randIntInRange(GRAPPLE_MODULE_MAXNUMITEM_MIN, GRAPPLE_MODULE_MAXNUMITEM_MAX);

    pTo_grapple_module->updateInfo();
    return pTo_grapple_module;
}







