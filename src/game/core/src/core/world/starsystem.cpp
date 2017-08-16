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

//#include <client/effect/DistantNebulaEffect.hpp>
//#include <client/effect/DistantStarEffect.hpp>
//#include <client/effect/lazerTrace.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>

//#include <client/text/VerticalFlowText.hpp>

//#include <client/gui/GuiManager.hpp>
//#include <client/gui/GuiRadar.hpp>

#include <descriptor/comm/Creation.hpp>
#include <descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>
#include <core/communication/TelegrammManager.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

//#include <jeti/Mesh.hpp>
#include <meti/RandUtils.hpp>

//int Starsystem::m_counter = 0;


namespace control {

StarSystem::StarSystem(descriptor::StarSystem* descr, model::StarSystem* model)
    :
      Base(descr, model)
    , m_descriptor_starsystem(descr)
    , m_model_starsystem(model)
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
    model()->setWritable(false);


//    std::vector<int_t> planets() const { return m_planets; }

    for(int_t id: model()->stars()) {
        add(manager::Entities::get().star(id));
    }
    for(int_t id: model()->planets()) {
        add(manager::Entities::get().planet(id));
    }
    for(int_t id: model()->asteroids()) {
        add(manager::Entities::get().asteroid(id));
    }

    for(int_t id: model()->ships()) {
        add(manager::Entities::get().ship(id));
    }
    for(int_t id: model()->satellites()) {
        add(manager::Entities::get().satellite(id));
    }
    for(int_t id: model()->spacestations()) {
        add(manager::Entities::get().spacestation(id));
    }
    for(int_t id: model()->containers()) {
        add(manager::Entities::get().container(id));
    }

//    __actualizeItems();

    model()->setWritable(true);
}

Star*
StarSystem::star() const
{
    Star* star = nullptr;
    if (!m_stars.empty()) {
        star = m_stars.front();
    }
    return star;
}

/* virtual */
void StarSystem::putChildrenToGarbage() const
{    
    assert(false);
    //    for(unsigned int i=0; i<m_stars.size(); i++)      { manager::EntityManager::get().addToGarbage(m_stars[i]->model()); }
//    for(unsigned int i=0; i<m_planets.size(); i++)    { manager::EntityManager::get().addToGarbage(m_planets[i]->model()); }
//    for(unsigned int i=0; i<m_asteroids.size(); i++)  { manager::EntityManager::get().addToGarbage(m_asteroids[i]->model()); }
    //for(unsigned int i=0; i<m_bullets.size(); i++)    { manager::EntityManager::get().addToGarbage(m_bullets[i]); }
    //for(unsigned int i=0; i<m_containers.size(); i++) { manager::EntityManager::get().addToGarbage(m_containers[i]); }
    //for(unsigned int i=0; i<m_blackholes.size(); i++) { manager::EntityManager::get().addToGarbage(m_blackholes[i]); }
    //for(unsigned int i=0; i<m_vehicles.size(); i++)   { manager::EntityManager::get().addToGarbage(m_vehicles[i]); }
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
        if (_vehicle->id() == vehicle->id()) {
            LOG("StarSystem::AddVehicle dublicated vehicle found(fix that)" + vehicle->dataTypeStr());
            exit(1);
        }
    }

    vehicle->model()->setPlace(place::Type::SPACE);
    vehicle->setStarSystem(this);

    vehicle->setPosition(position);
    vehicle->setDirection(glm::vec3(0,1,0)/*dir*/);

    m_vehicles.push_back(vehicle);
}

void StarSystem::add(SpaceStation* spacestation, const glm::vec3& position, const glm::vec3& dir)
{
    __addVehicleCommon(spacestation, position, dir);
    model()->addSpaceStation(spacestation->id());
    m_spacestations.push_back(spacestation);
}

void StarSystem::add(Ship* ship, const glm::vec3& position, const glm::vec3& dir)
{
    __addVehicleCommon(ship, position, dir);
    model()->addShip(ship->id());
    m_ships.push_back(ship);
}

