
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

#include <core/Base.hpp>

#include <map>
#include <cassert>
#include <string>

namespace core {

class Player;

namespace control {

class Npc;

class Galaxy;
class Sector;
class StarSystem;
class HyperSpace;

class Star;
class Planet;
class Asteroid;
class WormHole;

class Land;

class Vehicle;
class SpaceStation;
class Ship;
class Satellite;
class Container;
class Bullet;
class SpaceObject;

class Item;

class Weapon;
class Scaner;
class Drive;
class Bak;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;

} // namespace control

namespace manager {

class Entities
{
public:
    Entities() = default;
    Entities(const Entities&) = delete;
    ~Entities() = default;
    Entities& operator=(const Entities&) = delete;

//    void saveRequest() { m_save_request = true; }
//    void loadRequest() { m_load_request = true; }

    void setGalaxy(control::Galaxy* galaxy) { m_galaxy = galaxy; }

    void add(control::Base*);
    void remove(control::Base*);
    bool contain(int_t id) const { return (m_entities.count(id) == 1); }

    void setHyperSpace(control::HyperSpace* hyperspace) { m_hyperspace = hyperspace; }

    control::Base* base(int_t) const;
    control::Npc* npc(int_t) const;

    control::Galaxy* galaxy() const { return m_galaxy; }
    control::Galaxy* galaxy(int_t id) const;
    control::Sector* sector(int_t id) const;
    control::StarSystem* starsystem(int_t id) const;
    control::HyperSpace* hyperspace() const;

    control::Star* star(int_t id) const;
    control::Planet* planet(int_t id) const;
    control::Asteroid* asteroid(int_t id) const;
    control::WormHole* wormhole(int_t id) const;

    control::Vehicle* vehicle(int_t id) const;
    control::SpaceStation* spacestation(int_t id) const;
    control::Ship* ship(int_t id) const;
    control::Satellite* satellite(int_t id) const;
    control::Container* container(int_t id) const;
    control::Bullet* bullet(int_t id) const;

    control::SpaceObject* spaceObject(int_t id) const;
    control::Land* land(int_t id) const;

    control::Item* item(int_t) const;
    control::Weapon* weapon(int_t) const;
    control::Scaner* scaner(int_t) const;
    control::Drive* drive(int_t) const;
    control::Bak* bak(int_t) const;
    control::Droid* droid(int_t) const;
    control::Grapple* grapple(int_t) const;
    control::Lazer* lazer(int_t) const;
    control::Protector* protector(int_t) const;
    control::Radar* radar(int_t) const;
    control::Rocket* rocket(int_t) const;

    Player* player() const;

//    bool updateSaveRequest();
//    bool updateLoadRequest();

    int_t nextId();

//    void clear();

private:
    control::Galaxy* m_galaxy = nullptr;

    std::map<int_t, control::Base*> m_entities;

    control::HyperSpace* m_hyperspace = nullptr;

    static IdGenerator m_idGenerator;
};

} // namespace manager
} // namespace core

