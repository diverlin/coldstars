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
#include <core/descriptor/item/equipment/ALL>
#include <core/descriptor/spaceobject/ALL>
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

IdGenerator Manager::m_idGenerator;

Manager&
Manager::get()
{
    static Manager instance;
    return instance;
}

Manager::Manager()
    :
      m_mesh(ceti::Collector<Mesh>(descriptor_meshes_fname))
    , m_material(ceti::Collector<Material>(descriptor_materials_fname))
{
    bool regenerate = true;
    if (ceti::filesystem::is_file_exists(descriptors_fname) && !regenerate) {
        __load();
    } /*else {
       generate();
    }*/
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
void Manager::add(Container* container) {
    m_container.add(container);
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
        const auto it = m_descriptorsOLD.find(id);
        if (it != m_descriptorsOLD.end()) {
            throw std::runtime_error("descriptorOLD with that id already exist");
        }
        m_descriptorsOLD.insert(std::make_pair(id, descr));
    }

    {
        const auto it = m_descriptorsTypesOLD.find(type);
        if (it != m_descriptorsTypesOLD.end()) {
            it->second.push_back(descr);
        } else {
            std::vector<BaseOLD*> vector;
            vector.push_back(descr);
            m_descriptorsTypesOLD[type] = vector;
        }
    }
}

void
Manager::reg(Base* descr)
{
    //std::cout<<"add descriptor with type"<<descriptor::typeStr((descriptor::Type)descriptor.type())<<std::endl;
    if (descr->id() == NONE) {
        descr->setId(m_idGenerator.nextId());
    }

    const int_t id = descr->id();
    descriptor::Type type = descr->type();

    {
        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            assert(false);
            throw std::runtime_error("descriptor with that id already exist");
        }
        m_descriptors.insert(std::make_pair(id, descr));
    }

    {
        const auto it = m_descriptorsTypes.find(type);
        if (it != m_descriptorsTypes.end()) {
            it->second.push_back(descr);
        } else {
            std::vector<Base*> vector;
            vector.push_back(descr);
            m_descriptorsTypes[type] = vector;
        }
    }
}

Base*
Manager::get(int_t id) const
{
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        return it->second;
    }
    assert(false);
    throw std::runtime_error("Base* Manager::get descriptor id doesn't exist");
}

BaseOLD*
Manager::getRandOLD(const Type& type)
{
    const auto it = m_descriptorsTypesOLD.find(int(type));
    if (it != m_descriptorsTypesOLD.end()) {
        const std::vector<BaseOLD*> descriptors = it->second;
        return meti::getRand(descriptors);
    }
    throw std::runtime_error("descriptor type doesn't contain any descriptors, " + to_string(type));
}

BaseOLD*
Manager::getOLD(int_t id)
{
    const auto it = m_descriptorsOLD.find(id);
    if (it != m_descriptorsOLD.end()) {
        return it->second;
    }
    throw std::runtime_error("BaseOLD* Manager::get descriptor id doesn't exist");
}

Base*
Manager::rand(Type type) const
{
    std::map<Type, std::vector<Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it == m_descriptorsTypes.end()) {
        throw std::runtime_error("Base* Manager::randdescriptor type = " + to_string(type) + " doesn't exist");
    }
    Base* descr = meti::getRand(it->second);
    assert(descr);
    return descr;
}

Star*
Manager::randStar() const
{
    Star* descr = static_cast<Star*>(rand(Type::STAR));
    assert(descr);
    return descr;
}
Planet*
Manager::randPlanet() const
{
    Planet* descr = static_cast<Planet*>(rand(Type::PLANET));
    assert(descr);
    return descr;
}
Asteroid*
Manager::randAsteroid() const
{
    Asteroid* descr = static_cast<Asteroid*>(rand(Type::ASTEROID));
    assert(descr);
    return descr;
}

Ship*
Manager::randShip() const
{
    Ship* descr = static_cast<Ship*>(rand(Type::SHIP));
    assert(descr);
    return descr;
}
Satellite*
Manager::randSatellite() const
{
    Satellite* descr = static_cast<Satellite*>(rand(Type::SATELLITE));
    assert(descr);
    return descr;
}
SpaceStation*
Manager::randSpaceStation() const
{
    SpaceStation* descr = static_cast<SpaceStation*>(rand(Type::SPACESTATION));
    assert(descr);
    return descr;
}