void StarSystem::add(Satellite* satellite, const glm::vec3& position, const glm::vec3& dir, const model::SpaceObject* const parent)
{
    __addVehicleCommon(satellite, position, dir);
    model()->addSatellite(satellite->id());
    m_satellites.push_back(satellite);
}

//void StarSystem::add(model::Bullet* _model, const glm::vec3& position, const glm::vec3& dir)
//{
//    _model->setPlace(place::Type::SPACE);
//    _model->setStarSystem(id());

//    _model->setPosition(position);
//    _model->setDirection(dir);
//    //rocket->updateOrientation();

//    assert(false);
//    descriptor::Bullet* _descr = nullptr;
//    Bullet* rocket = new Bullet(_model, _descr);
//    //rocket->initialize();

//    m_bullets.push_back(rocket);
//}

//void StarSystem::add(model::Star* model)
//{
//    Star* star = new Star(model);
//    add(star);
//}

void StarSystem::add(Star* star)
{
    star->setStarSystem(this);

    star->model()->setPlace(place::Type::SPACE);

    m_stars.push_back(star);
    model()->addStar(star->id());
}

//void StarSystem::add(model::Planet* model)
//{
//    Planet* planet = new Planet(model);
//    add(planet);
//}

void StarSystem::add(Planet* planet, SpaceObject* parent)
{
    if (!parent) {
        parent = star();
    }

    if (parent) {
        planet->setParent(parent);
    }
    planet->setStarSystem(this);

    planet->model()->setPlace(place::Type::SPACE);

    float offset_radius = 0;
    if (m_planets.size()) {
        offset_radius = m_planets.back()->model()->radiusA();
    }
    planet->calibrateOrbit(offset_radius);
    planet->initOrbit();

    m_planets.push_back(planet);
    model()->addPlanet(planet->id());
}


//void StarSystem::add(model::Asteroid* _model, const model::SpaceObject* parent, int it)
//{
//    //asteroid->bindParent(parent, it);
    
//    if (parent) {
//        _model->setParent(parent->id());
//    }
//    _model->setStarSystem(id());
//    _model->setPlace(place::Type::SPACE);

//    Asteroid* asteroid = new Asteroid(_model);

//    m_asteroids.push_back(asteroid);
//    model()->addAsteroid(_model->id());
//}

void StarSystem::add(Asteroid* asteroid, SpaceObject* parent, int it)
{
    if (!parent) {
        parent = star();
    }

    if (parent) {
        asteroid->setParent(parent);
    }
    asteroid->setStarSystem(this);

    asteroid->model()->setPlace(place::Type::SPACE);

    asteroid->calibrateOrbit();
    asteroid->initOrbit();

    m_asteroids.push_back(asteroid);
    model()->addAsteroid(asteroid->id());
}

//void StarSystem::add(model::Container* _model, const glm::vec3& center)
//{
//    //LOG(" StarSystem(" + std::to_string(id()) + ")::AddVehicle(" + std::to_string(container->id()) + ")");

//    for (auto _container: m_containers) {
//        if (_container->id() == _model->id()) {
//            //LOG("StarSystem::AddContainer dublicated container found(fix that)" + getBaseInfoStr(container));
//            exit(1);
//        }
//    }

//    _model->setStarSystem(id());
//    _model->setPlace(place::Type::SPACE);
//    _model->setPosition(center);

//    Container* container = new Container(_model);
//    model()->addContainer(_model->id());
//    m_containers.push_back(container);
//}

void StarSystem::add(Container* container, const glm::vec3& center)
{
    container->model()->setPosition(center);
    add(container);
}

void StarSystem::add(Container* container)
{
    container->setStarSystem(this);
    container->model()->setPlace(place::Type::SPACE);

    model()->addContainer(container->id());
    m_containers.push_back(container);
}

//void StarSystem::add(model::WormHole* _model, const glm::vec3& center)
//{
//    _model->setStarSystem(id());
//    _model->setPlace(place::Type::SPACE);
//    _model->setPosition(center);

