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

#include <core/builder/spaceobject/WormHoleBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/builder/pilot/NpcBuilder.hpp>

#include <ceti/Logger.hpp>
#include <ceti/Collision.hpp>
#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <common/Config.hpp>

//#include <jeti/Render.hpp>

#include <core/slot/ItemSlot.hpp>
#include <core/item/other/Bomb.hpp>

#include <core/spaceobject/ALL>

//#include <client/pilots/Player.hpp>
#include <core/pilot/Npc.hpp>

#include <core/model/spaceobject/ALL>
#include <core/model/world/starsystem.hpp>

//#include <client/effects/DistantNebulaEffect.hpp>
//#include <client/effects/DistantStarEffect.hpp>
//#include <client/effects/lazerTrace.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>

//#include <client/text/VerticalFlowText.hpp>

//#include <client/gui/GuiManager.hpp>
//#include <client/gui/GuiRadar.hpp>

#include <descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>

//#include <jeti/Mesh.hpp>
#include <meti/RandUtils.hpp>

//int Starsystem::m_counter = 0;


namespace control {

StarSystem::StarSystem(model::StarSystem* model)
    :
      Base(model)
    , m_model_starsystem(model)
    , m_descriptor_starsystem(descriptor::Manager::get().starSystem(model->descriptor()))
{
    __actualizeModel();
}

StarSystem::~StarSystem()
{    
    // effects
    //    for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)   { delete distantNebulaEffect_vec[i]; }
    //    for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)     { delete distantStarEffect_vec[i];   }
    //    for(unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)     { delete effect_LAZERTRACE_vec[i]; }
    //    for(unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { delete effect_PARTICLESYSTEM_vec[i]; }
    //    for(unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)      { delete effect_SHOCKWAVE_vec[i]; }
    //    for(unsigned int i=0; i<text_DAMAGE_vec.size(); i++)           { delete text_DAMAGE_vec[i]; }
}      

void
StarSystem::__actualizeModel()
{
    if (actualizeModel())
        return;

    model()->setWritable(false);


//    std::vector<int_t> planets() const { return m_planets; }

    for(int_t id: model()->stars()) {
        model::Star* _model = EntityManager::get().star(id);
        add(_model);
    }
    for(int_t id: model()->planets()) {
        model::Planet* _model = EntityManager::get().planet(id);
        add(_model);
    }
    for(int_t id: model()->asteroids()) {
        model::Asteroid* _model = EntityManager::get().asteroid(id);
        add(_model);
    }

    for(int_t id: model()->ships()) {
        model::Ship* _model = EntityManager::get().ship(id);
        add(_model);
    }
    for(int_t id: model()->satellites()) {
        model::Satellite* _model = EntityManager::get().satellite(id);
        add(_model);
    }
    for(int_t id: model()->spacestations()) {
        model::SpaceStation* _model = EntityManager::get().spacestation(id);
        add(_model);
    }
    for(int_t id: model()->containers()) {
        model::Container* _model = EntityManager::get().container(id);
        add(_model);
    }

//    __actualizeItems();

    model()->setWritable(true);
    setActualizeModel();
}

Star*
StarSystem::star() const
{
    assert(!m_stars.empty());
    return m_stars[0];
}

/* virtual */
void StarSystem::putChildrenToGarbage() const
{    
    for(unsigned int i=0; i<m_stars.size(); i++)      { EntityManager::get().addToGarbage(m_stars[i]->model()); }
    for(unsigned int i=0; i<m_planets.size(); i++)    { EntityManager::get().addToGarbage(m_planets[i]->model()); }
    for(unsigned int i=0; i<m_asteroids.size(); i++)  { EntityManager::get().addToGarbage(m_asteroids[i]->model()); }
    assert(false);
    //for(unsigned int i=0; i<m_bullets.size(); i++)    { EntityManager::get().addToGarbage(m_bullets[i]); }
    //for(unsigned int i=0; i<m_containers.size(); i++) { EntityManager::get().addToGarbage(m_containers[i]); }
    //for(unsigned int i=0; i<m_blackholes.size(); i++) { EntityManager::get().addToGarbage(m_blackholes[i]); }
    //for(unsigned int i=0; i<m_vehicles.size(); i++)   { EntityManager::get().addToGarbage(m_vehicles[i]); }
}      

model::Npc*
StarSystem::freeLeaderByRaceId(race::Type race_id) const
{
    std::vector<model::Npc*> npcs;
    for (Vehicle* vehicle: m_vehicles) {
        assert(false);
        //        if (vehicle->npc()->raceId() == race_id) {
        //            npcs.push_back(vehicle->npc());
        //        }
    }
    
    int leader_skill_max = 0;
    model::Npc* result = nullptr;
    for (model::Npc* npc: npcs) {
        int leader_skill = npc->skills().leader();
        if (leader_skill > leader_skill_max) {
            leader_skill_max = leader_skill;
            result = npc;
        }
    }
    
    return result;
}

void StarSystem::createGroupAndShareTask(model::Npc* npc_leader, StarSystem* target_starsystem, int num_max) const
{    
    std::vector<model::Npc*> npcs;
    for (Vehicle* vehicle: m_vehicles) {
        assert(false);
        //        if (vehicle->npc()->raceId() == npc_leader->raceId()) {
        //            npcs.push_back(vehicle->npc());
        //        }
    }
    
    int num = 0;
    for (model::Npc* npc: npcs) {
        if (num>num_max)
            break;

        assert(false);
        //        if (npc->vehicle()->isAbleToJumpTo(target_starsystem)) {
        //            npc->cloneMacroTaskFrom(npc_leader);
        //            num++;
        //        }
    }
}

void StarSystem::__addVehicleCommon(Vehicle* vehicle, const glm::vec3& position, const glm::vec3& dir)
{
    //LOG(" StarSystem(" + std::to_string(id()) + ")::__addVehicleCommon(" + std::to_string(vehicle->id())+")");

    for (Vehicle* _vehicle: m_vehicles) {
        if (_vehicle->model()->id() == vehicle->model()->id()) {
            LOG("StarSystem::AddVehicle dublicated vehicle found(fix that)" + vehicle->dataTypeStr());
            exit(1);
        }
    }

    vehicle->model()->setPlace(place::type::KOSMOS);
    vehicle->setStarSystem(model());

    vehicle->setPosition(position);
    vehicle->setDirection(dir);
    vehicle->updateOrientation(); // remove bad logic

    //    alpitodorender vehicle->SetColor(color);
    m_vehicles.push_back(vehicle);
}

void StarSystem::add(model::SpaceStation* _model)
{
    auto spacestation = new SpaceStation(_model);
    add(spacestation, _model->position(), _model->direction());
}

void StarSystem::add(SpaceStation* spacestation, const glm::vec3& position, const glm::vec3& dir)
{
    __addVehicleCommon(spacestation, position, dir);
    model()->addSpaceStation(spacestation->model()->id());
    m_spacestations.push_back(spacestation);
}

void StarSystem::add(model::Ship* _model)
{
    auto ship = new Ship(_model);
    add(ship, _model->position(), _model->direction());
}

void StarSystem::add(Ship* ship, const glm::vec3& position, const glm::vec3& dir)
{
    __addVehicleCommon(ship, position, dir);
    model()->addShip(ship->model()->id());
    m_ships.push_back(ship);
}

void StarSystem::add(model::Satellite* _model)
{
    auto satellite = new Satellite(_model);
    add(satellite, _model->position(), _model->direction());
}

void StarSystem::add(Satellite* satellite, const glm::vec3& position, const glm::vec3& dir, const model::SpaceObject* const parent)
{
    __addVehicleCommon(satellite, position, dir);
    assert(false);
    //satellite->BindParent(parent);
    model()->addSatellite(satellite->model()->id());
    m_satellites.push_back(satellite);
}

void StarSystem::add(model::RocketBullet* _model, const glm::vec3& position, const glm::vec3& dir)
{
    _model->setPlace(place::type::KOSMOS);
    _model->setStarSystem(model()->id());

    _model->setPosition(position);
    _model->setDirection(dir);
    //rocket->updateOrientation();

    assert(false);
    descriptor::RocketBullet* _descr = nullptr;
    RocketBullet* rocket = new RocketBullet(_model, _descr);
    //rocket->initialize();

    m_bullets.push_back(rocket);
}

void StarSystem::add(model::Star* model)
{
    Star* star = new Star(model);
    add(star);
}

void StarSystem::add(Star* star)
{
    star->model()->setStarSystem(model()->id());
    star->model()->setPlace(place::type::KOSMOS);

    star->initialize();
    m_stars.push_back(star);

    model()->addStar(star->model()->id());
}

void StarSystem::add(model::Planet* model)
{
    Planet* planet = new Planet(model);
    add(planet);
}

void StarSystem::add(Planet* planet, SpaceObject* parent)
{
    if (!parent) {
        parent = star();
    }

    planet->model()->setParent(parent->model()->id());
    planet->model()->setStarSystem(model()->id());
    planet->model()->setPlace(place::type::KOSMOS);

    planet->model()->setRadiusA(planet->model()->radiusA() * (m_planets.size() + 2));
    planet->model()->setRadiusB(planet->model()->radiusB() * (m_planets.size() + 2));

    planet->initialize();
    m_planets.push_back(planet);

    model()->addPlanet(planet->model()->id());
}


void StarSystem::add(model::Asteroid* _model, const model::SpaceObject* parent, int it)
{
    //asteroid->bindParent(parent, it);
    
    if (parent) {
        _model->setParent(parent->id());
    }
    _model->setStarSystem(model()->id());
    _model->setPlace(place::type::KOSMOS);

    Asteroid* asteroid = new Asteroid(_model);
    asteroid->initialize();
    m_asteroids.push_back(asteroid);
}

void StarSystem::add(model::Container* _model, const glm::vec3& center)
{
    //LOG(" StarSystem(" + std::to_string(id()) + ")::AddVehicle(" + std::to_string(container->id()) + ")");

    for (auto _container: m_containers) {
        if (_container->model()->id() == _model->id()) {
            //LOG("StarSystem::AddContainer dublicated container found(fix that)" + getBaseInfoStr(container));
            exit(1);
        }
    }

    _model->setStarSystem(model()->id());
    _model->setPlace(place::type::KOSMOS);
    _model->setPosition(center);

    Container* container = new Container(_model);

    m_containers.push_back(container);
}

void StarSystem::add(model::WormHole* _model, const glm::vec3& center)
{
    _model->setStarSystem(model()->id());
    _model->setPlace(place::type::KOSMOS);
    _model->setPosition(center);

    WormHole* blackhole = new WormHole(_model);
    blackhole->initialize();

    m_wormholes.push_back(blackhole);
}    

void StarSystem::add(Explosion* explosion, const glm::vec3& center)
{
    assert(false);
    //    for (Vehicle* vehicle: m_vehicles) {
    //        if (glm::length(vehicle->position() - center) < explosion->radius()) {
    //            vehicle->hit(explosion->damage());
    //        }
    //    }
}

void StarSystem::add(ShockWaveEffect* shockwave, const glm::vec2& center)
{ 
    //    shockwave->setCenter(center);
    //    effect_SHOCKWAVE_vec.push_back(shockwave);
}

void StarSystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center)
{ 
    //    float radius_damage = explosion->GetRadius();
    //    float damage = 0;
    //    Add(explosion, center, damage, radius_damage);
}

void StarSystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center, float damage, float radius_damage)
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


// remove
void
StarSystem::remove(Star* star)
{
    assert(star);
    m_stars.remove(star);
    model()->removeStar(star->model()->id());

    delete star;
}

void
StarSystem::remove(Planet* planet)
{
    assert(planet);
    m_planets.remove(planet);
    model()->removePlanet(planet->model()->id());

    delete planet;
}

void
StarSystem::remove(WormHole* wormhole)
{
    assert(wormhole);
    m_wormholes.remove(wormhole);
    model()->removeWormHole(wormhole->model()->id());

    delete wormhole;
}

void
StarSystem::remove(Asteroid* asteroid)
{
    assert(asteroid);
    m_asteroids.remove(asteroid);
    model()->removeAsteroid(asteroid->model()->id());

    delete asteroid;
}

void
StarSystem::remove(Container* container)
{
    assert(container);
    m_containers.remove(container);
    model()->removeContainer(container->model()->id());

    delete container;
}

void
StarSystem::remove(SpaceStation* spacestation)
{
    assert(spacestation);
    m_spacestations.remove(spacestation);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->model()->id() == spacestation->model()->id()) {
            it = m_vehicles.erase(it);
        }
    }

    model()->removeSpaceStation(spacestation->model()->id());

    delete spacestation;
}

