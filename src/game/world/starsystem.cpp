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


#include <world/starsystem.hpp>
#include <world/Sector.hpp>

#include <math/myVector.hpp>

#include <builder/spaceobjects/BlackHoleBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/pilots/NpcBuilder.hpp>

#include <common/Logger.hpp>
#include <common/Collision.hpp>
#include <math/rand.hpp>
#include <common/myStr.hpp>

#include <world/EntityManager.hpp>

#include <config/config.hpp>

#include <render/Render.hpp>

#include <slots/ItemSlot.hpp>
#include <items/others/Bomb.hpp>

#include <spaceobjects/IncludeSpaceObjects.hpp>

#include <pilots/Player.hpp>
#include <pilots/Npc.hpp>

#include <effects/DistantNebulaEffect.hpp>
#include <effects/DistantStarEffect.hpp>
#include <effects/lazerTrace.hpp>
#include <effects/particlesystem/ExplosionEffect.hpp>

#include <text/VerticalFlowText.hpp> 

#include <garbage/EntityGarbage.hpp>

#include <gui/GuiManager.hpp>
#include <gui/GuiRadar.hpp>

#include <struct/RaceInformationCollector.hpp>

#include <render/Mesh.hpp>

int StarSystem::counter = 0;

                
StarSystem::StarSystem(int id)
:
race_id(TYPE::RACE::R0_ID),
conqueror_race_id(TYPE::RACE::NONE_ID),
unique_update_inDymanic_done(false),
unique_update_inStatic_done(false),
container_num_max(CONTAINER_NUM_MAX_DEFAULT),
sector(nullptr)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::STARSYSTEM_ID); 
    
    SetPlaceTypeId(TYPE::PLACE::SPACE_ID);
    
    condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;

    this->SetStarSystem(this);
    
    counter++;
}

StarSystem::~StarSystem()
{    
        // effects    
        for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)   { delete distantNebulaEffect_vec[i]; } 
        for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)     { delete distantStarEffect_vec[i];   } 
        for(unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)     { delete effect_LAZERTRACE_vec[i]; } 
        for(unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { delete effect_PARTICLESYSTEM_vec[i]; } 
        for(unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)      { delete effect_SHOCKWAVE_vec[i]; } 
        for(unsigned int i=0; i<text_DAMAGE_vec.size(); i++)           { delete text_DAMAGE_vec[i]; } 
        
        counter--;
}      

/* virtual */
void StarSystem::PutChildsToGarbage() const
{    
    for(unsigned int i=0; i<STAR_vec.size(); i++)        { EntityGarbage::Instance().Add(STAR_vec[i]); } 
    for(unsigned int i=0; i<PLANET_vec.size(); i++)    { EntityGarbage::Instance().Add(PLANET_vec[i]); } 
    for(unsigned int i=0; i<ASTEROID_vec.size(); i++)  { EntityGarbage::Instance().Add(ASTEROID_vec[i]); } 
    for(unsigned int i=0; i<CONTAINER_vec.size(); i++) { EntityGarbage::Instance().Add(CONTAINER_vec[i]); } 
    for(unsigned int i=0; i<ROCKET_vec.size(); i++)    { EntityGarbage::Instance().Add(ROCKET_vec[i]); } 
    for(unsigned int i=0; i<BLACKHOLE_vec.size(); i++) { EntityGarbage::Instance().Add(BLACKHOLE_vec[i]); } 
    for(unsigned int i=0; i<VEHICLE_vec.size(); i++)   { EntityGarbage::Instance().Add(VEHICLE_vec[i]); } 
}      

Npc* StarSystem::GetFreeLeaderByRaceId(TYPE::RACE race_id) const
{
    std::vector<Npc*> tmp_npc_vec;
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() == race_id)
        {
            tmp_npc_vec.push_back(VEHICLE_vec[i]->GetOwnerNpc());
        }
    }
    
    int leader_skill_max = 0;
    int index_max = -1;
    for (unsigned int i=0; i<tmp_npc_vec.size(); i++)
    {
        int leader_skill = tmp_npc_vec[i]->GetSkills().GetLeader();
        if (leader_skill > leader_skill_max)
        {
            leader_skill_max = leader_skill;
            index_max = i;
        }
    }
    
    if (index_max != -1)
    {
        return tmp_npc_vec[index_max];
    }
    
    return nullptr;
}

