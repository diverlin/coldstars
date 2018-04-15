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


#include <core/world/starsystem.hpp>
#include <core/world/Sector.hpp>

#include <core/builder/spaceobject/WormHoleBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/builder/pilot/NpcBuilder.hpp>

#include <core/math/rand.hpp>

#include <core/common/Global.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <common/Config.hpp>


#include <core/slot/ItemSlot.hpp>
#include <core/item/other/Bomb.hpp>

#include <core/spaceobject/ALL>

#include <core/pilot/Npc.hpp>

#include <core/model/spaceobject/ALL>
#include <core/model/world/starsystem.hpp>

#include <core/descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>
#include <core/communication/TelegramCreator.hpp>
#include <core/communication/TelegramHandler.hpp>

#include <ceti/Logger.hpp>
#include <ceti/Collision.hpp>

#include <meti/VectorUtils.hpp>
#include <meti/RandUtils.hpp>

#include <algorithm> // std::min

namespace {
core::TelegramCreator& composer() { return core::TelegramCreator::get(); }
} // namespace

namespace core {
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
}      

const glm::vec3& StarSystem::position() const { return model()->position(); }

void
StarSystem::__actualizeModel()
{
    model()->setWritable(false);

    for(int_t id: model()->stars()) {
        add(core::shortcuts::entities()->star(id));
    }
    for(int_t id: model()->planets()) {
        add(core::shortcuts::entities()->planet(id));
    }
    for(int_t id: model()->asteroids()) {
        add(core::shortcuts::entities()->asteroid(id));
    }
    for(int_t id: model()->wormholes()) {
        __add(core::shortcuts::entities()->wormhole(id));
    }

    for(int_t id: model()->ships()) {
        add(core::shortcuts::entities()->ship(id));
    }
    for(int_t id: model()->satellites()) {
        add(core::shortcuts::entities()->satellite(id));
    }
    for(int_t id: model()->spacestations()) {
        add(core::shortcuts::entities()->spacestation(id));
    }
    for(int_t id: model()->containers()) {
        __add(core::shortcuts::entities()->container(id));
    }
    for(int_t id: model()->bullets()) {
        __add(core::shortcuts::entities()->bullet(id));
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

void StarSystem::__addVehicleCommon(Vehicle* vehicle, const glm::vec3& position, const glm::vec3& direction)
{
    for (Vehicle* _vehicle: m_vehicles) {
        if (_vehicle->id() == vehicle->id()) {
            //LOG("StarSystem::AddVehicle dublicated vehicle found(fix that)" + vehicle->dataTypeStr());
            exit(1);
        }
    }

    vehicle->setPlace(place::Type::SPACE);
    vehicle->setStarSystem(this);

    vehicle->setPosition(position);
    vehicle->setDirection(direction);

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

void StarSystem::add(Satellite* satellite, const glm::vec3& position, const glm::vec3& direction, const model::SpaceObject* const parent)
{
    __addVehicleCommon(satellite, position, direction);
    model()->addSatellite(satellite->id());
    m_satellites.push_back(satellite);
}

void StarSystem::add(Bullet* bullet, const glm::vec3& position, const glm::vec3& direction)
{
    bullet->setPosition(position);
    bullet->setDirection(direction);

    __add(bullet);
}

void StarSystem::__add(Bullet* bullet)
{
    bullet->setStarSystem(this);

    bullet->setPlace(place::Type::SPACE);

    m_bullets.push_back(bullet);
    model()->addStar(bullet->id());
}

void StarSystem::add(Star* star)
{
    star->setStarSystem(this);

    star->setPlace(place::Type::SPACE);

    m_stars.push_back(star);
    model()->addStar(star->id());
}

void StarSystem::add(Planet* planet, SpaceObject* parent)
{
    if (!parent) {
        parent = star();
    }

    if (parent) {
        planet->setParent(parent);
    }
    planet->setStarSystem(this);

    planet->setPlace(place::Type::SPACE);

    float offset_radius = 0;
    if (m_planets.size()) {
        offset_radius = m_planets.back()->model()->radiusA();
    }
    planet->calibrateOrbit(offset_radius);
    planet->initOrbit();

    m_planets.push_back(planet);
    model()->addPlanet(planet->id());
}

void StarSystem::add(Asteroid* asteroid, SpaceObject* parent, int it)
{
    if (!parent) {
        parent = star();
    }

    if (parent) {
        asteroid->setParent(parent);
    }
    asteroid->setStarSystem(this);

    asteroid->setPlace(place::Type::SPACE);

    asteroid->calibrateOrbit();
    asteroid->initOrbit();

    m_asteroids.push_back(asteroid);
    model()->addAsteroid(asteroid->id());
}

void StarSystem::__add(Container* container)
{
    container->setStarSystem(this);
    container->setPlace(place::Type::SPACE);

    model()->addContainer(container->id());
    m_containers.push_back(container);
}

void StarSystem::add(Container* container, const glm::vec3& center)
{
    container->setPosition(center);
    __add(container);
}

void StarSystem::__add(WormHole* wormhole)
{
    wormhole->setStarSystem(this);
    wormhole->setPlace(place::Type::SPACE);

    m_wormholes.push_back(wormhole);
    model()->addWormhole(wormhole->id());
}

void StarSystem::add(WormHole* wormhole, const glm::vec3& center)
{
    wormhole->model()->setPosition(center);
    __add(wormhole);
}

// remove

void
StarSystem::remove(SpaceObject* object)
{
    assert(object);
    switch(object->type()) {
    case entity::Type::STAR: __remove(static_cast<Star*>(object)); break;
    case entity::Type::PLANET: __remove(static_cast<Planet*>(object)); break;
    case entity::Type::ASTEROID: __remove(static_cast<Asteroid*>(object)); break;
    case entity::Type::WORMHOLE: __remove(static_cast<WormHole*>(object)); break;
    case entity::Type::CONTAINER: __remove(static_cast<Container*>(object)); break;
    case entity::Type::BULLET: __remove(static_cast<Bullet*>(object)); break;
    case entity::Type::SHIP: __remove(static_cast<Ship*>(object)); break;
    case entity::Type::SATELLITE: __remove(static_cast<Satellite*>(object)); break;
    case entity::Type::SPACESTATION: __remove(static_cast<SpaceStation*>(object)); break;
    default: assert(false);
    }
}


void
StarSystem::__remove(Star* star)
{
    assert(star);
    m_stars.remove(star);
    star->setPlace(place::Type::NONE);
    model()->removeStar(star->id());
}

void
StarSystem::__remove(Planet* planet)
{
    assert(planet);
    m_planets.remove(planet);
    planet->setPlace(place::Type::NONE);
    model()->removePlanet(planet->id());
}

void
StarSystem::__remove(WormHole* wormhole)
{
    assert(wormhole);
    m_wormholes.remove(wormhole);
    wormhole->setPlace(place::Type::NONE);
    model()->removeWormHole(wormhole->id());
}

void
StarSystem::__remove(Asteroid* asteroid)
{
    assert(asteroid);
    m_asteroids.remove(asteroid);
    asteroid->setPlace(place::Type::NONE);
    model()->removeAsteroid(asteroid->id());
}

void
StarSystem::__remove(Container* container)
{
    assert(container);
    m_containers.remove(container);
    container->setPlace(place::Type::NONE);
    model()->removeContainer(container->id());
}

void
StarSystem::__remove(Bullet* bullet)
{
    assert(bullet);
    m_bullets.remove(bullet);
    bullet->setPlace(place::Type::NONE);
    model()->removeContainer(bullet->id());
}

void
StarSystem::__remove(SpaceStation* spacestation)
{
    assert(spacestation);
    m_spacestations.remove(spacestation);

    __removeVehicle(spacestation->id());

    spacestation->setPlace(place::Type::NONE);
    model()->removeSpaceStation(spacestation->id());
}

void
StarSystem::__remove(Ship* ship)
{
    assert(ship);
    m_ships.remove(ship);

    __removeVehicle(ship->id());

    ship->setPlace(place::Type::NONE);
    model()->removeShip(ship->id());
}

void
StarSystem::__remove(Satellite* satellite)
{
    assert(satellite);
    m_satellites.remove(satellite);

    __removeVehicle(satellite->id());

    satellite->setPlace(place::Type::NONE);
    model()->removeSatellite(satellite->id());
}

void StarSystem::__removeVehicle(int_t id) {
    for(std::vector<Vehicle*>::iterator it = m_vehicles.begin(); it < m_vehicles.end(); ++it) {
        if ((*it)->id() == id) {
            it = m_vehicles.erase(it);
        }
    }
}

//


void StarSystem::explosionEvent(const glm::vec3& epicenter, int damage, float radius) const
{
    assert(false);
    //    for (Vehicle* vehicle: m_vehicles) {
    //        if (glm::length(vehicle->position() - center) < radius) {
    //            vehicle->hit(damage);
    //        }
    //    }
}


// poor                
Planet*
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
    
    return requested_planet;
}

Planet*
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
        requested_planet = meti::rand::get_element_or_die(tmp_planet_vec);
    }

    return requested_planet;
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
        result = meti::rand::get_element_or_die(vehicles);
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
        result = meti::rand::get_element_or_die(vehicles);
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
        result = meti::rand::get_element_or_die(vehicles);
    }
    
    return result;
}


