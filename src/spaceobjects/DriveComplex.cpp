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


DriveComplex::DriveComplex(Vehicle* owner_vehicle)
{      
	this->owner_vehicle = owner_vehicle;
        
	ResetTarget();

	drive_effect = NULL; 
}

DriveComplex::~DriveComplex()
{      
        delete drive_effect;
}

void DriveComplex::ResetTarget()
{
	target = NULL;
    		
	target_distance = 0.0;
	target_offset.Set(0, 0);
	target_pos.Set(0, 0);
	action_id = NAVIGATOR_ACTION::NONE_ID;
	
	direction_list_END = true;
	
	//std::cout<<"drive_complex reset target"<<std::endl;
}
      
void DriveComplex::SetStaticTargetCoords(const vec2f& target_pos)
{    
    	ResetTarget();
        
    	this->target_pos = target_pos;
    	
       	UpdatePath();
}      
    
    
          		
void DriveComplex::SetTarget(BaseGameEntity* target, int _action_id)
{
    	ResetTarget();

	this->target = target;    
	
	DefineDistance(_action_id);
	
	UpdatePath();
}
  

void DriveComplex::DefineDistance(int action_id)
{
	this->action_id = action_id;
    	
    	switch(action_id)
    	{	
    		case NAVIGATOR_ACTION::DOCKING_ID:
    		{
    			target_distance = target->GetCollisionRadius()/4;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/15, target->GetCollisionRadius()/10); 
    			
    			break;   
    		}
    		
    		case NAVIGATOR_ACTION::COLLECTING_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*1.2;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/10, target->GetCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case NAVIGATOR_ACTION::KEEP_CLOSE_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*1.2;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/10, target->GetCollisionRadius()/5); 
    			
    			break;    		
    		}

    		case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*2.5;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/10, target->GetCollisionRadius()/5); 
    			
    			break;    		
    		}
    		
    		case NAVIGATOR_ACTION::KEEP_FAR_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*4;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/10, target->GetCollisionRadius()/5); 
    			
    			break;    
    		}

    	}
}
                  
void DriveComplex::UpdatePath()
{
	if (target != NULL)
	{
		if (ValidateTarget() == true)
		{
			UpdateTargetCoord();
		}
		else
		{
			ResetTarget();
		}
	}
	CalcPath();
}

bool DriveComplex::ValidateTarget() const
{
        if (target->GetAlive() == true)
	{
		if (target->GetPlaceTypeId() == ENTITY::SPACE_ID)
		{
			return true;
		}
	}
	
	return false;
}



