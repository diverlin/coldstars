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

#include "DriveComplex.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/SpaceStation.hpp"

#include "../slots/ItemSlot.hpp"

#include "../common/myVector.hpp"
#include "../common/Collision.hpp"
#include "../common/constants.hpp"
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"

#include "../world/starsystem.hpp"

DriveComplex::DriveComplex()
{      
	owner_vehicle = NULL;
    			
	target_distance = 0.0;
	action_id = NAVIGATOR_ACTION::NONE_ID;
	
        has_target = false;
	direction_list_END = true;

	target = NULL;
	drive_effect = NULL; 
}

DriveComplex::~DriveComplex()
{      
        delete drive_effect;
}

bool DriveComplex::PathExists() const
{
    	if ( (direction_list_END == true) and (path_center_vec.size() == 0 ) )
    	{
    		return false;
    	}	
    	
    	return true;
}

void DriveComplex::ResetTarget()
{
	#if DRIVECOMPLEX_LOG_ENABLED == 1 
	if (target == NULL)
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::ResetTarget", DRIVECOMPLEX_LOG_DIP); 
	else
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::ResetTarget" + getBaseInfoStr(target), DRIVECOMPLEX_LOG_DIP); 
	#endif    
	
	target = NULL;
    		
	target_distance = 0.0;
	target_offset.Set(0.0, 0.0);
	target_pos.Set(0.0, 0.0);
	action_id = NAVIGATOR_ACTION::NONE_ID;
	
        has_target = false;
	direction_list_END = true;
}
      
void DriveComplex::SetStaticTargetCoords(const vec2f& target_pos)
{	
    	ResetTarget();
    	has_target = true;
    	        
    	this->target_pos = target_pos;
        
       	UpdatePath();

	#if DRIVECOMPLEX_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::SetStaticTargetCoords:"+int2str((int)target_pos.x)+", "+int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP); 
	#endif  
}      
         		
void DriveComplex::SetTarget(BaseSpaceEntity* target, int action_id)
{
    	ResetTarget();

	this->target = target;    
	this->action_id = action_id;

    	has_target = true;
    	
	#if DRIVECOMPLEX_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::SetTarget " + getBaseInfoStr(target) + " navigator_action = " + getNavigatorActionStr(action_id), DRIVECOMPLEX_LOG_DIP); 
	#endif 
}
  
void DriveComplex::DefineDistance()
{   	
    	switch(action_id)
    	{	
    		case NAVIGATOR_ACTION::DOCKING_ID:
    		{
    			target_distance = target->GetCollisionRadius()/4;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/5, target->GetCollisionRadius()/2); 
    			
    			break;   
    		}
    		
    		case NAVIGATOR_ACTION::COLLECTING_ID:
    		{
    		    	target_distance = owner_vehicle->GetProperties().grab_radius/2; 
    			target_offset = getRandVec2f(target->GetCollisionRadius()/2, target->GetCollisionRadius()); 
    			
    			break;    		
    		}

    		case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:
    		{
    			int weapon_radius_min = owner_vehicle->GetWeaponComplex().GetWeaponRadiusMin();
    			if (weapon_radius_min < 10) // in some cases case thee the bug (HACK)
    			{
    		    		target_distance = 150;    			
    			}
    			
			target_offset = getRandVec2f(weapon_radius_min/4, weapon_radius_min/2); 
    			
    			break;    		
    		}
    		    		
    		case NAVIGATOR_ACTION::KEEP_CLOSE_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*1.5;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/5, target->GetCollisionRadius()/2); 
    			
    			break;    		
    		}

    		case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*4;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/2, target->GetCollisionRadius()); 
    			
    			break;    		
    		}
    		
    		case NAVIGATOR_ACTION::KEEP_FAR_ID:
    		{
    		    	target_distance = target->GetCollisionRadius()*8;
    			target_offset = getRandVec2f(target->GetCollisionRadius()/2, target->GetCollisionRadius()); 
    			
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
			DefineDistance();
			UpdateDynamicTargetCoord();
		}
		else
		{
			ResetTarget();
		}
	}
	
        if (has_target == true)
        {
                CalcPath();
        }
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



