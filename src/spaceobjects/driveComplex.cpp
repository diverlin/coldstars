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


DriveComplex :: DriveComplex(Vehicle* owner_vehicle)
{      
	this->owner_vehicle = owner_vehicle;
   
        target = NULL;
        
	resetTarget();
	
	drive_slot   = new ItemSlot(DRIVE_SLOT_ID, owner_vehicle, owner_vehicle->getSlotTexOb());
			
	drive_slot->setRect(  owner_vehicle->getKonturRect().getCenter().x - 5*SHIP_SLOT_WIDTH, 
			      owner_vehicle->getKonturRect().getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT/2,
			      SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				  
	owner_vehicle->add(drive_slot);
	
	
	bak_slot     = new ItemSlot(BAK_SLOT_ID, owner_vehicle,  owner_vehicle->getSlotTexOb());
				    
	bak_slot->setRect(  owner_vehicle->getKonturRect().getCenter().x - 5*SHIP_SLOT_WIDTH, 
			    owner_vehicle->getKonturRect().getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT/2,
			    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	owner_vehicle->add(bak_slot);
}

DriveComplex :: ~DriveComplex()
{
	delete drive_slot;
        delete bak_slot;
}
  
  
ItemSlot* DriveComplex :: getDriveSlot()     const { return drive_slot; }
ItemSlot* DriveComplex :: getBakSlot()       const { return bak_slot; }

BaseGameEntity* DriveComplex :: getTarget() const { return target; }  

void  DriveComplex :: resetTarget()
{
	target = NULL;
    		
	target_distance = 0.0;
	target_offset.set(0, 0);
	action_id = NONE_NAVIGATOR_ACTION_ID;
	
	direction_list_END = true;
}
      
void DriveComplex :: setStaticTargetCoords(vec2f _target_pos)
{    
    	resetTarget();
        
    	target_pos = _target_pos;
       	calcPath();
}      
    
    
          		
void DriveComplex :: setTarget(BaseGameEntity* target, int _action_id)
{
    	resetTarget();

	this->target = target;    
	
	defineDistance(_action_id);
}
  

void DriveComplex :: defineDistance(int _action_id)
{
	action_id = _action_id;
    	
    	switch(action_id)
    	{	
    		case DOCKING_NAVIGATOR_ACTION_ID:
    		{
    			target_distance = target->getCollisionRadius()/4;
    			target_offset = getRandVec(target->getCollisionRadius()/15, target->getCollisionRadius()/10); 
    			
    			break;   
    		}
    		
    		case COLLECTING_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = target->getCollisionRadius()*1.2;
    			target_offset = getRandVec(target->getCollisionRadius()/10, target->getCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = target->getCollisionRadius()*1.2;
    			target_offset = getRandVec(target->getCollisionRadius()/10, target->getCollisionRadius()/5); 
    			
    			break;    		
    		}

    		case FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = target->getCollisionRadius()*2.5;
    			target_offset = getRandVec(target->getCollisionRadius()/10, target->getCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case FOLLOWING_FAR_NAVIGATOR_ACTION_ID:
    		{
    		    	target_distance = target->getCollisionRadius()*4;
    			target_offset = getRandVec(target->getCollisionRadius()/10, target->getCollisionRadius()/5); 
    			
    			break;    
    		}

    	}
}
                      

void DriveComplex :: update_inSpace_inStatic()
{
	if (target != NULL)
	{
		validateTarget();
		updateTargetCoord();
	}
	calcPath();
}

void DriveComplex :: update_inSpace_inDynamic()
{
	updatePosition();
}

bool DriveComplex :: validateTarget() const
{
        if (target->getAlive() == true)
	{
		if (target->getPlaceTypeId() == SPACE_ID)
		{
			return true;
		}
	}
	
	return false;
}



bool DriveComplex :: updateTargetCoord()
{		
	switch(target->getTypeId())
	{
    		case STARSYSTEM_ID:
    		{
    	 	    	target_pos.set(800, 800);  // get correct coords
    			target_distance = 100;  // ??      		
        		return false; break;        			
		}

    		case PLANET_ID:
    		{ 
        		target_pos = ((Planet*)target)->getOrbit()->getNextTurnPosition() + target_offset;         	
		       	return true; break;		       	
    		} 

    		case ASTEROID_ID:
    		{ 
        		target_pos = ((Asteroid*)target)->getOrbit()->getNextTurnPosition() + target_offset;         	
        		return true; break;
    		} 
    	     
    		case SHIP_ID:
    		{ 
			target_pos = target->getPoints()->getCenter() + target_offset;  
        		return true; break;    
    		}      
    		
    		case SPACESTATION_ID:
    		{ 
			target_pos = target->getPoints()->getCenter() + target_offset;  
        		return true; break;    
    		} 
    	}
}


bool DriveComplex :: checkEchievement()
{
	if (target != NULL)
	{
     		if (collisionBetweenCenters(owner_vehicle->getPoints(), target_pos, target_distance) == true)
     		{
        		return true;
        	}
	}
	
	return false;
}


bool DriveComplex :: getDockingPermission()
{
	switch(target->getTypeId())
	{
		case PLANET_ID:       { return ((Planet*)target)->getLand()->getPermissionToLand(); break; }
		case SPACESTATION_ID: { return ((SpaceStation*)target)->getLand()->getPermissionToLand(); break; }
		//case SHIP_ID:   { return targetOb->getVehicle()->getPermissionToLand(); break; }
	}
	
        return false;
}


void DriveComplex :: calcPath()
{
	path_vec.clear();
	angle_inD_vec.clear();
    	    	
	vec2f mid = calcRoundPath();
	calcDirectPath(mid);

	if (path_vec.size() > 1)
	{
		direction_list_END = false;
               
       		visual_path.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue->texture, &path_vec, 10, 10);
       		move_it = 0;
       	}
}






//void DriveComplex :: calcDirectPath() 
//{   
    	////path_vec.clear();
    	////angle_inD_vec.clear();
  
  	//vec2f last_pos = ship_owner->getPoints()->getCenter();
    	
    	//vec2f ll = target_pos - last_pos;
    	       		
        //if ( (ship_owner->propetries.speed > FLOAT_EPSILON) and (ll.isNull() == false) )
    	//{
    		//float step = ship_owner->propetries.speed/100.0;  // remove from here    
       		    		
		//vec2f vstep = ll.getNorm() * step;

       		//unsigned int it = ll.getLen() / step;
       		//for(unsigned int i = 0; i < it; i++)
       		//{
            		//last_pos += vstep;
            		//float angleInD = atan2(target_pos.y - last_pos.y, target_pos.x - last_pos.x) * RADIAN_TO_DEGREE_RATE;

            		//path_vec.push_back(last_pos);
            		//angle_inD_vec.push_back(angleInD);
       		//}
		
		//direction_list_END = false;
                
                //visual_path.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue->texture, &path_vec, 10, 10);
    	//}
    
    	//move_it = 0;
//}



vec2f DriveComplex :: calcRoundPath()  // not working yet
{
        // vychislenie centrov okruzhnostej traektorij na osnovanii tekuwego polozhenija ob'ekta 
        float start_angle_inD = owner_vehicle->getPoints()->getAngleDegree();
        vec2f start_pos = owner_vehicle->getPoints()->getCenter();
        
        float R = 100.0f; //(float)getRandInt(80, 130);
                        
        float gamma1 = (start_angle_inD + 90) / RADIAN_TO_DEGREE_RATE;
        float gamma2 = (start_angle_inD - 90) / RADIAN_TO_DEGREE_RATE;
                
        float center1_x = start_pos.x + R * cos(gamma1);
        float center1_y = start_pos.y + R * sin(gamma1);

        float center2_x = start_pos.x + R * cos(gamma2);
        float center2_y = start_pos.y + R * sin(gamma2);
       
        // find closest center
        float len_toCenter1 = distBetweenPoints(target_pos, center1_x, center1_y);
        float len_toCenter2 = distBetweenPoints(target_pos, center2_x, center2_y);

        float rotation_center_x, rotation_center_y;
        if (len_toCenter1 < len_toCenter2)
        {
                rotation_center_x = center1_x; 
                rotation_center_y = center1_y;
        }
        else
        {
                rotation_center_x = center2_x; 
                rotation_center_y = center2_y;
        }
        
        // vychislenija tochek kasanija k okruzhnosti lucha isxodjawego iz target_xy 
        float dx = target_pos.x - rotation_center_x;
        float dy = target_pos.y - rotation_center_y;

        float L = sqrt(dx*dx + dy*dy);

        float L1 = sqrt(L*L - R*R);  // teorema pifagora
        float a1 = asin((rotation_center_x - target_pos.x) / L);
        float b1 = asin(R / L);

        int k;        
        if (rotation_center_y < target_pos.y) 
        {
                k = -1;
        }
        else
        {
                k = 1;
        }
        

        float xk1 = target_pos.x +     L1 * sin(a1 - b1);    
        float yk1 = target_pos.y + k * L1 * cos(a1 - b1);
           
        float xk2 = target_pos.x +     L1 * sin(a1 + b1);     
        float yk2 = target_pos.y + k * L1 * cos(a1 + b1);         

      
        float len1 = distBetweenPoints(owner_vehicle->getPoints()->getCenter(), xk1, yk1);
        float len2 = distBetweenPoints(owner_vehicle->getPoints()->getCenter(), xk2, yk2);
           
        
           
           
           
           
        float xx = 1;
        float xy = 0;
        
        float ax = cos(start_angle_inD/RADIAN_TO_DEGREE_RATE);
        float ay = sin(start_angle_inD/RADIAN_TO_DEGREE_RATE);
        //printf("ax = %f \n",  ax);  
        //printf("ay = %f \n",  ay);  

        float bx = target_pos.x                              - owner_vehicle->getPoints()->getCenter().x;
        float by = target_pos.y                              - owner_vehicle->getPoints()->getCenter().y;

        float dax = cos(start_angle_inD/RADIAN_TO_DEGREE_RATE);
        float day = sin(start_angle_inD/RADIAN_TO_DEGREE_RATE);  
                        
        float dbx = owner_vehicle->getPoints()->getCenter().x - target_pos.x;
        float dby = owner_vehicle->getPoints()->getCenter().y - target_pos.y;

        float la = sqrt(dax*dax+day*day);
        float lb = sqrt(dbx*dbx+dby*dby);
        float lx = 1;

        //float angle_diff_ax  = PI - acos((ax*xx+ay*xy)/(la*lx));
        float angle_diff_ax  = acos((ax*xx+ay*xy)/(la*lx));
        float angle_diff_bx  = acos((bx*xx+by*xy)/(lb*lx));
        
         
        // 0 - 180 ->> 0 - 360
        if (ay < 0)
        {	
        	angle_diff_ax *= -1;
        }

        if (by < 0)
        {	
        	angle_diff_bx *= -1;
        }
        
        if (angle_diff_ax < 0)
        {	
        	angle_diff_ax = 2*PI + angle_diff_ax;
        }
        
        
        if (angle_diff_bx < 0)
        {	
        	angle_diff_bx = 2*PI + angle_diff_bx;
        }
                                
        //float angle_diff  = fabs(angle_diff_ax) - fabs(angle_diff_bx);
        float angle_diff  = angle_diff_bx - angle_diff_ax;
        
        //printf("angle_diff_ax = %f \n",  angle_diff_ax * RADIAN_TO_DEGREE_RATE);       
        //printf("angle_diff_bx = %f \n",  angle_diff_bx * RADIAN_TO_DEGREE_RATE);       
        //printf("angle_diff = %f \n",  angle_diff * RADIAN_TO_DEGREE_RATE);
        
        
        if (fabs(angle_diff) < 3/RADIAN_TO_DEGREE_RATE) //  if difference is low there is no need to calculate rounded path
        {
      		return start_pos;     	
        }
        
        bool clockwise;
        if ( (angle_diff > 0) and (angle_diff < PI) )
        {
           	clockwise = true;
        }
        if ( (angle_diff < 0) and (angle_diff > -PI) )
        {
           	clockwise = false;
        }        
        if ( angle_diff > PI )
        {
           	clockwise = false;
        }
        if ( angle_diff < -PI )
        {
           	clockwise = true;
        }
        
        
        bool closest_k;	
        if ( (fabs(angle_diff) < PI/2 ) or (fabs(angle_diff) > 3*PI/2))
        {
           	closest_k = true;
        }
        else
        {
           	closest_k = false;
        }
        
        
        float xk; 
        float yk;
        if (len1 <= len2) 
        {
        	if (closest_k == true)
        	{
                	xk = xk1; 
                	yk = yk1;
        	}
        	else
        	{
        	        xk = xk2; 
               		yk = yk2;
        	}
        }
        else
        {
                if (closest_k == true)
        	{
                	xk = xk2; 
                	yk = yk2;
        	}
        	else
        	{
        	        xk = xk1; 
               		yk = yk1;
        	}
        }
               
        
        c1c2_vec.clear();                                                                                 // debug
        rc_vec.clear();                                                                                   // debug
        k1k2_vec.clear();                                                                                 // debug
        k_vec.clear();                                                                                    // debug
        target_vec.clear();                                                                               // debug
        
        c1c2_vec.push_back(vec2f(center1_x, center1_y)); c1c2_vec.push_back(vec2f(center2_x, center2_y)); // debug
        rc_vec.push_back(vec2f(rotation_center_x, rotation_center_y));                                    // debug
        k1k2_vec.push_back(vec2f(xk1, yk1)); k1k2_vec.push_back(vec2f(xk2, yk2));                         // debug
        k_vec.push_back(vec2f(xk, yk));                                                                   // debug
        target_vec.push_back(target_pos);                                                                 // debug
        
        visual_c1c2.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_yellow->texture, &c1c2_vec, 1, 20);     // debug
        visual_rc.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_red->texture, &rc_vec, 1, 10);            // debug
        visual_k1k2.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_green->texture, &k1k2_vec, 1, 20);      // debug   
        visual_k.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_red->texture, &k_vec, 1, 10);              // debug  
        visual_target.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_red->texture, &target_vec, 1, 10);    // debug
                
                

        
        float angle = start_angle_inD/RADIAN_TO_DEGREE_RATE;
        vec2f new_pos = start_pos;
        
        float d_a = 0.02;
        
        vec2f prev_pos;
        float angleInD;

        if (clockwise == true)
        {                
                while ( (abs(xk - new_pos.x) > 3.0f) or (abs(yk - new_pos.y) > 3.0f) )
                {
                        angle += d_a;
                        
			prev_pos = new_pos;
			
                        new_pos.x = rotation_center_x + R * cos(angle - PI/2);    
                        new_pos.y = rotation_center_y + R * sin(angle - PI/2);
                        
            		angleInD = atan2(new_pos.y - prev_pos.y, new_pos.x - prev_pos.x) * RADIAN_TO_DEGREE_RATE;

            		path_vec.push_back(new_pos);
            		angle_inD_vec.push_back(angleInD);
                }
        }
        else
        {
                while ( (abs(xk - new_pos.x) > 3.0f) or (abs(yk - new_pos.y) > 3.0f) )
                {
                        angle -= d_a;
                        
                        prev_pos = new_pos;
                        			
                        new_pos.x = rotation_center_x + R * cos(angle + PI/2);    
                        new_pos.y = rotation_center_y + R * sin(angle + PI/2);

            		angleInD = atan2(new_pos.y - prev_pos.y, new_pos.x - prev_pos.x) * RADIAN_TO_DEGREE_RATE;
            		
            		path_vec.push_back(new_pos);
            		angle_inD_vec.push_back(angleInD);       		
                }
        }
        
        return vec2f(xk, yk);
}



