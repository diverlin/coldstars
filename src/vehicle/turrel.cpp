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
    
         
     target_type_id = -1;
     target_ship      = NULL;
     target_asteroid  = NULL;
     target_mineral   = NULL;
     target_container = NULL;
     has_TARGET = false;
     pTo_target_is_alive = NULL;

     pTo_pos_x = NULL;
     pTo_pos_y = NULL;
     
     pTo_target_pos_x = NULL;
     pTo_target_pos_y = NULL;
            
}

void Turrel :: setSelectedStatus(bool _selected) { is_SELECTED = _selected; }                
bool Turrel :: getSelectedStatus() const { return is_SELECTED; }
bool Turrel :: getHasTargetStatus() const { return has_TARGET; }

float Turrel :: getCenterX() const { return points.center_x; }
float Turrel :: getCenterY() const { return points.center_y; }
float Turrel :: getAngle()   const { return points.angle_inD; }
                                
void Turrel :: bindSlot(ItemSlot* _slot)
{
        slot = _slot;
}



void Turrel :: setTexOb(TextureOb* _texOb)
{
    pTo_texOb = _texOb;
    w = pTo_texOb->w;
    h = pTo_texOb->h;   
    texture = pTo_texOb->texture;   // move this to linkTexture func

    //////
    points.initCenterPoint();
    points.initMainQuadPoints(w, h);
    //////
}

bool* Turrel :: getTarget_pAliveStatus() const { return pTo_target_is_alive; }
float* Turrel :: getTarget_pCenterX() const { return pTo_target_pos_x; }
float* Turrel :: getTarget_pCenterY() const { return pTo_target_pos_y; }

float* Turrel :: get_pCenterX() const { return pTo_pos_x; }
float* Turrel :: get_pCenterY() const { return pTo_pos_y; }

Turrel :: ~Turrel()
{}


void Turrel :: placed(float* _pTo_pos_x, float* _pTo_pos_y)
{
     pTo_pos_x = _pTo_pos_x;
     pTo_pos_y = _pTo_pos_y;
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

    float dist_to_target = lengthBetweenPoints(slot->getShip()->points.center_x, 
                                               slot->getShip()->points.center_y, 
                                               (*pTo_target_pos_x), 
                                               (*pTo_target_pos_y));
                                               
    if (dist_to_target > slot->getItemRadius())
    {
         resetTarget();
         return false;
    }
     
    return true;  
}


bool Turrel :: isTargetAlive()
{
     if (target_type_id == SHIP_ID)
        if (target_ship->is_alive == true)
           return true;
        else
           return false;

     if (target_type_id == ASTEROID_ID)
        if (target_asteroid->is_alive == true)
           return true;
        else
           return false;

     if (target_type_id == MINERAL_ID)
        if (target_mineral->is_alive == true)
           return true;
        else
           return false; 

     if (target_type_id == CONTAINER_ID)
        if (target_container->is_alive == true)
           return true;
        else
           return false;

     printf("ERROR MES: WeaponSlot :: isTargetAlive(): UNKNOWN TARGET");
}

bool Turrel :: isTargetInSpace()
{
     if (target_type_id == SHIP_ID)
        if (target_ship->in_SPACE == true)
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
        if (target_ship->pTo_starsystem == slot->getShip()->pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == ASTEROID_ID)
        if (target_asteroid->starsystem == slot->getShip()->pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == MINERAL_ID)
        if (target_mineral->pTo_starsystem == slot->getShip()->pTo_starsystem)
           return true;
        else
           return false;

     if (target_type_id == CONTAINER_ID)
        if (target_container->pTo_starsystem == slot->getShip()->pTo_starsystem)
           return true;
        else
           return false;

     printf("ERROR MES: WeaponSlot :: isTargetOnTheSameStarSystem(): UNKNOWN TARGET");
}





bool Turrel :: isAmmoAvailable()
{
    if (slot->getItemSubType() == LAZER_ID)
       return true;
    if (slot->getItemSubType() == ROCKET_ID)
       if (slot->getRocketEquipment()->getAmmo() > 0)
          return true;

    return false;           
}




