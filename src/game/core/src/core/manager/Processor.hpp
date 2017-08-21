
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

#include <glm/glm.hpp>

#include <vector>

namespace descriptor {
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

namespace comm {
class TelegrammHub;
} // namespace comm

namespace manager {

class Entity;

class Processor
{
private:
    Processor();
    Processor(const Processor&) = delete;
    ~Processor() = default;
    Processor& operator=(const Processor&) = delete;

    void death(control::Asteroid*);
    void death(control::Vehicle*);
    void death(control::Bullet*);
    void death(control::Container*);

    void hit(control::SpaceObject* object, int damage);

    void genBullets_DEBUG(control::StarSystem*, int) const;

public:
    static Processor& get();

private:
    core::comm::TelegrammHub& m_telegrammHub;
    manager::Entity& m_entitiesManager;
    descriptor::Manager& m_descriptorManager;

    void __explosion(float, const glm::vec3&);
    std::vector<glm::vec3> __genImpulses(int num) const;
};

} // namespace manager
} // namespace core
