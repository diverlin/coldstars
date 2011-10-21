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
        following_type_id = NONE_ID;
       
	ship_owner = _ship;
   
	target_planet     = NULL;
    	target_ship       = NULL;
    	target_starsystem = NULL; 

    	pTo_target_pos = NULL;
        offset = 0;
        direction_list_END = true;
}

Navigator :: ~Navigator()
{}
  
  
void  Navigator :: removeTarget()
{
	if (following_type_id == PLANET_TYPE_ID)
    		target_planet = NULL;   	
	if (following_type_id == SHIP_ID)
    		target_ship = NULL;   	
    	if (following_type_id == STARSYSTEM_TYPE_ID)
    		target_starsystem = NULL;
    		
    	following_type_id = NONE_ID;
	offset = 0;
    	pTo_target_pos = NULL;
}
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos)
{    
    	removeTarget();
    	
        target_pos = _target_pos;
       	calculateDetaledWayToPosition();
}
      
      
//template <typename TARGET>
//void Navigator :: checkHuperJumpNecessary(TARGET _target)
//{
    	//if (ship->getStarSystem()->getId() != _target->getStarSystem()->getId())
    	//{
    		//JUMP_is_needed = true;
    		//target_starsystem = _target->getStarSystem();
    		//jump_pos.set(800, 800);
    	//}
	//else
	//{
	    	//JUMP_is_needed = false;
	    	//target_starsystem = NULL;
	    	//jump_pos.set(0, 0);
	//}
//}

      
      
      
void Navigator :: setTargetPlanet(Planet* _target_planet)
{
    	removeTarget();

    	target_planet = _target_planet;
    	pTo_target_pos = target_planet->getPoints()->getpCenter();
    	echievement_radius = target_planet->getDockingRadius();
    	
     	following_type_id = target_planet->getTypeId();
}

void Navigator :: setTargetShip(Ship* _target_ship, int _offset)
{   
    	removeTarget();
	
    	target_ship = _target_ship;
    	offset = _offset;
    	pTo_target_pos = target_ship->getPoints()->getpCenter();
    	//docking_radius = target_planet->getDockingRadius();    // ??
    	following_type_id = target_ship->getTypeId();
}
    

void Navigator :: setTargetStarSystem(StarSystem* _target_starsystem)
{   
    	removeTarget();
	
    	target_starsystem = _target_starsystem;
    	target_pos.set(800, 800);  // get correct coords
    	pTo_target_pos = &target_pos;
    	echievement_radius = 100;  // ??
    	following_type_id = target_starsystem->getTypeId();
}



Planet* Navigator :: getTargetPlanet() const { return target_planet; }
vec2f Navigator :: getTargetPos()      const { return target_pos; }
int Navigator :: getFollowingTypeId()  const { return following_type_id; }                         


bool Navigator :: updateDynamicTargetCoords()
{
    	if (following_type_id == PLANET_TYPE_ID)
    	{
        	target_pos.set(target_planet->getNextTurnPosition().x, target_planet->getNextTurnPosition().y);  
        	calculateDetaledWayToPosition();
        	return true;
    	} 
     
    	if (following_type_id == SHIP_ID)
    	{
    		if (offset != 0)
    		{
    		    	// gfenerate point where to move
    			float alpha = (float)getRandInt(0, 360) / 57.0;
   
    			target_pos.x = target_ship->getPoints()->getCenter().x + sin(alpha) * offset;
    			target_pos.y = target_ship->getPoints()->getCenter().y + cos(alpha) * offset;
    		}    		
    		else
    		{
    			target_pos = target_ship->getPoints()->getCenter();  
    		}
    		
        	calculateDetaledWayToPosition();
        	return true;    
    	}      
}


bool Navigator :: checkEchievement()
{
     	if (collisionBetweenCenters(ship_owner->getPoints(), pTo_target_pos->x, pTo_target_pos->y, echievement_radius) == true)
        	return true;
     	else    
        	return false;
}


bool Navigator :: getDockingPermission()
{
    	if (following_type_id == PLANET_TYPE_ID)
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
  
    	float last_pos_x = ship_owner->getPoints()->getCenter().x;
    	float last_pos_y = ship_owner->getPoints()->getCenter().y;

    	float step = ship_owner->propetries.speed/100.0;

    	if ( ((last_pos_x != getTargetPos().x) || (last_pos_y != getTargetPos().y)) && (ship_owner->propetries.speed != 0) )
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
           		ship_owner->getPoints()->setCenter(direction_x_list[move_it], direction_y_list[move_it]);
           		ship_owner->getPoints()->setAngle(angle_inD_list[move_it]);
           		move_it++;
        	}
        	else
        	{
           		direction_list_END = true;
           	}
     	}
}
