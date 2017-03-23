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
#include <ceti/Pack.hpp>

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
class Wormhole;
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
class Wormhole;
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

    void addStar(int_t star) { if (_isWritable()) m_stars.add(star); }
    void addPlanet(int_t planet) { if (_isWritable()) m_planets.add(planet); }
    void addWormhole(int_t wormhole) { if (_isWritable()) m_wormholes.add(wormhole); }
    void addAsteroid(int_t asteroid) { if (_isWritable()) m_asteroids.add(asteroid); }
    void addContainer(int_t container) { if (_isWritable()) m_containers.add(container); }
    void addBullet(int_t bullet) { if (_isWritable()) m_bullets.add(bullet); }

    void addSpaceStation(int_t spacestation) { if (_isWritable()) m_spacestations.add(spacestation); }
    void addShip(int_t ship) { if (_isWritable()) m_ships.add(ship); }
    void addSatellite(int_t satellite) { if (_isWritable()) m_satellites.add(satellite); }

    void removeStar(int_t id) { m_stars.remove(id); }
    void removePlanet(int_t id) { m_planets.remove(id); }
    void removeWormhole(int_t id) { m_wormholes.remove(id); }
    void removeAsteroid(int_t id) { m_asteroids.remove(id); }
    void removeContainer(int_t id) { m_containers.remove(id); }
    void removeBullet(int_t id) { m_bullets.remove(id); }

    void removeSpaceStation(int_t id) { m_spacestations.remove(id); }
    void removeShip(int_t id) { m_ships.remove(id); }
    void removeSatellite(int_t id) { m_satellites.remove(id); }

    ceti::pack<int_t> stars() const { return m_stars; }
    ceti::pack<int_t> planets() const { return m_planets; }
    ceti::pack<int_t> wormholes() const { return m_wormholes; }
    ceti::pack<int_t> asteroids() const { return m_asteroids; }
    ceti::pack<int_t> containers() const { return m_containers; }
    ceti::pack<int_t> bullets() const { return m_bullets; }

    ceti::pack<int_t> spacestations() const { return m_spacestations; }
    ceti::pack<int_t> ships() const { return m_ships; }
    ceti::pack<int_t> satellites() const { return m_satellites; }

private:
    int m_race_id = NONE;
    int m_conqueror_race_id = NONE;
    int m_condition_id = NONE;

    int_t m_sector = NONE;

    ceti::pack<int_t> m_stars;
    ceti::pack<int_t> m_planets;
    ceti::pack<int_t> m_wormholes;
    ceti::pack<int_t> m_asteroids;
    ceti::pack<int_t> m_containers;
    ceti::pack<int_t> m_bullets;

    ceti::pack<int_t> m_spacestations;
    ceti::pack<int_t> m_ships;
    ceti::pack<int_t> m_satellites;

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
        ar & m_wormholes;
        ar & m_asteroids;
        ar & m_containers;
        ar & m_bullets;

        ar & m_spacestations;
        ar & m_ships;
        ar & m_satellites;
    }
};

} // namespace model

