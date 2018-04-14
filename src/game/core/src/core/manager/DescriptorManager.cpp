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
#include <core/generator/DescriptorGenerator.hpp>

#include <core/descriptor/item/ALL>
#include <core/descriptor/spaceobject/ALL>
#include <core/descriptor/dock/ALL>
#include <core/descriptor/part/Turrel.hpp>
#include <core/descriptor/world/ALL>
#include <core/descriptor/pilot/Npc.hpp>

#include <core/descriptor/Mesh.hpp>
#include <core/descriptor/Texture.hpp>

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


Descriptors::Descriptors()
    :
      m_meshes(new Collector<Mesh>(""))
    , m_materials(new Collector<Material>(""))
{
    bool regenerate = true;
    if (ceti::filesystem::is_file_exists(descriptors_fname) && !regenerate) {
        __load();
    } /*else {
       generate();
    }*/

#ifdef USE_FAILBACK_RESOURCES
    __resolveId(m_meshes->failback());
    __resolveId(m_materials->failback());
#endif // USE_FAILBACK_RESOURCES
}

void
Descriptors::add(Base* descr)
{
    __resolveId(descr);

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

void
Descriptors::add(Mesh* descr)
{
    __resolveId(descr);
    m_meshes->add(descr);
}

void
Descriptors::add(Material* descr)
{
    __resolveId(descr);
    m_materials->add(descr);
}

bool
Descriptors::hasType(Type type) const
{
    std::map<Type, std::vector<Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    return (it != m_descriptorsTypes.end());
}

Base*
Descriptors::get(int_t id) const
{
    assert(id != NONE);
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        return it->second;
    }
    assert(false);
    throw std::runtime_error("Base* Manager::get descriptor id doesn't exist");
}

Base*
Descriptors::rand(Type type) const
{
    std::map<Type, std::vector<Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it == m_descriptorsTypes.end()) {
        throw std::runtime_error("Base* Manager::randdescriptor type = " + to_string(type) + " doesn't exist");
    }
    Base* descr = meti::rand::get_element_or_die(it->second);
    assert(descr);
    return descr;
}

Galaxy*
Descriptors::randGalaxy() const
{
    Galaxy* descr = static_cast<Galaxy*>(rand(Type::GALAXY));
    assert(descr);
    return descr;
}
Sector*
Descriptors::randSector() const
{
    Sector* descr = static_cast<Sector*>(rand(Type::SECTOR));
    assert(descr);
    return descr;
}
StarSystem*
Descriptors::randStarSystem() const
{
    StarSystem* descr = static_cast<StarSystem*>(rand(Type::STARSYSTEM));
    assert(descr);
    return descr;
}
HyperSpace*
Descriptors::randHyperSpace() const
{
    HyperSpace* descr = static_cast<HyperSpace*>(rand(Type::HYPERSPACE));
    assert(descr);
    return descr;
}

Star*
Descriptors::randStar() const
{
    Star* descr = static_cast<Star*>(rand(Type::STAR));
    assert(descr);
    return descr;
}
Planet*
Descriptors::randPlanet() const
{
    Planet* descr = static_cast<Planet*>(rand(Type::PLANET));
    assert(descr);
    return descr;
}
WormHole*
Descriptors::randWormHole() const
{
    WormHole* descr = static_cast<WormHole*>(rand(Type::WORMHOLE));
    assert(descr);
    return descr;
}
Asteroid*
Descriptors::randAsteroid() const
{
    Asteroid* descr = static_cast<Asteroid*>(rand(Type::ASTEROID));
    assert(descr);
    return descr;
}
Container*
Descriptors::randContainer() const
{
    Container* descr = static_cast<Container*>(rand(Type::CONTAINER));
    assert(descr);
    return descr;
}
Bullet*
Descriptors::randBullet() const
{
    Bullet* descr = static_cast<Bullet*>(rand(Type::BULLET));
    assert(descr);
    return descr;
}

Npc*
Descriptors::randNpc() const
{
    Npc* descr = static_cast<Npc*>(rand(Type::NPC));
    assert(descr);
    return descr;
}