void
StarSystem::remove(Ship* ship)
{
    assert(ship);
    m_ships.remove(ship);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->model()->id() == ship->model()->id()) {
            it = m_vehicles.erase(it);
        }
    }

    model()->removeShip(ship->model()->id());

    delete ship;
}

void
StarSystem::remove(Satellite* satellite)
{
    assert(satellite);
    m_satellites.remove(satellite);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->model()->id() == satellite->model()->id()) {
            it = m_vehicles.erase(it);
        }
    }

    model()->removeSatellite(satellite->model()->id());

    delete satellite;
}

//

// poor                
model::Planet*
StarSystem::closestInhabitedPlanet(const glm::vec2& _pos) const
{        
    Planet* requested_planet = nullptr;
    
    std::vector<Planet*> tmp_planet_vec;
    for(auto planet: m_planets) {
        if (planet->model()->population() > 0) {
            tmp_planet_vec.push_back(planet);
        }
    }
    
    if (tmp_planet_vec.size() >= 1) {
        requested_planet = tmp_planet_vec[0];
        float dist_min = meti::distance(_pos, tmp_planet_vec[0]->position());
        if (tmp_planet_vec.size() > 1) {
            for (unsigned int i=1; i<tmp_planet_vec.size(); i++) {
                float dist = meti::distance(_pos, tmp_planet_vec[i]->position());
                if (dist < dist_min) {
                    requested_planet = tmp_planet_vec[i];
                    dist_min = dist;
                }
            }
        }
    }
    
    return requested_planet->model();
}

