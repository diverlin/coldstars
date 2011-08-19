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


#include "turrel.h"


Turrel :: Turrel()
{
    //////
    points = Points();
    points.addCenterPoint();
    points.addMainQuadPoints();
    //////
    
        pos_z = -1.5;
    
    is_READY_TO_FIRE = false;
         
     target_type_id = -1;
     pTo_shipTarget      = NULL;
     pTo_asteroidTarget  = NULL;
     pTo_mineralTarget   = NULL;
     pTo_containerTarget = NULL;
     has_TARGET = false;
     pTo_target_is_alive = NULL;

     pTo_pos_x = NULL;
     pTo_pos_y = NULL;
     
     pTo_target_pos_x = NULL;
     pTo_target_pos_y = NULL;
            
}


void Turrel :: bindSlot(OtsecSlot* _pTo_slot)
{
        pTo_slot = _pTo_slot;
}


void Turrel :: setTexOb(TextureOb* _pTo_texOb)
{
    pTo_texOb = _pTo_texOb;
    w = (*pTo_texOb).w;
    h = (*pTo_texOb).h;   
    texture = (*pTo_texOb).texture;   // move this to linkTexture func

    //////
    points.initCenterPoint();
    points.initMainQuadPoints(w, h);
    //////
}


Turrel :: ~Turrel()
{}


void Turrel :: update(float _center_x, float _center_y, float _angle_inD)
{   
    points.setCenter(_center_x, _center_y);
    points.setAngle(_angle_inD);
    points.update();
}


void Turrel :: render()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    drawFlatQuadPerVertexIn2D(points.bottomLeft_x, points.bottomLeft_y, points.bottomRight_x, points.bottomRight_y, points.topRight_x, points.topRight_y, points.topLeft_x, points.topLeft_y, pos_z);
}





void Turrel :: placed(float* _pTo_pos_x, float* _pTo_pos_y)
{
     pTo_pos_x = _pTo_pos_x;
     pTo_pos_y = _pTo_pos_y;
}



void Turrel :: updateTurrelPosition(float _pos_x, float _pos_y, float angle_inD)
{
       update(_pos_x, _pos_y, angle_inD);
}

void Turrel :: renderTurrel()
{
render();
}











bool Turrel :: fireCheck()
{
    if (has_TARGET == true)
       if (isTargetAchievable() == true)
          if (isAmmoAvailable() == true)
             return true;

    return false; 
}


bool Turrel :: isTargetAchievable()
{
    if ( (isTargetAlive() == false) or (isTargetInSpace() == false) or (isTargetOnTheSameStarSystem() == false) )
    {   
         //printf("isTargetAchievable => false\n");  
         resetTarget();
         return false;
    }  

    float dist_to_target = lengthBetweenPoints(pTo_ship->points.center_x, 
                                               pTo_ship->points.center_y, 
                                               (*pTo_target_pos_x), 
                                               (*pTo_target_pos_y));
                                               
    if (dist_to_target > pTo_slot->getItemRadius())
    {
         resetTarget();
         return false;
    }
     
    return true;  
}


bool Turrel :: isTargetAlive()
{
     if (target_type_id == SHIP_ID)
        if ((*pTo_shipTarget).is_alive == true)
           return true;
        else
           return false;

     if (target_type_id == ASTEROID_ID)
        if ((*pTo_asteroidTarget).is_alive == true)
           return true;
        else
           return false;

     if (target_type_id == MINERAL_ID)
        if ((*pTo_mineralTarget).is_alive == true)
           return true;
        else
           return false; 

     if (target_type_id == CONTAINER_ID)
        if ((*pTo_containerTarget).is_alive == true)
           return true;
        else
           return false;

     printf("ERROR MES: WeaponSlot :: isTargetAlive(): UNKNOWN TARGET");
}

bool Turrel :: isTargetInSpace()
{
     if (target_type_id == SHIP_ID)
        if (pTo_shipTarget->in_SPACE == true)
           return true;
        else
           return false;

     if (target_type_id == ASTEROID_ID)
         return true;

     if (target_type_id == MINERAL_ID)
         return true;

     if (target_type_id == CONTAINER_ID)
         return true;

     printf("ERROR MES: WeaponSlot :: isTargetInSpace(): UNKNOWN TARGET");
}




bool Turrel :: isTargetOnTheSameStarSystem()
{
     if (target_type_id == SHIP_ID)
        if ((*pTo_shipTarget).pTo_starsystem == (*pTo_ship).pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == ASTEROID_ID)
        if ((*pTo_asteroidTarget).pTo_starsystem == (*pTo_ship).pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == MINERAL_ID)
        if ((*pTo_mineralTarget).pTo_starsystem == (*pTo_ship).pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == CONTAINER_ID)
        if ((*pTo_containerTarget).pTo_starsystem == (*pTo_ship).pTo_starsystem)
           return true;
        else
           return false;

     printf("ERROR MES: WeaponSlot :: isTargetOnTheSameStarSystem(): UNKNOWN TARGET");
}