//    WormHole* blackhole = new WormHole(_model);

//    m_wormholes.push_back(blackhole);

//    model()->addWormhole(_model->id());
//}

void StarSystem::add(WormHole* wormhole, const glm::vec3& center)
{
    wormhole->model()->setPosition(center);
    add(wormhole);
}

void StarSystem::add(WormHole* wormhole)
{
    wormhole->setStarSystem(this);
    wormhole->model()->setPlace(place::Type::SPACE);

    m_wormholes.push_back(wormhole);
    model()->addWormhole(wormhole->id());
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
    star->model()->setPlace(place::Type::NONE);
    model()->removeStar(star->id());
}

void
StarSystem::remove(Planet* planet)
{
    assert(planet);
    m_planets.remove(planet);
    planet->model()->setPlace(place::Type::NONE);
    model()->removePlanet(planet->id());
}

void
StarSystem::remove(WormHole* wormhole)
{
    assert(wormhole);
    m_wormholes.remove(wormhole);
    wormhole->model()->setPlace(place::Type::NONE);
    model()->removeWormHole(wormhole->id());
}

void
StarSystem::remove(Asteroid* asteroid)
{
    assert(asteroid);
    m_asteroids.remove(asteroid);
    asteroid->model()->setPlace(place::Type::NONE);
    model()->removeAsteroid(asteroid->id());
}

void
StarSystem::remove(Container* container)
{
    assert(container);
    m_containers.remove(container);
    container->model()->setPlace(place::Type::NONE);
    model()->removeContainer(container->id());
}

void
StarSystem::remove(SpaceStation* spacestation)
{
    assert(spacestation);
    m_spacestations.remove(spacestation);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->id() == spacestation->id()) {
            it = m_vehicles.erase(it);
        }
    }

    spacestation->model()->setPlace(place::Type::NONE);
    model()->removeSpaceStation(spacestation->id());
}

void
StarSystem::remove(Ship* ship)
{
    assert(ship);
    m_ships.remove(ship);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->id() == ship->id()) {
            it = m_vehicles.erase(it);
        }
    }

    ship->model()->setPlace(place::Type::NONE);
    model()->removeShip(ship->id());
}

void
StarSystem::remove(Satellite* satellite)
{
    assert(satellite);
    m_satellites.remove(satellite);

    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->id() == satellite->id()) {
            it = m_vehicles.erase(it);
        }
    }

    satellite->model()->setPlace(place::Type::NONE);
    model()->removeSatellite(satellite->id());
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

    for (const race::Type& race: races) {
        for (Vehicle* vehicle: m_vehicles) {
            if (race == vehicle->npc()->descriptor()->race()) {
                vehicles.push_back(vehicle);
            }
        }
    }
    
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

    core::comm::TelegrammManager& telegrammManager = core::global::get().telegrammManager();

    __updateEntities_s(time, detalied_simulation);
    __manageUnavaliableObjects_s();
    __manageDeadObjects();         // no need to update so frequently, pri /6

    if (time > 0) {
        telegrammManager.update();

        if (m_unique_update_inDymanic_done == false) {
            // assert(false); assert(false);
            //m_hyperspace.PostHyperJumpEvent(this);
            
            m_unique_update_inDymanic_done = true;
            m_unique_update_inStatic_done  = false;
        }

        // phisics
        __rocketCollision_s(detalied_simulation);   // pri/2
        __asteroidsCollision_s(); // pri/2
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
                    collide = ceti::checkCollision(m_bullets[ri], m_asteroids[ai]);
                    if (collide == true) { break; }
                }
            }
            else  { continue; }


            if (collide == false)
            {
                for (unsigned int ci = 0; ci < m_containers.size(); ci++)
                {
                    collide = ceti::checkCollision(m_bullets[ri], m_containers[ci]);
                    if (collide == true) {     break; }
                }
            }
            else  { continue; }
        }
    }
}

