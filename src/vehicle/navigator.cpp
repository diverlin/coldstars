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
	ship_owner = _ship_owner;
   
        targetOb = new TargetObject(NULL);
        
	target_starsystem = NULL;
	offset = 0.0;
	direction_list_END = true;
}

Navigator :: ~Navigator()
{
	delete targetOb;
}
  
  
void  Navigator :: resetTarget()
{
	target_starsystem = NULL;
	targetOb->reset();
    		
	offset = 0.0;
	direction_list_END = true;
}
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos, float _offset)
{    
    	resetTarget();
        
    	target_pos.set(_target_pos.x - _offset, _target_pos.y - _offset);
       	calcDetaledWay();
}
      
      
void Navigator :: setTarget(Planet* _planet)
{
    	resetTarget();

    	targetOb->setObject(_planet);
    	echievement_radius = _planet->getDockingRadius();
}

void Navigator :: setTarget(Ship* _ship, float _offset)
{   
    	resetTarget();
	
    	targetOb->setObject(_ship);    	    	
    	offset = _offset;
    	//docking_radius = target_planet->getDockingRadius();    // ??
}
    

void Navigator :: setTarget(StarSystem* _starsystem) { target_starsystem = _starsystem; }



Planet* Navigator :: getTargetPlanet() const         { return targetOb->getPlanet(); }
StarSystem* Navigator :: getTargetStarSystem() const { return targetOb->getObStarSystem(); }

int Navigator :: getTargetTypeId()  const 	     { return targetOb->getObTypeId(); }                         

void Navigator :: update_inSpace_inStatic()
{
	targetValidation();
	isJumpNeeded();
	
	updateTargetCoord();	
	calcDetaledWay();
}

void Navigator :: update_inSpace_inDynamic()
{
	updatePosition();
}

void Navigator :: targetValidation()
{
	if ( target_starsystem == ship_owner->getStarSystem() )
	{
		target_starsystem = NULL;
	}
	
	int _type_id = targetOb->getObTypeId();
	 
	if ( (_type_id == PLANET_ID) or (_type_id == STAR_ID) or (_type_id == ASTEROID_ID) )
	{
		 if (targetObValidation_dip1() == true)
		 {
		 	return;
		 }
	}
	
	if ( (_type_id == SHIP_ID) or (_type_id == MINERAL_ID) or (_type_id == CONTAINER_ID) )
	{
		if (targetObValidation_dip2() == true)
		{
		 	return;
		}
	}
	
	resetTarget();
}

bool Navigator :: targetObValidation_dip1() const
{
	if (targetOb->getAlive() == true)
	{
		return true;
	}
	
	return false;
}


bool Navigator :: targetObValidation_dip2() const
{
	if (targetOb->getAlive() == true)
	{
		if (targetOb->getObPlaceTypeId() == SPACE_ID)
		{
			return true;
		}
	}
	
	return false;
}


void Navigator :: isJumpNeeded()
{
	if (targetOb->getObStarSystem() != ship_owner->getStarSystem())
	{
		target_starsystem = targetOb->getObStarSystem();
	}
}

void Navigator :: updateTargetCoord()
{		
	if (target_starsystem != NULL)
	{
	    	target_pos.set(800, 800);  // get correct coords
    		echievement_radius = 100;  // ??        

        	return;	
	}

    	if (targetOb->getObTypeId() == PLANET_ID)
    	{ 
        	target_pos = targetOb->getPlanet()->getNextTurnPosition(); 
        	
        	return;
    	} 
     
    	if (targetOb->getObTypeId() == SHIP_ID)
    	{ 
    		vec2f _target_offset;
    		if (offset > FLOAT_EPSILON)
    		{
    			_target_offset = getRandVec(offset, offset);
    		}    		

		target_pos = targetOb->getShip()->getPoints()->getCenter() + _target_offset;  

        	return;    
    	}      
}


bool Navigator :: checkEchievement()
{
     	if (collisionBetweenCenters(ship_owner->getPoints(), *targetOb->getpCenter(), echievement_radius) == true)
        	return true;
     	else    
        	return false;
}


bool Navigator :: getDockingPermission()
{
    	if (targetOb->getObTypeId() == PLANET_ID)
       		return targetOb->getPlanet()->getPermissionToLand();

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