void DriveComplex::UpdateDynamicTargetCoord()
{		
	switch(target->GetTypeId())
	{
		case ENTITY::STARSYSTEM_ID:
		{
			float angleInD = 90-getAngleInD(target->GetPoints().GetCenter(), owner_vehicle->GetStarSystem()->GetPoints().GetCenter()); //??
		    	target_pos = getVec2f(ENTITY::STARSYSTEM::JUMPRADIUS, angleInD);
			target_distance = COLLISION_RADIUS_FOR_STATIC_COORD;
			
			break;
		}
	
    		case ENTITY::PLANET_ID:
    		{ 
        		//target_pos = ((Planet*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;         	
        		target_pos = ((Planet*)target)->GetPoints().GetCenter() + target_offset; 
		       	break;		       	
    		} 

    		case ENTITY::ASTEROID_ID:
    		{ 
        		target_pos = ((Asteroid*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;         	
        		break;
    		} 
    	     
    		case ENTITY::VEHICLE_ID:
    		{ 
			target_pos = target->GetPoints().GetCenter() + target_offset;  
        		break;    
    		}

    		case ENTITY::CONTAINER_ID:
    		{ 
			target_pos = target->GetPoints().GetCenter() + target_offset;  
        		break;    
    		}
    	}

	#if DRIVECOMPLEX_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::UpdateDynamicTargetCoord " + " target_pos=" + vec2f2str(target_pos) + " target_center=" + vec2f2str(target->GetPoints().GetCenter()) + " target_offset=" + vec2f2str(target_offset) + "target_distance=" + int2str(target_distance), DRIVECOMPLEX_LOG_DIP); 
	#endif 
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
	#if DRIVECOMPLEX_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + int2str((int)target_pos.x) + "," + int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP); 
	#endif   
	
	ClearPath();
                        
        if (CalcRoundPath() == true)
	{        
		CalcDirectPath();
	}

	if (path_center_vec.size() > 1)
	{
		direction_list_END = false;
       		move_it = 0;
       	}
        else
        {
                ClearPath();    
        }
}

bool DriveComplex::CalcRoundPath()
{  	
    	Vector2f vehicle_basis(owner_vehicle->GetPoints().GetMidLeft(), owner_vehicle->GetPoints().GetCenter());
    	Vector2f target_basis(owner_vehicle->GetPoints().GetMidLeft(),  target_pos);
    	    	    	
    	float target_angle_diff = getAngle(vehicle_basis, target_basis);
    	float target_angle_diff_start = target_angle_diff;    	
    	float angle_inD = owner_vehicle->GetPoints().GetAngleDegree();
       
    	float step = owner_vehicle->GetProperties().speed/100.0;  // remove from here 
    	float d_angle = 1.0f*step;
        
    	int it_max = 360.0f/d_angle + 1;
    	int i = 0;
        int sign = 1;  //hack, define right sign here
    	while (target_angle_diff > 1.1f*d_angle)
    	{   
                i++; 
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

        if ( (owner_vehicle->GetProperties().speed > FLOAT_EPSILON) and (ll.IsNull() == false) )
    	{
    		float step = owner_vehicle->GetProperties().speed/100.0;  // remove from here    
       		    		
		vec2f vstep = ll.GetNorm() * step;

       		unsigned int it = ll.GetLen() / step;
       		for (unsigned int i=0; i<it; i++)
       		{
            		new_pos += vstep;
            		float angleInD = getAngleInD(target_pos, new_pos);

            		path_center_vec.push_back(new_pos);
            		angle_inD_vec.push_back(angleInD);
       		}
    	}
}

//void DriveComplex::CalcAcceleratedPath() // used for hyper jump effect
//{
	//ClearPath();
	
	//float angleInD = owner_vehicle->GetPoints().GetAngleDegree();

	//vec2f start_pos(owner_vehicle->GetPoints().GetCenter());
    	
    	//vec2f ll(getVec2f(100, angleInD) - start_pos);
    	
    	//vec2f new_pos(start_pos);
    	//for (unsigned int i=0; i<500; i++)
	//{
	    	//float step = owner_vehicle->GetProperties().speed/100.0 + i*10;  // remove from here      		    		
		//vec2f vstep = ll.GetNorm() * step;
	
        	//new_pos += vstep;

            	//path_center_vec.push_back(new_pos);
            	//angle_inD_vec.push_back(angleInD);
       	//}
       	
       	//if (path_center_vec.size() >= 1)
	//{
		//direction_list_END = false;
               
       		//move_it = 0;
       	//}
//}

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

void DriveComplex::UpdatePathVisualisation()
{        
        visual_center_path.FillData(path_center_vec, 10, 10);
        visual_center_turn.FillData(path_center_vec, TURN_TIME, 14);
       	//visual_debug_midLeft_path.FillData(GuiTextureObCollector::Instance().dot_red->texture, &debug_midLeft_vec, 10, 10);}
}

void DriveComplex::DrawPath()
{
        if (direction_list_END == false)
        {
                this->UpdatePathVisualisation();
                visual_center_path.Draw();
                visual_center_turn.Draw();
                //visual_debug_midLeft_path.Draw();
        }
}

