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

namespace core {
class StarModel;
class PlanetModel;
class AsteroidModel;
class SatelliteModel;
class SpaceStationModel;
class ShipModel;
class Npc;
class VehicleModel;
class WormHoleModel;
class ContainerModel;
class BulletModel;
} // namespace core

namespace control {
class Star;
class Planet;
class Asteroid;
class Satellite;
class SpaceStation;
class Ship;
class Vehicle;
class WormHole;
class Container;
class Bullet;
} // namespace control


class Player;

class Sector;

class DistantNebulaEffect;
class DistantStarEffect;

class ShockWaveEffect;

namespace ENTITY {
namespace STARSYSTEM {

enum CONDITION {
    WAR=1, CAPTURED, SAFE
};

} // namespace STARSYSTEM
} // namespace ENTITY

namespace core {

class StarSystemModel : public BaseModel
{
public:
    StarSystemModel(int_t, int_t ob_id = NONE);
    ~StarSystemModel() = default;
    StarSystemModel(const std::string& data);
    std::string data() const;

    bool operator==(const StarSystemModel& rhs) const;
    bool operator!=(const StarSystemModel& rhs) const;

    void setSector(int_t sector)  { m_sector = sector; }
    void setPosition(const meti::vec3& position) { m_position = position; }

    int status() const { return m_status; }
    int race() const { return m_race; }
    int conquerorRaceId() const { return m_invader; }

    int_t sector() const { return m_sector; }
    const meti::vec3& position() const { return m_position; }

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
    void removeWormHole(int_t id) { m_wormholes.remove(id); }
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

    ceti::InfoTable info() const override final {
        ceti::InfoTable result;
        result.add("StarSystem");
        result.add("race", m_race);
        result.add("invader", m_invader);
        result.add("status", m_status);
        result.add("position", m_position);
        result.add("sector", m_sector);
        result.add("stars", m_stars);
        result.add("wormholes", m_wormholes);
        result.add("asteroids", m_asteroids);
        result.add("containers", m_containers);
        result.add("bullets", m_bullets);
        result.add("spacestations", m_spacestations);
        result.add("ships", m_ships);
        result.add("satellites", m_satellites);

        return result;
    }

private:
    int m_race = NONE;
    int m_invader = NONE;
    int m_status = NONE;

    meti::vec3 m_position;
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
        ar & boost::serialization::base_object<BaseModel>(*this);
        ar & m_race;
        ar & m_invader;
        ar & m_status;
        ar & m_position;
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

} // namespace core

