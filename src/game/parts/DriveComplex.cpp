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

#include <meti/VectorUtils.hpp>
#include <meti/RandUtils.hpp>
#include <ceti/Collision.hpp>
#include "../common/constants.hpp"
#include "../common/Logger.hpp"
#include <ceti/myStr.hpp>
#include <math/rand.hpp>

#include "../world/starsystem.hpp"
#include <jeti/particlesystem/DriveEffect.hpp>

#include <meti/VectorUtils.hpp>
#include <meti/QuaternionUtils.hpp>

DriveComplex::DriveComplex()
:
m_DriveSlot(nullptr),
m_BakSlot(nullptr),
m_OwnerVehicle(nullptr),
m_Target(nullptr),
m_EffectDrive(nullptr),
m_ActionId(NAVIGATOR_ACTION::NONE_ID),
m_TargetDistance(0.0f),
m_PathEnd(true),
m_HasTarget(false)
{}

DriveComplex::~DriveComplex()
{      
    delete m_EffectDrive;
}

bool DriveComplex::PathExists() const
{
    if ( (m_PathEnd == true) and (m_PathCenterVec.size() == 0 ) )
    {
        return false;
    }    
    
    return true;
}

void DriveComplex::ResetTarget()
{
    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    if (target == nullptr)
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::ResetTarget", DRIVECOMPLEX_LOG_DIP);
    else
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::ResetTarget" + getBaseInfoStr(target), DRIVECOMPLEX_LOG_DIP);
    #endif    
    
    m_Target = nullptr;
            
    m_TargetDistance = 0.0;
    m_TargetOffset = glm::vec3(0.0);
    m_TargetPos   = glm::vec3(0.0);
    
    m_ActionId = NAVIGATOR_ACTION::NONE_ID;
    
    m_HasTarget = false;
    m_PathEnd = true;
}
      
void DriveComplex::SetStaticTargetCoords(const glm::vec3& target_pos)
{    
    ResetTarget();
    m_HasTarget = true;
    
    m_TargetPos = target_pos;
    
    UpdatePath();

    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::SetStaticTargetCoords:"+ceti::int2str((int)target_pos.x)+", "+ceti::int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP);
    #endif  
}      
                 
void DriveComplex::SetTarget(BaseSpaceEntity* target, int action_id)
{
    ResetTarget();
    
    m_Target = target;    
    m_ActionId = action_id;
    
    m_HasTarget = true;
        
    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::SetTarget " + getBaseInfoStr(target) + " navigator_action = " + getNavigatorActionStr(m_ActionId), DRIVECOMPLEX_LOG_DIP);
    #endif 
}
  
void DriveComplex::DefineDistance()
{       
    switch(m_ActionId)
    {    
        case NAVIGATOR_ACTION::DOCKING_ID:
        {
            m_TargetDistance = m_Target->GetCollisionRadius()/4;
            m_TargetOffset = meti::getRandXYVec3f(m_Target->GetCollisionRadius()/5, m_Target->GetCollisionRadius()/2, m_Target->GetCenter().z);
            
            break;   
        }
        
        case NAVIGATOR_ACTION::COLLECTING_ID:
        {
            m_TargetDistance = m_OwnerVehicle->GetProperties().grab_radius/2; 
            m_TargetOffset = meti::getRandXYVec3f(m_Target->GetCollisionRadius()/2, m_Target->GetCollisionRadius(), m_Target->GetCenter().z);
            
            break;            
        }

        case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:
        {
            int weapon_radius_min = m_OwnerVehicle->GetComplexWeapon().GetRadiusMin();
            if (weapon_radius_min < 10) // in some cases case thee the bug (HACK)
            {
                m_TargetDistance = 150;                
            }
            
            m_TargetOffset = meti::getRandXYVec3f(weapon_radius_min/4, weapon_radius_min/2, m_Target->GetCenter().z);
            
            break;            
        }
                    
        case NAVIGATOR_ACTION::KEEP_CLOSE_ID:
        {
            m_TargetDistance = m_Target->GetCollisionRadius()*1.5;
            m_TargetOffset = meti::getRandXYVec3f(m_Target->GetCollisionRadius()/5, m_Target->GetCollisionRadius()/2, m_Target->GetCenter().z);
            
            break;            
        }

        case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:
        {
            m_TargetDistance = m_Target->GetCollisionRadius()*4;
            m_TargetOffset = meti::getRandXYVec3f(m_Target->GetCollisionRadius()/2, m_Target->GetCollisionRadius(), m_Target->GetCenter().z);
            
            break;            
        }
        
        case NAVIGATOR_ACTION::KEEP_FAR_ID:
        {
            m_TargetDistance = m_Target->GetCollisionRadius()*8;
            m_TargetOffset = meti::getRandXYVec3f(m_Target->GetCollisionRadius()/2, m_Target->GetCollisionRadius(), m_Target->GetCenter().z);
            
            break;    
        }

    }
}
                  
