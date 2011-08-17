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


#include "weaponslot.h"

WeaponSlot :: WeaponSlot()
{}

WeaponSlot :: WeaponSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{    
     CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);

     type_id = WEAPON_SLOT_ID;

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

     is_SELECTED      = false;

     //self.GL_LIST_slot_ID = None
}


void WeaponSlot :: placed(float* _pTo_pos_x, float* _pTo_pos_y)
{
     pTo_pos_x = _pTo_pos_x;
     pTo_pos_y = _pTo_pos_y;
}


void WeaponSlot :: updateTurrelPosition(float _pos_x, float _pos_y, float angle_inD)
{
    if (item_subtype_id == LAZER_ITEM_ID)
       pTo_lazerItem->pTo_turrel->update(_pos_x, _pos_y, angle_inD);
    if (item_subtype_id == ROCKET_ITEM_ID)
       pTo_rocketItem->pTo_turrel->update(_pos_x, _pos_y, angle_inD);
}

void WeaponSlot :: renderTurrel()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       pTo_lazerItem->pTo_turrel->render();
    if (item_subtype_id == ROCKET_ITEM_ID)
       pTo_rocketItem->pTo_turrel->render();
}


void WeaponSlot :: insertLazerItem(LazerItem* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;   
 
    pTo_lazerItem = pTo_item;
    pTo_lazerItem->pTo_ship = pTo_ship;
    pTo_lazerItem->pTo_wslot = this;

    is_EQUIPED = true;

    pTo_ship->updateFireAbility();
}

void WeaponSlot :: removeLazerItem()
{
    item_subtype_id = -1;
        
    pTo_lazerItem->pTo_ship = NULL;      
    pTo_lazerItem->pTo_wslot = NULL;
    pTo_lazerItem = NULL;

    is_EQUIPED = false;

    pTo_ship->updateFireAbility();
}



void WeaponSlot :: insertRocketItem(RocketItem* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;    
 
    pTo_rocketItem = pTo_item;
    
    pTo_rocketItem->pTo_ship = pTo_ship;
    pTo_rocketItem->pTo_wslot = this;
    
    is_EQUIPED = true;

    pTo_ship->updateFireAbility();
}

void WeaponSlot :: removeRocketItem()
{
    item_subtype_id = -1;
        
    pTo_rocketItem->pTo_ship = NULL;      
    pTo_rocketItem->pTo_wslot = NULL;
    pTo_rocketItem = NULL;
    
    is_EQUIPED = false;

    pTo_ship->updateFireAbility();
}


int WeaponSlot :: returnEquipedItemDamage()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       return pTo_lazerItem->damage;
    if (item_subtype_id == ROCKET_ITEM_ID)
       return pTo_rocketItem->damage;
}

int WeaponSlot :: returnEquipedItemRadius()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       return pTo_lazerItem->radius;
    if (item_subtype_id == ROCKET_ITEM_ID)
       return pTo_rocketItem->radius;   
}

int WeaponSlot :: returnEquipedItemCondition()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       return pTo_lazerItem->condition;
    if (item_subtype_id == ROCKET_ITEM_ID)
       return pTo_rocketItem->condition;
}

int WeaponSlot :: returnEquipedItemMass()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       return pTo_lazerItem->mass;
    if (item_subtype_id == ROCKET_ITEM_ID)
       return pTo_rocketItem->mass;
}


bool WeaponSlot :: fireCheck()
{
    if (has_TARGET == true)
       if (isTargetAchievable() == true)
          if (isAmmoAvailable() == true)
             return true;

    return false; 
}


bool WeaponSlot :: isTargetAchievable()
{
    if ( (isTargetAlive() == false) or (isTargetInSpace() == false) or (isTargetOnTheSameStarSystem() == false) )
    {   
         //printf("isTargetAchievable => false\n");  
         resetTarget();
         return false;
    }  

    float dist_to_target = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, (*pTo_target_pos_x), (*pTo_target_pos_y));
    if (dist_to_target > returnEquipedItemRadius())
    {
         resetTarget();
         return false;
    }
     
    return true;  
}


bool WeaponSlot :: isTargetAlive()
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

bool WeaponSlot :: isTargetInSpace()
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

bool WeaponSlot :: isTargetOnTheSameStarSystem()
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


bool WeaponSlot :: isAmmoAvailable()
{
    if (item_subtype_id == LAZER_ITEM_ID)
       return true;
    if (item_subtype_id == ROCKET_ITEM_ID)
       if (pTo_rocketItem->ammo > 0)
          return true;

    return false;           
}