void StarSystem::__updateStates()
{
//    if (m_containers.size() < 100) {
//        m_asteroid_manager.update(this);
//    }

    if (core::global::get().config().GetGameMode() == GAME_MODE::CRASH_TEST)
    {
        m_asteroid_manager.update(this);
        __shipManager_s(50);
        
        if (m_wormholes.size() < 5) {
            glm::vec2 center = meti::rand::gen_vec2(200, 1200);
            
            glm::vec3 center3(center.x, center.y, 0.0f);
            //add(core::global::get().blackHoleBuilder().gen(), center3);
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
        if (enemy_is_here) {
            if (friendly_is_here) {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR;
            } else {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED;
                if (randVehicleByNpcRaceId(race::Type::R6)) {
                    m_conqueror_race_id = race::Type::R6;
                }
                if (randVehicleByNpcRaceId(race::Type::R7)) {
                    m_conqueror_race_id = race::Type::R7;
                }
            }
        }
        break;
    }

    case ENTITY::STARSYSTEM::CONDITION::CAPTURED:
    {
        if (friendly_is_here) {
            if (enemy_is_here) {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::WAR;
            } else {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE;
                m_conqueror_race_id = race::Type::NONE;
            }
        }
        break;
    }

    case ENTITY::STARSYSTEM::CONDITION::WAR:
    {
        if (friendly_is_here) {
            if (!enemy_is_here) {
                m_condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE;
            }
        } else {
            m_condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED;
        }
        break;
    }
    }
}