void StarSystem::__processAsteroidDeath_s(Asteroid* asteroid) const
{
    core::comm::TelegrammManager& telegrammManager = core::global::get().telegrammManager();
    manager::Entities& entitiesManager = manager::Entities::get();
    descriptor::Manager& descriptorManager = descriptor::Manager::get();
    //comm::TelegrammManager& telegrammManager = core::global::get().telegrammManager();

    // send message asteroid death
    {
    descriptor::comm::Object object(asteroid->id());
    telegrammManager.add(core::comm::Telegramm(core::comm::Telegramm::Type::REMOVE_ASTEROID, object.data()));
    }

    // create minerals
    int containers_num = meti::getRandInt(1,3);
    for (int i=0; i<containers_num; ++i) {
        int mass = meti::getRandInt(3, 100);
        int_t object_id = entitiesManager.genId();
        int_t descriptor_id = descriptorManager.randContainer()->id();
        descriptor::comm::Container creation(object_id, descriptor_id, mass);
        telegrammManager.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_MINERAL, creation.data()));

        float strength = meti::getRandFloat(1.0f, 2.0f);
        glm::vec3 impulse(meti::getRandXYVec3(strength));
        AddToStarsystemDescriptor telegramm_descriptor(id(), object_id, asteroid->position(), impulse, asteroid->direction());
        telegrammManager.add(core::comm::Telegramm(core::comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM, telegramm_descriptor.data()));
    }
    // send telegram to create explosion
}

void StarSystem::__asteroidsCollision_s() const {
    for(Asteroid* asteroid: m_asteroids) {
        if (__asteroidCollision_s(asteroid)) {
            __processAsteroidDeath_s(asteroid);
        }
    }
}


bool StarSystem::__asteroidCollision_s(Asteroid* asteroid) const
{
    if (!asteroid->isAlive()) {
        return false;
    }

    for (auto vehicle: m_vehicles) {
        if (ceti::checkCollision(asteroid, vehicle)) {
            return true;
        }
    }
    for (auto planet: m_planets) {
        if (ceti::checkCollision(asteroid, planet)) {
            return true;
        }
    }
    for (auto star: m_stars) {
        if (ceti::checkCollision(asteroid, star)) {
            return true;
        }
    }
    return false;
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
    for (auto star: m_stars) { star->updateInSpace(time, show_effect);  }
    for (auto planet: m_planets) { planet->updateInSpace(time, show_effect); }
    for (unsigned int i=0; i<m_wormholes.size(); i++)        { m_wormholes[i]->updateInSpace(time, show_effect); }
    for (Container* container: m_containers) { container->updateInSpace(time); }
    for (Asteroid* asteroid: m_asteroids) { asteroid->updateInSpace(time, show_effect); }
    
    for (Vehicle* vehicle: m_vehicles) { vehicle->update(time); }
    for (unsigned int i=0; i<m_bullets.size(); i++) { m_bullets[i]->UpdateInSpace(time, show_effect); }
    
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
        vehicle->npc()->updateInSpaceInStatic();
        if (vehicle->descriptor()->obGroup() == entity::Type::SPACESTATION) {
            static_cast<SpaceStation*>(vehicle)->land()->updateInStatic();
        }
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
        
        entity::Type pgroup    = entity::Type::WARRIOR;
        entity::Type psubgroup = entity::Type::WARRIOR;
        int size_id     = SIZE_4;
        int weapons_num = 7;

        // prace_id, pgroup, psubgroup
        control::Npc* new_npc = builder::Npc::gen();
        control::Ship* new_pship = builder::Ship::gen();

        builder::BaseVehicle::equip(new_pship);
        new_pship->bindNpc(new_npc);

        glm::vec2 center = meti::getRandVec2f(100, 800);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        //glm::vec3 angle(0,0,meti::getRandInt(360));
        
        add(new_pship, center3/*, angle*/);
    }
}


