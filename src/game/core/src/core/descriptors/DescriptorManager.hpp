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

#include <core/descriptors/Base.hpp>

#include <core/descriptors/GalaxyDescriptor.hpp>
#include <core/descriptors/SectorDescriptor.hpp>
#include <core/descriptors/StarsystemDescriptor.hpp>
#include <core/descriptors/StarDescriptor.hpp>
#include <core/descriptors/PlanetDescriptor.hpp>
#include <core/descriptors/AsteroidDescriptor.hpp>
#include <core/descriptors/VehicleDescriptor.hpp>

#include <core/item/equipment/Bak.hpp> // descriptor
#include <core/item/equipment/Drive.hpp> // descriptor
#include <core/item/equipment/Droid.hpp> // descriptor
#include <core/item/equipment/Grapple.hpp> // descriptor
#include <core/item/equipment/Lazer.hpp> // descriptor
#include <core/item/equipment/Protector.hpp> // descriptor
#include <core/item/equipment/Radar.hpp> // descriptor

#include <ceti/descriptor/Collector.hpp>
#include <ceti/descriptor/Mesh.hpp>
#include <ceti/descriptor/Texture.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <string>

namespace descriptor {

template<typename T>
class MManager {
public:
    MManager() {}
    ~MManager() {}

    void add(const T& descriptor) {
        std::cout<<"MManager add"<<std::endl<<descriptor.info()<<std::endl;
        const auto it = m_descriptors.find(descriptor.id());
        if (it == m_descriptors.end()) {
            m_descriptors.insert(std::make_pair(descriptor.id(), descriptor));
        } else {
            throw std::runtime_error("descriptor with that id already exist");
        }
    }

    const T& get(int_t id) const {
        std::cout<<"MManager get(descriptor.id="<<id<<")"<<std::endl;
        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            return it->second;
        } else {
            throw std::runtime_error("descriptor id doesn't exist");
        }
    }

    const T& random() const {
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
    std::map<int_t, T> m_descriptors;
};

class Manager
{
public:
    Manager();
    ~Manager();

    void add(const BaseOLD&);
    BaseOLD getRand(const Type&);
    BaseOLD get(int_t);

    unsigned long int size() const { return m_descriptors.size(); }

    void add(const Galaxy& galaxy) {
        m_galaxy.add(galaxy);
    }
    void add(const Sector& sector) {
        m_sector.add(sector);
    }
    void add(const Starsystem& starsystem) {
        m_starsystem.add(starsystem);
    }
    void add(const Star& star) {
        m_star.add(star);
    }
    void add(const Planet& planet) {
        m_planet.add(planet);
    }
    void add(const Asteroid& asteroid) {
        m_asteroid.add(asteroid);
    }
    void add(const Ship& ship) {
        m_ship.add(ship);
    }
    void add(const SpaceStation& spacestation) {
        m_spacestation.add(spacestation);
    }
    void add(const Satellite& satellite) {
        m_satellite.add(satellite);
    }
    void add(const item::Drive& drive) {
        m_drive.add(drive);
    }
    void add(const item::Bak& bak) {
        m_bak.add(bak);
    }
    void add(const item::Droid& droid) {
        m_droid.add(droid);
    }
    void add(const item::Grapple& grapple) {
        m_grapple.add(grapple);
    }
    void add(const item::Lazer& lazer) {
        m_lazer.add(lazer);
    }
    void add(const item::Protector& protector) {
        m_protector.add(protector);
    }
    void add(const item::Radar& radar) {
        m_radar.add(radar);
    }
    void add(Mesh* mesh) {
        m_mesh.add(mesh);
    }
    void add(Material* texture) {
        m_material.add(texture);
    }

    const MManager<Galaxy>& galaxy() const { return m_galaxy; }
    const MManager<Sector>& sector() const { return m_sector; }
    const MManager<Starsystem>& starsystem() const { return m_starsystem; }
    const MManager<Star>& star() const { return m_star; }
    const MManager<Planet>& planet() const { return m_planet; }
    const MManager<Asteroid>& asteroid() const { return m_asteroid; }
    const MManager<Ship>& ship() const { return m_ship; }
    const MManager<SpaceStation>& spacestation() const { return m_spacestation; }
    const MManager<Satellite>& satellite() const { return m_satellite; }
    const MManager<item::Drive>& drive() const { return m_drive; }
    const MManager<item::Bak>& bak() const { return m_bak; }
    const MManager<item::Droid>& droid() const { return m_droid; }
    const MManager<item::Grapple>& grapple() const { return m_grapple; }
    const MManager<item::Lazer>& lazer() const { return m_lazer; }
    const MManager<item::Protector>& protector() const { return m_protector; }
    const MManager<item::Radar>& radar() const { return m_radar; }

    [[warning("replace this with const")]]
    ceti::Collector<Mesh>& mesh() { return m_mesh; }
    const ceti::Collector<Mesh>& mesh() const { return m_mesh; }

    [[warning("replace this with const")]]
    ceti::Collector<Material>& material() { return m_material; }
    const ceti::Collector<Material>& material() const { return m_material; }

    void generate();

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
    MManager<item::Bak> m_bak;
    MManager<item::Drive> m_drive;
    MManager<item::Droid> m_droid;
    MManager<item::Grapple> m_grapple;
    MManager<item::Lazer> m_lazer;
    MManager<item::Protector> m_protector;
    MManager<item::Radar> m_radar;
    ceti::Collector<Mesh> m_mesh;
    ceti::Collector<Material> m_material;

    std::map<int_t, BaseOLD> m_descriptors;
    std::map<int, std::vector<BaseOLD>> m_descriptorsTypes;

    void __clear();
    void __save();
    void __load();
}; 

} // namespace descriptor
