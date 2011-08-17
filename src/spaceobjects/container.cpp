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


#include "container.h"

Container :: Container(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _pos_x, float _pos_y, float _target_pos_x, float _target_pos_y)
{
    CommonForSpaceItems_init(_pTo_starsystem, _pTo_texOb, _pos_x, _pos_y, _target_pos_x, _target_pos_y);

    id = g_ENTITY_ID_GENERATOR.returnNextId(); 
    type_id = CONTAINER_ID;

    item_subtype_id = -1;
    mass = -1;

    pTo_rocketItem      = NULL;
    pTo_lazerItem       = NULL;
    pTo_radarItem       = NULL;
    pTo_driveItem       = NULL;
    pTo_bakItem         = NULL;
    pTo_energizerItem   = NULL;
    pTo_protectorItem   = NULL;
    pTo_droidItem       = NULL;
    pTo_freezerItem     = NULL;
    pTo_scanerItem      = NULL;
    pTo_grappleItem     = NULL;

    
    armor = randIntInRange(1,6);

    speed = randIntInRange(40, 42);
    stepCalculation();

    size = returnObjectSize(w, h);
}


Container :: ~Container()
{}


void Container :: packRocketItem(RocketItem* pTo_item)
{
    pTo_rocketItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    // ROCKET_ID
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packLazerItem(LazerItem* pTo_item)
{
    pTo_lazerItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass; 

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packRadarItem(RadarItem* pTo_item)
{
    pTo_radarItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;     

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packDriveItem(DriveItem* pTo_item)
{
    pTo_driveItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;       

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList; 
}

void Container :: packBakItem(BakItem* pTo_item)
{
    pTo_bakItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packEnergizerItem(EnergizerItem* pTo_item)
{
    pTo_energizerItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;   
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packProtectorItem(ProtectorItem* pTo_item)
{
    pTo_protectorItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;   
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packDroidItem(DroidItem* pTo_item)
{
    pTo_droidItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id; 
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;    

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packFreezerItem(FreezerItem* pTo_item)
{
    pTo_freezerItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass; 

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;   
}

void Container :: packScanerItem(ScanerItem* pTo_item)
{
    pTo_scanerItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;   
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packGrappleItem(GrappleItem* pTo_item)
{
    pTo_grappleItem = pTo_item;
    
    item_subtype_id = pTo_item->subtype_id;    // GRAPPLE_ID
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;  

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}        
        


void Container :: renderInfo()
{
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y);
}

 