void DriveComplex::UpdatePath()
{
    if (m_Target != nullptr)
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
    
    if (m_HasTarget == true)
    {
        CalcPath();
    }
}

bool DriveComplex::ValidateTarget() const
{
    if (m_Target->GetAlive() == true)
    {
        if (m_Target->GetPlaceTypeId() == TYPE::PLACE::SPACE_ID)
        {
            return true;
        }
    }
    
    return false;
}



void DriveComplex::UpdateDynamicTargetCoord()
{        
    switch(m_Target->GetTypeId())
    {
        case TYPE::ENTITY::STARSYSTEM_ID:
        {
            float angle = M_PI/2 - meti::getAngle(meti::vec3ToVec2(m_Target->GetCenter()), meti::vec3ToVec2(m_OwnerVehicle->GetStarSystem()->GetCenter())); //??    use cross()
            m_TargetPos = meti::getVec3f(ENTITY::STARSYSTEM::JUMPRADIUS, angle, m_OwnerVehicle->GetStarSystem()->GetCenter().z);
            m_TargetDistance = COLLISION_RADIUS_FOR_STATIC_COORD;
            
            break;
        }
    
        case TYPE::ENTITY::PLANET_ID:
        { 
            //target_pos = ((Planet*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;             
            m_TargetPos = ((Planet*)m_Target)->GetCenter() + m_TargetOffset; 
            break;                   
        } 

        case TYPE::ENTITY::ASTEROID_ID:
        { 
            m_TargetPos = ((Asteroid*)m_Target)->GetOrbit().GetNextTurnPosition() + m_TargetOffset;             
            break;
        } 
         
        case TYPE::ENTITY::VEHICLE_ID:
        { 
            m_TargetPos = m_Target->GetCenter() + m_TargetOffset;  
            break;    
        }

        case TYPE::ENTITY::CONTAINER_ID:
        { 
            m_TargetPos = m_Target->GetCenter() + m_TargetOffset;  
            break;    
        }
    }

    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::UpdateDynamicTargetCoord " + " target_pos=" + glm::vec22str(target_pos) + " target_center=" + glm::vec22str(target->GetCenter()) + " target_offset=" + glm::vec22str(target_offset) + "target_distance=" + ceti::int2str(target_distance), DRIVECOMPLEX_LOG_DIP);
    #endif 
}


bool DriveComplex::CheckTargetEchievement()
{
    if (m_Target != nullptr)
    {    
        if (ceti::checkCollisionDotWithCircle_DIRTY(meti::vec3ToVec2(m_OwnerVehicle->GetCenter()), meti::vec3ToVec2(m_TargetPos), m_TargetDistance) == true)
        {
            return true;
        }
    }
    
    return false;
}