void StarSystem::CreateGroupAndShareTask(Npc* npc_leader, StarSystem* target_starsystem, int num_max) const
{    
    std::vector<Npc*> tmp_npc_vec;
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() == npc_leader->GetRaceId())
        {
            tmp_npc_vec.push_back(VEHICLE_vec[i]->GetOwnerNpc());
        }
    }
    
    int num = 0;
    for (unsigned int i=0; (i<tmp_npc_vec.size() and (num<num_max)); i++)
    {
        if (tmp_npc_vec[i]->GetVehicle()->IsAbleToJumpTo(target_starsystem) == true)
        {
            tmp_npc_vec[i]->CloneMacroTaskFrom(npc_leader);
            num++;
        }
    }
}
        
void StarSystem::AddVehicle(Vehicle* vehicle, const glm::vec3& center, const glm::vec3& angle, const BaseSpaceEntity* const parent)
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1
    Logger::Instance().Log(" StarSystem(" + int2str(GetId()) + ")::AddVehicle(" + int2str(vehicle->GetId())+")", ENTITY_TRANSACTION_LOG_DIP);
    
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if (VEHICLE_vec[i]->GetId() == vehicle->GetId())
        {
            Logger::Instance().Log("StarSystem::AddVehicle dublicated vehicle found(fix that)" + getBaseInfoStr(vehicle));
            exit(0);
        }
    }
    #endif
    
    vehicle->SetPlaceTypeId(TYPE::PLACE::SPACE_ID);
    vehicle->SetStarSystem(this);  
    
    vehicle->SetCenter(center); 
    //vehicle->SetAngle(angle);   
    vehicle->UpdateOrientation();  
    
    vehicle->SetColor(color);
    
    VEHICLE_vec.push_back(vehicle);  

    if (vehicle->GetSubTypeId() == TYPE::ENTITY::SATELLITE_ID)
    {
        ((Satellite*)vehicle)->BindParent(parent);
    }
    else
    {
        vehicle->SetParent(parent);
    }
}


void StarSystem::AddBullet(RocketBullet* rocket, const glm::vec3& center, const glm::vec3& angle)
{
    rocket->SetPlaceTypeId(TYPE::PLACE::SPACE_ID);
    rocket->SetStarSystem(this);  
            
    rocket->SetCenter(center); 
    //rocket->SetAngle(angle);   
    rocket->UpdateOrientation();          

    ROCKET_vec.push_back(rocket);  
}

void StarSystem::Add(BasePlanet* object, const BaseSpaceEntity* parent, int it)
{
    object->BindParent(parent, it);
    
    object->SetStarSystem(this);
    object->SetPlaceTypeId(TYPE::PLACE::SPACE_ID);   
        
    switch(object->GetTypeId())
    {
        case TYPE::ENTITY::STAR_ID:
        {
            STAR_vec.push_back((Star*)object);
            break;
        }
        
        case TYPE::ENTITY::PLANET_ID:
        {
            PLANET_vec.push_back((Planet*)object);
            break;
        }
        
        case TYPE::ENTITY::ASTEROID_ID:
        {
            ASTEROID_vec.push_back((Asteroid*)object);
            break;
        }
    }
}
                
void StarSystem::AddContainer(Container* container, const glm::vec3& center)
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1
    Logger::Instance().Log(" StarSystem(" + int2str(GetId()) + ")::AddVehicle(" + int2str(container->GetId()) + ")", ENTITY_TRANSACTION_LOG_DIP);
    
    
    for (unsigned int i=0; i<CONTAINER_vec.size(); i++)
    {
        if (CONTAINER_vec[i]->GetId() == container->GetId())
        {
            Logger::Instance().Log("StarSystem::AddContainer dublicated container found(fix that)" + getBaseInfoStr(container));
            exit(0);
        }
    }
    #endif
    
    container->SetStarSystem(this);
    container->SetPlaceTypeId(TYPE::PLACE::SPACE_ID);
    container->SetCenter(center);
    
    CONTAINER_vec.push_back(container);
}

void StarSystem::Add(BlackHole* blackhole, const glm::vec3& center)
{
    blackhole->SetStarSystem(this);
    blackhole->SetPlaceTypeId(TYPE::PLACE::SPACE_ID);
    blackhole->SetCenter(center);
    BLACKHOLE_vec.push_back(blackhole);
}    
            
void StarSystem::Add(ShockWaveEffect* shockwave, const glm::vec2& center)           
{ 
    shockwave->SetCenter(center); 
    effect_SHOCKWAVE_vec.push_back(shockwave); 
}

void StarSystem::Add(ExplosionEffect* explosion, const glm::vec3& center)           
{ 
    float radius_damage = explosion->GetRadius();
    float damage = 0;
    Add(explosion, center, damage, radius_damage);
}

