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

#include <meti/VectorUtils.hpp>

#include <builder/spaceobjects/BlackHoleBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/pilots/NpcBuilder.hpp>

#include <ceti/Logger.hpp>
#include <ceti/Collision.hpp>
#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>
#include <common/Config.hpp>

//#include <jeti/Render.hpp>

#include <slots/ItemSlot.hpp>
#include <item/others/Bomb.hpp>

#include <spaceobjects/ALL>

//#include <pilots/Player.hpp>
#include <pilots/Npc.hpp>

//#include <effects/DistantNebulaEffect.hpp>
//#include <effects/DistantStarEffect.hpp>
//#include <effects/lazerTrace.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>

//#include <text/VerticalFlowText.hpp>

//#include <gui/GuiManager.hpp>
//#include <gui/GuiRadar.hpp>

#include <descriptors/RaceDescriptors.hpp>
#include <descriptors/VehicleDescriptorGenerator.hpp>

//#include <jeti/Mesh.hpp>
#include <meti/RandUtils.hpp>

int Starsystem::m_counter = 0;


Starsystem::Starsystem(int id)
{ 
    setId(id);
    setTypeId(TYPE::ENTITY::STARSYSTEM_ID);
    
    setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    
    m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;

    setStarSystem(this);
    
    m_counter++;
}

Starsystem::~Starsystem()
{    
    // effects
//    for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)   { delete distantNebulaEffect_vec[i]; }
//    for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)     { delete distantStarEffect_vec[i];   }
//    for(unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)     { delete effect_LAZERTRACE_vec[i]; }
//    for(unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { delete effect_PARTICLESYSTEM_vec[i]; }
//    for(unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)      { delete effect_SHOCKWAVE_vec[i]; }
//    for(unsigned int i=0; i<text_DAMAGE_vec.size(); i++)           { delete text_DAMAGE_vec[i]; }

    m_counter--;
}      

/* virtual */
void Starsystem::putChildrenToGarbage() const
{    
    for(unsigned int i=0; i<m_stars.size(); i++)        { global::get().entityManager().addToGarbage(m_stars[i]); }
    for(unsigned int i=0; i<m_planets.size(); i++)    { global::get().entityManager().addToGarbage(m_planets[i]); }
    for(unsigned int i=0; i<m_asteroids.size(); i++)  { global::get().entityManager().addToGarbage(m_asteroids[i]); }
    for(unsigned int i=0; i<m_containers.size(); i++) { global::get().entityManager().addToGarbage(m_containers[i]); }
    for(unsigned int i=0; i<m_bullets.size(); i++)    { global::get().entityManager().addToGarbage(m_bullets[i]); }
    for(unsigned int i=0; i<m_blackholes.size(); i++) { global::get().entityManager().addToGarbage(m_blackholes[i]); }
    for(unsigned int i=0; i<m_vehicles.size(); i++)   { global::get().entityManager().addToGarbage(m_vehicles[i]); }
}      

