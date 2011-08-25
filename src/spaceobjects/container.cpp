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

    pTo_rocketEquipment      = NULL;
    pTo_lazerEquipment       = NULL;
    pTo_radarEquipment       = NULL;
    pTo_driveEquipment       = NULL;
    pTo_bakEquipment         = NULL;
    pTo_energizerEquipment   = NULL;
    pTo_protectorEquipment   = NULL;
    pTo_droidEquipment       = NULL;
    pTo_freezerEquipment     = NULL;
    pTo_scanerEquipment      = NULL;
    pTo_grappleEquipment     = NULL;

    
    armor = randIntInRange(1,6);

    speed = randIntInRange(40, 42);
    stepCalculation();

    size = returnObjectSize(w, h);
}


Container :: ~Container()
{}


void Container :: packRocketEquipment(RocketEquipment* pTo_item)
{
    pTo_rocketEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packLazerEquipment(LazerEquipment* pTo_item)
{
    pTo_lazerEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass; 

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packRadarEquipment(RadarEquipment* pTo_item)
{
    pTo_radarEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;     

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packDriveEquipment(DriveEquipment* pTo_item)
{
    pTo_driveEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;       

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList; 
}

void Container :: packBakEquipment(BakEquipment* pTo_item)
{
    pTo_bakEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packEnergizerEquipment(EnergizerEquipment* pTo_item)
{
    pTo_energizerEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();   
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packProtectorEquipment(ProtectorEquipment* pTo_item)
{
    pTo_protectorEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();   
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packDroidEquipment(DroidEquipment* pTo_item)
{
    pTo_droidEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType(); 
    item_id         = pTo_item->id;    

    mass = pTo_item->mass;    

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packFreezerEquipment(FreezerEquipment* pTo_item)
{
    pTo_freezerEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass; 

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;   
}

void Container :: packScanerEquipment(ScanerEquipment* pTo_item)
{
    pTo_scanerEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();   
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;      

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}

void Container :: packGrappleEquipment(GrappleEquipment* pTo_item)
{
    pTo_grappleEquipment = pTo_item;
    
    item_subtype_id = pTo_item->getSubType();    
    item_id         = pTo_item->id;    

    mass = (*pTo_item).mass;  

    info_title_pList = pTo_item->info_title_pList;
    info_value_pList = pTo_item->info_value_pList;
}        
        


void Container :: renderInfo()
{
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y);
}

 
