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

#include "../math/myVector.hpp"
#include "../common/Collision.hpp"
#include "../common/constants.hpp"
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
#include "../common/rand.hpp"

#include "../world/starsystem.hpp"
#include "../effects/particlesystem/DriveEffect.hpp"

DriveComplex::DriveComplex()
{      
    owner_vehicle = nullptr;
                
    target_distance = 0.0;
    action_id = NAVIGATOR_ACTION::NONE_ID;
    
        has_target = false;
    direction_list_END = true;

    target = nullptr;
    drive_effect = nullptr; 
        
        drive_slot = nullptr;
        bak_slot   = nullptr;
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
    if (target == nullptr)
    Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::ResetTarget", DRIVECOMPLEX_LOG_DIP); 
    else
    Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::ResetTarget" + getBaseInfoStr(target), DRIVECOMPLEX_LOG_DIP); 
    #endif    
    
    target = nullptr;
            
    target_distance = 0.0;
    target_offset.Set(0.0, 0.0, 0.0);
    target_pos.Set(0.0, 0.0, 0.0);
    action_id = NAVIGATOR_ACTION::NONE_ID;
    
        has_target = false;
    direction_list_END = true;
}
      
void DriveComplex::SetStaticTargetCoords(const Vec3<float>& target_pos)
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
                target_offset = getRandXYVec3f(target->GetCollisionRadius()/5, target->GetCollisionRadius()/2, target->GetCenter().z); 
                
                break;   
            }
            
            case NAVIGATOR_ACTION::COLLECTING_ID:
            {
                    target_distance = owner_vehicle->GetProperties().grab_radius/2; 
                target_offset = getRandXYVec3f(target->GetCollisionRadius()/2, target->GetCollisionRadius(), target->GetCenter().z); 
                
                break;            
            }

            case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:
            {
                int weapon_radius_min = owner_vehicle->GetComplexWeapon().GetRadiusMin();
                if (weapon_radius_min < 10) // in some cases case thee the bug (HACK)
                {
                        target_distance = 150;                
                }
                
            target_offset = getRandXYVec3f(weapon_radius_min/4, weapon_radius_min/2, target->GetCenter().z); 
                
                break;            
            }
                        
            case NAVIGATOR_ACTION::KEEP_CLOSE_ID:
            {
                    target_distance = target->GetCollisionRadius()*1.5;
                target_offset = getRandXYVec3f(target->GetCollisionRadius()/5, target->GetCollisionRadius()/2, target->GetCenter().z); 
                
                break;            
            }

            case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:
            {
                    target_distance = target->GetCollisionRadius()*4;
                target_offset = getRandXYVec3f(target->GetCollisionRadius()/2, target->GetCollisionRadius(), target->GetCenter().z); 
                
                break;            
            }
            
            case NAVIGATOR_ACTION::KEEP_FAR_ID:
            {
                    target_distance = target->GetCollisionRadius()*8;
                target_offset = getRandXYVec3f(target->GetCollisionRadius()/2, target->GetCollisionRadius(), target->GetCenter().z); 
                
                break;    
            }

        }
}
                  
void DriveComplex::UpdatePath()
{
    if (target != nullptr)
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
        if (target->GetPlaceTypeId() == TYPE::PLACE::SPACE_ID)
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
        case TYPE::ENTITY::STARSYSTEM_ID:
        {
            float angleInD = 90-getAngleInD(target->GetCenter(), owner_vehicle->GetStarSystem()->GetCenter()); //??
                target_pos = getVec3f(ENTITY::STARSYSTEM::JUMPRADIUS, angleInD, owner_vehicle->GetStarSystem()->GetCenter().z);
            target_distance = COLLISION_RADIUS_FOR_STATIC_COORD;
            
            break;
        }
    
            case TYPE::ENTITY::PLANET_ID:
            { 
                //target_pos = ((Planet*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;             
                target_pos = ((Planet*)target)->GetCenter() + target_offset; 
                   break;                   
            } 

            case TYPE::ENTITY::ASTEROID_ID:
            { 
                target_pos = ((Asteroid*)target)->GetOrbit().GetNextTurnPosition() + target_offset;             
                break;
            } 
             
            case TYPE::ENTITY::VEHICLE_ID:
            { 
            target_pos = target->GetCenter() + target_offset;  
                break;    
            }

            case TYPE::ENTITY::CONTAINER_ID:
            { 
            target_pos = target->GetCenter() + target_offset;  
                break;    
            }
        }

    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::UpdateDynamicTargetCoord " + " target_pos=" + Vec2<float>2str(target_pos) + " target_center=" + Vec2<float>2str(target->GetCenter()) + " target_offset=" + Vec2<float>2str(target_offset) + "target_distance=" + int2str(target_distance), DRIVECOMPLEX_LOG_DIP); 
    #endif 
}


