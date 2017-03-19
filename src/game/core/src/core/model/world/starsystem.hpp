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

enum CONDITION {
    WAR=1, CAPTURED, SAFE
};

} // namespace STARSYSTEM
} // namespace ENTITY

namespace model {

//# TODO:: remove inherits from SpaceObject, do the same for Sector and Galaxy
class StarSystem : public Base
{
public:
    StarSystem(int_t);
    ~StarSystem() = default;
    StarSystem(const std::string& data);
    std::string data() const;

    bool operator==(const StarSystem& rhs) const;
    bool operator!=(const StarSystem& rhs) const;

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
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
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