void StarSystem::Add(ExplosionEffect* explosion, const glm::vec3& center, float damage, float radius_damage)           
{ 
    explosion->SetCenter(center);
    effect_PARTICLESYSTEM_vec.push_back(explosion); 
    
    float radius_effect = explosion->GetRadius();
    if ((radius_effect > 75) && (GetShockWaveEffectNum() < SHOCKWAVES_MAX_NUM))
    {
        ShockWaveEffect* shockwave = getNewShockWave(radius_effect);
        Add(shockwave, vec3ToVec2(center));
    }
    
    if (radius_effect > 25)
    {
        DamageEventInsideCircle(center, radius_damage, damage, true);
    }
    //explosion.play()
}

void StarSystem::Add(LazerTraceEffect* lazerTraceEffect)     { effect_LAZERTRACE_vec.push_back(lazerTraceEffect); }
void StarSystem::Add(BaseParticleSystem* ps)                 { effect_PARTICLESYSTEM_vec.push_back(ps); }
void StarSystem::Add(VerticalFlowText* text)                 { text_DAMAGE_vec.push_back(text); }
void StarSystem::Add(DistantNebulaEffect* dn)                { distantNebulaEffect_vec.push_back(dn); }
void StarSystem::Add(DistantStarEffect* ds)                  { distantStarEffect_vec.push_back(ds); }
//// ******* TRANSITION ******* 
                     
// poor                
Planet* StarSystem::GetClosestInhabitedPlanet(const glm::vec2& _pos) const
{        
    Planet* requested_planet = nullptr;
    
    std::vector<Planet*> tmp_planet_vec;         
    for(unsigned int i=0; i<PLANET_vec.size(); i++)
    {
        if (PLANET_vec[i]->GetPopulation() > 0)
        {
            tmp_planet_vec.push_back(PLANET_vec[i]);
        }
    }
    
    if (tmp_planet_vec.size() >= 1)
    {
        requested_planet = tmp_planet_vec[0];
        float dist_min = distanceBetween(_pos, tmp_planet_vec[0]->GetCenter());
        if (tmp_planet_vec.size() > 1)
        {
            for (unsigned int i=1; i<tmp_planet_vec.size(); i++)
            {
                float dist = distanceBetween(_pos, tmp_planet_vec[i]->GetCenter());
                if (dist < dist_min)
                {
                    requested_planet = tmp_planet_vec[i];
                    dist_min = dist;
                }
            }
        
        }
    }
    
    return requested_planet;
}

Planet* StarSystem::GetRandomInhabitedPlanet() const
{
    Planet* requested_planet = nullptr;

    std::vector<Planet*> tmp_planet_vec;
    for(unsigned int i=0; i<PLANET_vec.size(); i++)
    {
        if (PLANET_vec[i]->GetPopulation() > 0)
        {
            tmp_planet_vec.push_back(PLANET_vec[i]);
        }
    }
    
    if (tmp_planet_vec.size() >= 1) 
    {
        requested_planet = tmp_planet_vec[getRandInt(0, tmp_planet_vec.size()-1)];
    }

    return requested_planet;
}

Planet* StarSystem::GetRandomPlanet() const
{
    return PLANET_vec[getRandInt(0, PLANET_vec.size()-1)];
}

Vehicle* StarSystem::GetRandomVehicle() const
{
    return VEHICLE_vec[getRandInt(0, VEHICLE_vec.size()-1)];
}