Npc* Starsystem::freeLeaderByRaceId(TYPE::RACE race_id) const
{
    std::vector<Npc*> tmp_npc_vec;
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        if (m_vehicles[i]->npc()->GetRaceId() == race_id) {
            tmp_npc_vec.push_back(m_vehicles[i]->npc());
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

void Starsystem::createGroupAndShareTask(Npc* npc_leader, Starsystem* target_starsystem, int num_max) const
{    
    std::vector<Npc*> tmp_npc_vec;
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        if (m_vehicles[i]->npc()->GetRaceId() == npc_leader->GetRaceId())
        {
            tmp_npc_vec.push_back(m_vehicles[i]->npc());
        }
    }
    
    int num = 0;
    for (unsigned int i=0; (i<tmp_npc_vec.size() and (num<num_max)); i++)
    {
        if (tmp_npc_vec[i]->GetVehicle()->isAbleToJumpTo(target_starsystem) == true)
        {
            tmp_npc_vec[i]->CloneMacroTaskFrom(npc_leader);
            num++;
        }
    }
}

void Starsystem::add(Vehicle* vehicle, const glm::vec3& center, const glm::vec3& angle, const SpaceObject* const parent)
{
    //LOG(" StarSystem(" + std::to_string(id()) + ")::AddVehicle(" + std::to_string(vehicle->id())+")");
    
    for (unsigned int i=0; i<m_vehicles.size(); i++) {
        if (m_vehicles[i]->id() == vehicle->id()) {
            //LOG("StarSystem::AddVehicle dublicated vehicle found(fix that)" + getBaseInfoStr(vehicle));
            exit(1);
        }
    }
    
    vehicle->setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    vehicle->setStarSystem(this);
    
    vehicle->setCenter(center);
    //vehicle->SetAngle(angle);
    //vehicle->updateOrientation();
    
    // alpitodorender vehicle->SetColor(color);
    
    m_vehicles.push_back(vehicle);

    if (vehicle->subTypeId() == TYPE::ENTITY::SATELLITE_ID) {
        ((Satellite*)vehicle)->BindParent(parent);
    } else {
        vehicle->setParent(parent);
    }
}

void Starsystem::add(Ship* ship, const glm::vec3& center, const glm::vec3& angle)
{
    ship->setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    ship->setStarSystem(this);

    ship->setCenter(center);
    //ship->SetAngle(angle);
    //ship->updateOrientation();

    // alpitodorender ship->SetColor(color);

    m_vehicles.push_back(ship);
}

void Starsystem::add(RocketBullet* rocket, const glm::vec3& center, const glm::vec3& angle)
{
    rocket->setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    rocket->setStarSystem(this);

    rocket->setCenter(center);
    //rocket->SetAngle(angle);
    //rocket->updateOrientation();

    m_bullets.push_back(rocket);
}

void Starsystem::add(Planetoid* object, const SpaceObject* parent, int it)
{
    object->BindParent(parent, it);
    
    object->setStarSystem(this);
    object->setPlaceTypeId(TYPE::PLACE::SPACE_ID);

    switch(object->typeId())
    {
        case TYPE::ENTITY::STAR_ID:
        {
            m_stars.push_back((Star*)object);
            break;
        }

        case TYPE::ENTITY::PLANET_ID:
        {
            m_planets.push_back((Planet*)object);
            break;
        }

        case TYPE::ENTITY::ASTEROID_ID:
        {
            m_asteroids.push_back((Asteroid*)object);
            break;
        }
    }
}

void Starsystem::add(Container* container, const glm::vec3& center)
{
    //LOG(" StarSystem(" + std::to_string(id()) + ")::AddVehicle(" + std::to_string(container->id()) + ")");
        
    for (unsigned int i=0; i<m_containers.size(); i++) {
        if (m_containers[i]->id() == container->id()) {
            //LOG("StarSystem::AddContainer dublicated container found(fix that)" + getBaseInfoStr(container));
            exit(1);
        }
    }
    
    container->setStarSystem(this);
    container->setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    container->setCenter(center);
    
    m_containers.push_back(container);
}

void Starsystem::add(BlackHole* blackhole, const glm::vec3& center)
{
    blackhole->setStarSystem(this);
    blackhole->setPlaceTypeId(TYPE::PLACE::SPACE_ID);
    blackhole->setCenter(center);
    m_blackholes.push_back(blackhole);
}    

void Starsystem::add(Explosion* explosion, const glm::vec3& center)
{
    for (Vehicle* vehicle: m_vehicles) {
        if (glm::length(vehicle->center() - center) < explosion->radius()) {
            vehicle->hit(explosion->damage());
        }
    }
}

void Starsystem::add(ShockWaveEffect* shockwave, const glm::vec2& center)
{ 
//    shockwave->setCenter(center);
//    effect_SHOCKWAVE_vec.push_back(shockwave);
}

void Starsystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center)
{ 
//    float radius_damage = explosion->GetRadius();
//    float damage = 0;
//    Add(explosion, center, damage, radius_damage);
}

void Starsystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center, float damage, float radius_damage)
{ 
//    explosion->setCenter(center);
//    effect_PARTICLESYSTEM_vec.push_back(explosion);
    
//    float radius_effect = explosion->GetRadius();
//    if ((radius_effect > 75) && (GetShockWaveEffectNum() < SHOCKWAVES_MAX_NUM))
//    {
//        ShockWaveEffect* shockwave = getNewShockWave(radius_effect);
//        Add(shockwave, meti::vec2(center));
//    }
    
//    if (radius_effect > 25)
//    {
//        DamageEventInsideCircle(center, radius_damage, damage, true);
//    }
    //explosion.play()
}