Ship*
Descriptors::randShip() const
{
    Ship* descr = static_cast<Ship*>(rand(Type::SHIP));
    assert(descr);
    return descr;
}
Satellite*
Descriptors::randSatellite() const
{
    Satellite* descr = static_cast<Satellite*>(rand(Type::SATELLITE));
    assert(descr);
    return descr;
}
SpaceStation*
Descriptors::randSpaceStation() const
{
    SpaceStation* descr = static_cast<SpaceStation*>(rand(Type::SPACESTATION));
    assert(descr);
    return descr;
}

// dock
Kosmoport*
Descriptors::randKosmoport() const
{
    Kosmoport* descr = static_cast<Kosmoport*>(rand(Type::KOSMOPORT));
    assert(descr);
    return descr;
}
NatureLand*
Descriptors::randNatureLand() const
{
    NatureLand* descr = static_cast<NatureLand*>(rand(Type::NATURELAND));
    assert(descr);
    return descr;
}
Angar*
Descriptors::randAngar() const
{
    Angar* descr = static_cast<Angar*>(rand(Type::ANGAR));
    assert(descr);
    return descr;
}
Store*
Descriptors::randStore() const
{
    Store* descr = static_cast<Store*>(rand(Type::STORE));
    assert(descr);
    return descr;
}
Shop*
Descriptors::randShop() const
{
    Shop* descr = static_cast<Shop*>(rand(Type::SHOP));
    assert(descr);
    return descr;
}
Goverment*
Descriptors::randGoverment() const
{
    Goverment* descr = static_cast<Goverment*>(rand(Type::GOVERMENT));
    assert(descr);
    return descr;
}