Vehicle* StarSystem::GetRandomVehicleExcludingNpcRaceId(TYPE::RACE _race_id) const
{
    std::vector<Vehicle*> _vehicle_vec;
    Vehicle* requested_vehicle = nullptr;
    
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if (VEHICLE_vec[i]->GetOwnerNpc() != nullptr)
        {
            if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() != _race_id)
            {
                _vehicle_vec.push_back(VEHICLE_vec[i]);
            }
        }
    }
    
    if (_vehicle_vec.size() > 0)
    {
        requested_vehicle = _vehicle_vec[getRandInt(0, _vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}

Vehicle* StarSystem::GetRandomVehicleByNpcRaceId(TYPE::RACE _race_id) const
{
    std::vector<Vehicle*> _vehicle_vec;
    Vehicle* requested_vehicle = nullptr;
    
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if (VEHICLE_vec[i]->GetOwnerNpc() != nullptr)
        {
            if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() == _race_id)
            {
                _vehicle_vec.push_back(VEHICLE_vec[i]);
            }
        }
    }
    
    if (_vehicle_vec.size() > 0)
    {
        requested_vehicle = _vehicle_vec[getRandInt(0, _vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}

Vehicle* StarSystem::GetRandomVehicle(const std::vector<TYPE::RACE>& rVec_race_id) const
{
    std::vector<Vehicle*> tmp_vehicle_vec;
    Vehicle* requested_vehicle = nullptr;

    for (unsigned int i=0; i<rVec_race_id.size(); i++)
    {    
        for (unsigned int j=0; j<VEHICLE_vec.size(); j++)
        {
            if (rVec_race_id[i] == VEHICLE_vec[j]->GetOwnerNpc()->GetRaceId())
            {
                tmp_vehicle_vec.push_back(VEHICLE_vec[j]);
            }
        }
    }
    
    if (tmp_vehicle_vec.size() > 0)
    {
        requested_vehicle = tmp_vehicle_vec[getRandInt(0, tmp_vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}


void StarSystem::UpdateStates()
{
    if (CONTAINER_vec.size() < 100)
    {
        asteroid_manager.Update(this);
    }
             
    if (Config::Instance().GetGameMode() == GAME_MODE::CRASH_TEST)
    {
        asteroid_manager.Update(this);
        ShipManager_s(50);
        
        if (BLACKHOLE_vec.size() < 5)
        {
            glm::vec2 center = getRandVec2f(200, 1200);
        
            
            glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
            Add(BlackHoleBuilder::Instance().GetNewBlackHole(), center3);
        }
    }
    
    //if (PLAYER_vec.size() > 0)
    //{
        //detalied_simulation = true;
    //}
    //else
    //{
        //detalied_simulation = false;
    //}

    bool enemy_is_here    = false;
    bool friendly_is_here = false; 
    
    Vehicle* _vehicle_evil = GetRandomVehicle(RaceInformationCollector::Instance().RACES_EVIL_vec);
    if (_vehicle_evil != nullptr)
    {
        enemy_is_here = true;
    }
    
    Vehicle* _vehicle_good = GetRandomVehicle(RaceInformationCollector::Instance().RACES_GOOD_vec);
    if (_vehicle_good != nullptr)
    {
        friendly_is_here = true;
    }
    
    switch(condition_id)
    {
        case ENTITY::STARSYSTEM::CONDITION::SAFE_ID:
        {
            if (enemy_is_here == true)
            {
                if (friendly_is_here == true)
                {
                    condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
                }
                else
                {
                    condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
                    if (GetRandomVehicleByNpcRaceId(TYPE::RACE::R6_ID) != nullptr)
                    {
                        conqueror_race_id = TYPE::RACE::R6_ID;
                    }
                
                    if (GetRandomVehicleByNpcRaceId(TYPE::RACE::R7_ID) != nullptr)
                    {
                        conqueror_race_id = TYPE::RACE::R7_ID;
                    }
                }
            }
        
            break;
        }

        case ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID:
        {
            if (friendly_is_here == true)
            {
                if (enemy_is_here == true)
                {
                    condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
                }
                else    
                {
                    condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
                    conqueror_race_id = TYPE::RACE::NONE_ID;
                }
            }
            
            break;
        }

        case ENTITY::STARSYSTEM::CONDITION::WAR_ID:
        {
            if (friendly_is_here == true)
            {
                if (enemy_is_here == false)
                {
                    condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
                }
            }
            else
            {
                condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
            }
                
            break;
        }
    }
}

float StarSystem::CalcResultGravityForce(const glm::vec3& center, const glm::vec3& orient, float mass) const
{
    float rate = 1; 
    for (unsigned int i=0; i<STAR_vec.size(); i++)
    {
        float dist = distanceBetween(center, STAR_vec[i]->GetCenter());
        if (dist < 5*STAR_vec[i]->GetCollisionRadius())
        {
            glm::vec3 force_dir(STAR_vec[i]->GetCenter() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);
                
            rate += power1*power2;
        }
    }

    for (unsigned int i=0; i<PLANET_vec.size(); i++)
    {
        float dist = distanceBetween(center, PLANET_vec[i]->GetCenter());
        if (dist < 5*PLANET_vec[i]->GetCollisionRadius())
        {
            glm::vec3 force_dir(PLANET_vec[i]->GetCenter() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);
            
            rate += power1*power2;
        }        
    }
    
    return rate;
}

        
void StarSystem::Update(int time)
{                
    bool detalied_simulation = true;

    UpdateEntities_s(time, detalied_simulation);
    ManageUnavaliableObjects_s();
    ManageDeadObjects_s();         // no need to update so frequently, pri /6
                        
    if (time > 0)
    {
        if (unique_update_inDymanic_done == false)
        {
            hyperspace.PostHyperJumpEvent(this);
            
            unique_update_inDymanic_done = true;
            unique_update_inStatic_done  = false;
        }

        // phisics
        rocketCollision_s(detalied_simulation);   // pri/2
        asteroidCollision_s(detalied_simulation); // pri/2
        ExternalForcesAffection_s(detalied_simulation); // pri/2
        //phisics
        
        if (CONTAINER_vec.size() > container_num_max)
        {
            unsigned int index = getRandInt(0, container_num_max-1);
            CONTAINER_vec[index]->Hit(100, true);
        }
    }
    else
    {
        if (unique_update_inStatic_done == false)
        {                    
            UpdateInSpaceInStatic_s();                 
            
            unique_update_inDymanic_done = false;
            unique_update_inStatic_done  = true;
        }            
    }
}

void StarSystem::rocketCollision_s(bool show_effect)
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                if (ROCKET_vec[ri]->GetAlive() == true) 
                {
                    // vehicle
                    if (collide == false)
                    {
                        for (unsigned int vi = 0; vi < VEHICLE_vec.size(); vi++)
                        {
                                if (ROCKET_vec[ri]->GetOwnerId() != VEHICLE_vec[vi]->GetId())
                                {                        
                                    collide = checkCollision2D(ROCKET_vec[ri], VEHICLE_vec[vi], show_effect);
                                    if (collide == true) { break; }                        
                                }
                        }
                    }
                    else  { continue; }   
                    //
                    
                    
                    if (collide == false)
                    {
                            for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
                            {
                                collide = checkCollision2D(ROCKET_vec[ri], ASTEROID_vec[ai], show_effect);
                                if (collide == true) { break; }
                            }
                    }
                    else  { continue; }
                    
                    
                    if (collide == false)
                    {
                            for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
                            {
                                collide = checkCollision2D(ROCKET_vec[ri], CONTAINER_vec[ci], show_effect);
                                if (collide == true) {     break; }
                            }
                    }
                    else  { continue; }
                }
        }
}






void StarSystem::asteroidCollision_s(bool show_effect)
{
    bool collide = false;
    
        for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
        {
                if (ASTEROID_vec[ai]->GetAlive() == true) 
                {
                    if (collide == false)
                    {
                            for (unsigned int vi = 0; vi < VEHICLE_vec.size(); vi++)
                            {
                                    collide = checkCollision2D(ASTEROID_vec[ai], VEHICLE_vec[vi], show_effect);
                                if (collide == true) { break; }
                            }                            
                    }
                    else { continue; }            
                                        
                    if (collide == false)
                    {
                            for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
                            {
                                    collide = checkCollision2D(ASTEROID_vec[ai], PLANET_vec[pi], show_effect);
                                if (collide == true) { break; }
                            }                            
                    }
                    else { continue; }
                    
                    
                    
                    if (collide == false)
                    {
                            for (unsigned int si = 0; si < STAR_vec.size(); si++)
                            {
                                    collide = checkCollision2D(ASTEROID_vec[ai], STAR_vec[si], show_effect);
                                if (collide == true) { break; }
                            }                            
                    }
                    else { continue; }
                }
    }
}

void StarSystem::ExternalForcesAffection_s(bool detalied_simulation)
{
    //for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
    //{

    //}   
    
    //for (unsigned int si = 0; si < STAR_vec.size(); si++)
    //{

    //}  
                            
}

void StarSystem::UpdateEntities_s(int time, bool show_effect)
{
    for (unsigned int i=0; i<STAR_vec.size(); i++)             { STAR_vec[i]->UpdateInSpace(time, show_effect);  }    
    for (unsigned int i=0; i<PLANET_vec.size(); i++)           { PLANET_vec[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)         { BLACKHOLE_vec[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<CONTAINER_vec.size(); i++)           { CONTAINER_vec[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)            { ASTEROID_vec[i]->UpdateInSpace(time, show_effect); }
    
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)             { VEHICLE_vec[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<ROCKET_vec.size(); i++)              { ROCKET_vec[i]->UpdateInSpace(time, show_effect); }
    
    // effects
    for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)      { effect_LAZERTRACE_vec[i]->Update(); }
    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { effect_PARTICLESYSTEM_vec[i]->Update(); }
    for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)     { effect_SHOCKWAVE_vec[i]->Update(); }
    for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)         { text_DAMAGE_vec[i]->Update(); }   
    for (unsigned int i=0; i<distantNebulaEffect_vec.size(); i++) { distantNebulaEffect_vec[i]->Update(); } 
}  
      
void StarSystem::UpdateInSpaceInStatic_s()
{
    UpdateStates();
            
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)         
    { 
        VEHICLE_vec[i]->GetOwnerNpc()->UpdateInSpaceInStatic(); 
        if (VEHICLE_vec[i]->GetSubTypeId() == TYPE::ENTITY::SPACESTATION_ID)
        {
            ((SpaceStation*)VEHICLE_vec[i])->GetLand()->UpdateInStatic();
        }
    }

    for (unsigned int i=0; i<STAR_vec.size(); i++)         { STAR_vec[i]->UpdateInSpaceInStatic(); }         
    for (unsigned int i=0; i<PLANET_vec.size(); i++)         { PLANET_vec[i]->UpdateInSpaceInStatic(); }

    garbage_effects.clear(); 
}      

void StarSystem::FindRenderVisibleEntities_c(Player* player)
{
    player->ClearVisibleEntities();
        
    for (unsigned int i=0; i<STAR_vec.size(); i++)             { player->AddIfVisible(STAR_vec[i]); }    
    for (unsigned int i=0; i<PLANET_vec.size(); i++)           { player->AddIfVisible(PLANET_vec[i]); }
    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)         { player->AddIfVisible(ASTEROID_vec[i]); } 
    for (unsigned int i=0; i<CONTAINER_vec.size(); i++)        { player->AddIfVisible(CONTAINER_vec[i]); }
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)     { player->AddIfVisible(VEHICLE_vec[i]); } 
    for (unsigned int i=0; i<ROCKET_vec.size(); i++)           { player->AddIfVisible(ROCKET_vec[i]); }
    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)        { player->AddIfVisible(BLACKHOLE_vec[i]); } 
                   
        //effects
    for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)    { player->AddIfVisible(effect_SHOCKWAVE_vec[i]); }
    for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)   { player->AddIfVisible(effect_LAZERTRACE_vec[i]); }
    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { player->AddIfVisible(effect_PARTICLESYSTEM_vec[i]); }
    for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)        { player->AddIfVisible(text_DAMAGE_vec[i]); }
}