bool WeaponSlot :: fireEvent_TRUE()
{
    if (item_subtype_id == LAZER_ITEM_ID)
    {   
       pTo_lazerItem->fireEvent();
       pTo_lazerItem->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           pTo_shipTarget->hit_TRUE(pTo_lazerItem->damage);
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           pTo_asteroidTarget->hit_TRUE(pTo_lazerItem->damage);
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           pTo_mineralTarget->hit_TRUE(pTo_lazerItem->damage);
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           pTo_containerTarget->hit_TRUE(pTo_lazerItem->damage);
           return true;
       }
    }

    if (item_subtype_id == ROCKET_ITEM_ID)
    {   
       pTo_rocketItem->fireEvent();
       pTo_rocketItem->deterioration();
       return true; 
    }

    return false;
}





bool WeaponSlot :: fireEvent_FALSE()
{
    if (item_subtype_id == LAZER_ITEM_ID)
    {   
       pTo_lazerItem->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           pTo_shipTarget->hit_FALSE(pTo_lazerItem->damage);
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           pTo_asteroidTarget->hit_FALSE(pTo_lazerItem->damage);
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           pTo_mineralTarget->hit_FALSE(pTo_lazerItem->damage);
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           pTo_containerTarget->hit_FALSE(pTo_lazerItem->damage);
           return true;
       }
    }

    if (item_subtype_id == ROCKET_ITEM_ID)
    {   
       pTo_rocketItem->deterioration();
       return true; 
    }

    return false;
}





int WeaponSlot :: returnTargetId()
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


void WeaponSlot :: setShipTarget(Ship* _pTo_ship)
{
     pTo_shipTarget = _pTo_ship;
     target_type_id = pTo_shipTarget->type_id;

     pTo_target_pos_x = &(pTo_shipTarget->points.center_x);
     pTo_target_pos_y = &(pTo_shipTarget->points.center_y);

     pTo_target_is_alive = &(pTo_shipTarget->is_alive);
     has_TARGET = true;
}

void WeaponSlot :: setAsteroidTarget(Asteroid* _pTo_asteroid)
{
     pTo_asteroidTarget = _pTo_asteroid;
     target_type_id = pTo_asteroidTarget->type_id;

     pTo_target_pos_x = &(pTo_asteroidTarget->points.center_x);
     pTo_target_pos_y = &(pTo_asteroidTarget->points.center_y);

     pTo_target_is_alive = &(pTo_asteroidTarget->is_alive);
     has_TARGET = true;
}

void WeaponSlot :: setMineralTarget(Mineral* _pTo_mineral)
{
     pTo_mineralTarget = _pTo_mineral;
     target_type_id = pTo_mineralTarget->type_id;

     pTo_target_pos_x = &(pTo_mineralTarget->points.center_x);
     pTo_target_pos_y = &(pTo_mineralTarget->points.center_y);

     pTo_target_is_alive = &(pTo_mineralTarget->is_alive);
     has_TARGET = true;
}

void WeaponSlot :: setContainerTarget(Container* _pTo_container)
{
     pTo_containerTarget = _pTo_container;
     target_type_id = pTo_containerTarget->type_id;

     pTo_target_pos_x = &(pTo_containerTarget->points.center_x);
     pTo_target_pos_y = &(pTo_containerTarget->points.center_y);

     pTo_target_is_alive = &(pTo_containerTarget->is_alive);
     has_TARGET = true;
}





void WeaponSlot :: resetTarget()
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





void WeaponSlot :: renderFrame(GLuint flash_tex)
{
    drawTexturedRect(pTo_texOb->texture, rect, -1.5);

    //if self.flash == True:
       //drawTexturedRect(flash_tex, self.rect, -1.0)
    if (is_EQUIPED == true)
    {
       if (item_subtype_id == LAZER_ITEM_ID)
          pTo_lazerItem->render(rect);
        
       if (item_subtype_id == ROCKET_ITEM_ID)
          pTo_rocketItem->render(rect);
    }
        
}


void WeaponSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void WeaponSlot :: renderItemInfo()
{
    if (is_EQUIPED == true)
    {
       if (item_subtype_id == LAZER_ITEM_ID)
          pTo_lazerItem->renderInfo(rect);
        
       if (item_subtype_id == ROCKET_ITEM_ID)
          pTo_rocketItem->renderInfo(rect);
    }      
}