void StarSystem::__manageUnavaliableObjects_s()
{
    // old bad logic, use event system here
//    for (std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it) {
//        assert(false);
//        //        if ((*it)->place() != type::place::KOSMOS) {
//        //            LOG("starsysten("+std::to_string(id())+ ")::RemoveVehicle(" + std::to_string((*it)->id())+")");
//        //            it = m_vehicles.erase(it);
//        //        }
//    }
}

void StarSystem::__manageDeadObjects()
{      
    // bad approach, use event system here
//    for(std::vector<Vehicle*>::iterator it=m_vehicles.begin(); it<m_vehicles.end(); ++it) {
//        assert(false);
//        //        if ((*it)->isReadyForGarbage()) {
//        //           manager::EntityManager::get().addToGarbage(*it);
//        //            it = m_vehicles.erase(it);
//        //        }
//    }

//    for(std::vector<WormHole*>::iterator it=m_wormholes.begin(); it<m_wormholes.end(); ++it) {
//        assert(false);
////        if ((*it)->isReadyForGarbage()) {
////            manager::EntityManager::get().addToGarbage(*it);
////            it = m_blackholes.erase(it);
////        }
//    }


    // asteroid
//    std::vector<Asteroid*> to_remove;
//    for(Asteroid* asteroid: m_asteroids) {
//        if(!asteroid->isAlive()) {
//            //manager::Garbage::get().add(asteroid);
//            //to_remove.push_back(asteroid);
//        }
//    }

//    for(Asteroid* asteroid: to_remove) {
//        //remove(asteroid);
//    }
    //to_remove.clear();
    //


//    for(std::vector<Container*>::iterator it=m_containers.begin(); it<m_containers.end(); ++it) {
//        assert(false);
////        if ((*it)->isReadyForGarbage() == true) {
////            manager::EntityManager::get().addToGarbage(*it);
////            it = m_containers.erase(it);
////        }
//    }

//    for(std::vector<Bullet*>::iterator it=m_bullets.begin(); it<m_bullets.end(); ++it) {
////        if ((*it)->isReadyForGarbage() == true) {
////            manager::EntityManager::get().addToGarbage(*it);
////            it = m_bullets.erase(it);
////        }
//    }

//    //effects
//    //    for(std::vector<ShockWaveEffect*>::iterator it=effect_SHOCKWAVE_vec.begin(); it<effect_SHOCKWAVE_vec.end(); ++it)
//    //    {
//    //        if ((*it)->isAlive() == false)
//    //        {
//    //            garbage_effects.add(*it);
//    //            it = effect_SHOCKWAVE_vec.erase(it);
//    //        }
//    //    }

//    //    for(std::vector<LazerTraceEffect*>::iterator it=effect_LAZERTRACE_vec.begin(); it<effect_LAZERTRACE_vec.end(); ++it)
//    //    {
//    //        if ((*it)->isAlive() == false)
//    //        {
//    //            garbage_effects.add(*it);
//    //            it = effect_LAZERTRACE_vec.erase(it);
//    //        }
//    //    }

//    //    for(std::vector<jeti::BaseParticleSystem*>::iterator it=effect_PARTICLESYSTEM_vec.begin(); it<effect_PARTICLESYSTEM_vec.end(); ++it)
//    //    {
//    //        if ((*it)->isAlive() == false)
//    //        {
//    //            garbage_effects.add(*it);
//    //            it = effect_PARTICLESYSTEM_vec.erase(it);
//    //        }
//    //    }

//    //    for(std::vector<VerticalFlowText*>::iterator it=text_DAMAGE_vec.begin(); it<text_DAMAGE_vec.end(); ++it)
//    //    {
//    //        if ((*it)->isAlive() == false)
//    //        {
//    //            garbage_effects.add(*it);
//    //            it = text_DAMAGE_vec.erase(it);
//    //        }
//    //    }
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
//    //((Sector*)manager::EntityManager::get().get(m_data_unresolved_StarSystem.sector_id))->add(this, data_unresolved_Orientation.center);
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