bool DriveComplex::CheckTargetEchievement()
{
    if (target != nullptr)
    {    
             if (checkCollisionDotWithCircle_DIRTY(owner_vehicle->GetCenter(), target_pos, target_distance) == true)
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
        case TYPE::ENTITY::PLANET_ID:       { return ((Planet*)target)->GetLand()->GetPermissionToLand(); break; }
        case TYPE::ENTITY::VEHICLE_ID: 
        { 
            switch(target->GetSubTypeId())
            {
                case TYPE::ENTITY::SPACESTATION_ID: { return ((SpaceStation*)target)->GetLand()->GetPermissionToLand(); break; }
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

void DriveComplex::CalcPath2()
{
    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + int2str((int)target_pos.x) + "," + int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP); 
    #endif   
    
    ClearPath();
        
        float speed = owner_vehicle->GetProperties().speed;
        
        Vec3<float> new_center(owner_vehicle->GetCenter());
    Vec3<float> target_dir(target_pos - owner_vehicle->GetCenter());
    target_dir.Normalize();
    float az = owner_vehicle->GetAngle().z;
    Vec3<float> orient(cos(az*DEGREE_TO_RADIAN_RATE), sin(az*DEGREE_TO_RADIAN_RATE), 0.0);

    // identify sign for rotation
    int sign;
    {
        float prob_az1 = az+1;
        float prob_az2 = az-1;
        
        Vec3<float> prob_orient1(cos(prob_az1*DEGREE_TO_RADIAN_RATE), sin(prob_az1*DEGREE_TO_RADIAN_RATE), 0.0);
        Vec3<float> prob_orient2(cos(prob_az2*DEGREE_TO_RADIAN_RATE), sin(prob_az2*DEGREE_TO_RADIAN_RATE), 0.0);
        
        float prob_cosa1 = dotUnits(prob_orient1, target_dir);        
        float prob_cosa2 = dotUnits(prob_orient2, target_dir);
                
        if (prob_cosa1 > 0)
        {
            if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))
            {
                sign = -1;
            }
            else
            {
                sign = 1;
            }
        }
        else
        {
            if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }
        }
    }

    // rotated path
    float cosa = dotUnits(orient, target_dir);
    float angle_step = 3.0;
    int counter_max = 3 + 360/angle_step;
    int i = 0;
    while (std::fabs(cosa) < 0.999 or (cosa < 0)) // cosa <0 condition works if the orient and target vector is straigforward opposite (dot ~ -1)
    {
        az += sign*angle_step;
        orient.x = cos(az*DEGREE_TO_RADIAN_RATE);
        orient.y = sin(az*DEGREE_TO_RADIAN_RATE);
        
        new_center += orient*speed;
         
        target_dir.Set(target_pos - new_center);
        target_dir.Normalize();
                 
        path_center_vec.push_back(new_center);
        angle_inD_vec.push_back(az);
        
        cosa = dotUnits(orient, target_dir);
        
        i++;
        if (i>counter_max) // target_pos is not reachable (within circle)
        {
            ClearPath();
            return;
        }
    }
    
    // direct path
    Vec3<float> way(target_pos - new_center);
    while (way.GetLength() > 1.1*speed)
    {
        new_center += target_dir*speed;

        path_center_vec.push_back(new_center);
        angle_inD_vec.push_back(az);
                        
        way.Set(target_pos - new_center);
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


void DriveComplex::CalcPath()
{
    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + int2str((int)target_pos.x) + "," + int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP); 
    #endif   
    
    ClearPath();
        
        float speed_base = owner_vehicle->GetProperties().speed;
        
        Vec3<float> new_center(owner_vehicle->GetCenter());
    Vec3<float> target_dir(target_pos - owner_vehicle->GetCenter());
    target_dir.Normalize();
    float az = owner_vehicle->GetAngle().z;
    Vec3<float> orient(cos(az*DEGREE_TO_RADIAN_RATE), sin(az*DEGREE_TO_RADIAN_RATE), 0.0);

    Vec3<float> gravity;
    const StarSystem& starsystem = *owner_vehicle->GetStarSystem();
    int mass = owner_vehicle->GetMass();
    
    int sign = 1;
    float angle_step = 3.0;
    int round_counter = 0;
    int round_counter_max = 3 + 360/angle_step;
    while((new_center-target_pos).GetLength() > 5*speed_base)
    {
        target_dir.Set(target_pos - new_center);
        target_dir.Normalize();
            
        float cosa = dotUnits(orient, target_dir);
        if (std::fabs(cosa) < 0.999 or (cosa < 0)) // cosa <0 condition works if the orient and target vector is straigforward opposite (dot ~ -1)
        {
            if (round_counter == 0)
            {
                float prob_az1 = az+1;
                float prob_az2 = az-1;
                
                Vec3<float> prob_orient1(cos(prob_az1*DEGREE_TO_RADIAN_RATE), sin(prob_az1*DEGREE_TO_RADIAN_RATE), 0.0);
                Vec3<float> prob_orient2(cos(prob_az2*DEGREE_TO_RADIAN_RATE), sin(prob_az2*DEGREE_TO_RADIAN_RATE), 0.0);
                
                float prob_cosa1 = dotUnits(prob_orient1, target_dir);        
                float prob_cosa2 = dotUnits(prob_orient2, target_dir);
                        
                if (prob_cosa1 > 0)
                {
                    if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))     { sign = -1; }
                    else                             { sign = 1; }
                }
                else
                {
                    if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))     { sign = 1; }
                    else                            { sign = -1; }
                }
            }
        
            az += sign*angle_step;
            orient.x = cos(az*DEGREE_TO_RADIAN_RATE);
            orient.y = sin(az*DEGREE_TO_RADIAN_RATE);
        
            cosa = dotUnits(orient, target_dir);
            
            round_counter++;
            if (round_counter>round_counter_max) // target_pos is not reachable (within circle)
            {
                ClearPath();
                return;
            }        
        }
        else
        {
            round_counter = 0;
        }

if (path_center_vec.size() > 10000) { std::cout<<"BREAK PASS CALC, vehicle id="<<owner_vehicle->GetId()<<std::endl; break; }

        float gravity_rate = starsystem.CalcResultGravityForce(new_center, orient, mass);        
        
        new_center += orient*speed_base*gravity_rate;
                
        path_center_vec.push_back(new_center);
        angle_inD_vec.push_back(az);
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

void DriveComplex::UpdatePosition()
{
    if (direction_list_END == false)
    {
        if (move_it < path_center_vec.size())
        {
            owner_vehicle->SetCenter(path_center_vec[move_it]);
            owner_vehicle->SetAngleZ(angle_inD_vec[move_it]);
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