model::Planet*
StarSystem::randomInhabitedPlanet() const
{
    Planet* requested_planet = nullptr;

    std::vector<Planet*> tmp_planet_vec;
    for(auto planet: m_planets) {
        if (planet->model()->population() > 0) {
            tmp_planet_vec.push_back(planet);
        }
    }
    
    if (tmp_planet_vec.size() >= 1)  {
        requested_planet = meti::getRand(tmp_planet_vec);
    }

    return requested_planet->model();
}

model::Planet*
StarSystem::randomPlanet() const
{
    return meti::getRand(m_planets)->model();
}

Vehicle*
StarSystem::randomVehicle() const
{
    return meti::getRand(m_vehicles);
}

Vehicle*
StarSystem::randomVehicleExcludingNpcRaceId(race::Type race_id) const
{
    std::vector<Vehicle*> vehicles;
    Vehicle* result = nullptr;
    assert(false);
    //    for (Vehicle* vehicle: m_vehicles) {
    //        if (vehicle->npc()) {
    //            if (vehicle->npc()->raceId() != race_id) {
    //                vehicles.push_back(vehicle);
    //            }
    //        }
    //    }
    
    if (vehicles.size()) {
        result = meti::getRand(vehicles);
    }
    
    return result;
}

Vehicle*
StarSystem::randVehicleByNpcRaceId(race::Type race_id) const
{
    std::vector<Vehicle*> vehicles;
    Vehicle* result = nullptr;

    assert(false);
    //    for (Vehicle* vehicle: m_vehicles) {
    //        if (vehicle->npc()) {
    //            if (vehicle->npc()->raceId() == race_id) {
    //                vehicles.push_back(vehicle);
    //            }
    //        }
    //    }
    
    if (vehicles.size()) {
        result = meti::getRand(vehicles);
    }
    
    return result;
}