// items
item::Scaner*
Descriptors::randScaner() const
{
    item::Scaner* descr = static_cast<item::Scaner*>(rand(Type::SCANER_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Drive*
Descriptors::randDrive() const
{
    item::Drive* descr = static_cast<item::Drive*>(rand(Type::DRIVE_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Bak*
Descriptors::randBak() const
{
    item::Bak* descr = static_cast<item::Bak*>(rand(Type::BAK_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Droid*
Descriptors::randDroid() const
{
    item::Droid* descr = static_cast<item::Droid*>(rand(Type::DROID_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Grapple*
Descriptors::randGrapple() const
{
    item::Grapple* descr = static_cast<item::Grapple*>(rand(Type::GRAPPLE_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Lazer*
Descriptors::randLazer() const
{
    item::Lazer* descr = static_cast<item::Lazer*>(rand(Type::LAZER_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Protector*
Descriptors::randProtector() const
{
    item::Protector* descr = static_cast<item::Protector*>(rand(Type::PROTECTOR_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Radar*
Descriptors::randRadar() const
{
    item::Radar* descr = static_cast<item::Radar*>(rand(Type::RADAR_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Rocket*
Descriptors::randRocket() const
{
    item::Rocket* descr = static_cast<item::Rocket*>(rand(Type::ROCKET_EQUIPMENT));
    assert(descr);
    return descr;
}

item::Goods*
Descriptors::randGoods() const
{
    item::Goods* descriptor = static_cast<item::Goods*>(rand(Type::GOODS));
    assert(descriptor);
    return descriptor;
}

// parts
Turrel*
Descriptors::randTurrel() const
{
    Turrel* descr = static_cast<Turrel*>(rand(Type::TURREL));
    assert(descr);
    return descr;
}

Galaxy*
Descriptors::galaxy(int_t id) const
{
    Galaxy* descr = static_cast<Galaxy*>(get(id));
    assert(descr);
    return descr;
}
Sector*
Descriptors::sector(int_t id) const
{
    Sector* descr = static_cast<Sector*>(get(id));
    assert(descr);
    return descr;
}
StarSystem*
Descriptors::starSystem(int_t id) const
{
    StarSystem* descr = static_cast<StarSystem*>(get(id));
    assert(descr);
    return descr;
}
HyperSpace*
Descriptors::hyperSpace(int_t id) const
{
    HyperSpace* descr = static_cast<HyperSpace*>(get(id));
    assert(descr);
    return descr;
}

Star*
Descriptors::star(int_t id) const
{
    Star* descr = static_cast<Star*>(get(id));
    assert(descr);
    return descr;
}
Planet*
Descriptors::planet(int_t id) const
{
    Planet* descr = static_cast<Planet*>(get(id));
    assert(descr);
    return descr;
}
WormHole*
Descriptors::wormHole(int_t id) const
{
    WormHole* descr = static_cast<WormHole*>(get(id));
    assert(descr);
    return descr;
}
Asteroid*
Descriptors::asteroid(int_t id) const
{
    Asteroid* descr = static_cast<Asteroid*>(get(id));
    assert(descr);
    return descr;
}
Container*
Descriptors::container(int_t id) const
{
    Container* descr = static_cast<Container*>(get(id));
    assert(descr);
    return descr;
}
Bullet*
Descriptors::bullet(int_t id) const
{
    Bullet* descr = static_cast<Bullet*>(get(id));
    assert(descr);
    return descr;
}

Npc*
Descriptors::npc(int_t id) const
{
    Npc* descr = static_cast<Npc*>(get(id));
    assert(descr);
    return descr;
}

Ship*
Descriptors::ship(int_t id) const
{
    Ship* descr = static_cast<Ship*>(get(id));
    assert(descr);
    return descr;
}
Satellite*
Descriptors::satellite(int_t id) const
{
    Satellite* descr = static_cast<Satellite*>(get(id));
    assert(descr);
    return descr;
}
SpaceStation*
Descriptors::spaceStation(int_t id) const
{
    SpaceStation* descr = static_cast<SpaceStation*>(get(id));
    assert(descr);
    return descr;
}

// dock
Kosmoport*
Descriptors::kosmoport(int_t id) const
{
    Kosmoport* descr = static_cast<Kosmoport*>(get(id));
    assert(descr);
    return descr;
}
NatureLand*
Descriptors::natureLand(int_t id) const
{
    NatureLand* descr = static_cast<NatureLand*>(get(id));
    assert(descr);
    return descr;
}
Angar*
Descriptors::angar(int_t id) const
{
    Angar* descr = static_cast<Angar*>(get(id));
    assert(descr);
    return descr;
}
Store*
Descriptors::store(int_t id) const
{
    Store* descr = static_cast<Store*>(get(id));
    assert(descr);
    return descr;
}
Shop*
Descriptors::shop(int_t id) const
{
    Shop* descr = static_cast<Shop*>(get(id));
    assert(descr);
    return descr;
}
Goverment*
Descriptors::goverment(int_t id) const
{
    Goverment* descr = static_cast<Goverment*>(get(id));
    assert(descr);
    return descr;
}


// items
item::Scaner*
Descriptors::scaner(int_t id) const
{
    item::Scaner* descr = static_cast<item::Scaner*>(get(id));
    assert(descr);
    return descr;
}

item::Drive*
Descriptors::drive(int_t id) const
{
    item::Drive* descr = static_cast<item::Drive*>(get(id));
    assert(descr);
    return descr;
}
item::Bak*
Descriptors::bak(int_t id) const
{
    item::Bak* descr = static_cast<item::Bak*>(get(id));
    assert(descr);
    return descr;
}

item::Droid*
Descriptors::droid(int_t id) const
{
    Base* base = get(id);
    item::Droid* descr = static_cast<item::Droid*>(base);
    assert(descr);
    return descr;
}

item::Grapple*
Descriptors::grapple(int_t id) const
{
    item::Grapple* descr = static_cast<item::Grapple*>(get(id));
    assert(descr);
    return descr;
}

item::Lazer*
Descriptors::lazer(int_t id) const
{
    item::Lazer* descr = static_cast<item::Lazer*>(get(id));
    assert(descr);
    return descr;
}

item::Protector*
Descriptors::protector(int_t id) const
{
    item::Protector* descr = static_cast<item::Protector*>(get(id));
    assert(descr);
    return descr;
}

item::Radar*
Descriptors::radar(int_t id) const
{
    item::Radar* descr = static_cast<item::Radar*>(get(id));
    assert(descr);
    return descr;
}

item::Rocket*
Descriptors::rocket(int_t id) const
{
    item::Rocket* descr = static_cast<item::Rocket*>(get(id));
    assert(descr);
    return descr;
}

// other
item::Goods*
Descriptors::goods(int_t id) const
{
    item::Goods* descriptor = static_cast<item::Goods*>(get(id));
    assert(descriptor);
    return descriptor;
}


Mesh*
Descriptors::mesh(int_t id) const
{
    Mesh* mesh = m_meshes->get(id);
    assert(mesh);
    return mesh;
}

Material*
Descriptors::material(int_t id) const
{
    Material* material = m_materials->get(id);
    assert(material);
    return material;
}

Mesh*
Descriptors::randMesh(mesh::Type type) const
{
    Mesh* mesh = m_meshes->random(int_t(type));
    assert(mesh);
    return mesh;
}

Material*
Descriptors::randMaterial(texture::Type type) const
{
    Material* material = m_materials->random(int_t(type));
    assert(material);
    return material;
}

void
Descriptors::__save()
{
//    assert(false);
//    std::fstream filestream;
//    filestream.open(descriptors_fname);
//    if(filestream.is_open()) {
//        for(const auto& lists: m_descriptorsTypesOLD) {
//            const auto& list = lists.second;
//            for(BaseOLD* descr: list) {
//                filestream<<descr->data()<<std::endl;
//            }
//        }
//    } else {
//        throw std::runtime_error("not able to open file="+descriptors_fname);
//    }
//    filestream.close();
}

void
Descriptors::__load()
{
    assert(false);
//    __clear();

//    std::fstream filestream;
//    std::string line;
//    filestream.open(descriptors_fname);
//    if(filestream.is_open()) {
//        while(std::getline(filestream, line)) {
//            if (!line.empty()) {
//                BaseOLD* descr = new BaseOLD(line);
//                add(descr);
//            }
//        }
//    }
//    filestream.close();
}

void
Descriptors::__clear()
{
    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Descriptors::generate()
{
    ceti::filesystem::create_file(descriptors_fname);

    __clear();

    for (int i=0; i<5; ++i) {
        genBullet(); // nested for rocket, so must be generated firstly
    }
    item::genGoods();

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
//        add(getNewBomb());
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
        genContainer();
    }

    // world
    num = base * 10;
    for(int i=0; i<num; ++i) {
        genStarSystem();
    }

    // npc
    num = 5;
    for(int i=0; i<num; ++i) {
        genNpc();
    }

    num = 4;
    for(int i=0; i<num; ++i) {
        const auto& ids = __ids(Type::STARSYSTEM).random(5);
        genSector(ids);
    }

    const auto& ids = __ids(Type::SECTOR).random(2);
    genGalaxy(ids);

    __save();
}

void
Descriptors::clear()
{
    if (m_meshes) {
        assert(false);
        //m_meshes->clear();
        m_meshes = nullptr;
    }
    if (m_materials) {
        assert(false);
        //m_materials->clear();
        m_materials = nullptr;
    }

    for (std::map<int_t, Base*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it) {
        delete it->second;
    }

    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Descriptors::__resolveId(Base* descr) {

    if (descr->id() == NONE) {
        descr->setId(m_idGenerator.nextId());
    }
}

void
Descriptors::__resolveId(ceti::descriptor::Base* descr) {
    if (descr->id() == NONE) {
        descr->setId(m_idGenerator.nextId());
    }
}

ceti::pack<int_t>
Descriptors::__ids(Type type) const
{
    ceti::pack<int_t> result;

    std::map<Type, std::vector<Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it != m_descriptorsTypes.end()) {
        const std::vector<Base*>& descriptors = it->second;
        for (Base* descr: descriptors) {
            result.add(descr->id());
        }
    }
    return result;
}

} // namespace descriptor
