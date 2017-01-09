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
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include <math/rand.hpp>

#include "../world/starsystem.hpp"
//#include <jeti/particlesystem/DriveEffect.hpp>

#include <meti/VectorUtils.hpp>
#include <meti/QuaternionUtils.hpp>

DriveComplex::DriveComplex()
:
m_driveSlot(nullptr),
m_bakSlot(nullptr),
m_ownerVehicle(nullptr),
m_target(nullptr),
m_effectDrive(nullptr),
m_ActionId(NAVIGATOR_ACTION::NONE_ID),
m_TargetDistance(0.0f),
m_PathEnd(true),
m_HasTarget(false)
{}

DriveComplex::~DriveComplex()
{      
    delete m_effectDrive;
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
//    if (!m_Target)
//        LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::ResetTarget");
//    else
//        LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::ResetTarget" + getBaseInfoStr(target));

    
    m_target = nullptr;
            
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

    LOG("vehicle_id="+std::to_string(m_ownerVehicle->id())+" DriveComplex::SetStaticTargetCoords:"+std::to_string((int)target_pos.x)+", "+std::to_string((int)target_pos.y));
}      
                 
void DriveComplex::SetTarget(SpaceObject* target, int action_id)
{
    ResetTarget();
    
    m_target = target;    
    m_ActionId = action_id;
    
    m_HasTarget = true;
        
    //LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::SetTarget " + getBaseInfoStr(target) + " navigator_action = " + getNavigatorActionStr(m_ActionId));
}
  
void DriveComplex::DefineDistance()
{       
    switch(m_ActionId)
    {    
        case NAVIGATOR_ACTION::DOCKING_ID:
        {
            m_TargetDistance = m_target->collisionRadius()/4;
            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/5, m_target->collisionRadius()/2, m_target->position().z);
            
            break;   
        }
        
        case NAVIGATOR_ACTION::COLLECTING_ID:
        {
            m_TargetDistance = m_ownerVehicle->properties().grab_radius/2; 
            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
            break;            
        }

        case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:
        {
            int weapon_radius_min = m_ownerVehicle->weaponComplex().radiusMin();
            if (weapon_radius_min < 10) // in some cases case thee the bug (HACK)
            {
                m_TargetDistance = 150;                
            }
            
            m_TargetOffset = meti::getRandXYVec3f(weapon_radius_min/4, weapon_radius_min/2, m_target->position().z);
            
            break;            
        }
                    
        case NAVIGATOR_ACTION::KEEP_CLOSE_ID:
        {
            m_TargetDistance = m_target->collisionRadius()*1.5;
            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/5, m_target->collisionRadius()/2, m_target->position().z);
            
            break;            
        }

        case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:
        {
            m_TargetDistance = m_target->collisionRadius()*4;
            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
            break;            
        }
        
        case NAVIGATOR_ACTION::KEEP_FAR_ID:
        {
            m_TargetDistance = m_target->collisionRadius()*8;
            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
            break;    
        }

    }
}
                  
void DriveComplex::UpdatePath()
{
    if (m_target != nullptr)
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
    if (m_target->isAlive() == true)
    {
        if (m_target->place() == type::place::KOSMOS)
        {
            return true;
        }
    }
    
    return false;
}



void DriveComplex::UpdateDynamicTargetCoord()
{        
    switch(m_target->type())
    {
        case type::entity::STARSYSTEM_ID:
        {
            float angle = M_PI/2 - meti::getAngle(meti::vec2(m_target->position()), meti::vec2(m_ownerVehicle->starsystem()->position())); //??    use cross()
            m_TargetPos = meti::genVec3f(ENTITY::STARSYSTEM::JUMPRADIUS, angle, m_ownerVehicle->starsystem()->position().z);
            m_TargetDistance = COLLISION_RADIUS_FOR_STATIC_COORD;
            
            break;
        }
    
        case type::entity::PLANET_ID:
        { 
            //target_pos = ((Planet*)target)->GetOrbit()->GetNextTurnPosition() + target_offset;             
            //m_TargetPos = ((Planet*)m_target)->position() + m_TargetOffset;
            break;                   
        } 

        case type::entity::ASTEROID_ID:
        { 
        // TODO
//            m_TargetPos = ((Asteroid*)m_target)->orbit().nextTurnPosition() + m_TargetOffset;
//            break;
        } 
         
        case type::entity::VEHICLE_ID:
        { 
            m_TargetPos = m_target->position() + m_TargetOffset;  
            break;    
        }

        case type::entity::CONTAINER_ID:
        { 
            m_TargetPos = m_target->position() + m_TargetOffset;  
            break;    
        }
    }

    //LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::UpdateDynamicTargetCoord " + " target_pos=" + glm::vec22str(target_pos) + " target_center=" + glm::vec22str(target->center()) + " target_offset=" + glm::vec22str(target_offset) + "target_distance=" + std::to_string(target_distance), DRIVECOMPLEX_LOG_DIP);
}


bool DriveComplex::CheckTargetEchievement()
{
    if (m_target != nullptr)
    {    
        if (ceti::checkCollisionDotWithCircle_DIRTY(meti::vec2(m_ownerVehicle->position()), meti::vec2(m_TargetPos), m_TargetDistance) == true)
        {
            return true;
        }
    }
    
    return false;
}


bool DriveComplex::GetDockingPermission()
{
    switch(m_target->type())
    {
        //case type::entity::PLANET_ID:       { return ((Planet*)m_target)->GetLand()->GetPermissionToLand(); break; }
        case type::entity::VEHICLE_ID: 
        { 
            switch(m_target->subtype())
            {
                case type::entity::SPACESTATION_ID: { return ((SpaceStation*)m_target)->land()->GetPermissionToLand(); break; }
                //case SHIP_ID:   { return targetOb->vehicle()->getPermissionToLand(); break; }
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
    //LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + std::to_string((int)target_pos.x) + "," + std::to_string((int)target_pos.y), DRIVECOMPLEX_LOG_DIP);
    
    ClearPath();

    int round_counter_max = 2000;//2 + 2*M_PI/angle_step;
    int round_counter = 0;

    float speed_base = m_ownerVehicle->properties().speed;
    
    glm::vec3 new_center(m_ownerVehicle->position());
    glm::vec3 target_dir = glm::normalize(m_TargetPos - m_ownerVehicle->position());

    glm::quat zero_quat;    
    glm::quat target_quat;

    glm::vec3 direction = glm::normalize(m_ownerVehicle->direction());

    meti::quatBetweenVectors(target_quat, direction, target_dir);
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

    //float az = atan2(m_OwnerVehicle->direction().y, m_OwnerVehicle->direction().x);
    ////float az = acos(glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), m_OwnerVehicle->direction()));
    //std::cout<<"angle= "<<glm::degrees(az)<<std::endl;

    //glm::vec3 direction = m_OwnerVehicle->direction();
        
    //glm::vec3 gravity;
    //const StarSystem& starsystem = *m_OwnerVehicle->starsystem();
    //int mass = m_OwnerVehicle->mass();
    
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
if (m_PathCenterVec.size() > 10000) { std::cout<<"BREAK PASS CALC, vehicle id="<<m_OwnerVehicle->id()<<std::endl; break; }


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
            m_ownerVehicle->setPosition(m_PathCenterVec[m_PathIndex]);
            m_ownerVehicle->setDirection(m_PathDirectionVec[m_PathIndex]);
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
//    m_PathVisualCenter.FillData(m_PathCenterVec, 10, 10);
//    m_PathVisualTurn.FillData(m_PathCenterVec, TURN_TIME, 14);
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

