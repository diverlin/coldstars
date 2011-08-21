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


#include "navigator.h"


Navigator :: Navigator(Ship* _pTo_ship)
{
    pTo_ship = _pTo_ship;
   
    pTo_target_planet     = NULL;
    pTo_target_ship       = NULL;
    pTo_target_starsystem = NULL; 

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 

    docking_radius = 50;
}

Navigator :: ~Navigator()
{}
      
      
void Navigator :: setStaticTargetCoords(float _target_pos_x, float _target_pos_y)
{
    target_pos_x = _target_pos_x;
    target_pos_y = _target_pos_y;
    
    removeTargetPlanet();
    removeTargetShip(); 
    removeTargetStarSystem(); 
    
    pTo_ship->calculateDetaledWayToPosition();
}
      
      
void Navigator :: setTargetPlanet(Planet* _pTo_planet)
{
    removeTargetShip();
    removeTargetStarSystem(); 

    pTo_target_planet = _pTo_planet;
    pTo_ship->is_FOLLOWING_PLANET = true;

    pTo_target_pos_x = &pTo_target_planet->points.center_x;
    pTo_target_pos_y = &pTo_target_planet->points.center_y;

    docking_radius = 100;
}

void Navigator :: setTargetShip(Ship* _pTo_ship)
{    
    removeTargetPlanet();
    removeTargetStarSystem(); 

    pTo_target_ship = _pTo_ship;
    pTo_ship->is_FOLLOWING_SHIP = true;

    pTo_target_pos_x = &pTo_target_ship->points.center_x;
    pTo_target_pos_y = &pTo_target_ship->points.center_y;
}
    
void Navigator :: setTargetStarSystem(StarSystem* _pTo_starsystem)
{
    //target_pos_x = xxx;   jump point 
    //target_pos_y = yyy;

    removeTargetPlanet();
    removeTargetShip(); 

    pTo_target_starsystem = _pTo_starsystem;
    pTo_ship->is_FOLLOWING_STARSYSTEM = true;
}



void Navigator :: removeTargetPlanet()
{
    pTo_target_planet = NULL;
    pTo_ship->is_FOLLOWING_PLANET = false;

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetShip()
{
    pTo_target_ship = NULL;
    pTo_ship->is_FOLLOWING_SHIP = false;

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetStarSystem()
{
    pTo_target_starsystem = NULL;
    pTo_ship->is_FOLLOWING_STARSYSTEM = false;
}


bool Navigator :: updateTargetCoords()
{
    if (pTo_ship->is_FOLLOWING_PLANET == true)
    {
        target_pos_x = pTo_target_planet->orbit_vector_x[pTo_target_planet->step+TURN_TIME];   
        target_pos_y = pTo_target_planet->orbit_vector_y[pTo_target_planet->step+TURN_TIME];  
        pTo_ship->calculateDetaledWayToPosition();

        return true;
    } 
     
    if (pTo_ship->is_FOLLOWING_SHIP = true)
    {
        return true;    
    }      

    if (pTo_ship->is_FOLLOWING_STARSYSTEM = true)
    {
        return true;    
    }       
}


bool Navigator :: checkDocking()
{
     if (collisionBetweenCenters(pTo_ship->points.center_x, pTo_ship->points.center_y, (*pTo_target_pos_x), (*pTo_target_pos_y), docking_radius) == true)
        return true;
     else    
        return false;
}


bool Navigator :: getDockingPermission()
{
    if (pTo_ship->is_FOLLOWING_PLANET == true)
       return pTo_target_planet->getPermissionToLand();

    //if (pTo_ship->is_FOLLOWING_SHIP == true)
    //   return pTo_target_ship->getPermissionToLand();

    //if (pTo_ship->is_FOLLOWING_SPACESTATION == true)
    //   return pTo_target_spacestation->getPermissionToLand();
}