Vehicle*
StarSystem::randomVehicle(const std::vector<race::Type>& races) const
{
    std::vector<Vehicle*> vehicles;
    Vehicle* result = nullptr;

    assert(false);
    //    for (const race::type& race: races) {
    //        for (Vehicle* vehicle: m_vehicles) {
    //            if (race == vehicle->npc()->raceId()) {
    //                vehicles.push_back(vehicle);
    //            }
    //        }
    //    }
    
    if (vehicles.size()) {
        result = meti::getRand(vehicles);
    }
    
    return result;
}


void StarSystem::__updateStates()
{
    if (m_containers.size() < 100) {
        m_asteroid_manager.update(this);
    }

    if (core::global::get().config().GetGameMode() == GAME_MODE::CRASH_TEST)
    {
        m_asteroid_manager.update(this);
        __shipManager_s(50);
        
        if (m_wormholes.size() < 5) {
            glm::vec2 center = meti::getRandVec2f(200, 1200);
            
            glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
            add(core::global::get().blackHoleBuilder().gen(), center3);
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
    
    Vehicle* _vehicle_evil = randomVehicle(core::global::get().raceDescriptors().getRaces(race::KIND::EVIL));
    if (_vehicle_evil) {
        enemy_is_here = true;
    }

    Vehicle* _vehicle_good = randomVehicle(core::global::get().raceDescriptors().getRaces(race::KIND::GOOD));
    if (_vehicle_good) {
        friendly_is_here = true;
    }
    
    switch(m_condition_id)
    {
    case ENTITY::STARSYSTEM::CONDITION::SAFE:
    {
        if (enemy_is_here == true)
        {
            if (friendly_is_here == true)
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR;
            }
            else
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED;
                if (randVehicleByNpcRaceId(race::Type::R6) != nullptr)
                {
                    m_conqueror_race_id = race::Type::R6;
                }

                if (randVehicleByNpcRaceId(race::Type::R7) != nullptr)
                {
                    m_conqueror_race_id = race::Type::R7;
                }
            }
        }

        break;
    }

    case ENTITY::STARSYSTEM::CONDITION::CAPTURED:
    {
        if (friendly_is_here == true)
        {
            if (enemy_is_here == true)
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR;
            }
            else
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE;
                m_conqueror_race_id = race::Type::NONE;
            }
        }

        break;
    }

    case ENTITY::STARSYSTEM::CONDITION::WAR:
    {
        if (friendly_is_here == true)
        {
            if (enemy_is_here == false)
            {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE;
            }
        }
        else
        {
            m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED;
        }

        break;
    }
    }
}

float StarSystem::calcResultGravityForce(const glm::vec3& center, const glm::vec3& orient, float mass) const
{
    float rate = 1;
    for (unsigned int i=0; i<m_stars.size(); i++)
    {
        float dist = meti::distance(center, m_stars[i]->position());
        if (dist < 5*m_stars[i]->collisionRadius())
        {
            glm::vec3 force_dir(m_stars[i]->position() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = meti::dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);

            rate += power1*power2;
        }
    }

    for (unsigned int i=0; i<m_planets.size(); i++)
    {
        float dist = meti::distance(center, m_planets[i]->position());
        if (dist < 5*m_planets[i]->collisionRadius())
        {
            glm::vec3 force_dir(m_planets[i]->position() - center);
            force_dir = glm::normalize(force_dir);
            float power1 = meti::dotUnits(force_dir, orient);
            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);
            
            rate += power1*power2;
        }
    }
    
    return rate;
}


