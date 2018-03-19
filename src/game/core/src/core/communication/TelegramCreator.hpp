
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

# pragma once

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace descriptor {
class Galaxy;
class Manager;
} // namespace descriptor

namespace control {
class SpaceObject;
class StarSystem;
class Vehicle;
class Asteroid;
class Bullet;
class Container;
} // namespace control

namespace core {

class Player;

namespace comm {
class TelegramHub;
} // namespace comm

class TelegramCreator
{
private:
    TelegramCreator();
    TelegramCreator(const TelegramCreator&) = delete;
    ~TelegramCreator() = default;
    TelegramCreator& operator=(const TelegramCreator&) = delete;

public:
    static TelegramCreator& get();

    void death_spaceobject(control::SpaceObject*);
    void death(control::Asteroid*);
    void death(control::Bullet*);

    void hit(control::SpaceObject* object, int damage);

    void genBullets_DEBUG(control::StarSystem*, int) const;

    void createPlayer(int_t, int_t);
//    void bindPlayerWithNpc(int_t, int_t);
    void createGalaxy(descriptor::Galaxy*);

    void moveVehicle(int_t, const glm::vec3&) const;
    void endTurn() const;
    void targetingSpaceObject(int_t vehicle_id, int_t target_id) const;

private:
    core::comm::TelegramHub& m_telegramHub;

    void __addSpaceObjectToGarbage(control::SpaceObject*);
    void __removeSpaceObjectFromStarSystem(control::SpaceObject*);
    void __explosionEffect(float, const glm::vec3&);

    void __death(control::Vehicle*);
    void __death(control::Container*);

    std::vector<glm::vec3> __genImpulses(int num) const;

    int_t __createSector(int_t sector_descriptor_id) const;
    int_t __createStarsystem(int_t starsystem_descriptor_id) const;
    int_t __createStar(int_t) const;
    int_t __createPlanet(int_t planet_descriptor_id) const;
    int_t __createShip(int_t descriptor_id) const;
    int_t __createNpc(int_t descriptor_id) const;

    void __addSectorToGalaxy(int_t sector_id, int_t galaxy_id) const;
    void __addStarsystemToSector(int_t starsystem_id, int_t sector_id) const;
    void __addStarToStarsystem(int_t star_id, int_t starsystem_id) const;
    void __addPlanetToStarsystem(int_t planet_id, int_t starsystem_id) const;
    void __addShipToStarSystem(int_t starsystem_id, int_t ship_id, const glm::vec3& center = glm::vec3()) const;

    void __addNpcToShip(int_t npc_id, int_t ship_id) const;
    void __equipShip(int_t ship_id) const;

    void __createBak(int_t descriptor_id, int_t id) const;
    void __createDrive(int_t descriptor_id, int_t id) const;
    void __createProtector(int_t descriptor_id, int_t id) const;
    void __createScaner(int_t descriptor_id, int_t id) const;
    void __createRadar(int_t descriptor_id, int_t id) const;
    void __createGrapple(int_t descriptor_id, int_t id) const;
    void __createLazer(int_t descriptor_id, int_t id) const;
    void __createRocket(int_t descriptor_id, int_t id) const;

    void __mountItem(int_t ship_id, int_t id) const;
    void __loadItem(int_t ship_id, int_t id) const;
};

} // namespace core