bool DriveComplex::UpdateTargetCoord()
{		
	switch(target->GetTypeId())
	{
    		case ENTITY::STARSYSTEM_ID:
    		{
    	 	    	target_pos.Set(800, 800);  // get correct coords
    			target_distance = 100;  // ??      		
        		return false; break;        			
		}

    		case ENTITY::PLANET_ID:
    		{ 
        		target_pos = ((Planet*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;         	
		       	return true; break;		       	
    		} 

    		case ENTITY::ASTEROID_ID:
    		{ 
        		target_pos = ((Asteroid*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;         	
        		return true; break;
    		} 
    	     
    		case ENTITY::VEHICLE_ID:
    		{ 
			target_pos = target->GetPoints().GetCenter() + target_offset;  
        		return true; break;    
    		}
    	}
}


bool DriveComplex::CheckTargetEchievement()
{
	if (target != NULL)
	{
     		if (collisionBetweenCenters(owner_vehicle->GetPoints(), target_pos, target_distance) == true)
     		{
        		return true;
        	}
	}
	
	return false;
}


bool DriveComplex::GetDockingPermission()
{
	switch(target->GetTypeId())
	{
		case ENTITY::PLANET_ID:       { return ((Planet*)target)->GetLand()->GetPermissionToLand(); break; }
		case ENTITY::VEHICLE_ID: 
		{ 
			switch(target->GetSubTypeId())
			{
				case ENTITY::SPACESTATION_ID: { return ((SpaceStation*)target)->GetLand()->GetPermissionToLand(); break; }
				//case SHIP_ID:   { return targetOb->GetVehicle()->getPermissionToLand(); break; }
			}
			break;
		}
	}
	
        return false;
}

void DriveComplex::ClearPath()
{
	path_center_vec.clear();
	//debug_midLeft_vec.clear();
	angle_inD_vec.clear();
}

void DriveComplex::CalcPath()
{
	ClearPath();
	
       	visual_center_path.FillData(GuiTextureObCollector::Instance().dot_blue->texture, &path_center_vec, 10, 10);
       		
    	//if ( (distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target_pos) < 300) or (target_pos.x == 0 and target_pos.y == 0) ) // hack
    	//if (distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target_pos) < 300)
    	if (target_pos.x == 0 and target_pos.y == 0)
    	{
    		return;
    	}
    	  
	if (CalcRoundPath() == true)
	{        	
		CalcDirectPath();
	}

	if (path_center_vec.size() >= 1)
	{
		direction_list_END = false;
               
       		visual_center_path.FillData(GuiTextureObCollector::Instance().dot_blue->texture, &path_center_vec, 10, 10);
       		//visual_debug_midLeft_path.FillData(GuiTextureObCollector::Instance().dot_red->texture, &debug_midLeft_vec, 10, 10);
       		move_it = 0;
       	}
}

bool DriveComplex::CalcRoundPath()
{  	
    	vector2f vehicle_basis(owner_vehicle->GetPoints().GetMidLeft(), owner_vehicle->GetPoints().GetCenter());
    	vector2f target_basis(owner_vehicle->GetPoints().GetMidLeft(),  target_pos);
    	    	    	
    	float d_angle = 1.0f;
    	float target_angle_diff = getAngle(vehicle_basis, target_basis);
    	float target_angle_diff_start = target_angle_diff;
    	
    	float angle_inD = owner_vehicle->GetPoints().GetAngleDegree();
    	
    	int sign = 1;  //hack, define right sign here

    	float step = owner_vehicle->propetries.speed/100.0;  // remove from here 

    	int it_max = 361/d_angle;
    	int i = 0;
    	while (target_angle_diff > 2*d_angle)
    	{   		
    		i++; //std::cout<<i<<std::endl;
    		if (i > it_max)
    		{
    			return false; // if a target point is close to object and is not reachable, then further calc has no sense
    		}
    		
    		angle_inD += sign*d_angle;	    	
	    	
       		float angle_radian = angle_inD/RADIAN_TO_DEGREE_RATE;
   		         
        	float cosa = cos(angle_radian);
        	float sina = sin(angle_radian);
        	
    		vec2f delta_step(step*cosa, step*sina);
    		 
       		////// rotation around center
       		vec2f midleft_orig(owner_vehicle->GetPoints().GetMidLeftOrig());
       		vec2f midleft_rotated(midleft_orig.x * cosa - midleft_orig.y * sina, midleft_orig.x * sina + midleft_orig.y * cosa);
     	        	
        	vehicle_basis.p += delta_step;
       		vec2f midleft_trans(midleft_rotated + vehicle_basis.p);
       		
        	vehicle_basis.p0(midleft_trans);        	        	
        	target_basis.p0(midleft_trans);        	
         	        	
        	target_angle_diff = getAngle(vehicle_basis, target_basis);
        	
        	if (target_angle_diff > target_angle_diff_start) // hack
        	{
        		sign *= -1;
        		angle_inD += sign*d_angle;
        		continue;    		
        	}
        	//debug_midLeft_vec.push_back(vehicle_basis.p0);
        	path_center_vec.push_back(vehicle_basis.p);
            	angle_inD_vec.push_back(angle_inD);
        }
        
        return true;	
}


void DriveComplex::CalcDirectPath() 
{   
	vec2f start_pos;
	if (path_center_vec.size() == 0)
	{
    		start_pos(owner_vehicle->GetPoints().GetCenter());
    	}
    	else
    	{
		start_pos(path_center_vec[path_center_vec.size()-1]);
    	}
    	
    	vec2f ll(target_pos - start_pos);
    	vec2f new_pos(start_pos);
    	       		
        if ( (owner_vehicle->propetries.speed > FLOAT_EPSILON) and (ll.IsNull() == false) )
    	{
    		float step = owner_vehicle->propetries.speed/100.0;  // remove from here    
       		    		
		vec2f vstep = ll.GetNorm() * step;

       		unsigned int it = ll.GetLen() / step;
       		for(unsigned int i=0; i<it; i++)
       		{
            		new_pos += vstep;
            		float angleInD = atan2(target_pos.y - new_pos.y, target_pos.x - new_pos.x) * RADIAN_TO_DEGREE_RATE;

            		path_center_vec.push_back(new_pos);
            		angle_inD_vec.push_back(angleInD);
       		}
    	}
}




void DriveComplex::UpdatePosition()
{
     	if (direction_list_END == false)
     	{
        	if (move_it < path_center_vec.size())
        	{
           		owner_vehicle->GetPoints().SetCenter(path_center_vec[move_it]);
           		owner_vehicle->GetPoints().SetAngle(angle_inD_vec[move_it]);
           		move_it++;
        	}
        	else
        	{
           		direction_list_END = true;
           	}
     	}
}

void DriveComplex::DrawPath()
{
        if (direction_list_END == false)
        {
                visual_center_path.Draw();
                //visual_debug_midLeft_path.Draw();
        }
}

                
void DriveComplex::RenderTrail()
{
	drive_effect->Update();
	drive_effect->Render();
}