void StarSystem::FindRadarVisibleEntities_c(Player* player)
{    
    GuiRadar& gui_radar = *(GuiRadar*)GuiManager::Instance().GetGuiElement(TYPE::GUI::GUI_RADAR_ID);
    const Vehicle& vehicle = *player->GetNpc()->GetVehicle();
    gui_radar.ResetData();
    
    for (unsigned int i=0; i<STAR_vec.size(); i++)        { gui_radar.Add(STAR_vec[i]); }    
    for (unsigned int i=0; i<PLANET_vec.size(); i++)      { gui_radar.Add(PLANET_vec[i]); } 
    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)   { gui_radar.Add(BLACKHOLE_vec[i]); } 
                
    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)    { gui_radar.AddIfWithinRadarRange(ASTEROID_vec[i], vehicle); }         
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)     { gui_radar.AddIfWithinRadarRange(VEHICLE_vec[i], vehicle); }        
}


void StarSystem::DrawBackground(const Renderer& render, const glm::vec2& scroll_coords)
{   
    for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)
    { 
        distantNebulaEffect_vec[i]->Render(render, glm::vec3(1.0f)); 
    }

    for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)
    { 
        DistantStarEffect& ds = *distantStarEffect_vec[i]; 
        render.DrawParticles(ds.GetMesh(), ds.GetTextureOb(), ds.GetActualModelMatrix()); 
    }
}
    