bool Turrel :: fireEvent_TRUE()
{
    if (slot->getItemSubType() == LAZER_ID)
    {   
       slot->getLazerEquipment()->fireEvent(this);
       slot->getLazerEquipment()->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           target_ship->hit_TRUE(slot->getLazerEquipment()->getDamage());
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           target_asteroid->hit_TRUE(slot->getLazerEquipment()->getDamage());
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           target_mineral->hit_TRUE(slot->getLazerEquipment()->getDamage());
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           target_container->hit_TRUE(slot->getLazerEquipment()->getDamage());
           return true;
       }
    }

    if (slot->getItemSubType() == ROCKET_ID)
    {   
       slot->getRocketEquipment()->fireEvent();
       slot->getRocketEquipment()->deterioration();
       return true; 
    }

    return false;
}





bool Turrel :: fireEvent_FALSE()
{
    if (slot->getItemSubType() == LAZER_ID)
    {   
       slot->getLazerEquipment()->deterioration();

       if (target_type_id == SHIP_ID) 
       { 
           target_ship->hit_FALSE(slot->getLazerEquipment()->getDamage());
           return true;
       } 

       if (target_type_id == ASTEROID_ID)  
       { 
           target_asteroid->hit_FALSE(slot->getLazerEquipment()->getDamage());
           return true;
       }

       if (target_type_id == MINERAL_ID)  
       { 
           target_mineral->hit_FALSE(slot->getLazerEquipment()->getDamage());
           return true;
       }

       if (target_type_id == CONTAINER_ID)  
       { 
           target_container->hit_FALSE(slot->getLazerEquipment()->getDamage());
           return true;
       }
    }

    if (slot->getItemSubType() == ROCKET_ID)
    {   
       slot->getRocketEquipment()->deterioration();
       return true; 
    }

    return false;
}











int Turrel :: returnTargetId()
{
    if (has_TARGET == true)
    {
        if (target_type_id == SHIP_ID)
           return target_ship->id;
        if (target_type_id == ASTEROID_ID)
           return target_asteroid->id;
        if (target_type_id == MINERAL_ID)
           return target_mineral->id;
        if (target_type_id == CONTAINER_ID)
           return target_container->id;

        printf("ERROR MES: WeaponSlot :: returnTargetId(): UNKNOWN TARGET");
    }
}


void Turrel :: setShipTarget(Ship* _ship)
{
     target_ship = _ship;
     target_type_id = target_ship->type_id;

     pTo_target_pos_x = &(target_ship->points.center_x);
     pTo_target_pos_y = &(target_ship->points.center_y);

     pTo_target_is_alive = &(target_ship->is_alive);
     has_TARGET = true;
}

void Turrel :: setAsteroidTarget(Asteroid* _asteroid)
{
     target_asteroid = _asteroid;
     target_type_id = target_asteroid->type_id;

     pTo_target_pos_x = &(target_asteroid->points.center_x);
     pTo_target_pos_y = &(target_asteroid->points.center_y);

     pTo_target_is_alive = &(target_asteroid->is_alive);
     has_TARGET = true;
}

void Turrel :: setMineralTarget(Mineral* _mineral)
{
     target_mineral = _mineral;
     target_type_id = target_mineral->type_id;

     pTo_target_pos_x = &(target_mineral->points.center_x);
     pTo_target_pos_y = &(target_mineral->points.center_y);

     pTo_target_is_alive = &(target_mineral->is_alive);
     has_TARGET = true;
}

void Turrel :: setContainerTarget(Container* _container)
{
     target_container = _container;
     target_type_id = target_container->type_id;

     pTo_target_pos_x = &(target_container->points.center_x);
     pTo_target_pos_y = &(target_container->points.center_y);

     pTo_target_is_alive = &(target_container->is_alive);
     has_TARGET = true;
}






void Turrel :: resetTarget()
{
     if (has_TARGET == true) 
     {  
        if (target_type_id == SHIP_ID)
           target_ship = NULL;
        if (target_type_id == ASTEROID_ID)
           target_asteroid = NULL;
        if (target_type_id == MINERAL_ID)
           target_mineral = NULL;
        if (target_type_id == CONTAINER_ID)
           target_container = NULL;

        pTo_target_pos_x = NULL;
        pTo_target_pos_y = NULL;
        pTo_target_is_alive = NULL;

        has_TARGET = false;  
     }  
}


void Turrel :: updatePosition(float _center_x, float _center_y, float _angle_inD)
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