void StarSystem::update(int time)
{                
    bool detalied_simulation = true;

    __updateEntities_s(time, detalied_simulation);
    __manageUnavaliableObjects_s();
    __manageDeadObjects_s();         // no need to update so frequently, pri /6

    if (time > 0) {
        if (m_unique_update_inDymanic_done == false) {
            assert(false);
            //m_hyperspace.PostHyperJumpEvent(this);
            
            m_unique_update_inDymanic_done = true;
            m_unique_update_inStatic_done  = false;
        }

        // phisics
        __rocketCollision_s(detalied_simulation);   // pri/2
        __asteroidCollision_s(detalied_simulation); // pri/2
        __externalForcesAffection_s(detalied_simulation); // pri/2
        //phisics
        
        if (m_containers.size() > m_container_num_max) {
            unsigned int index = meti::getRandInt(m_container_num_max-1);
            m_containers[index]->hit(100);
        }
    } else {
        if (!m_unique_update_inStatic_done) {
            __updateInSpaceInStatic_s();
            
            m_unique_update_inDymanic_done = false;
            m_unique_update_inStatic_done  = true;
        }
    }
}

void StarSystem::__rocketCollision_s(bool show_effect)
{
    bool collide = false;
    for (unsigned int ri = 0; ri < m_bullets.size(); ri++)
    {
        if (m_bullets[ri]->model()->isAlive())
        {
            // vehicle
            if (collide == false)
            {
                for (unsigned int vi = 0; vi < m_vehicles.size(); vi++)
                {
                    assert(false);
                    //                    if (m_bullets[ri]->GetOwnerId() != m_vehicles[vi]->id())
                    //                    {
                    //                        collide = ceti::checkCollision2D(m_bullets[ri], m_vehicles[vi], show_effect);
                    //                        if (collide == true) { break; }
                    //                    }
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






void StarSystem::__asteroidCollision_s(bool show_effect)
{
    bool collide = false;
    for(auto asteroid: m_asteroids) {
        if (asteroid->model()->isAlive()) {
            if (!collide) {
                for (auto vehicle: m_vehicles) {
                    collide = ceti::checkCollision2D(asteroid, vehicle, show_effect);
                    if (collide) {
                        break;
                    }
                }
            } else {
                continue;
            }

            if (!collide) {
                for (auto planet: m_planets) {
                    collide = ceti::checkCollision2D(asteroid, planet, show_effect);
                    if (collide) {
                        break;
                    }
                }
            } else {
                continue;
            }

            if (!collide) {
                for (auto star: m_stars) {
                    collide = ceti::checkCollision2D(asteroid, star, show_effect);
                    if (collide) {
                        break;
                    }
                }
            } else {
                continue;
            }
        }
    }
}

void StarSystem::__externalForcesAffection_s(bool detalied_simulation)
{
    //for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
    //{

    //}
    
    //for (unsigned int si = 0; si < STAR_vec.size(); si++)
    //{

    //}

}

void StarSystem::__updateEntities_s(int time, bool show_effect)
{
    loadEntitiesResource(); // hack for speed run

    for (auto star: m_stars) { star->updateInSpace(time, show_effect);  }
    for (auto planet: m_planets) { planet->updateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_wormholes.size(); i++)        { m_wormholes[i]->updateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_containers.size(); i++)        { m_containers[i]->updateInSpace(time, show_effect); }
    for (auto asteroid: m_asteroids) { asteroid->updateInSpace(time, show_effect); }
    
    assert(false);
    //for (unsigned int i=0; i<m_vehicles.size(); i++)          { m_vehicles[i]->UpdateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_bullets.size(); i++)           { m_bullets[i]->UpdateInSpace(time, show_effect); }
    
    // effects
    //    for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)      { effect_LAZERTRACE_vec[i]->Update(); }
    //    for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { effect_PARTICLESYSTEM_vec[i]->Update(); }
    //    for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)     { effect_SHOCKWAVE_vec[i]->Update(); }
    //    for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)         { text_DAMAGE_vec[i]->Update(); }
    //    for (unsigned int i=0; i<distantNebulaEffect_vec.size(); i++) { distantNebulaEffect_vec[i]->Update(); }
}

void StarSystem::loadEntitiesResource()
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

void StarSystem::__updateInSpaceInStatic_s()
{
    __updateStates();

    for (Vehicle* vehicle: m_vehicles) {
        assert(false);
        //        vehicle->npc()->updateInSpaceInStatic();
        //        if (vehicle->subtype() == entity::Type::SPACESTATION) {
        //            static_cast<SpaceStation*>(vehicle)->land()->UpdateInStatic();
        //        }
    }

    for (auto star: m_stars) { star->updateInSpaceInStatic(); }
    for (auto planet: m_planets) { planet->updateInSpaceInStatic(); }

    //garbage_effects.clear();
}      

void StarSystem::findRenderVisibleEntities_c(Player* player)
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

void StarSystem::findRadarVisibleEntities_c(Player* player)
{    
    //    GuiRadar& gui_radar = *(GuiRadar*)GuiManager::Instance().GetGuiElement(gui::type::GUI_RADAR);
    //    const Vehicle& vehicle = *player->GetNpc()->vehicle();
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

void StarSystem::__shipManager_s(unsigned int num)
{
    while (m_vehicles.size() < num)
    {
        race::Type prace_id = race::Type::R0;
        if (meti::getRandBool()) {
            prace_id = race::Type::R6;
        }
        
        entity::Type psubtype_id    = entity::Type::WARRIOR;
        entity::Type psubsubtype_id = entity::Type::WARRIOR;
        int size_id     = SIZE_4;
        int weapons_num = 7;

        model::Npc* new_pnpc = core::global::get().npcBuilder().create(prace_id, psubtype_id, psubsubtype_id);
        model::Ship* new_pship = builder::Ship::gen();

        assert(false);
        //builder::ShipBuilder::equip(new_pship);   // improove
        assert(false);
        //new_pship->bindNpc(new_pnpc);

        glm::vec2 center = meti::getRandVec2f(100, 800);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,meti::getRandInt(360));
        
        assert(false);
        //add(new_pship, center3, angle);
    }
}


void StarSystem::__manageUnavaliableObjects_s()
{               
    for (std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it) {
        assert(false);
        //        if ((*it)->place() != type::place::KOSMOS) {
        //            LOG("starsysten("+std::to_string(id())+ ")::RemoveVehicle(" + std::to_string((*it)->id())+")");
        //            it = m_vehicles.erase(it);
        //        }
    }
}

void StarSystem::__manageDeadObjects_s()
{      
    for(std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it) {
        assert(false);
        //        if ((*it)->isReadyForGarbage()) {
        //           EntityManager::get().addToGarbage(*it);
        //            it = m_vehicles.erase(it);
        //        }
    }

    for(std::vector<WormHole*>::iterator it=m_wormholes.begin(); it<m_wormholes.end(); ++it) {
        assert(false);
//        if ((*it)->isReadyForGarbage()) {
//            EntityManager::get().addToGarbage(*it);
//            it = m_blackholes.erase(it);
//        }
    }

    //    for(std::vector<Asteroid*>::iterator it=m_asteroids.begin(); it<m_asteroids.end(); ++it) {
    //        if ((*it)->isReadyForGarbage() == true) {
    //           EntityManager::get().addToGarbage(*it);
    //            it = m_asteroids.erase(it);
    //        }
    //    }

    for(std::vector<Container*>::iterator it=m_containers.begin(); it<m_containers.end(); ++it) {
        assert(false);
//        if ((*it)->isReadyForGarbage() == true) {
//            EntityManager::get().addToGarbage(*it);
//            it = m_containers.erase(it);
//        }
    }

    for(std::vector<RocketBullet*>::iterator it=m_bullets.begin(); it<m_bullets.end(); ++it) {
//        if ((*it)->isReadyForGarbage() == true) {
//            EntityManager::get().addToGarbage(*it);
//            it = m_bullets.erase(it);
//        }
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

void StarSystem::bombExplosionEvent(Container* container, bool show_effect)
{
    assert(false);
//    float radius = container->itemSlot()->item()->radius();
//    float damage = container->itemSlot()->item()->damage();
    glm::vec3 center(container->position());
    
    //jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(radius);
    //Add(explosion, center, radius, damage);
}

void StarSystem::starSparkEvent(float radius) const
{
    for (unsigned int i=0; i<m_vehicles.size(); i++) {
        assert(false);
        //        if ( meti::distance(m_vehicles[i]->position(), star()->position()) < radius ) {
        //            if (m_vehicles[i]->radarSlot()->item() != nullptr) {
        //                m_vehicles[i]->radarSlot()->item()->doLock(2);
        //            }
        //        }
    }
}

void StarSystem::__damageEventInsideCircle(const glm::vec3& position, float radius, int damage, bool show_effect)
{
    for (unsigned int i=0; i<m_vehicles.size(); i++) {
        assert(false);
        //        if ( meti::distance(m_vehicles[i]->position(), position) < radius ) {
        //            m_vehicles[i]->hit(damage);
        //        }
    }

    for (unsigned int i=0; i<m_containers.size(); i++) {
        float dist = meti::distance(m_containers[i]->position(), position);
        if (dist < radius) {
            glm::vec3 force_dir(m_containers[i]->position() - position);
            force_dir = glm::normalize(force_dir);
            float force_power = CONVERTER::RADIUS2FORCE.GetEquivalent(dist);
            std::cout<<dist<<" "<<force_power<<" "<<meti::str(force_dir)<<std::endl;

            m_containers[i]->addImpulse(force_dir, force_power);
        }
    }

}

bool StarSystem::isAnyActiveParticlesEffectPresent(int request_type_id) const
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
void StarSystem::_postDeathUniqueEvent(bool)
{}

//void Starsystem::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    save_ptree.put(root+"sector_id", m_sector->id());
    
//    save_ptree.put(root+"color.r", m_color.r);
//    save_ptree.put(root+"color.g", m_color.g);
//    save_ptree.put(root+"color.b", m_color.b);
//    save_ptree.put(root+"color.a", m_color.a);

//    //    for (unsigned int i=0; i<distantStarEffect_vec.size(); i++)
//    //    {
//    //        distantStarEffect_vec[i]->Save(save_ptree, root);
//    //    }

//    //    for (unsigned int i = 0; i<distantNebulaEffect_vec.size(); i++)
//    //    {
//    //        distantNebulaEffect_vec[i]->Save(save_ptree, root);
//    //    }
//}

//void Starsystem::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    m_data_unresolved_StarSystem.sector_id = load_ptree.get<int>("sector_id");
    
//    m_color.r = load_ptree.get<float>("color.r");
//    m_color.g = load_ptree.get<float>("color.g");
//    m_color.b = load_ptree.get<float>("color.b");
//    m_color.a = load_ptree.get<float>("color.a");

//    boost::property_tree::ptree tmp_ptree = load_ptree;
//    if (tmp_ptree.get_child_optional("distant_nebula_effect"))
//    {
//        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_nebula_effect"))
//        {
//            //            DistantNebulaEffect* dn = GetNewDistantNebulaEffect(NONE);
//            //            dn->Load(v.second);
//            //            dn->Resolve();
//            //            Add(dn);
//        }
//    }
    
//    if (tmp_ptree.get_child_optional("distant_star_effect"))
//    {
//        for (boost::property_tree::ptree::value_type &v : tmp_ptree.get_child("distant_star_effect"))
//        {
//            //            DistantStarEffect* ds = GetNewDistantStarEffect(NONE);
//            //            ds->Load(v.second);
//            //            ds->Resolve();
//            //            Add(ds);
//        }
//    }
//}

//void Starsystem::ResolveData()
//{
//    //((Sector*)EntityManager::get().get(m_data_unresolved_StarSystem.sector_id))->add(this, data_unresolved_Orientation.center);
//}

//void Starsystem::Save(boost::property_tree::ptree& save_ptree) const
//{
//    const std::string root = "starsystem." + std::to_string(starsystem()->id())+".";

//    Base::SaveData(save_ptree, root);
//    SpaceObject::SaveData(save_ptree, root);
//    Starsystem::SaveData(save_ptree, root);
//}

//void Starsystem::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//    SpaceObject::LoadData(load_ptree);
//    Starsystem::LoadData(load_ptree);
//}

//void Starsystem::Resolve()
//{
//    Base::ResolveData();
//    SpaceObject::ResolveData();
//    Starsystem::ResolveData();
//}

} // namespace control