void StarSystem::DrawOrbits(const Renderer& render)
{
    for(unsigned int i = 0; i < PLANET_vec.size(); i++) 
    { 
        PLANET_vec[i]->GetOrbit().DrawPath(render); 
    }

    for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
    { 
        ASTEROID_vec[i]->GetOrbit().DrawPath(render); 
    }
}
 
void StarSystem::DrawPath()
{
        for(unsigned int i=0; i<VEHICLE_vec.size(); i++) 
    { 
        //VEHICLE_vec[i]->GetDriveComplex()->DrawPath(); 
    }
}
     
void StarSystem::ShipManager_s(unsigned int num)
{
    while (VEHICLE_vec.size() < num)
    {
        TYPE::RACE prace_id = TYPE::RACE::R0_ID;
        if (getRandBool())
        {
            prace_id = TYPE::RACE::R6_ID;
        }
        
        TYPE::ENTITY psubtype_id    = TYPE::ENTITY::WARRIOR_ID;
        TYPE::ENTITY psubsubtype_id = TYPE::ENTITY::WARRIOR_ID;
        int size_id     = SIZE_4_ID;
        int weapons_num = 7;
    
        Npc* new_pnpc = NpcBuilder::Instance().GetNewNpc(prace_id, psubtype_id, psubsubtype_id);
        Ship* new_pship = ShipBuilder::Instance().GetNewShip(prace_id, psubtype_id, size_id, weapons_num);
        ShipBuilder::Instance().EquipEquipment(new_pship);   // improove
    
        new_pship->BindOwnerNpc(new_pnpc);

        glm::vec2 center = getRandVec2f(100, 800);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,getRandInt(0, 360));
        
        AddVehicle(new_pship, center3, angle);
    }
}


