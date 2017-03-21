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

#include <core/spaceobject/SpaceObject.hpp>
#include <core/world/HyperSpace.hpp>
#include <core/manager/AsteroidManager.hpp>
#include <core/type/RaceType.hpp>

#include <core/descriptor/world/StarSystemDescriptor.hpp>

#include <ceti/type/IdType.hpp>

#include <boost/serialization/vector.hpp>

#include <vector>

namespace model {
class StarSystem;

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

namespace control {

class StarSystem : public Base
{
    //    using Stars = std::vector<Star*>;
    //    using Planets = std::vector<Planet*>;
    //    using Vehicles = std::vector<Vehicle*>;

public:
    StarSystem(model::StarSystem*);
    ~StarSystem();

    virtual void putChildrenToGarbage() const;

    void setContainerNumMax(int container_num_max) { m_container_num_max = container_num_max; }
    void setSector(Sector* sector)  { m_sector = sector; }
    void setColor(const glm::vec4& color)  { m_color = color; }
    AsteroidManager& asteroidManager()  { return m_asteroid_manager; }

    const glm::vec4& color() const { return m_color; }
    //bool GetDetailedSimulationFlag() const { return detalied_simulation; }
    int conditionId()     const { return m_condition_id; }
    race::Type raceId()          const { return m_race_id; }
    race::Type conquerorRaceId() const { return m_conqueror_race_id; }
    Star* star() const;
    Sector* sector()      const { return m_sector; }
    //        unsigned int GetShockWaveEffectNum()    const { return effect_SHOCKWAVE_vec.size(); }
    unsigned int asteroidNum()     const { return m_asteroids.size(); }
    //        unsigned int GetExplosionEffectNum()     const { return effect_PARTICLESYSTEM_vec.size(); }
    //        unsigned int GetTextDamageNum()     const { return text_DAMAGE_vec.size(); }
    bool isAnyActiveParticlesEffectPresent(int) const;

    HyperSpace& hyperSpace() { return m_hyperspace; };

    model::Npc* freeLeaderByRaceId(race::Type) const;
    void createGroupAndShareTask(model::Npc*, StarSystem*, int) const;

    //// TRANSITION
    void add(model::SpaceStation*);
    void add(SpaceStation*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f));
    void add(model::Ship*);
    void add(Ship*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f));
    void add(model::Satellite*);
    void add(Satellite*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f), const model::SpaceObject* const parent = nullptr);

    void add(model::RocketBullet*, const glm::vec3&, const glm::vec3&);

    void add(model::Star*);
    void add(Star*);
    void add(model::Planet*);
    void add(Planet*, SpaceObject* parent = nullptr);
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
    std::vector<control::SpaceStation*> spacestations() const { return m_spacestations; }
    std::vector<control::Ship*> ships() const { return m_ships; }
    std::vector<control::Satellite*> satellites() const { return m_satellites; }

    std::vector<control::Container*> containers() const { return m_containers; }

    model::Planet* closestInhabitedPlanet(const glm::vec2&) const;
    model::Planet* randomInhabitedPlanet() const;
    model::Planet* randomPlanet() const;
    control::Vehicle* randomVehicle() const;
    control::Vehicle* randomVehicleExcludingNpcRaceId(race::Type) const;
    control::Vehicle* randVehicleByNpcRaceId(race::Type) const;
    control::Vehicle* randomVehicle(const std::vector<race::Type>&) const;
    //

    model::StarSystem* model() const { return m_model_starsystem; }
    descriptor::StarSystem* descriptor() const { return m_descriptor_starsystem; }

private:
    model::StarSystem* m_model_starsystem = nullptr;
    descriptor::StarSystem* m_descriptor_starsystem = nullptr;

    race::Type m_race_id = race::Type::R0;
    race::Type m_conqueror_race_id = race::Type::NONE;

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
    std::vector<control::SpaceStation*> m_spacestations;
    std::vector<control::Ship*> m_ships;
    std::vector<control::Satellite*> m_satellites;

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

    void __actualizeModel();

    friend class GuiGalaxyMap;
    friend class Observation;
    friend class Player;
    friend class God;
};

} // namespace control