void DriveComplex :: calcDirectPath(vec2f start_pos) 
{   
    	vec2f ll = target_pos - start_pos;
    	vec2f new_pos = start_pos;
    	       		
        if ( (owner_vehicle->propetries.speed > FLOAT_EPSILON) and (ll.isNull() == false) )
    	{
    		float step = owner_vehicle->propetries.speed/100.0;  // remove from here    
       		    		
		vec2f vstep = ll.getNorm() * step;

       		unsigned int it = ll.getLen() / step;
       		for(unsigned int i = 0; i < it; i++)
       		{
            		new_pos += vstep;
            		float angleInD = atan2(target_pos.y - new_pos.y, target_pos.x - new_pos.x) * RADIAN_TO_DEGREE_RATE;

            		path_vec.push_back(new_pos);
            		angle_inD_vec.push_back(angleInD);
       		}
    	}
}




void DriveComplex :: updatePosition()
{
     	if (direction_list_END == false)
     	{
        	if (move_it < (path_vec.size() - 1))
        	{
           		owner_vehicle->getPoints()->setCenter(path_vec[move_it]);
           		owner_vehicle->getPoints()->setAngle(angle_inD_vec[move_it]);
           		move_it++;
        	}
        	else
        	{
           		direction_list_END = true;
           	}
     	}
}

void DriveComplex :: drawPath()
{
        if (direction_list_END == false)
        {
                visual_path.draw();

        	//visual_c1c2.draw();   // debug
        	//visual_rc.draw();     // debug
        	//visual_k1k2.draw();   // debug
        	visual_k.draw();      // debug
        	visual_target.draw(); // debug
        }
}


