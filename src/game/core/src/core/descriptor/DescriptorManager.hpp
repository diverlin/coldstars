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
#include <core/descriptor/StarDescriptor.hpp>
#include <core/descriptor/PlanetDescriptor.hpp>
#include <core/descriptor/AsteroidDescriptor.hpp>
#include <core/descriptor/VehicleDescriptor.hpp>
#include <core/descriptor/Container.hpp>

#include <core/descriptor/spaceobject/Ship.hpp>
#include <core/descriptor/spaceobject/Satellite.hpp>
#include <core/descriptor/spaceobject/SpaceStation.hpp>

#include <core/descriptor/item/equipment/ALL>

#include <ceti/descriptor/Collector.hpp>
#include <ceti/descriptor/Mesh.hpp>
#include <ceti/descriptor/Texture.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <string>

namespace descriptor {

class Ship;
class SpaceStation;
class Satellite;

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

    item::Scaner* randScaner() const;
    item::Drive* randDrive() const;
    item::Bak* randBak() const;
    item::Droid* randDroid() const;
    item::Grapple* randGrapple() const;
    item::Lazer* randLazer() const;
    item::Protector* randProtector() const;
    item::Radar* randRadar() const;
    item::Rocket* randRocket() const;

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
    BaseOLD* getRand(const Type&);
    BaseOLD* get(int_t);

    unsigned long int size() const { return m_descriptorsOLD.size(); }

    void add(Galaxy*);
    void add(Sector*);
    void add(Starsystem*);
    void add(Star*);
    void add(Planet*);
    void add(Asteroid*);
    void add(Ship*);
    void add(SpaceStation*);
    void add(Satellite*);
    void add(Container*);

    void add(Mesh*);
    void add(Material*);

    const MManager<Galaxy>& galaxy() const { return m_galaxy; }
    const MManager<Sector>& sector() const { return m_sector; }
    const MManager<Starsystem>& starsystem() const { return m_starsystem; }
    const MManager<Star>& star() const { return m_star; }
    const MManager<Planet>& planet() const { return m_planet; }
    const MManager<Asteroid>& asteroid() const { return m_asteroid; }
    const MManager<Ship>& ship() const { return m_ship; }
    const MManager<SpaceStation>& spacestation() const { return m_spacestation; }
    const MManager<Satellite>& satellite() const { return m_satellite; }

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
    MManager<Galaxy> m_galaxy;
    MManager<Sector> m_sector;
    MManager<Starsystem> m_starsystem;
    MManager<Star> m_star;
    MManager<Planet> m_planet;
    MManager<Asteroid> m_asteroid;
    MManager<Ship> m_ship;
    MManager<SpaceStation> m_spacestation;
    MManager<Satellite> m_satellite;
    MManager<Container> m_container;

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