bool Turrel :: isAmmoAvailable()
{
    if (pTo_slot->item_subtype_id == LAZER_ID)
       return true;
    if (pTo_slot->item_subtype_id == ROCKET_ID)
       if (pTo_slot->get_pToRocketEquipment()->ammo > 0)
          return true;

    return false;           
}




bool Turrel :: fireEvent_TRUE()
{
    if (pTo_slot->item_subtype_id == LAZER_ID)
    {   
       pTo_slot->get_pToLazerEquipment()->fireEvent();
       pTo_slot->get_pToLazerEquipment()->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           pTo_shipTarget->hit_TRUE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           pTo_asteroidTarget->hit_TRUE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           pTo_mineralTarget->hit_TRUE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           pTo_containerTarget->hit_TRUE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }
    }

    if (pTo_slot->item_subtype_id == ROCKET_ID)
    {   
       pTo_slot->get_pToRocketEquipment()->fireEvent();
       pTo_slot->get_pToRocketEquipment()->deterioration();
       return true; 
    }

    return false;
}





bool Turrel :: fireEvent_FALSE()
{
    if (pTo_slot->item_subtype_id == LAZER_ID)
    {   
       pTo_slot->get_pToLazerEquipment()->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           pTo_shipTarget->hit_FALSE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           pTo_asteroidTarget->hit_FALSE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           pTo_mineralTarget->hit_FALSE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           pTo_containerTarget->hit_FALSE(pTo_slot->get_pToLazerEquipment()->damage);
           return true;
       }
    }

    if (pTo_slot->item_subtype_id == ROCKET_ID)
    {   
       pTo_slot->get_pToRocketEquipment()->deterioration();
       return true; 
    }

    return false;
}











int Turrel :: returnTargetId()
{
    if (has_TARGET == true)
    {
        if (target_type_id == SHIP_ID)
           return pTo_shipTarget->id;
        if (target_type_id == ASTEROID_ID)
           return pTo_asteroidTarget->id;
        if (target_type_id == MINERAL_ID)
           return pTo_mineralTarget->id;
        if (target_type_id == CONTAINER_ID)
           return pTo_containerTarget->id;

        printf("ERROR MES: WeaponSlot :: returnTargetId(): UNKNOWN TARGET");
    }
}


void Turrel :: setShipTarget(Ship* _pTo_ship)
{
     pTo_shipTarget = _pTo_ship;
     target_type_id = pTo_shipTarget->type_id;

     pTo_target_pos_x = &(pTo_shipTarget->points.center_x);
     pTo_target_pos_y = &(pTo_shipTarget->points.center_y);

     pTo_target_is_alive = &(pTo_shipTarget->is_alive);
     has_TARGET = true;
}

void Turrel :: setAsteroidTarget(Asteroid* _pTo_asteroid)
{
     pTo_asteroidTarget = _pTo_asteroid;
     target_type_id = pTo_asteroidTarget->type_id;

     pTo_target_pos_x = &(pTo_asteroidTarget->points.center_x);
     pTo_target_pos_y = &(pTo_asteroidTarget->points.center_y);

     pTo_target_is_alive = &(pTo_asteroidTarget->is_alive);
     has_TARGET = true;
}

void Turrel :: setMineralTarget(Mineral* _pTo_mineral)
{
     pTo_mineralTarget = _pTo_mineral;
     target_type_id = pTo_mineralTarget->type_id;

     pTo_target_pos_x = &(pTo_mineralTarget->points.center_x);
     pTo_target_pos_y = &(pTo_mineralTarget->points.center_y);

     pTo_target_is_alive = &(pTo_mineralTarget->is_alive);
     has_TARGET = true;
}

void Turrel :: setContainerTarget(Container* _pTo_container)
{
     pTo_containerTarget = _pTo_container;
     target_type_id = pTo_containerTarget->type_id;

     pTo_target_pos_x = &(pTo_containerTarget->points.center_x);
     pTo_target_pos_y = &(pTo_containerTarget->points.center_y);

     pTo_target_is_alive = &(pTo_containerTarget->is_alive);
     has_TARGET = true;
}






void Turrel :: resetTarget()
{
     if (has_TARGET == true) 
     {  
        if (target_type_id == SHIP_ID)
           pTo_shipTarget = NULL;
        if (target_type_id == ASTEROID_ID)
           pTo_asteroidTarget = NULL;
        if (target_type_id == MINERAL_ID)
           pTo_mineralTarget = NULL;
        if (target_type_id == CONTAINER_ID)
           pTo_containerTarget = NULL;

        pTo_target_pos_x = NULL;
        pTo_target_pos_y = NULL;
        pTo_target_is_alive = NULL;

        has_TARGET = false;  
     }  
}