bool DriveComplex::GetDockingPermission()
{
    switch(m_Target->GetTypeId())
    {
        case TYPE::ENTITY::PLANET_ID:       { return ((Planet*)m_Target)->GetLand()->GetPermissionToLand(); break; }
        case TYPE::ENTITY::VEHICLE_ID: 
        { 
            switch(m_Target->GetSubTypeId())
            {
                case TYPE::ENTITY::SPACESTATION_ID: { return ((SpaceStation*)m_Target)->GetLand()->GetPermissionToLand(); break; }
                //case SHIP_ID:   { return targetOb->GetVehicle()->getPermissionToLand(); break; }
            }
            break;
        }
    }
    
    return false;
}

void DriveComplex::ClearPath()
{
    m_PathCenterVec.clear();
    m_PathDirectionVec.clear();
}

void DriveComplex::CalcPath()
{
    #if DRIVECOMPLEX_LOG_ENABLED == 1 
    Logger::Instance().Log("vehicle_id="+ceti::int2str(m_OwnerVehicle->GetId())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + ceti::int2str((int)target_pos.x) + "," + ceti::int2str((int)target_pos.y), DRIVECOMPLEX_LOG_DIP);
    #endif   
    
    ClearPath();

    int round_counter_max = 2000;//2 + 2*M_PI/angle_step;
    int round_counter = 0;

    float speed_base = m_OwnerVehicle->GetProperties().speed;
    
    glm::vec3 new_center(m_OwnerVehicle->GetCenter());
    glm::vec3 target_dir = glm::normalize(m_TargetPos - m_OwnerVehicle->GetCenter());

    glm::quat zero_quat;    
    glm::quat target_quat;

    glm::vec3 direction = glm::normalize(m_OwnerVehicle->GetDirection());

    meti::RotationBetweenVectors(target_quat, direction, target_dir);
    glm::quat interpolated_quat = glm::lerp(zero_quat, target_quat, 0.02f);
    while (std::fabs(glm::dot(direction, target_dir)) < 0.9999) 
    {
        direction = interpolated_quat * direction;
 
        new_center += direction * speed_base/* * gravity_rate*/;
        target_dir = glm::normalize(m_TargetPos - new_center);

        m_PathCenterVec.push_back(new_center);
        m_PathDirectionVec.push_back(direction);

        round_counter++;
        if (round_counter > round_counter_max) // target_pos is not reachable (within circle)
        {
            //ClearPath();
            break;
            //return;
        } 
    }

    //float az = atan2(m_OwnerVehicle->GetDirection().y, m_OwnerVehicle->GetDirection().x);
    ////float az = acos(glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), m_OwnerVehicle->GetDirection()));
    //std::cout<<"angle= "<<glm::degrees(az)<<std::endl;

    //glm::vec3 direction = m_OwnerVehicle->GetDirection();
        
    //glm::vec3 gravity;
    //const StarSystem& starsystem = *m_OwnerVehicle->GetStarSystem();
    //int mass = m_OwnerVehicle->GetMass();
    
    //int sign = 1;
    //float angle_step = glm::radians(1.0f);

    //int round_counter_max = 2 + 2*M_PI/angle_step;
    //int round_counter = 0;
    //while (std::fabs(glm::dot(direction, target_dir)) < 0.999) 
    //{
        //if (round_counter == 0)
        //{
            //float prob_az1 = az + angle_step;
            //float prob_az2 = az - angle_step;
            
            //glm::vec3 prob_direction1(cos(prob_az1), sin(prob_az1), 0.0);
            //glm::vec3 prob_direction2(cos(prob_az2), sin(prob_az2), 0.0);
            
            //float prob_cosa1 = glm::dot(prob_direction1, target_dir);        
            //float prob_cosa2 = glm::dot(prob_direction2, target_dir);
                    
            //if (prob_cosa1 > 0)
            //{
                //if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))      { sign = -1; }
                //else                                                    { sign = 1; }
            //}
            //else
            //{
                //if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))      { sign = 1; }
                //else                                                    { sign = -1; }
            //}
        //}        
    
        //az += sign * angle_step;

        //direction.x = cos(az);
        //direction.y = sin(az);
        
        //round_counter++;
        //if (round_counter > round_counter_max) // target_pos is not reachable (within circle)
        //{
            //ClearPath();
            //return;
        //}  

        ////float gravity_rate = starsystem.CalcResultGravityForce(new_center, direction, mass);        
        
        //new_center += direction * speed_base/* * gravity_rate*/;

        //m_PathCenterVec.push_back(new_center);
        //m_PathDirectionVec.push_back(direction);
    //}


/*

    while(glm::length(m_TargetPos - new_center) > 2*speed_base)
    {

// UGLY
if (m_PathCenterVec.size() > 10000) { std::cout<<"BREAK PASS CALC, vehicle id="<<m_OwnerVehicle->GetId()<<std::endl; break; }


        new_center += direction * speed_base * gravity_rate;
                
        m_PathCenterVec.push_back(new_center);
        m_PathDirectionVec.push_back(direction);
    }           
*/

    if (m_PathCenterVec.size() > 1)
    {
        m_PathEnd = false;
        m_PathIndex = 0;
    }
    else
    {
        ClearPath();    
    }
}