item::Scaner*
Manager::randScaner() const
{
    item::Scaner* descr = static_cast<item::Scaner*>(rand(Type::SCANER_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Drive*
Manager::randDrive() const
{
    item::Drive* descr = static_cast<item::Drive*>(rand(Type::DRIVE_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Bak*
Manager::randBak() const
{
    item::Bak* descr = static_cast<item::Bak*>(rand(Type::BAK_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Droid*
Manager::randDroid() const
{
    item::Droid* descr = static_cast<item::Droid*>(rand(Type::DROID_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Grapple*
Manager::randGrapple() const
{
    item::Grapple* descr = static_cast<item::Grapple*>(rand(Type::GRAPPLE_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Lazer*
Manager::randLazer() const
{
    item::Lazer* descr = static_cast<item::Lazer*>(rand(Type::LAZER_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Protector*
Manager::randProtector() const
{
    item::Protector* descr = static_cast<item::Protector*>(rand(Type::PROTECTOR_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Radar*
Manager::randRadar() const
{
    item::Radar* descr = static_cast<item::Radar*>(rand(Type::RADAR_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Rocket*
Manager::randRocket() const
{
    item::Rocket* descr = static_cast<item::Rocket*>(rand(Type::ROCKET_EQUIPMENT));
    assert(descr);
    return descr;
}

Star*
Manager::star(int_t id) const
{
    Star* descr = static_cast<Star*>(get(id));
    assert(descr);
    return descr;
}
Planet*
Manager::planet(int_t id) const
{
    Planet* descr = static_cast<Planet*>(get(id));
    assert(descr);
    return descr;
}
Asteroid*
Manager::asteroid(int_t id) const
{
    Asteroid* descr = static_cast<Asteroid*>(get(id));
    assert(descr);
    return descr;
}

Ship*
Manager::ship(int_t id) const
{
    Ship* descr = static_cast<Ship*>(get(id));
    assert(descr);
    return descr;
}
Satellite*
Manager::satellite(int_t id) const
{
    Satellite* descr = static_cast<Satellite*>(get(id));
    assert(descr);
    return descr;
}
SpaceStation*
Manager::spaceStation(int_t id) const
{
    SpaceStation* descr = static_cast<SpaceStation*>(get(id));
    assert(descr);
    return descr;
}

item::Scaner*
Manager::scaner(int_t id) const
{
    item::Scaner* descr = static_cast<item::Scaner*>(get(id));
    assert(descr);
    return descr;
}

item::Drive*
Manager::drive(int_t id) const
{
    item::Drive* descr = static_cast<item::Drive*>(get(id));
    assert(descr);
    return descr;
}
item::Bak*
Manager::bak(int_t id) const
{
    item::Bak* descr = static_cast<item::Bak*>(get(id));
    assert(descr);
    return descr;
}

item::Droid*
Manager::droid(int_t id) const
{
    Base* base = get(id);
    item::Droid* descr = static_cast<item::Droid*>(base);
    assert(descr);
    return descr;
}

item::Grapple*
Manager::grapple(int_t id) const
{
    item::Grapple* descr = static_cast<item::Grapple*>(get(id));
    assert(descr);
    return descr;
}

item::Lazer*
Manager::lazer(int_t id) const
{
    item::Lazer* descr = static_cast<item::Lazer*>(get(id));
    assert(descr);
    return descr;
}

item::Protector*
Manager::protector(int_t id) const
{
    item::Protector* descr = static_cast<item::Protector*>(get(id));
    assert(descr);
    return descr;
}

item::Radar*
Manager::radar(int_t id) const
{
    item::Radar* descr = static_cast<item::Radar*>(get(id));
    assert(descr);
    return descr;
}

item::Rocket*
Manager::rocket(int_t id) const
{
    item::Rocket* descr = static_cast<item::Rocket*>(get(id));
    assert(descr);
    return descr;
}

void
Manager::__save()
{
    std::fstream filestream;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        for(const auto& lists: m_descriptorsTypesOLD) {
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
    m_descriptorsOLD.clear();
    m_descriptorsTypesOLD.clear();
}

int_t
Manager::nextId() const
{
    return m_idGenerator.nextId();
}

void
Manager::generate()
{
    ceti::filesystem::create_file(descriptors_fname);

    __clear();

    int base = 1;
    int num = base * 20;
    // items
    for(int i=0; i<num; ++i) {
        item::genBak();
        item::genDrive();
        item::genDroid();
        item::genGrapple();
        item::genProtector();
        item::genRadar();
        item::genScaner();
        item::genLazer();
        item::genRocket();
        add(getNewBomb());
    }

    num = base * 10;
    // spaceobjects
    for(int i=0; i<num; ++i) {
        genShip();
        genSpaceStation();
        genSatellite();
        genStar();
        genPlanet();
        genAsteroid();
        //add(getNewContainer());
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
