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


#pragma once

#include <core/spaceobjects/SpaceObject.hpp>
#include <core/world/HyperSpace.hpp>
#include <core/managers/AsteroidManager.hpp>
#include <core/types/RaceTypes.hpp>

#include <core/descriptor/StarsystemDescriptor.hpp>

#include <ceti/type/IdType.hpp>

#include <boost/serialization/vector.hpp>

#include <vector>

namespace model {
class Star;
class Planet;
class Asteroid;
class Satellite;
class SpaceStation;
class Ship;
class Npc;
class Vehicle;
class BlackHole;
class Container;
class RocketBullet;
} // namespace model

namespace control {
class Star;
class Planet;
class Asteroid;
class Satellite;
class SpaceStation;
class Ship;
class Vehicle;
class BlackHole;
class Container;
class RocketBullet;
} // namespace model


class Player;

class Sector;

class DistantNebulaEffect;
class DistantStarEffect;

class ShockWaveEffect;

namespace jeti {
class ExplosionEffect;
class BaseParticleSystem;
}

class LazerTraceEffect;


namespace ENTITY {
namespace STARSYSTEM {
const int JUMPRADIUS = 1200;

const int PLANET_NUM_MIN = 3;
const int PLANET_NUM_MAX = 5;

const int SHIP_INIT_MIN = 4;
const int SHIP_INIT_MAX = 7;
const int SHIPENEMY_INIT_MIN = 50;
const int SHIPENEMY_INIT_MAX = 100;

const int SPACESTATION_NUM_MIN = 1;
const int SPACESTATION_NUM_MAX = 3;

const int DISTANT_NEBULA_MIN = 6;
const int DISTANT_NEBULA_MAX = 8;

enum CONDITION {
    WAR=1, CAPTURED, SAFE
};
} // namespace STARSYSTEM
} // namespace ENTITY

const int CONTAINER_NUM_MAX_DEFAULT = 400;

class Explosion
{
public:
    Explosion(int damage, int radius)
        :
          m_damage(damage),
          m_radius(radius)
    {}
    ~Explosion() {}

    int damage() const { return m_damage; }
    int radius() const { return m_radius; }

private:
    int m_damage = 0;
    int m_radius = 0;
};



namespace model {

//# TODO:: remove inherits from SpaceObject, do the same for Sector and Galaxy
class Starsystem : public model::SpaceObject
{
public:
    Starsystem();
    ~Starsystem() = default;
    Starsystem(const std::string& data);
    std::string data() const;

    bool operator==(const Starsystem& rhs) const;
    bool operator!=(const Starsystem& rhs) const;

    void setSector(int_t sector)  { m_sector = sector; }

    int conditionId()     const { return m_condition_id; }
    int raceId()          const { return m_race_id; }
    int conquerorRaceId() const { return m_conqueror_race_id; }

    int_t sector() const { return m_sector; }

    void addVehicle(int_t vehicle) { m_vehicles.push_back(vehicle); }
    void addBullet(int_t bullet) { m_bullets.push_back(bullet); }
    void addStar(int_t star) { m_stars.push_back(star); }
    void addPlanet(int_t planet) { m_planets.push_back(planet); }
    void addAsteroid(int_t asteroid) { m_asteroids.push_back(asteroid); }
    void addContainer(int_t container) { m_containers.push_back(container); }
    void addBlackhole(int_t blackhole) { m_blackholes.push_back(blackhole); }

    std::vector<int_t> planets() const { return m_planets; }
    std::vector<int_t> stars() const { return m_stars; }
    std::vector<int_t> asteroids() const { return m_asteroids; }
    std::vector<int_t> vehicles() const { return m_vehicles; }
    std::vector<int_t> containers() const { return m_containers; }

private:
    int m_race_id = NONE;
    int m_conqueror_race_id = NONE;
    int m_condition_id = NONE;

    int_t m_sector = NONE;

    std::vector<int_t> m_stars;
    std::vector<int_t> m_planets;
    std::vector<int_t> m_asteroids;
    std::vector<int_t> m_containers;
    std::vector<int_t> m_bullets;
    std::vector<int_t> m_blackholes;
    std::vector<int_t> m_vehicles;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_race_id;
        ar & m_conqueror_race_id;
        ar & m_condition_id;
        ar & m_sector;

        ar & m_stars;
        ar & m_planets;
        ar & m_asteroids;
        ar & m_containers;
        ar & m_bullets;
        ar & m_blackholes;
        ar & m_vehicles;
    }
};

} // namespace model


namespace control {

class Starsystem : public control::SpaceObject
{
    //    using Stars = std::vector<Star*>;
    //    using Planets = std::vector<Planet*>;
    //    using Vehicles = std::vector<Vehicle*>;

public:
    Starsystem(model::Starsystem*);
    ~Starsystem();

    virtual void putChildrenToGarbage() const;

    void setContainerNumMax(int container_num_max) { m_container_num_max = container_num_max; }
    void setSector(Sector* sector)  { m_sector = sector; }
    void setColor(const glm::vec4& color)  { m_color = color; }
    AsteroidManager& asteroidManager()  { return m_asteroid_manager; }

    const glm::vec4& color() const { return m_color; }
    //bool GetDetailedSimulationFlag() const { return detalied_simulation; }
    int conditionId()     const { return m_condition_id; }
    race::type raceId()          const { return m_race_id; }
    race::type conquerorRaceId() const { return m_conqueror_race_id; }
    model::Star* star() const;
    Sector* sector()      const { return m_sector; }
    //        unsigned int GetShockWaveEffectNum()    const { return effect_SHOCKWAVE_vec.size(); }
    unsigned int asteroidNum()     const { return m_asteroids.size(); }
    //        unsigned int GetExplosionEffectNum()     const { return effect_PARTICLESYSTEM_vec.size(); }
    //        unsigned int GetTextDamageNum()     const { return text_DAMAGE_vec.size(); }
    bool isAnyActiveParticlesEffectPresent(int) const;

