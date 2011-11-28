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
        
	target_distance = 0.0;
	
	action_id = NONE_NAVIGATOR_ACTION_ID;
		
	direction_list_END = true;
}

Navigator :: ~Navigator()
{
	delete targetOb;
}
  
  
void  Navigator :: resetTarget()
{
	targetOb->reset();
    		
	target_distance = 0.0;
	target_offset.set(0, 0);
	action_id = NONE_NAVIGATOR_ACTION_ID;
	
	direction_list_END = true;
}
      
void Navigator :: setStaticTargetCoords(vec2f _target_pos)
{    
    	resetTarget();
        
    	target_pos = _target_pos;
       	calcDetaledWay();
}      
    
    
          		
template <typename TARGET_TYPE>
void Navigator :: setTarget(TARGET_TYPE* _target, int _action_id)
{
    	resetTarget();

	targetOb->setObject(_target);    
	
	defineDistance(_action_id);
}
  

void Navigator :: defineDistance(int _action_id)
{
	action_id = _action_id;
    	
    	switch(action_id)
    	{	
    		case DOCKING_NAVIGATOR_ACTION_ID:
    		{
    			target_distance = targetOb->getCollisionRadius()/4;
    			target_offset = getRandVec(targetOb->getCollisionRadius()/15, targetOb->getCollisionRadius()/10); 
    			
    			break;   		
    		}
    		
    		case COLLECTING_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = targetOb->getCollisionRadius()*1.2;
    			target_offset = getRandVec(targetOb->getCollisionRadius()/10, targetOb->getCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = targetOb->getCollisionRadius()*1.2;
    			target_offset = getRandVec(targetOb->getCollisionRadius()/10, targetOb->getCollisionRadius()/5); 
    			
    			break;    		
    		}

    		case FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = targetOb->getCollisionRadius()*2.5;
    			target_offset = getRandVec(targetOb->getCollisionRadius()/10, targetOb->getCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case FOLLOWING_FAR_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = targetOb->getCollisionRadius()*4;
    			target_offset = getRandVec(targetOb->getCollisionRadius()/10, targetOb->getCollisionRadius()/5); 
    			
    			break;    		
    		}

    	}
}
		
  
Planet* Navigator :: getTargetPlanet() const         { return targetOb->getPlanet(); }
TargetObject* Navigator :: getTargetOb() const       { return targetOb; } 

int Navigator :: getTargetTypeId()  const 	     { return targetOb->getObTypeId(); }                         

void Navigator :: update_inSpace_inStatic()
{
	targetValidation();
	
	updateTargetCoord();	
	calcDetaledWay();
}

void Navigator :: update_inSpace_inDynamic()
{
	updatePosition();
}

void Navigator :: targetValidation()
{	
	int _type_id = targetOb->getObTypeId();
	 
	if ( (_type_id == PLANET_ID) or (_type_id == STAR_ID) or (_type_id == ASTEROID_ID) )
	{
		 if (targetObValidation_dip1() == false)
		 {
		 	resetTarget();
		 	return;
		 }
		 else
		 {
		 	return;
		 }
	}
	
	if ( (_type_id == SHIP_ID) or (_type_id == MINERAL_ID) or (_type_id == CONTAINER_ID) )
	{
		if (targetObValidation_dip2() == false)
		{
			resetTarget();
		 	return;
		}
		else
		{
			return;
		}
	}
	
	
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



void Navigator :: updateTargetCoord()
{		
    	if (targetOb->getObTypeId() == STARSYSTEM_ID)
    	{ 
	    	target_pos.set(800, 800);  // get correct coords
    		target_distance = 100;  // ??        

        	return;	
	}

    	if (targetOb->getObTypeId() == PLANET_ID)
    	{ 
        	target_pos = targetOb->getPlanet()->getNextTurnPosition() + target_offset; 
        	
        	return;
    	} 

    	if (targetOb->getObTypeId() == ASTEROID_ID)
    	{ 
        	target_pos = targetOb->getAsteroid()->getNextTurnPosition() + target_offset; 
        	
        	return;
    	} 
    	     
    	if (targetOb->getObTypeId() == SHIP_ID)
    	{ 
		target_pos = targetOb->getShip()->getPoints()->getCenter() + target_offset;  

        	return;    
    	}      
}


bool Navigator :: checkEchievement()
{
	if (targetOb->getValid() == true)
	{
     		if (collisionBetweenCenters(ship_owner->getPoints(), target_pos, target_distance) == true)
     		{
        		return true;
        	}
	}
	
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





void Navigator :: calcDetaledWay() // not sure if speed will be better
{   
    	path_vec.clear();
    	angle_inD_vec.clear();
  
  	vec2f last_pos = ship_owner->getPoints()->getCenter();
    	
    	vec2f ll      = target_pos - last_pos;
    	       		
        if ( (ship_owner->propetries.speed > FLOAT_EPSILON) and (ll.isNull() == false) )
    	{
    		float step = ship_owner->propetries.speed/100.0;  // remove from here    
       		    		
		vec2f vstep = ll.getNorm() * step;

       		unsigned int it = ll.getLen() / step;
       		for(unsigned int i = 0; i < it; i++)
       		{
            		last_pos += vstep;
            		float angleInD = atan2(target_pos.y - last_pos.y, target_pos.x - last_pos.x) * RADIAN_TO_DEGREE_RATE;

            		path_vec.push_back(last_pos);
            		angle_inD_vec.push_back(angleInD);
       		}
		
		direction_list_END = false;
    	}
    
    	move_it = 0;
}


void Navigator :: updatePosition()
{
     	if (direction_list_END == false)
     	{
        	if (move_it < (path_vec.size() - 1))
        	{
           		ship_owner->getPoints()->setCenter(path_vec[move_it]);
           		ship_owner->getPoints()->setAngle(angle_inD_vec[move_it]);
           		move_it++;
        	}
        	else
        	{
           		direction_list_END = true;
           	}
     	}
}





    
//void Navigator :: calcDetaledWay()
//{   
    	//path_vec.clear();
    	//angle_inD_vec.clear();
  
    	//float last_pos_x = ship_owner->getPoints()->getCenter().x;
    	//float last_pos_y = ship_owner->getPoints()->getCenter().y;

    	//float step = ship_owner->propetries.speed/100.0;

        //printf("%f,%f,%f,%f\n", last_pos_x, last_pos_y, target_pos.x, target_pos.y);

        //if ( ( abs(last_pos_x - target_pos.x) > FLOAT_EPSILON ) || ( abs(last_pos_y - target_pos.y) > FLOAT_EPSILON ) )
        //if (ship_owner->propetries.speed > FLOAT_EPSILON) 
    	//{
       		//float xl = target_pos.x - last_pos_x;
       		//float yl = target_pos.y - last_pos_y;

       		//float l = sqrt(xl*xl + yl*yl);
       		//float x_normalized = xl/l;
       		//float y_normalized = yl/l;

       		//unsigned int it = l / step;

       		//float x_step = x_normalized * step;
       		//float y_step = y_normalized * step;

       		//for(unsigned int i = 0; i < it; i++)
       		//{
            		//last_pos_x += x_step;
            		//last_pos_y += y_step;
            		//float angleInD = atan2(target_pos.y - last_pos_y, target_pos.x - last_pos_x) * RADIAN_TO_DEGREE_RATE;

            		//path_vec.push_back( vec2f(last_pos_x, last_pos_y) );
            		//angle_inD_vec.push_back(angleInD);
       		//}
    	//}
    
    	//move_it = 0;

    	//direction_list_END = false;
//}

