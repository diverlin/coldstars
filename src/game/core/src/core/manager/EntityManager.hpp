
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

#include <core/common/Base.hpp>

#include <map>
#include <cassert>
#include <string>

class Player;

namespace control {

class StarSystem;

class Star;
class Planet;
class Asteroid;

class SpaceStation;
class Ship;
class Satellite;
class Container;
class SpaceObject;

class Item;

namespace item {
class Scaner;
class Drive;
class Bak;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
} // namespace item

} // namespace control


class EntityManager
{
private:
    EntityManager() = default;
    EntityManager(const EntityManager&) = delete;
    ~EntityManager() = default;
    EntityManager& operator=(const EntityManager&) = delete;

public:
    static EntityManager& get();

    void saveRequest() { m_save_request = true; }
    void loadRequest() { m_load_request = true; }

    void reg(control::Base*);

    control::Base* get(int_t) const;
    control::Item* getItemBase(int_t) const;

    control::StarSystem* starsystem(int_t id) const;

    control::Star* star(int_t id) const;
    control::Planet* planet(int_t id) const;
    control::Asteroid* asteroid(int_t id) const;

    control::SpaceStation* spacestation(int_t id) const;
    control::Ship* ship(int_t id) const;
    control::Satellite* satellite(int_t id) const;
    control::Container* container(int_t id) const;
    control::SpaceObject* spaceObject(int_t id) const;

    control::item::Scaner* scaner(int_t) const;
    control::item::Drive* drive(int_t) const;
    control::item::Bak* bak(int_t) const;
    control::item::Droid* droid(int_t) const;
    control::item::Grapple* grapple(int_t) const;
    control::item::Lazer* lazer(int_t) const;
    control::item::Protector* protector(int_t) const;
    control::item::Radar* radar(int_t) const;
    control::item::Rocket* rocket(int_t) const;

    Player* player() const;

    bool updateSaveRequest();
    bool updateLoadRequest();

    void addToGarbage(control::Base*);
    void clearGarbage();

    int_t genId();

private:
    bool m_save_request = false;
    bool m_load_request = false;

    std::map<int_t, control::Base*> m_models;
    std::vector<control::Base*> m_garbage;

    void clear();

    void saveEvent(const std::string&);
    void loadEvent(const std::string&);

    static IdGenerator m_idGenerator;
};