//void StarSystem::Add(LazerTraceEffect* lazerTraceEffect)     { effect_LAZERTRACE_vec.push_back(lazerTraceEffect); }
//void StarSystem::Add(jeti::BaseParticleSystem* ps)                 { effect_PARTICLESYSTEM_vec.push_back(ps); }
//void StarSystem::Add(VerticalFlowText* text)                 { text_DAMAGE_vec.push_back(text); }
//void StarSystem::Add(DistantNebulaEffect* dn)                { distantNebulaEffect_vec.push_back(dn); }
//void StarSystem::Add(DistantStarEffect* ds)                  { distantStarEffect_vec.push_back(ds); }
//// ******* TRANSITION ******* 

// poor                
Planet* Starsystem::GetClosestInhabitedPlanet(const glm::vec2& _pos) const
{        
    Planet* requested_planet = nullptr;
    
    std::vector<Planet*> tmp_planet_vec;
    for(unsigned int i=0; i<m_planets.size(); i++)
    {
        if (m_planets[i]->GetPopulation() > 0)
        {
            tmp_planet_vec.push_back(m_planets[i]);
        }
    }
    
    if (tmp_planet_vec.size() >= 1)
    {
        requested_planet = tmp_planet_vec[0];
        float dist_min = meti::distance(_pos, tmp_planet_vec[0]->center());
        if (tmp_planet_vec.size() > 1)
        {
            for (unsigned int i=1; i<tmp_planet_vec.size(); i++)
            {
                float dist = meti::distance(_pos, tmp_planet_vec[i]->center());
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

Planet* Starsystem::GetRandomInhabitedPlanet() const
{
    Planet* requested_planet = nullptr;

    std::vector<Planet*> tmp_planet_vec;
    for(unsigned int i=0; i<m_planets.size(); i++)
    {
        if (m_planets[i]->GetPopulation() > 0)
        {
            tmp_planet_vec.push_back(m_planets[i]);
        }
    }
    
    if (tmp_planet_vec.size() >= 1)
    {
        requested_planet = tmp_planet_vec[meti::getRandInt(0, tmp_planet_vec.size()-1)];
    }

    return requested_planet;
}

Planet* Starsystem::GetRandomPlanet() const
{
    return m_planets[meti::getRandInt(0, m_planets.size()-1)];
}

Vehicle* Starsystem::GetRandomVehicle() const
{
    return m_vehicles[meti::getRandInt(0, m_vehicles.size()-1)];
}

Vehicle* Starsystem::GetRandomVehicleExcludingNpcRaceId(TYPE::RACE _race_id) const
{
    std::vector<Vehicle*> _vehicle_vec;
    Vehicle* requested_vehicle = nullptr;
    
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        if (m_vehicles[i]->npc() != nullptr)
        {
            if (m_vehicles[i]->npc()->GetRaceId() != _race_id)
            {
                _vehicle_vec.push_back(m_vehicles[i]);
            }
        }
    }
    
    if (_vehicle_vec.size() > 0)
    {
        requested_vehicle = _vehicle_vec[meti::getRandInt(0, _vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}

Vehicle* Starsystem::GetRandomVehicleByNpcRaceId(TYPE::RACE _race_id) const
{
    std::vector<Vehicle*> _vehicle_vec;
    Vehicle* requested_vehicle = nullptr;
    
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        if (m_vehicles[i]->npc() != nullptr)
        {
            if (m_vehicles[i]->npc()->GetRaceId() == _race_id)
            {
                _vehicle_vec.push_back(m_vehicles[i]);
            }
        }
    }
    
    if (_vehicle_vec.size() > 0)
    {
        requested_vehicle = _vehicle_vec[meti::getRandInt(0, _vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}

Vehicle* Starsystem::GetRandomVehicle(const std::vector<TYPE::RACE>& rVec_race_id) const
{
    std::vector<Vehicle*> tmp_vehicle_vec;
    Vehicle* requested_vehicle = nullptr;

    for (unsigned int i=0; i<rVec_race_id.size(); i++)
    {
        for (unsigned int j=0; j<m_vehicles.size(); j++)
        {
            if (rVec_race_id[i] == m_vehicles[j]->npc()->GetRaceId())
            {
                tmp_vehicle_vec.push_back(m_vehicles[j]);
            }
        }
    }
    
    if (tmp_vehicle_vec.size() > 0)
    {
        requested_vehicle = tmp_vehicle_vec[meti::getRandInt(0, tmp_vehicle_vec.size()-1)];
    }
    
    return requested_vehicle;
}


void Starsystem::UpdateStates()
{
    if (m_containers.size() < 100)
    {
        m_asteroid_manager.Update(this);
    }

    if (global::get().config().GetGameMode() == GAME_MODE::CRASH_TEST)
    {
        m_asteroid_manager.Update(this);
        ShipManager_s(50);
        
        if (m_blackholes.size() < 5)
        {
            glm::vec2 center = meti::getRandVec2f(200, 1200);
            
            glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
            add(global::get().blackHoleBuilder().create(), center3);
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
    
    Vehicle* _vehicle_evil = GetRandomVehicle(global::get().raceDescriptors().getRaces(TYPE::KIND::EVIL));
    if (_vehicle_evil) {
        enemy_is_here = true;
    }

    Vehicle* _vehicle_good = GetRandomVehicle(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    if (_vehicle_good) {
        friendly_is_here = true;
    }
    
    switch(m_condition_id)
    {
        case ENTITY::STARSYSTEM::CONDITION::SAFE_ID:
        {
            if (enemy_is_here == true)
            {
                if (friendly_is_here == true)
                {
                    m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
                }
                else
                {
                    m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
                    if (GetRandomVehicleByNpcRaceId(TYPE::RACE::R6_ID) != nullptr)
                    {
                        m_conqueror_race_id = TYPE::RACE::R6_ID;
                    }

                    if (GetRandomVehicleByNpcRaceId(TYPE::RACE::R7_ID) != nullptr)
                    {
                        m_conqueror_race_id = TYPE::RACE::R7_ID;
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
                    m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
                }
                else
                {
                    m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
                    m_conqueror_race_id = TYPE::RACE::NONE_ID;
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
                    m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
                }
            }
            else
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
            }

            break;
        }
    }
}

float Starsystem::calcResultGravityForce(const glm::vec3& center, const glm::vec3& orient, float mass) const
{
    float rate = 1;
    for (unsigned int i=0; i<m_stars.size(); i++)
    {
        float dist = meti::distance(center, m_stars[i]->center());
        if (dist < 5*m_stars[i]->collisionRadius())
        {
            glm::vec3 force_dir(m_stars[i]->center() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = meti::dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);

            rate += power1*power2;
        }
    }

    for (unsigned int i=0; i<m_planets.size(); i++)
    {
        float dist = meti::distance(center, m_planets[i]->center());
        if (dist < 5*m_planets[i]->collisionRadius())
        {
            glm::vec3 force_dir(m_planets[i]->center() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = meti::dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);
            
            rate += power1*power2;
        }
    }
    
    return rate;
}


void Starsystem::update(int time)
{                
    bool detalied_simulation = true;

    UpdateEntities_s(time, detalied_simulation);
    ManageUnavaliableObjects_s();
    ManageDeadObjects_s();         // no need to update so frequently, pri /6

    if (time > 0) {
        if (m_unique_update_inDymanic_done == false) {
            m_hyperspace.PostHyperJumpEvent(this);
            
            m_unique_update_inDymanic_done = true;
            m_unique_update_inStatic_done  = false;
        }

        // phisics
        rocketCollision_s(detalied_simulation);   // pri/2
        asteroidCollision_s(detalied_simulation); // pri/2
        ExternalForcesAffection_s(detalied_simulation); // pri/2
        //phisics
        
        if (m_containers.size() > m_container_num_max) {
            unsigned int index = meti::getRandInt(0, m_container_num_max-1);
            m_containers[index]->hit(100);
        }
    } else {
        if (!m_unique_update_inStatic_done) {
            UpdateInSpaceInStatic_s();
            
            m_unique_update_inDymanic_done = false;
            m_unique_update_inStatic_done  = true;
        }
    }
}

void Starsystem::rocketCollision_s(bool show_effect)
{
    bool collide = false;
    for (unsigned int ri = 0; ri < m_bullets.size(); ri++)
    {
        if (m_bullets[ri]->isAlive() == true)
        {
            // vehicle
            if (collide == false)
            {
                for (unsigned int vi = 0; vi < m_vehicles.size(); vi++)
                {
                    if (m_bullets[ri]->GetOwnerId() != m_vehicles[vi]->id())
                    {
                        collide = ceti::checkCollision2D(m_bullets[ri], m_vehicles[vi], show_effect);
                        if (collide == true) { break; }
                    }
                }
            }
            else  { continue; }
            //


            if (collide == false)
            {
                for (unsigned int ai = 0; ai < m_asteroids.size(); ai++)
                {
                    collide = ceti::checkCollision2D(m_bullets[ri], m_asteroids[ai], show_effect);
                    if (collide == true) { break; }
                }
            }
            else  { continue; }


            if (collide == false)
            {
                for (unsigned int ci = 0; ci < m_containers.size(); ci++)
                {
                    collide = ceti::checkCollision2D(m_bullets[ri], m_containers[ci], show_effect);
                    if (collide == true) {     break; }
                }
            }
            else  { continue; }
        }
    }
}






void Starsystem::asteroidCollision_s(bool show_effect)
{
    bool collide = false;
    
    for(unsigned int ai = 0; ai < m_asteroids.size(); ai++)
    {
        if (m_asteroids[ai]->isAlive() == true)
        {
            if (collide == false)
            {
                for (unsigned int vi = 0; vi < m_vehicles.size(); vi++)
                {
                    collide = ceti::checkCollision2D(m_asteroids[ai], m_vehicles[vi], show_effect);
                    if (collide == true) { break; }
                }
            }
            else { continue; }

            if (collide == false)
            {
                for (unsigned int pi = 0; pi < m_planets.size(); pi++)
                {
                    collide = ceti::checkCollision2D(m_asteroids[ai], m_planets[pi], show_effect);
                    if (collide == true) { break; }
                }
            }
            else { continue; }



            if (collide == false)
            {
                for (unsigned int si = 0; si < m_stars.size(); si++)
                {
                    collide = ceti::checkCollision2D(m_asteroids[ai], m_stars[si], show_effect);
                    if (collide == true) { break; }
                }
            }
            else { continue; }
        }
    }
}

void Starsystem::ExternalForcesAffection_s(bool detalied_simulation)
{
    //for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
    //{

    //}
    
    //for (unsigned int si = 0; si < STAR_vec.size(); si++)
    //{

    //}

}

void Starsystem::UpdateEntities_s(int time, bool show_effect)
{
    loadEntitiesResource(); // hack for speed run

    for (unsigned int i=0; i<m_stars.size(); i++)             { m_stars[i]->UpdateInSpace(time, show_effect);  }
    for (unsigned int i=0; i<m_planets.size(); i++)           { m_planets[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_blackholes.size(); i++)         { m_blackholes[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_containers.size(); i++)           { m_containers[i]->updateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_asteroids.size(); i++)            { m_asteroids[i]->UpdateInSpace(time, show_effect); }
    
    for (unsigned int i=0; i<m_vehicles.size(); i++)             { m_vehicles[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_bullets.size(); i++)              { m_bullets[i]->UpdateInSpace(time, show_effect); }
    
    // effects
//    for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)      { effect_LAZERTRACE_vec[i]->Update(); }
//    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { effect_PARTICLESYSTEM_vec[i]->Update(); }
//    for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)     { effect_SHOCKWAVE_vec[i]->Update(); }
//    for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)         { text_DAMAGE_vec[i]->Update(); }
//    for (unsigned int i=0; i<distantNebulaEffect_vec.size(); i++) { distantNebulaEffect_vec[i]->Update(); }
}

void Starsystem::loadEntitiesResource()
{
    // alpitodorender
    //    for (unsigned int i=0; i<STAR_vec.size(); i++)      { STAR_vec[i]->ValidateResources();  }
    //    for (unsigned int i=0; i<PLANET_vec.size(); i++)    { PLANET_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++) { BLACKHOLE_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<CONTAINER_vec.size(); i++) { CONTAINER_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)  { ASTEROID_vec[i]->ValidateResources(); }

    //    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)   { VEHICLE_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<ROCKET_vec.size(); i++)    { ROCKET_vec[i]->ValidateResources(); }

    //    // effects
    //    //for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)      { effect_LAZERTRACE_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { effect_PARTICLESYSTEM_vec[i]->ValidateResources(); }
    //    //for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)     { effect_SHOCKWAVE_vec[i]->ValidateResources(); }
    //    //for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)         { text_DAMAGE_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<distantNebulaEffect_vec.size(); i++) { distantNebulaEffect_vec[i]->ValidateResources(); }
    //    for (unsigned int i=0; i<distantStarEffect_vec.size(); i++) { distantStarEffect_vec[i]->ValidateResources(); }

}

void Starsystem::UpdateInSpaceInStatic_s()
{
    UpdateStates();

    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        m_vehicles[i]->npc()->UpdateInSpaceInStatic();
        if (m_vehicles[i]->subTypeId() == TYPE::ENTITY::SPACESTATION_ID)
        {
            ((SpaceStation*)m_vehicles[i])->land()->UpdateInStatic();
        }
    }

    for (unsigned int i=0; i<m_stars.size(); i++)         { m_stars[i]->UpdateInSpaceInStatic(); }
    for (unsigned int i=0; i<m_planets.size(); i++)         { m_planets[i]->UpdateInSpaceInStatic(); }

    //garbage_effects.clear();
}      

void Starsystem::findRenderVisibleEntities_c(Player* player)
{
    //player->ClearVisibleEntities();

//    for (unsigned int i=0; i<STAR_vec.size(); i++)             { player->addIfVisible(STAR_vec[i]); }
//    for (unsigned int i=0; i<PLANET_vec.size(); i++)           { player->addIfVisible(PLANET_vec[i]); }
//    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)         { player->addIfVisible(ASTEROID_vec[i]); }
//    for (unsigned int i=0; i<CONTAINER_vec.size(); i++)        { player->addIfVisible(CONTAINER_vec[i]); }
//    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)     { player->addIfVisible(VEHICLE_vec[i]); }
//    for (unsigned int i=0; i<ROCKET_vec.size(); i++)           { player->addIfVisible(ROCKET_vec[i]); }
//    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)        { player->addIfVisible(BLACKHOLE_vec[i]); }

    //effects
//    for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)    { player->addIfVisible(effect_SHOCKWAVE_vec[i]); }
//    for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)   { player->addIfVisible(effect_LAZERTRACE_vec[i]); }
//    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { player->addIfVisible(effect_PARTICLESYSTEM_vec[i]); }
//    for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)        { player->addIfVisible(text_DAMAGE_vec[i]); }
}

void Starsystem::findRadarVisibleEntities_c(Player* player)
{    
//    GuiRadar& gui_radar = *(GuiRadar*)GuiManager::Instance().GetGuiElement(TYPE::GUI::GUI_RADAR_ID);
//    const Vehicle& vehicle = *player->GetNpc()->GetVehicle();
//    gui_radar.ResetData();
    
//    for (unsigned int i=0; i<STAR_vec.size(); i++)        { gui_radar.Add(STAR_vec[i]); }
//    for (unsigned int i=0; i<PLANET_vec.size(); i++)      { gui_radar.Add(PLANET_vec[i]); }
//    for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)   { gui_radar.Add(BLACKHOLE_vec[i]); }

//    for (unsigned int i=0; i<ASTEROID_vec.size(); i++)    { gui_radar.AddIfWithinRadarRange(ASTEROID_vec[i], vehicle); }
//    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)     { gui_radar.AddIfWithinRadarRange(VEHICLE_vec[i], vehicle); }
}


//void StarSystem::DrawBackground(const jeti::Renderer& render, const glm::vec2& scroll_coords)
//{
//    for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)
//    {
//        distantNebulaEffect_vec[i]->Render(render, glm::vec3(1.0f));
//    }

//    for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)
//    {
//        DistantStarEffect& ds = *distantStarEffect_vec[i];
//        render.DrawParticles(ds.mesh(), ds.textureOb(), ds.actualModelMatrix());
//    }
//}

//void StarSystem::DrawOrbits(const jeti::Renderer& render)
//{
//    for(unsigned int i = 0; i < PLANET_vec.size(); i++)
//    {
//        PLANET_vec[i]->GetOrbit().DrawPath(render);
//    }

//    for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
//    {
//        ASTEROID_vec[i]->GetOrbit().DrawPath(render);
//    }
//}

//void StarSystem::DrawPath()
//{
//    for(unsigned int i=0; i<VEHICLE_vec.size(); i++)
//    {
//        //VEHICLE_vec[i]->GetDriveComplex()->DrawPath();
//    }
//}

void Starsystem::ShipManager_s(unsigned int num)
{
    while (m_vehicles.size() < num)
    {
        TYPE::RACE prace_id = TYPE::RACE::R0_ID;
        if (meti::getRandBool()) {
            prace_id = TYPE::RACE::R6_ID;
        }
        
        TYPE::ENTITY psubtype_id    = TYPE::ENTITY::WARRIOR_ID;
        TYPE::ENTITY psubsubtype_id = TYPE::ENTITY::WARRIOR_ID;
        int size_id     = SIZE_4_ID;
        int weapons_num = 7;

        Npc* new_pnpc = global::get().npcBuilder().create(prace_id, psubtype_id, psubsubtype_id);
        Ship* new_pship = ShipBuilder::getNew();
        ShipBuilder::equip(new_pship);   // improove

        new_pship->bindNpc(new_pnpc);

        glm::vec2 center = meti::getRandVec2f(100, 800);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,meti::getRandInt(0, 360));
        
        add(new_pship, center3, angle);
    }
}


void Starsystem::ManageUnavaliableObjects_s()
{               
    for (std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it)
    {
        if ((*it)->placeTypeId() != TYPE::PLACE::SPACE_ID)
        {
            LOG("starsysten("+std::to_string(id())+ ")::RemoveVehicle(" + std::to_string((*it)->id())+")");
            it = m_vehicles.erase(it);
        }
    }
}

void Starsystem::ManageDeadObjects_s()
{      
    for(std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it)
    {
        if ((*it)->isReadyForGarbage() == true)
        {
            global::get().entityManager().addToGarbage(*it);
            it = m_vehicles.erase(it);
        }
    }

    for(std::vector<BlackHole*>::iterator it=m_blackholes.begin(); it<m_blackholes.end(); ++it)
    {
        if ((*it)->isReadyForGarbage() == true)
        {
            global::get().entityManager().addToGarbage(*it);
            it = m_blackholes.erase(it);
        }
    }

    for(std::vector<Asteroid*>::iterator it=m_asteroids.begin(); it<m_asteroids.end(); ++it)
    {
        if ((*it)->isReadyForGarbage() == true)
        {
            global::get().entityManager().addToGarbage(*it);
            it = m_asteroids.erase(it);
        }
    }

    for(std::vector<Container*>::iterator it=m_containers.begin(); it<m_containers.end(); ++it)
    {
        if ((*it)->isReadyForGarbage() == true)
        {
            global::get().entityManager().addToGarbage(*it);
            it = m_containers.erase(it);
        }
    }

    for(std::vector<RocketBullet*>::iterator it=m_bullets.begin(); it<m_bullets.end(); ++it)
    {
        if ((*it)->isReadyForGarbage() == true)
        {
            global::get().entityManager().addToGarbage(*it);
            it = m_bullets.erase(it);
        }
    }

    //effects
//    for(std::vector<ShockWaveEffect*>::iterator it=effect_SHOCKWAVE_vec.begin(); it<effect_SHOCKWAVE_vec.end(); ++it)
//    {
//        if ((*it)->isAlive() == false)
//        {
//            garbage_effects.add(*it);
//            it = effect_SHOCKWAVE_vec.erase(it);
//        }
//    }

//    for(std::vector<LazerTraceEffect*>::iterator it=effect_LAZERTRACE_vec.begin(); it<effect_LAZERTRACE_vec.end(); ++it)
//    {
//        if ((*it)->isAlive() == false)
//        {
//            garbage_effects.add(*it);
//            it = effect_LAZERTRACE_vec.erase(it);
//        }
//    }

//    for(std::vector<jeti::BaseParticleSystem*>::iterator it=effect_PARTICLESYSTEM_vec.begin(); it<effect_PARTICLESYSTEM_vec.end(); ++it)
//    {
//        if ((*it)->isAlive() == false)
//        {
//            garbage_effects.add(*it);
//            it = effect_PARTICLESYSTEM_vec.erase(it);
//        }
//    }

//    for(std::vector<VerticalFlowText*>::iterator it=text_DAMAGE_vec.begin(); it<text_DAMAGE_vec.end(); ++it)
//    {
//        if ((*it)->isAlive() == false)
//        {
//            garbage_effects.add(*it);
//            it = text_DAMAGE_vec.erase(it);
//        }
//    }
}    


//void StarSystem::LaunchingEvent() const
//{
//for (unsigned int i=0; i<PLANET_vec.size(); i++)
//{
////PLANET_vec[i]->GetLand()->ManageLaunching();
//}
//}        

void Starsystem::bombExplosionEvent(Container* container, bool show_effect)
{
    float radius = ((Bomb*)container->itemSlot()->item())->radius();
    float damage = ((Bomb*)container->itemSlot()->item())->damage();
    glm::vec3 center(container->center());
    
    //jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(radius);
    //Add(explosion, center, radius, damage);
}

void Starsystem::starSparkEvent(float radius) const
{
    for (unsigned int i=0; i<m_vehicles.size(); i++) {
        if ( meti::distance(m_vehicles[i]->center(), star()->center()) < radius ) {
            if (m_vehicles[i]->radarSlot()->item() != nullptr) {
                m_vehicles[i]->radarSlot()->item()->doLock(2);
            }
        }
    }
}

void Starsystem::DamageEventInsideCircle(const glm::vec3& center, float radius, int damage, bool show_effect)
{
    for (unsigned int i=0; i<m_vehicles.size(); i++) {
        if ( meti::distance(m_vehicles[i]->center(), center) < radius ) {
            m_vehicles[i]->hit(damage);
        }
    }

    for (unsigned int i=0; i<m_containers.size(); i++) {
        float dist = meti::distance(m_containers[i]->center(), center);
        if (dist < radius) {
            glm::vec3 force_dir(m_containers[i]->center() - center);
            force_dir = glm::normalize(force_dir);
            float force_power = CONVERTER::RADIUS2FORCE.GetEquivalent(dist);
            std::cout<<dist<<" "<<force_power<<" "<<meti::str(force_dir)<<std::endl;

            m_containers[i]->addImpulse(force_dir, force_power);
        }
    }

}

bool Starsystem::isAnyActiveParticlesEffectPresent(int request_type_id) const
{
//    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++)
//    {
//        if (effect_PARTICLESYSTEM_vec[i]->typeId() == request_type_id)
//        {
//            return true;
//        }
//    }
    
    return false;
}


/*virtual */
void Starsystem::postDeathUniqueEvent(bool) 
{}

void Starsystem::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"sector_id", m_sector->id());
    
    save_ptree.put(root+"color.r", m_color.r);
    save_ptree.put(root+"color.g", m_color.g);
    save_ptree.put(root+"color.b", m_color.b);
    save_ptree.put(root+"color.a", m_color.a);

//    for (unsigned int i=0; i<distantStarEffect_vec.size(); i++)
//    {
//        distantStarEffect_vec[i]->Save(save_ptree, root);
//    }

//    for (unsigned int i = 0; i<distantNebulaEffect_vec.size(); i++)
//    {
//        distantNebulaEffect_vec[i]->Save(save_ptree, root);
//    }
}

void Starsystem::LoadData(const boost::property_tree::ptree& load_ptree)
{
    m_data_unresolved_StarSystem.sector_id = load_ptree.get<int>("sector_id");
    
    m_color.r = load_ptree.get<float>("color.r");
    m_color.g = load_ptree.get<float>("color.g");
    m_color.b = load_ptree.get<float>("color.b");
    m_color.a = load_ptree.get<float>("color.a");

    boost::property_tree::ptree tmp_ptree = load_ptree;
    if (tmp_ptree.get_child_optional("distant_nebula_effect"))
    {
        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_nebula_effect"))
        {
//            DistantNebulaEffect* dn = GetNewDistantNebulaEffect(NONE_ID);
//            dn->Load(v.second);
//            dn->Resolve();
//            Add(dn);
        }
    }
    
    if (tmp_ptree.get_child_optional("distant_star_effect"))
    {
        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_star_effect"))
        {
//            DistantStarEffect* ds = GetNewDistantStarEffect(NONE_ID);
//            ds->Load(v.second);
//            ds->Resolve();
//            Add(ds);
        }
    }
}

void Starsystem::ResolveData()
{
    ((Sector*)global::get().entityManager().get(m_data_unresolved_StarSystem.sector_id))->add(this, data_unresolved_Orientation.center);
}

void Starsystem::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "starsystem." + std::to_string(starsystem()->id())+".";

    Base::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Starsystem::SaveData(save_ptree, root);
}

void Starsystem::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Starsystem::LoadData(load_ptree);
}

void Starsystem::Resolve()
{
    Base::ResolveData();
    SpaceObject::ResolveData();
    Starsystem::ResolveData();
}        

