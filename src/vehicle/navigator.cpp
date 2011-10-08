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


#include "navigator.hpp"


Navigator :: Navigator(Ship* _ship)
{
        following_TYPE_ID = NONE_ID;
       
	ship = _ship;
   
	target_planet     = NULL;
    	target_ship       = NULL;
    	target_starsystem = NULL; 

    	pTo_target_pos = NULL;
        
        direction_list_END = true;
}

Navigator :: ~Navigator()
{}
      
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos)
{
    	target_pos = _target_pos;
    
    	removeTargetPlanet();
    	removeTargetShip(); 
    	removeTargetStarSystem(); 
    
    	calculateDetaledWayToPosition();
}
      
      
void Navigator :: setTargetPlanet(Planet* _planet)
{
    	removeTargetShip();
    	removeTargetStarSystem(); 

    	target_planet = _planet;
    	following_TYPE_ID = target_planet->getTypeId();

    	pTo_target_pos = target_planet->getPoints()->getpCenter();

    	docking_radius = target_planet->getDockingRadius();
}

void Navigator :: setTargetShip(Ship* _target_ship)
{    
    	removeTargetPlanet();
    	removeTargetStarSystem(); 

    	target_ship = _target_ship;
        following_TYPE_ID = target_ship->getTypeId();

    	pTo_target_pos = target_ship->getPoints()->getpCenter();
}
    
void Navigator :: setTargetStarSystem(StarSystem* _target_starsystem)
{
    	//target_pos_x = xxx;   jump point 
    	//target_pos_y = yyy;

    	removeTargetPlanet();
    	removeTargetShip(); 

    	target_starsystem = _target_starsystem;
        following_TYPE_ID = target_starsystem->getTypeId();
}

void Navigator :: setFollowingTypeID(int _type_id) { following_TYPE_ID = _type_id; }



Planet* Navigator :: getTargetPlanet() const { return target_planet; }
vec2f Navigator :: getTargetPos() const { return target_pos; }
int Navigator :: getFollowingTypeID() const { following_TYPE_ID; }                         

void Navigator :: removeTargetPlanet()
{
    	target_planet = NULL;
    	following_TYPE_ID = NONE_ID;

    	pTo_target_pos = NULL;
}

void Navigator :: removeTargetShip()
{
    	target_ship = NULL;
    	following_TYPE_ID = NONE_ID;

    	pTo_target_pos = NULL;
}

void Navigator :: removeTargetStarSystem()
{
    	target_starsystem = NULL;
    	following_TYPE_ID = NONE_ID;
}


bool Navigator :: updateTargetCoords()
{
    	if (following_TYPE_ID == PLANET_TYPE_ID)
    	{
        	target_pos.set(target_planet->getNextTurnPosition().x,    
       	 		       target_planet->getNextTurnPosition().y);  
        	calculateDetaledWayToPosition();

        	return true;
    	} 
     
    	if (following_TYPE_ID == SHIP_ID)
    	{
        	return true;    
    	}      

    	if (following_TYPE_ID  = STARSYSTEM_TYPE_ID)
    	{
        	return true;    
    	}       
}


bool Navigator :: checkDocking()
{
     	if (collisionBetweenCenters(ship->getPoints(), pTo_target_pos->x, pTo_target_pos->y, docking_radius) == true)
        	return true;
     	else    
        	return false;
}


bool Navigator :: getDockingPermission()
{
    	if (following_TYPE_ID == PLANET_TYPE_ID)
       		return target_planet->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SHIP == true)
    	//   return pTo_target_ship->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SPACESTATION == true)
    	//   return pTo_target_spacestation->getPermissionToLand();
}




    
void Navigator :: calculateDetaledWayToPosition()
{   
    	direction_x_list.clear();
    	direction_y_list.clear();
    	angle_inD_list.clear();
  
    	float last_pos_x = ship->getPoints()->getCenter().x;
    	float last_pos_y = ship->getPoints()->getCenter().y;

    	float step = ship->speed/100.0;

    	if ( ((last_pos_x != getTargetPos().x) || (last_pos_y != getTargetPos().y)) && (ship->speed != 0) )
    	{
       		float xl = getTargetPos().x - last_pos_x;
       		float yl = getTargetPos().y - last_pos_y;

       		float l = sqrt(xl*xl + yl*yl);
       		float x_normalized = xl/l;
       		float y_normalized = yl/l;

       		int it = l / step;

       		float x_step = x_normalized * step;
       		float y_step = y_normalized * step;

       		for(unsigned int i = 0; i < it; i++)
       		{
            		last_pos_x += x_step;
            		last_pos_y += y_step;
            		float angleInD = atan2(getTargetPos().y - last_pos_y, getTargetPos().x - last_pos_x) * RADIAN_TO_DEGREE_RATE;

            		direction_x_list.push_back(last_pos_x);
            		direction_y_list.push_back(last_pos_y);
            		angle_inD_list.push_back(angleInD);
       		}
    	}
    
    	move_it = 0;
    	len_direction_list = direction_x_list.size();

    	direction_list_END = false;
}


void Navigator :: updatePosition()
{
     	if (direction_list_END == false)
     	{
        	if (move_it < (len_direction_list - 1))
        	{
           		ship->getPoints()->setCenter(direction_x_list[move_it], direction_y_list[move_it]);
           		ship->getPoints()->setAngle(angle_inD_list[move_it]);
           		move_it++;
        	}
        	else
           		direction_list_END = true;
     	}
}
