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


Navigator :: Navigator(Ship* _ship)
{
	ship = _ship;
   
	target_planet     = NULL;
    	target_ship       = NULL;
    	target_starsystem = NULL; 

    	pTo_target_pos_x = NULL;
    	pTo_target_pos_y = NULL; 

    	docking_radius = 50;
}

Navigator :: ~Navigator()
{}
      
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos)
{
    	target_pos = _target_pos;
    
    	removeTargetPlanet();
    	removeTargetShip(); 
    	removeTargetStarSystem(); 
    
    	ship->calculateDetaledWayToPosition();
}
      
      
void Navigator :: setTargetPlanet(Planet* _pTo_planet)
{
    	removeTargetShip();
    	removeTargetStarSystem(); 

    	target_planet = _pTo_planet;
    	ship->is_FOLLOWING_PLANET = true;

    	pTo_target_pos_x = &target_planet->getPoints()->getCenter().x;
    	pTo_target_pos_y = &target_planet->getPoints()->getCenter().y;

    	docking_radius = 100;
}

void Navigator :: setTargetShip(Ship* _target_ship)
{    
    	removeTargetPlanet();
    	removeTargetStarSystem(); 

    	target_ship = _target_ship;
    	ship->is_FOLLOWING_SHIP = true;

    	pTo_target_pos_x = &target_ship->getPoints()->getCenter().x;
    	pTo_target_pos_y = &target_ship->getPoints()->getCenter().y;
}
    
void Navigator :: setTargetStarSystem(StarSystem* _target_starsystem)
{
    	//target_pos_x = xxx;   jump point 
    	//target_pos_y = yyy;

    	removeTargetPlanet();
    	removeTargetShip(); 

    	target_starsystem = _target_starsystem;
    	ship->is_FOLLOWING_STARSYSTEM = true;
}


Planet* Navigator :: getTargetPlanet() const { return target_planet; }


vec2f Navigator :: getTargetPos() const { return target_pos; }
                              

void Navigator :: removeTargetPlanet()
{
    	target_planet = NULL;
    	ship->is_FOLLOWING_PLANET = false;

    	pTo_target_pos_x = NULL;
    	pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetShip()
{
    	target_ship = NULL;
    	ship->is_FOLLOWING_SHIP = false;

    	pTo_target_pos_x = NULL;
    	pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetStarSystem()
{
    	target_starsystem = NULL;
    	ship->is_FOLLOWING_STARSYSTEM = false;
}


bool Navigator :: updateTargetCoords()
{
    	if (ship->is_FOLLOWING_PLANET == true)
    	{
        	target_pos.set(target_planet->getNextTurnPosition().x,    
       	 		       target_planet->getNextTurnPosition().y);  
        	ship->calculateDetaledWayToPosition();

        	return true;
    	} 
     
    	if (ship->is_FOLLOWING_SHIP = true)
    	{
        	return true;    
    	}      

    	if (ship->is_FOLLOWING_STARSYSTEM = true)
    	{
        	return true;    
    	}       
}


bool Navigator :: checkDocking()
{
     	if (collisionBetweenCenters(ship->getPoints(), (*pTo_target_pos_x), (*pTo_target_pos_y), docking_radius) == true)
        	return true;
     	else    
        	return false;
}


bool Navigator :: getDockingPermission()
{
    	if (ship->is_FOLLOWING_PLANET == true)
       		return target_planet->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SHIP == true)
    	//   return pTo_target_ship->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SPACESTATION == true)
    	//   return pTo_target_spacestation->getPermissionToLand();
}

