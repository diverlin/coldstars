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


Navigator :: Navigator(Ship* _ship_owner)
{
        following_type_id = NONE_ID;
       
	ship_owner = _ship_owner;
   
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
	if (following_type_id == PLANET_ID)
    		target_planet = NULL;   	
	if (following_type_id == SHIP_ID)
    		target_ship = NULL;   	
    	if (following_type_id == STARSYSTEM_ID)
    		target_starsystem = NULL;
    		
    	following_type_id = NONE_ID;
	offset = 0.0;
    	pTo_target_pos = NULL;
}
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos, float _offset)
{    
    	removeTarget();
        
    	target_pos.set(_target_pos.x - _offset, _target_pos.y - _offset);
       	calcDetaledWay();
}
      
      
void Navigator :: setTarget(Planet* _target_planet)
{
    	removeTarget();

    	target_planet = _target_planet;
    	pTo_target_pos = target_planet->getPoints()->getpCenter();
    	echievement_radius = target_planet->getDockingRadius();
    	
     	following_type_id = target_planet->getTypeId();
}

void Navigator :: setTarget(Ship* _target_ship, float _offset)
{   
    	removeTarget();
	
    	target_ship = _target_ship;
    	offset = _offset;
    	pTo_target_pos = target_ship->getPoints()->getpCenter();
    	//docking_radius = target_planet->getDockingRadius();    // ??
    	following_type_id = target_ship->getTypeId();
}
    

void Navigator :: setTarget(StarSystem* _target_starsystem)
{   
    	removeTarget();
	
    	target_starsystem = _target_starsystem;
    	target_pos.set(800, 800);  // get correct coords
    	pTo_target_pos = &target_pos;
    	echievement_radius = 100;  // ??
    	following_type_id = target_starsystem->getTypeId();
        
        calcDetaledWay();
}



Planet* Navigator :: getTargetPlanet() const { return target_planet; }
StarSystem* Navigator :: getTargetStarSystem() const { return target_starsystem; }

int Navigator :: getFollowingTypeId()  const { return following_type_id; }                         


void Navigator :: updateDynamicTargetCoord()
{
    	if (following_type_id == PLANET_ID)
    	{ 
        	target_pos = target_planet->getNextTurnPosition(); 
                calcDetaledWay();
        	return;
    	} 
     
    	if (following_type_id == SHIP_ID)
    	{ 
    		if (offset > FLOAT_EPSILON)
    		{
    		    	// generate point where to move
    			float alpha = (float)getRandInt(0, 360) / 57.0;
   
    			target_pos.x = target_ship->getPoints()->getCenter().x + sin(alpha) * offset;
    			target_pos.y = target_ship->getPoints()->getCenter().y + cos(alpha) * offset;
    		}    		
    		else
    		{
    			target_pos = target_ship->getPoints()->getCenter();  
    		}
    		
        	calcDetaledWay();
        	return;    
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
    	if (following_type_id == PLANET_ID)
       		return target_planet->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SHIP == true)
    	//   return pTo_target_ship->getPermissionToLand();

    	//if (pTo_ship->is_FOLLOWING_SPACESTATION == true)
    	//   return pTo_target_spacestation->getPermissionToLand();
        
        return false;
}




    
void Navigator :: calcDetaledWay()
{   
    	direction_x_list.clear();
    	direction_y_list.clear();
    	angle_inD_list.clear();
  
    	float last_pos_x = ship_owner->getPoints()->getCenter().x;
    	float last_pos_y = ship_owner->getPoints()->getCenter().y;

    	float step = ship_owner->propetries.speed/100.0;

        //printf("%f,%f,%f,%f\n", last_pos_x, last_pos_y, target_pos.x, target_pos.y);

        if ( ( abs(last_pos_x - target_pos.x) > FLOAT_EPSILON ) || ( abs(last_pos_y - target_pos.y) > FLOAT_EPSILON ) )
        if (ship_owner->propetries.speed > FLOAT_EPSILON) 
    	{
       		float xl = target_pos.x - last_pos_x;
       		float yl = target_pos.y - last_pos_y;

       		float l = sqrt(xl*xl + yl*yl);
       		float x_normalized = xl/l;
       		float y_normalized = yl/l;

       		unsigned int it = l / step;

       		float x_step = x_normalized * step;
       		float y_step = y_normalized * step;

       		for(unsigned int i = 0; i < it; i++)
       		{
            		last_pos_x += x_step;
            		last_pos_y += y_step;
            		float angleInD = atan2(target_pos.y - last_pos_y, target_pos.x - last_pos_x) * RADIAN_TO_DEGREE_RATE;

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
