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
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Planet.hpp>
#include <core/spaceobject/Asteroid.hpp>
#include <core/spaceobject/SpaceStation.hpp>

#include <core/slot/ItemSlot.hpp>

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

#include <glm/gtx/transform.hpp>


namespace complex {

bool Drive::pathExists() const
{
    if (m_pathEnd || m_pathCenters.empty()) {
        return false;
    }    
    return true;
}

void Drive::resetTarget()
{
    m_target = nullptr;
            
    m_targetDistance = 0.0;
    m_targetOffset = glm::vec3(0.0);
    m_targetPos = glm::vec3(0.0);
    
    m_action = Action::NONE;
    
    m_hasTarget = false;
    m_pathEnd = true;
}
      
void Drive::setTarget(const glm::vec3& target_pos)
{
    resetTarget();
    m_hasTarget = true;
    
    m_targetPos = target_pos;
    
    refreshPath();
}
                 
void Drive::setTarget(control::SpaceObject* target, Action action_id)
{
    resetTarget();
    
    m_target = target;
    m_action = action_id;
    
    m_hasTarget = true;
}
  
//void DriveComplex::__defineDistance()
//{
//    switch(m_action)
//    {
//        case Action::DOCKING:
//        {
//            assert(false);
////            m_TargetDistance = m_target->collisionRadius()/4;
////            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/5, m_target->collisionRadius()/2, m_target->position().z);
            
//            break;
//        }
        
//        case Action::COLLECTING:
//        {
//            assert(false);
//            //m_TargetDistance = m_ownerVehicle->properties().grab_radius/2;
//            //m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
//            break;
//        }

//        case Action::KEEP_FIRE_DISTANCE:
//        {
//            assert(false);
//            //int weapon_radius_min = m_ownerVehicle->weaponComplex().radiusMin();
//            //if (weapon_radius_min < 10) // in some cases case thee the bug (HACK)
////            {
////                m_TargetDistance = 150;
////            }
            
//            //m_TargetOffset = meti::getRandXYVec3f(weapon_radius_min/4, weapon_radius_min/2, m_target->position().z);
            
//            break;
//        }
                    
//        case Action::KEEP_CLOSE:
//        {
//            assert(false);
////            m_TargetDistance = m_target->collisionRadius()*1.5;
////            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/5, m_target->collisionRadius()/2, m_target->position().z);
            
//            break;
//        }

//        case Action::KEEP_MIDDLE:
//        {
//            assert(false);
////            m_TargetDistance = m_target->collisionRadius()*4;
////            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
//            break;
//        }
        
//        case Action::KEEP_FAR:
//        {
//            assert(false);
////            m_TargetDistance = m_target->collisionRadius()*8;
////            m_TargetOffset = meti::getRandXYVec3f(m_target->collisionRadius()/2, m_target->collisionRadius(), m_target->position().z);
            
//            break;
//        }

//    }
//}
                  
void Drive::refreshPath()
{
    if (m_target) {
        if (__validateTarget()) {
            //__defineDistance();
            __updateDynamicTargetCoord();
        } else {
            resetTarget();
        }
    }
    
    if (m_hasTarget) {
        __calcPath();
    }
}

bool Drive::__validateTarget() const
{
    if (m_target->model()->isAlive()) {
        if (m_target->model()->place() == place::Type::SPACE) {
            return true;
        }
    }
    
    return false;
}



void Drive::__updateDynamicTargetCoord()
{
    switch(m_target->descriptor()->obType())
    {
//    case entity::Type::STARSYSTEM:
//    {
//        float angle = M_PI/2 - meti::getAngle(meti::vec2(m_target->position()), meti::vec2(m_ownerVehicle->starsystem()->position())); //??    use cross()
//        m_targetPos = meti::genVec3f(ENTITY::STARSYSTEM::JUMPRADIUS, angle, m_ownerVehicle->starsystem()->position().z);
//        m_targetDistance = COLLISION_RADIUS_FOR_STATIC_COORD;
//        break;
//    }

    case entity::Type::PLANET:
    case entity::Type::ASTEROID: {
        m_targetPos = m_target->nextTurnPosition() + m_targetOffset;
        break;
    }
    case entity::Type::STAR:
    case entity::Type::CONTAINER:
    case entity::Type::VEHICLE: {
        m_targetPos = m_target->position() + m_targetOffset;
        break;
    }

    }
}


bool Drive::checkTargetEchievement(const meti::vec3& pos)
{
    if (m_target) {
        bool result = ceti::checkCollisionDotWithCircle_DIRTY(meti::vec2(pos),
                                                              meti::vec2(m_targetPos),
                                                              m_targetDistance);
        if (result) {
            return true;
        }
    }
    
    return false;
}


bool Drive::getDockingPermission()
{
    assert(false);
//    switch(m_target->type())
//    {
//        //case entity::Type::PLANET:       { return ((Planet*)m_target)->GetLand()->GetPermissionToLand(); break; }
//        case entity::Type::VEHICLE:
//        {
//            switch(m_target->subtype())
//            {
//                assert(false);
//                //case entity::Type::SPACESTATION: { return ((SpaceStation*)m_target)->land()->GetPermissionToLand(); break; }
//                //case SHIP:   { return targetOb->vehicle()->getPermissionToLand(); break; }
//            }
//            break;
//        }
//    }
    
    return false;
}

void Drive::__clearPath()
{
    m_pathCenters.clear();
    m_pathDirections.clear();
}

void Drive::__calcPath()
{
    //LOG("vehicle_id="+std::to_string(m_OwnerVehicle->id())+" DriveComplex::CalcPath " + "target_pos(int, int)=" + std::to_string((int)target_pos.x) + "," + std::to_string((int)target_pos.y), DRIVECOMPLEX_LOG_DIP);
    
    __clearPath();

    int round_counter_max = 2000;//2 + 2*M_PI/angle_step;
    int round_counter = 0;

// DANGER    assert(false);
    float speed_base = m_ownerVehicle->properties().speed;
    
    glm::vec3 new_center(m_ownerVehicle->position());
    glm::vec3 target_dir = glm::normalize(m_targetPos - m_ownerVehicle->position());

    glm::quat zero_quat;
    glm::quat target_quat;

    glm::vec3 direction = glm::normalize(glm::vec3(m_ownerVehicle->direction()));

    meti::quatBetweenVectors(target_quat, direction, target_dir);
    glm::quat interpolated_quat = glm::lerp(zero_quat, target_quat, 0.02f);
    while (std::fabs(glm::dot(direction, target_dir)) < 0.9999) {
        direction = interpolated_quat * direction;
 
        new_center += direction * speed_base/* * gravity_rate*/;
        target_dir = glm::normalize(m_targetPos - new_center);

        m_pathCenters.push_back(new_center);
        m_pathDirections.push_back(direction);

        round_counter++;
        if (round_counter > round_counter_max) // target_pos is not reachable (within circle)
        {
            //__clearPath();
            break;
            //return;
        }
    }



    /// old
    ///
/*
   float az = atan2(m_ownerVehicle->direction().y, m_ownerVehicle->direction().x);
    //float az = acos(glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), m_OwnerVehicle->direction()));
    std::cout<<"angle= "<<glm::degrees(az)<<std::endl;

    glm::vec3 direction = m_ownerVehicle->direction();
        
    glm::vec3 gravity;
    const StarSystem& starsystem = *m_ownerVehicle->starsystem();
    int mass = m_ownerVehicle->mass();
    
    int sign = 1;
    float angle_step = glm::radians(1.0f);

    int round_counter_max = 2 + 2*M_PI/angle_step;
    int round_counter = 0;
    while (std::fabs(glm::dot(direction, target_dir)) < 0.999)
    {
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
    
        az += sign * angle_step;

        direction.x = cos(az);
        direction.y = sin(az);
        
        round_counter++;
        if (round_counter > round_counter_max) // target_pos is not reachable (within circle)
        {
            __clearPath();
            return;
        }

        //float gravity_rate = starsystem.CalcResultGravityForce(new_center, direction, mass);
        
        new_center += direction * speed_base; gravity_rate;

        m_PathCenterVec.push_back(new_center);
        m_PathDirectionVec.push_back(direction);
    }
*/
/// old

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

    if (m_pathCenters.size() > 1) {
        m_pathEnd = false;
        m_pathIndex = 0;
    } else {
        __clearPath();
    }
}


void Drive::update()
{
    if (!m_pathEnd) {
        if (m_pathIndex < m_pathCenters.size()) {
            m_ownerVehicle->setPosition(m_pathCenters[m_pathIndex]);
            m_ownerVehicle->setDirection(m_pathDirections[m_pathIndex]);
            m_pathIndex++;
        } else {
            m_pathEnd = true;
        }
    }
}

//void DriveComplex::updatePathVisualisation()
//{
////    m_PathVisualCenter.FillData(m_PathCenterVec, 10, 10);
////    m_PathVisualTurn.FillData(m_PathCenterVec, TURN_TIME, 14);
//}

//void DriveComplex::drawPath(const jeti::Renderer& render)
//{
//    if (m_pathEnd == false)
//    {
//        updatePathVisualisation();
////        m_PathVisualCenter.Draw(render);
////        m_PathVisualTurn.Draw(render);
//    }
//}

} // namespace complex