void StarSystem::ManageUnavaliableObjects_s()
{               
    for (std::vector<Vehicle*>::iterator it=VEHICLE_vec.begin(); it<VEHICLE_vec.end(); ++it)
    {
        if ((*it)->GetPlaceTypeId() != TYPE::PLACE::SPACE_ID)
        {    
            #if ENTITY_TRANSACTION_LOG_ENABLED == 1
            Logger::Instance().Log("starsysten("+int2str(GetId())+ ")::RemoveVehicle(" + int2str((*it)->GetId())+")");
            #endif
            it = VEHICLE_vec.erase(it);
        }
    }
}
            
void StarSystem::ManageDeadObjects_s()
{      
       for(std::vector<Vehicle*>::iterator it=VEHICLE_vec.begin(); it<VEHICLE_vec.end(); ++it)
        {
                   if ((*it)->GetGarbageReady() == true)
            {  
                    EntityGarbage::Instance().Add(*it);
                    it = VEHICLE_vec.erase(it);
            } 
        }

       for(std::vector<BlackHole*>::iterator it=BLACKHOLE_vec.begin(); it<BLACKHOLE_vec.end(); ++it)
        {
            if ((*it)->GetGarbageReady() == true)
            {
                    EntityGarbage::Instance().Add(*it);
                    it = BLACKHOLE_vec.erase(it);
                }
        }  
                
       for(std::vector<Asteroid*>::iterator it=ASTEROID_vec.begin(); it<ASTEROID_vec.end(); ++it)
        {
            if ((*it)->GetGarbageReady() == true)
            {
                    EntityGarbage::Instance().Add(*it);
                    it = ASTEROID_vec.erase(it);
                }
        }  

       for(std::vector<Container*>::iterator it=CONTAINER_vec.begin(); it<CONTAINER_vec.end(); ++it)
        {
            if ((*it)->GetGarbageReady() == true)
            {   
                    EntityGarbage::Instance().Add(*it);
                    it = CONTAINER_vec.erase(it);
            }     
        }

       for(std::vector<RocketBullet*>::iterator it=ROCKET_vec.begin(); it<ROCKET_vec.end(); ++it)
        {
            if ((*it)->GetGarbageReady() == true)
            {   
                    EntityGarbage::Instance().Add(*it);
                    it = ROCKET_vec.erase(it);
            } 
        }        
        
        //effects
       for(std::vector<ShockWaveEffect*>::iterator it=effect_SHOCKWAVE_vec.begin(); it<effect_SHOCKWAVE_vec.end(); ++it)
        {
            if ((*it)->is_alive == false)
            {
                garbage_effects.add(*it);
                   it = effect_SHOCKWAVE_vec.erase(it);
            }
        }

       for(std::vector<LazerTraceEffect*>::iterator it=effect_LAZERTRACE_vec.begin(); it<effect_LAZERTRACE_vec.end(); ++it)
        {
             if ((*it)->GetIsAlive() == false)
             {   
                   garbage_effects.add(*it);
                    it = effect_LAZERTRACE_vec.erase(it);
             } 
        }

       for(std::vector<BaseParticleSystem*>::iterator it=effect_PARTICLESYSTEM_vec.begin(); it<effect_PARTICLESYSTEM_vec.end(); ++it)
        {
            if ((*it)->GetAlive() == false)
            {   
                    garbage_effects.add(*it);
                    it = effect_PARTICLESYSTEM_vec.erase(it);
            } 
        }

       for(std::vector<VerticalFlowText*>::iterator it=text_DAMAGE_vec.begin(); it<text_DAMAGE_vec.end(); ++it)
        {
            if ((*it)->GetAlive() == false)
            {   
                    garbage_effects.add(*it);
                    it = text_DAMAGE_vec.erase(it);
            } 
        }
}    
    

//void StarSystem::LaunchingEvent() const
//{
    //for (unsigned int i=0; i<PLANET_vec.size(); i++)
    //{
        ////PLANET_vec[i]->GetLand()->ManageLaunching();
    //}