void DriveComplex::CalcPath_DEBUG()
{       

    glm::vec3 direction  = glm::vec3(1.0, 0.0, 0.0);
    float alphatarget = M_PI;    
    glm::vec3 target_dir = glm::normalize(glm::vec3(cos(alphatarget), sin(alphatarget), 0.0));
  
    std::cout<<target_dir.x<<" "<<target_dir.y<<std::endl;
      
   // float az = 0.0;

    int sign = 1;
    float angle_step = 0.1;

    float cosa = glm::dot(direction, target_dir);
    float a = acos(cosa);
    for (int i=0; i<32; i++) 
    {/*
        if (round_counter == 0)
        {
            float prob_az1 = az + angle_step;
            float prob_az2 = az - angle_step;
            
            glm::vec3 prob_direction1(cos(prob_az1), sin(prob_az1), 0.0);
            glm::vec3 prob_direction2(cos(prob_az2), sin(prob_az2), 0.0);
            
            float prob_cosa1 = glm::dot(prob_direction1, target_dir);        
            float prob_cosa2 = glm::dot(prob_direction2, target_dir);
                    
            if (prob_cosa1 > 0)
            {
                if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))      { sign = -1; }
                else                                                    { sign = 1; }
            }
            else
            {
                if (std::fabs(prob_cosa2) > std::fabs(prob_cosa1))      { sign = 1; }
                else                                                    { sign = -1; }
            }
        }
    */

        a += sign*angle_step;
        std::cout<<"alpha="<<glm::degrees(a)<<" dir="<<direction.x<<" "<<direction.y<<std::endl;
        direction.x = cos(a);
        direction.y = sin(a);
    

    }
}

void DriveComplex::UpdatePosition()
{
    if (m_PathEnd == false)
    {
        if (m_PathIndex < m_PathCenterVec.size())
        {
            m_OwnerVehicle->SetCenter(m_PathCenterVec[m_PathIndex]);
            m_OwnerVehicle->SetDirection(m_PathDirectionVec[m_PathIndex]);
            m_PathIndex++;
        }
        else
        {
            m_PathEnd = true;
        }
    }
}

void DriveComplex::UpdatePathVisualisation()
{        
    m_PathVisualCenter.FillData(m_PathCenterVec, 10, 10);
    m_PathVisualTurn.FillData(m_PathCenterVec, TURN_TIME, 14);
}

void DriveComplex::DrawPath(const jeti::Renderer& render)
{
    if (m_PathEnd == false)
    {
        UpdatePathVisualisation();
//        m_PathVisualCenter.Draw(render);
//        m_PathVisualTurn.Draw(render);
    }
}