//float StarSystem::calcResultGravityForce(const glm::vec3& center, const glm::vec3& orient, float mass) const
//{
//    float rate = 1;
//    for (unsigned int i=0; i<m_stars.size(); i++)
//    {
//        float dist = meti::distance(center, m_stars[i]->position());
//        if (dist < 5*m_stars[i]->collisionRadius())
//        {
//            glm::vec3 force_dir(m_stars[i]->position() - center);
//            force_dir = glm::normalize(force_dir);
//            float power1 = meti::dotUnits(force_dir, orient);
//            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);

//            rate += power1*power2;
//        }
//    }

//    for (unsigned int i=0; i<m_planets.size(); i++)
//    {
//        float dist = meti::distance(center, m_planets[i]->position());
//        if (dist < 5*m_planets[i]->collisionRadius())
//        {
//            glm::vec3 force_dir(m_planets[i]->position() - center);
//            force_dir = glm::normalize(force_dir);
//            float power1 = meti::dotUnits(force_dir, orient);
//            float power2 = CONVERTER::DIST2GRAVITY.GetEquivalent(dist);
            
//            rate += power1*power2;
//        }
//    }
    
//    return rate;
//}

void StarSystem::update_client(int time)
{
    __updateEntities_s(time);
}

void StarSystem::update_server(int time)
{                
    __updateEntities_s(time);
    __manageUnavaliableObjects_s();

    if (meti::rand::gen_probability(/*percent*/100)) {
        __manageDeadObjects();
    }

    if (time > 0) {
        //composer().genBullets_DEBUG(this, 100);

        if (m_unique_update_inDymanic_done == false) {
            // assert(false); assert(false);
            //m_hyperspace.PostHyperJumpEvent(this);
            
            m_unique_update_inDymanic_done = true;
            m_unique_update_inStatic_done  = false;
        }

        // phisics
        if (meti::rand::gen_probability(/*percent*/33)) {
            __bulletsCollisionCheck_s();    // pri/2
            __asteroidsCollisionCheck_s(); // pri/2
        }
        //phisics
        
        if (m_containers.size() > m_container_num_max) {
            unsigned int index = meti::rand::gen_int(m_container_num_max-1);
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

void StarSystem::__bulletsCollisionCheck_s() const {
    for(Bullet* bullet: m_bullets) {
        __bulletCollisionCheck_s(bullet);
    }
}

void StarSystem::__asteroidsCollisionCheck_s() const {
    for(Asteroid* asteroid: m_asteroids) {
        __asteroidCollisionCheck_s(asteroid);
    }
}

void StarSystem::__bulletCollisionCheck_s(Bullet* bullet) const
{
    if (!bullet->isAlive() || !bullet->collideable()) {
        return;
    }

    for (auto v: m_vehicles) {
        if (bullet->ownerId() != v->id()) {
            if (ceti::checkCollision(bullet, v)) {
                composer().death(bullet);
                composer().hit(v, bullet->damage());
                return;
            }
        }
    }
    for (auto a: m_asteroids) {
        if (ceti::checkCollision(bullet, a)) {
            composer().death(bullet);
            composer().hit(a, bullet->damage());
            return;
        }
    }
    for (auto c: m_containers) {
        if (ceti::checkCollision(bullet, c)) {
            composer().death(bullet);
            composer().hit(c, bullet->damage());
            return;
        }
    }
    for (auto b: m_bullets) {
        if (b->collideable() && (b->ownerId() != bullet->ownerId())) {
            if (ceti::checkCollision(bullet, b)) {
                composer().death(bullet);
                composer().death(b);
                return;
            }
        }
    }
}

void StarSystem::__asteroidCollisionCheck_s(Asteroid* asteroid) const
{
    //std::cout<<"asteroid mass ="<<asteroid->mass()<<std::endl;
    //std::cout<<"asteroid armor ="<<asteroid->model()->armor()<<std::endl;

    if (!asteroid->isAlive()) {
        return;
    }

    for (auto v: m_vehicles) {
        if (ceti::checkCollision(asteroid, v)) {
            composer().death(asteroid);
            composer().hit(v, asteroid->mass());
            return;
        }
    }
    for (auto p: m_planets) {
        if (ceti::checkCollision(asteroid, p)) {
            composer().death(asteroid);
            //processor().hit(p, asteroid->mass());
            return;
        }
    }
    for (auto s: m_stars) {
        if (ceti::checkCollision(asteroid, s)) {
            composer().death(asteroid);
            //processor().hit(s, asteroid->mass());
            return;
        }
    }
    for (auto a: m_asteroids) {
        if (a->id() != asteroid->id()) {
            if (ceti::checkCollision(asteroid, a)) {
                composer().death(asteroid);
                composer().death(a);
                return;
            }
        }
    }
    for (auto b: m_bullets) {
        if (b->collideable()) {
            if (ceti::checkCollision(asteroid, b)) {
                composer().hit(asteroid, b->damage());
                composer().death(b);
                return;
            }
        }
    }
}

void StarSystem::__updateEntities_s(int time)
{
    for (Star* star: m_stars) { star->updateInSpace(time);  }
    for (Planet* planet: m_planets) { planet->updateInSpace(time); }
    for (WormHole* wormhole: m_wormholes) { wormhole->updateInSpace(time); }
    for (Container* container: m_containers) { container->updateInSpace(time); }
    for (Asteroid* asteroid: m_asteroids) { asteroid->updateInSpace(time); }
    for (Vehicle* vehicle: m_vehicles) { vehicle->update(time); }
    for (Bullet* bullet: m_bullets) { bullet->update(time); }
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
}      

void StarSystem::__shipManager_s(unsigned int num)
{
    while (m_vehicles.size() < num) {
        race::Type prace_id = race::Type::R0;
        if (meti::rand::gen_bool()) {
            prace_id = race::Type::R6;
        }
        
        entity::Type pgroup    = entity::Type::WARRIOR;
        entity::Type psubgroup = entity::Type::WARRIOR;
        int size_id     = SIZE_4;
        int weapons_num = 7;

        // prace_id, pgroup, psubgroup
        control::Npc* new_npc = builder::Npc::gen();
        control::Ship* new_pship = builder::ShipBuilder::gen();

        builder::VehicleBuilder::equip(new_pship);
        new_pship->bindNpc(new_npc);

        glm::vec2 center = meti::rand::gen_vec2(100, 800);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 direction = meti::rand::gen_vec3xy_unit();
        
        add(new_pship, center3, direction);
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
//            //Sessions::get().session()->garbage()->add(asteroid);
//            //to_remove.push_back(asteroid);
//        }
//    }

//    for(Asteroid* aster//            //            DistantNebulaEffect* dn = GetNewDistantNebulaEffect(NONE);
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
    //}oid: to_remove) {
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
            //std::cout<<dist<<" "<<force_power<<" "<<ceti::to_string(force_dir)<<std::endl;

            m_containers[i]->addImpulse(force_dir, force_power);
        }
    }

}

void StarSystem::_postDeathUniqueEvent(bool)
{}

} // namespace control
} // namespace core