    HyperSpace& hyperSpace() { return m_hyperspace; };

    model::Npc* freeLeaderByRaceId(race::type) const;
    void createGroupAndShareTask(model::Npc*, Starsystem*, int) const;

    //// TRANSITION
    void add(model::Ship*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f));
    void add(model::SpaceStation*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f));
    void add(model::Satellite*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f), const model::SpaceObject* const parent = nullptr);
    void add(model::RocketBullet*, const glm::vec3&, const glm::vec3&);

    void add(model::Star*);
    void add(model::Planet*, const model::SpaceObject* parent = nullptr);
    void add(model::Asteroid*, const model::SpaceObject* parent = nullptr, int it = 0);
    void add(model::Container*, const glm::vec3& = glm::vec3(0.0f));
    void add(model::BlackHole*, const glm::vec3&);

    void add(Explosion*, const glm::vec3&);

    // effects
    void add(jeti::BaseParticleSystem*);
    void add(ShockWaveEffect*, const glm::vec2&);
    void add(jeti::ExplosionEffect*, const glm::vec3&, float, float);
    void add(jeti::ExplosionEffect*, const glm::vec3&);
    void add(LazerTraceEffect*);

    void add(DistantNebulaEffect*);
    void add(DistantStarEffect*);

    //void Add(VerticalFlowText*);
    //

    void bombExplosionEvent(control::Container*, bool);
    void starSparkEvent(float) const;

    void findRenderVisibleEntities_c(Player*);
    void findRadarVisibleEntities_c(Player*);

    void update(int);
    void loadEntitiesResource();

    float calcResultGravityForce(const glm::vec3&, const glm::vec3&, float) const;

    //        void DrawBackground(const jeti::Renderer&, const glm::vec2&);
    //        void DrawOrbits(const jeti::Renderer&);
    //        void DrawPath();

    void Save(boost::property_tree::ptree&) const;
    void Load(const boost::property_tree::ptree&);
    void Resolve();

    // poor

    std::vector<control::Planet*> planets() const { return m_planets; }
    std::vector<control::Star*> stars() const { return m_stars; }
    std::vector<control::Asteroid*> asteroids() const { return m_asteroids; }
    std::vector<control::Vehicle*> vehicles() const { return m_vehicles; }
    std::vector<control::Container*> containers() const { return m_containers; }

    model::Planet* closestInhabitedPlanet(const glm::vec2&) const;
    model::Planet* randomInhabitedPlanet() const;
    model::Planet* randomPlanet() const;
    control::Vehicle* randomVehicle() const;
    control::Vehicle* randomVehicleExcludingNpcRaceId(race::type) const;
    control::Vehicle* randVehicleByNpcRaceId(race::type) const;
    control::Vehicle* randomVehicle(const std::vector<race::type>&) const;
    //

    model::Starsystem* model() const { return m_model_starsystem; }
    descriptor::Starsystem* descriptor() const { return m_descriptor_starsystem; }

private:
    model::Starsystem* m_model_starsystem = nullptr;
    descriptor::Starsystem* m_descriptor_starsystem = nullptr;

    race::type m_race_id = race::type::R0;
    race::type m_conqueror_race_id = race::type::NONE;

    bool m_unique_update_inDymanic_done = false;
    bool m_unique_update_inStatic_done = false;

    int m_condition_id;
    unsigned int m_container_num_max = CONTAINER_NUM_MAX_DEFAULT;

    Sector* m_sector = nullptr;
    glm::vec4 m_color;

    AsteroidManager m_asteroid_manager;

    // ENTITY VECTORS
    //std::vector<Player*>        PLAYER_vec;

    std::vector<control::Star*> m_stars;
    std::vector<control::Planet*> m_planets;
    std::vector<control::Asteroid*> m_asteroids;
    std::vector<control::Container*> m_containers;
    std::vector<control::RocketBullet*> m_bullets;
    std::vector<control::BlackHole*> m_blackholes;
    std::vector<control::Vehicle*> m_vehicles;

    HyperSpace m_hyperspace;

    // effects
    //        std::vector<DistantNebulaEffect*> distantNebulaEffect_vec;
    //        std::vector<DistantStarEffect*>   distantStarEffect_vec;

    //        std::vector<LazerTraceEffect*>    effect_LAZERTRACE_vec;
    //        std::vector<jeti::BaseParticleSystem*>  effect_PARTICLESYSTEM_vec;
    //        std::vector<ShockWaveEffect*>     effect_SHOCKWAVE_vec;
    //        std::vector<VerticalFlowText*>    text_DAMAGE_vec;

    //        GarbageEffects  garbage_effects;

    void __launchingEvent() const;

    void __updateInSpaceInStatic_s();
    void __updateEntities_s(int, bool);

    void __updateStates();

    void __damageEventInsideCircle(const glm::vec3&, float, int, bool);

    void _postDeathUniqueEvent(bool);

    void __shipManager_s(unsigned int);

    void __manageUnavaliableObjects_s();
    void __manageDeadObjects_s();

    void __rocketCollision_s(bool);
    void __asteroidCollision_s(bool);
    void __externalForcesAffection_s(bool);

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

    void __addVehicleCommon(control::Vehicle*, const glm::vec3&, const glm::vec3&);

    friend class GuiGalaxyMap;
    friend class Observation;
    friend class Player;
    friend class God;
};

} // namespace control
