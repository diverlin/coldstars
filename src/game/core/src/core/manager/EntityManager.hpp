
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

namespace model {
class StarSystem;
class Ship;
class Container;
class SpaceObject;
} // namespace model

namespace control {
class StarSystem;
class Ship;
class Container;
class SpaceObject;
} // namespace control

namespace model {

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

StarSystem* getStarsystem(int_t id);
Ship* getShip(int_t id);
Container* getContainer(int_t id);
SpaceObject* getSpaceObject(int_t id);

} // namespace model

namespace control {

StarSystem* getNewStarsystem();
Container* getNewContainer();

} // namespace control

class EntityManager
{
public:
    EntityManager() {}

    void saveRequest() { m_save_request = true; }
    void loadRequest() { m_load_request = true; }

    void reg(model::Base*);

    model::Base* get(int_t) const;

    model::item::Scaner* scaner(int_t) const;
    model::item::Drive* drive(int_t) const;
    model::item::Bak* bak(int_t) const;
    model::item::Droid* droid(int_t) const;
    model::item::Grapple* grapple(int_t) const;
    model::item::Lazer* lazer(int_t) const;
    model::item::Protector* protector(int_t) const;
    model::item::Radar* radar(int_t) const;
    model::item::Rocket* rocket(int_t) const;

    Player* player() const;

    bool updateSaveRequest();
    bool updateLoadRequest();

    void addToGarbage(model::Base*);
    void clearGarbage();

private:
    bool m_save_request = false;
    bool m_load_request = false;

    std::map<int_t, model::Base*> m_models;
    std::vector<model::Base*> m_garbage;

    void clear();

    void saveEvent(const std::string&);
    void loadPass0(const std::string&);
    void loadPass1() const;
};

