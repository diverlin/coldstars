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

#include "DescriptorManager.hpp"
#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/common/Global.hpp>

#include <meti/RandUtils.hpp>

#include <ceti/FsUtils.hpp>

#include <fstream>

namespace descriptor {

namespace {
const std::string descriptors_fname = "descriptors.txt";
const std::string descriptor_meshes_fname = "mesh_descriptors.txt";
const std::string descriptor_materials_fname = "material_descriptors.txt";
} // namespace

Manager::Manager()
    :
      m_mesh(ceti::Collector<Mesh>(descriptor_meshes_fname))
    , m_material(ceti::Collector<Material>(descriptor_materials_fname))
{
    bool regenerate = true;
    if (ceti::filesystem::is_file_exists(descriptors_fname) && !regenerate) {
        __load();
    }
}

void Manager::add(Galaxy* galaxy) {
    m_galaxy.add(galaxy);
}
void Manager::add(Sector* sector) {
    m_sector.add(sector);
}
void Manager::add(Starsystem* starsystem) {
    m_starsystem.add(starsystem);
}
void Manager::add(Star* star) {
    m_star.add(star);
}
void Manager::add(Planet* planet) {
    m_planet.add(planet);
}
void Manager::add(Asteroid* asteroid) {
    m_asteroid.add(asteroid);
}
void Manager::add(Ship* ship) {
    m_ship.add(ship);
}
void Manager::add(SpaceStation* spacestation) {
    m_spacestation.add(spacestation);
}
void Manager::add( Satellite* satellite) {
    m_satellite.add(satellite);
}
void Manager::add(item::Drive* drive) {
    m_drive.add(drive);
}
void Manager::add(item::Bak* bak) {
    m_bak.add(bak);
}
void Manager::add(item::Droid* droid) {
    m_droid.add(droid);
}
void Manager::add(item::Grapple* grapple) {
    m_grapple.add(grapple);
}
void Manager::add(item::Lazer* lazer) {
    m_lazer.add(lazer);
}
void Manager::add(item::Protector* protector) {
    m_protector.add(protector);
}
void Manager::add(item::Radar* radar) {
    m_radar.add(radar);
}
void Manager::add(item::Rocket* rocket) {
    m_rocket.add(rocket);
}
void Manager::add(item::Scaner* scaner) {
    m_scaner.add(scaner);
}
void Manager::add(Mesh* mesh) {
    m_mesh.add(mesh);
}
void Manager::add(Material* texture) {
    m_material.add(texture);
}


void
Manager::add(BaseOLD* descr)
{
    //std::cout<<"add descriptor with type"<<descriptor::typeStr((descriptor::Type)descriptor.type())<<std::endl;
    const int_t id = descr->id();
    int type = descr->type();

    {
        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            throw std::runtime_error("descriptor with that id already exist");
        }
        m_descriptors.insert(std::make_pair(id, descr));
    }

    {
        const auto it = m_descriptorsTypes.find(type);
        if (it != m_descriptorsTypes.end()) {
            it->second.push_back(descr);
        } else {
            std::vector<BaseOLD*> vector;
            vector.push_back(descr);
            m_descriptorsTypes[type] = vector;
        }
    }
}

BaseOLD*
Manager::getRand(const Type& type)
{
    const auto it = m_descriptorsTypes.find(int(type));
    if (it != m_descriptorsTypes.end()) {
        const std::vector<BaseOLD*> descriptors = it->second;
        return meti::getRand(descriptors);
    }
    throw std::runtime_error("descriptor type doesn't contain any descriptors, " + typeStr(type));
}

BaseOLD*
Manager::get(int_t id)
{
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        return it->second;
    }
    throw std::runtime_error("descriptor id doesn't exist");
}

void
Manager::__save()
{
    std::fstream filestream;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        for(const auto& lists: m_descriptorsTypes) {
            const auto& list = lists.second;
            for(BaseOLD* descr: list) {
                filestream<<descr->data()<<std::endl;
            }
        }
    } else {
        throw std::runtime_error("not able to open file="+descriptors_fname);
    }
    filestream.close();
}

void
Manager::__load()
{
    __clear();

    std::fstream filestream;
    std::string line;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            if (!line.empty()) {
                BaseOLD* descr = new BaseOLD(line);
                add(descr);
            }
        }
    }
    filestream.close();
}

void
Manager::__clear()
{
    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Manager::generate()
{
    ceti::filesystem::create_file(descriptors_fname);

    __clear();

    int base = 1;
    int num = base * 20;
    for(int i=0; i<num; ++i) {
        // items
        add(item::getNewBak());
        add(item::getNewDrive());
        add(item::getNewDroid());
        add(item::getNewGrapple());
        add(item::getNewProtector());
        add(item::getNewRadar());
        add(item::getNewScaner());
        add(getNewBomb());
    }

    num = base * 10;
    for(int i=0; i<num; ++i) {
        // spaceobjects
        add(getNewShip());
        add(getNewSpaceStation());
        add(getNewSatellite());
        add(getNewStar());
        add(getNewPlanet());
        add(getNewAsteroid());
        add(getNewContainer());
    }

    // world
    num = base * 10;
    for(int i=0; i<num; ++i) {
        add(getNewStarsystem());
    }

    num = base * 4;
    for(int i=0; i<num; ++i) {
        add(getNewSector(m_starsystem.idList()));
    }

    num = base * 1;
    for(int i=0; i<num; ++i) {
        add(getNewGalaxy(m_sector.idList()));
    }

    __save();
}

} // namespace descriptor