//}        

void StarSystem::BombExplosionEvent(Container* container, bool show_effect)
{
    float radius = ((Bomb*)container->GetItemSlot()->GetItem())->GetRadius();
    float damage = ((Bomb*)container->GetItemSlot()->GetItem())->GetDamage(); 
    glm::vec3 center(container->GetCenter());
    
    ExplosionEffect* explosion = getNewExplosionEffect(radius);
    Add(explosion, center, radius, damage);
}

void StarSystem::StarSparkEvent(float radius) const
{
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
        {
                   if ( distanceBetween(VEHICLE_vec[i]->GetCenter(), GetStar()->GetCenter()) < radius )
                   {
                       if (VEHICLE_vec[i]->GetSlotRadar()->GetItem() != nullptr)
                       {
                       VEHICLE_vec[i]->GetSlotRadar()->GetItem()->LockEvent(2); 
                   }
               }
        }
}

void StarSystem::DamageEventInsideCircle(const glm::vec3& center, float radius, int damage, bool show_effect)
{
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {
        if ( distanceBetween(VEHICLE_vec[i]->GetCenter(), center) < radius )
        {
            VEHICLE_vec[i]->Hit(damage, show_effect); 
        }
    }
        
    for (unsigned int i=0; i<CONTAINER_vec.size(); i++)           
     {
         float dist = distanceBetween(CONTAINER_vec[i]->GetCenter(), center);
         if (dist < radius)
         {
            glm::vec3 force_dir(CONTAINER_vec[i]->GetCenter() - center);
            force_dir = glm::normalize(force_dir);
            float force_power = CONVERTER::RADIUS2FORCE.GetEquivalent(dist); 
            std::cout<<dist<<" "<<force_power<<" "<<str(force_dir)<<std::endl;                       
    
            CONTAINER_vec[i]->ApplyImpulse(force_dir, force_power); 
         }
     }
         
}

bool StarSystem::IsAnyActiveParticlesEffectPresent(int request_type_id) const
{
    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++)
    {
        if (effect_PARTICLESYSTEM_vec[i]->GetTypeId() == request_type_id)
        {
            return true;
        }
    } 
    
    return false;
}
        

/*virtual */
void StarSystem::PostDeathUniqueEvent(bool) 
{}

void StarSystem::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"sector_id", sector->GetId());
    
    save_ptree.put(root+"color.r", color.r);
    save_ptree.put(root+"color.g", color.g);
    save_ptree.put(root+"color.b", color.b);
    save_ptree.put(root+"color.a", color.a);
            
    for (unsigned int i=0; i<distantStarEffect_vec.size(); i++)
    {
        distantStarEffect_vec[i]->Save(save_ptree, root);
    }

    for (unsigned int i = 0; i<distantNebulaEffect_vec.size(); i++)
    {
        distantNebulaEffect_vec[i]->Save(save_ptree, root);
    }

}

void StarSystem::LoadData(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_StarSystem.sector_id = load_ptree.get<int>("sector_id");
    
    color.r = load_ptree.get<float>("color.r");
    color.g = load_ptree.get<float>("color.g");
    color.b = load_ptree.get<float>("color.b");
    color.a = load_ptree.get<float>("color.a");
                    
    boost::property_tree::ptree tmp_ptree = load_ptree;
    if (tmp_ptree.get_child_optional("distant_nebula_effect"))
    {    
        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_nebula_effect"))
        {
            DistantNebulaEffect* dn = GetNewDistantNebulaEffect(NONE_ID);
            dn->Load(v.second);
            dn->Resolve();
            Add(dn);
        }
    }
    
    if (tmp_ptree.get_child_optional("distant_star_effect"))
    {    
        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_star_effect"))
        {
            DistantStarEffect* ds = GetNewDistantStarEffect(NONE_ID);
            ds->Load(v.second);
            ds->Resolve();
            Add(ds);
        }
    }
}

void StarSystem::ResolveData()
{
    ((Sector*)EntityManager::Instance().GetEntityById(data_unresolved_StarSystem.sector_id))->Add(this, data_unresolved_Orientation.center);
}

void StarSystem::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "starsystem." + int2str(GetStarSystem()->GetId())+".";

    Base::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    StarSystem::SaveData(save_ptree, root);
}

void StarSystem::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    StarSystem::LoadData(load_ptree);
}

void StarSystem::Resolve()
{
    Base::ResolveData(); 
    BaseSpaceEntity::ResolveData(); 
    StarSystem::ResolveData(); 
}        

