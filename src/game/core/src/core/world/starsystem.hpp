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
#include <core/manager/AsteroidManager.hpp>
#include <core/type/RaceType.hpp>

#include <core/descriptor/world/StarSystemDescriptor.hpp>

#include <ceti/type/IdType.hpp>
#include <ceti/Pack.hpp>

#include <boost/serialization/vector.hpp>

#include <vector>

namespace model {
class StarSystem;
class Star;
class Planet;
class Asteroid;
class WormHole;
class Container;
class Bullet;
class Vehicle;
class SpaceStation;
class Ship;
class Satellite;
class Npc;
} // namespace model

namespace control {
class Star;
class Planet;
class Asteroid;
class WormHole;
class Container;
class Bullet;
class SpaceStation;
class Ship;
class Satellite;
class Vehicle;
} // namespace model


class Player;

class Sector;

class ShockWaveEffect;

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
public:
    StarSystem(descriptor::StarSystem*, model::StarSystem*);
    ~StarSystem();

    virtual void putChildrenToGarbage() const;

    void setContainerNumMax(int container_num_max) { m_container_num_max = container_num_max; }
    void setSector(Sector* sector)  { m_sector = sector; }
    void setColor(const glm::vec4& color)  { m_color = color; }
    AsteroidManager& asteroidManager()  { return m_asteroid_manager; }

    const glm::vec4& color() const { return m_color; }
    //bool GetDetailedSimulationFlag() const { return detalied_simulation; }
    int conditionId() const { return m_condition_id; }
    race::Type raceId() const { return m_race_id; }
    race::Type conquerorRaceId() const { return m_conqueror_race_id; }
    Star* star() const;
    Sector* sector()      const { return m_sector; }

    model::Npc* freeLeaderByRaceId(race::Type) const;
    void createGroupAndShareTask(model::Npc*, StarSystem*, int) const;

    void explosionEvent(const glm::vec3&, int, float) const;

    /** TRANSITION */
    // add
public:
    void add(SpaceStation*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = meti::OY);
    void add(Ship*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = meti::OY);
    void add(Satellite*, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& dir = meti::OY, const model::SpaceObject* const parent = nullptr);
    void add(Bullet*, const glm::vec3&, const glm::vec3&);
    void add(Star*);
    void add(Planet*, SpaceObject* parent = nullptr);
    void add(Asteroid*, SpaceObject* parent = nullptr, int it = 0);
    void add(Container*, const glm::vec3&);
    void add(WormHole*, const glm::vec3&);

private:
    void __add(Container*);
    void __add(WormHole*);
    void __add(Bullet*);

public:
    // remove
    void remove(Star*);
    void remove(Planet*);
    void remove(WormHole*);
    void remove(Asteroid*);
    void remove(Container*);
    void remove(Bullet*);
    void remove(SpaceStation*);
    void remove(Ship*);
    void remove(Satellite*);
    //

    void bombExplosionEvent(Container*, bool);
    void starSparkEvent(float) const;

    void update(int);

    //float calcResultGravityForce(const glm::vec3&, const glm::vec3&, float) const;

    const ceti::pack<Star*>& stars() const { return m_stars; }
    const ceti::pack<Planet*>& planets() const { return m_planets; }
    const ceti::pack<WormHole*>& wormholes() const { return m_wormholes; }
    const ceti::pack<Asteroid*>& asteroids() const { return m_asteroids; }
    const ceti::pack<Container*>& containers() const { return m_containers; }
    const ceti::pack<Bullet*>& bullets() const { return m_bullets; }

    const ceti::pack<Vehicle*>& vehicles() const { return m_vehicles; }
    const ceti::pack<SpaceStation*>& spacestations() const { return m_spacestations; }
    const ceti::pack<Ship*>& ships() const { return m_ships; }
    const ceti::pack<Satellite*>& satellites() const { return m_satellites; }

    // ugly
    Planet* closestInhabitedPlanet(const glm::vec2&) const;
    Planet* randomInhabitedPlanet() const;
    Vehicle* randomVehicleExcludingNpcRaceId(race::Type) const;
    Vehicle* randVehicleByNpcRaceId(race::Type) const;
    Vehicle* randomVehicle(const std::vector<race::Type>&) const;
    //

    descriptor::StarSystem* descriptor() const { return m_descriptor_starsystem; }
    model::StarSystem* model() const { return m_model_starsystem; }

private:
    descriptor::StarSystem* m_descriptor_starsystem = nullptr;
    model::StarSystem* m_model_starsystem = nullptr;

    race::Type m_race_id = race::Type::R0;
    race::Type m_conqueror_race_id = race::Type::NONE;

    bool m_unique_update_inDymanic_done = false;
    bool m_unique_update_inStatic_done = false;

    int m_condition_id;
    unsigned int m_container_num_max = CONTAINER_NUM_MAX_DEFAULT;

    Sector* m_sector = nullptr;
    glm::vec4 m_color;

    AsteroidManager m_asteroid_manager;

    ceti::pack<Star*> m_stars;
    ceti::pack<Planet*> m_planets;
    ceti::pack<Asteroid*> m_asteroids;
    ceti::pack<Container*> m_containers;
    ceti::pack<Bullet*> m_bullets;
    ceti::pack<WormHole*> m_wormholes;
    ceti::pack<Vehicle*> m_vehicles;
    ceti::pack<SpaceStation*> m_spacestations;
    ceti::pack<Ship*> m_ships;
    ceti::pack<Satellite*> m_satellites;

    void __launchingEvent() const;

    void __updateInSpaceInStatic_s();
    void __updateEntities_s(int);

    void __updateStates();

    void __damageEventInsideCircle(const glm::vec3&, float, int, bool);

    void _postDeathUniqueEvent(bool);

    void __shipManager_s(unsigned int);

    void __manageUnavaliableObjects_s();
    void __manageDeadObjects();

    void __bulletsCollisionCheck_s() const;
    void __asteroidsCollisionCheck_s() const;
    bool __bulletCollisionCheck_s(Bullet*) const;
    bool __asteroidCollisionCheck_s(Asteroid*) const;

    void __bulletsManager_DEBUG(int) const;
    void __processBulletDeath_s(Bullet*) const;
    void __processAsteroidDeath_s(Asteroid*) const;

    void __removeVehicle(int_t);
    void __addVehicleCommon(Vehicle*, const glm::vec3&, const glm::vec3&);

    void __actualizeModel();
};

} // namespace control
