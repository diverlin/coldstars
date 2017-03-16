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

#include <core/descriptor/Base.hpp>

#include <core/descriptor/GalaxyDescriptor.hpp>
#include <core/descriptor/SectorDescriptor.hpp>
#include <core/descriptor/StarsystemDescriptor.hpp>

#include <core/descriptor/spaceobject/Container.hpp>

#include <ceti/descriptor/Collector.hpp>
#include <ceti/descriptor/Mesh.hpp>
#include <ceti/descriptor/Texture.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <string>

namespace descriptor {

class Galaxy;
class Sector;
class StarSystem;
class Star;
class Planet;
class Asteroid;
class Container;
class Ship;
class SpaceStation;
class Satellite;

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

template<typename T>
class MManager {
public:
    MManager() = default;
    ~MManager() = default;

    void add(T* descr) {
        std::cout<<"MManager add"<<std::endl<<descr->info()<<std::endl;
        const auto it = m_descriptors.find(descr->id());
        if (it == m_descriptors.end()) {
            m_descriptors.insert(std::make_pair(descr->id(), descr));
        } else {
            throw std::runtime_error("MManager descriptor with that id already exist");
        }
    }

    T* get(int_t id) const {
        std::cout<<"MManager get(descriptor.id="<<id<<")"<<std::endl;
        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            return it->second;
        } else {
            throw std::runtime_error("T* get descriptor id doesn't exist");
        }
    }

    T* random() const {
        int_t key = meti::getRand(idList());
        auto it = m_descriptors.find(key);
        assert(it != m_descriptors.end());
        return it->second;
    }

    std::vector<int_t> idList() const {
        std::vector<int_t> result;
        for (auto it: m_descriptors) {
            result.push_back(it.first);
        }
        assert(!result.empty());
        return result;
    }
    int size() const {
        return m_descriptors.size();
    }

private:
    std::map<int_t, T*> m_descriptors;
};


class Manager
{
    Manager();
    Manager(const Manager&) = delete;
    ~Manager() = default;
    Manager& operator=(const Manager&) = delete;

public:
    static Manager& get();

    void reg(Base*);
    Base* get(int_t) const;
    Base* rand(Type) const;

    Galaxy* randGalaxy() const;
    Sector* randSector() const;
    StarSystem* randStarSystem() const;

    Star* randStar() const;
    Planet* randPlanet() const;
    Asteroid* randAsteroid() const;
    Container* randContainer() const;
    Ship* randShip() const;
    Satellite* randSatellite() const;
    SpaceStation* randSpaceStation() const;

    item::Scaner* randScaner() const;
    item::Drive* randDrive() const;
    item::Bak* randBak() const;
    item::Droid* randDroid() const;
    item::Grapple* randGrapple() const;
    item::Lazer* randLazer() const;
    item::Protector* randProtector() const;
    item::Radar* randRadar() const;
    item::Rocket* randRocket() const;

    Galaxy* galaxy(int_t) const;
    Sector* sector(int_t) const;
    StarSystem* starSystem(int_t) const;

    Star* star(int_t) const;
    Planet* planet(int_t) const;
    Asteroid* asteroid(int_t) const;
    Container* container(int_t) const;
    Ship* ship(int_t) const;
    Satellite* satellite(int_t) const;
    SpaceStation* spaceStation(int_t) const;

    item::Scaner* scaner(int_t) const;
    item::Drive* drive(int_t) const;
    item::Bak* bak(int_t) const;
    item::Droid* droid(int_t) const;
    item::Grapple* grapple(int_t) const;
    item::Lazer* lazer(int_t) const;
    item::Protector* protector(int_t) const;
    item::Radar* radar(int_t) const;
    item::Rocket* rocket(int_t) const;

    void add(BaseOLD*);
    BaseOLD* getRandOLD(const Type&);
    BaseOLD* getOLD(int_t);

    unsigned long int size() const { return m_descriptorsOLD.size(); }

    void add(Mesh*);
    void add(Material*);

    [[warning("replace this with const")]]
    ceti::Collector<Mesh>& mesh() { return m_mesh; }
    const ceti::Collector<Mesh>& mesh() const { return m_mesh; }

    [[warning("replace this with const")]]
    ceti::Collector<Material>& material() { return m_material; }
    const ceti::Collector<Material>& material() const { return m_material; }

    void generate();
    [[warning("remove")]]
    int_t nextId() const;

private:
    ceti::Collector<Mesh> m_mesh;
    ceti::Collector<Material> m_material;

    std::map<int_t, Base*> m_descriptors;
    std::map<Type, std::vector<Base*>> m_descriptorsTypes;

    std::map<int_t, BaseOLD*> m_descriptorsOLD;
    std::map<int, std::vector<BaseOLD*>> m_descriptorsTypesOLD;

    void __clear();
    void __save();
    void __load();

    static IdGenerator m_idGenerator;
}; 

} // namespace descriptor
