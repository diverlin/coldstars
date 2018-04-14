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

namespace core {
namespace manager {

namespace {
const std::string descriptors_fname = "descriptors.txt";
const std::string descriptor_meshes_fname = "mesh_descriptors.txt";
const std::string descriptor_materials_fname = "material_descriptors.txt";
} // namespace


Descriptors::Descriptors()
    :
      m_meshes(new Collector<descriptor::Mesh>(""))
    , m_materials(new Collector<descriptor::Material>(""))
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
Descriptors::add(descriptor::Base* descr)
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
            std::vector<descriptor::Base*> vector;
            vector.push_back(descr);
            m_descriptorsTypes[type] = vector;
        }
    }
}

void
Descriptors::add(descriptor::Mesh* descr)
{
    __resolveId(descr);
    m_meshes->add(descr);
}

void
Descriptors::add(descriptor::Material* descr)
{
    __resolveId(descr);
    m_materials->add(descr);
}

bool
Descriptors::hasType(descriptor::Type type) const
{
    std::map<descriptor::Type, std::vector<descriptor::Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    return (it != m_descriptorsTypes.end());
}

descriptor::Base*
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

descriptor::Base*
Descriptors::rand(descriptor::Type type) const
{
    std::map<descriptor::Type, std::vector<descriptor::Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it == m_descriptorsTypes.end()) {
        throw std::runtime_error("Base* Manager::randdescriptor type = " + to_string(type) + " doesn't exist");
    }
    descriptor::Base* descr = meti::rand::get_element_or_die(it->second);
    assert(descr);
    return descr;
}

descriptor::Galaxy*
Descriptors::randGalaxy() const
{
    descriptor::Galaxy* descr = static_cast<descriptor::Galaxy*>(rand(descriptor::Type::GALAXY));
    assert(descr);
    return descr;
}
descriptor::Sector*
Descriptors::randSector() const
{
    descriptor::Sector* descr = static_cast<descriptor::Sector*>(rand(descriptor::Type::SECTOR));
    assert(descr);
    return descr;
}
descriptor::StarSystem*
Descriptors::randStarSystem() const
{
    descriptor::StarSystem* descr = static_cast<descriptor::StarSystem*>(rand(descriptor::Type::STARSYSTEM));
    assert(descr);
    return descr;
}
descriptor::HyperSpace*
Descriptors::randHyperSpace() const
{
    descriptor::HyperSpace* descr = static_cast<descriptor::HyperSpace*>(rand(descriptor::Type::HYPERSPACE));
    assert(descr);
    return descr;
}

descriptor::Star*
Descriptors::randStar() const
{
    descriptor::Star* descr = static_cast<descriptor::Star*>(rand(descriptor::Type::STAR));
    assert(descr);
    return descr;
}
descriptor::Planet*
Descriptors::randPlanet() const
{
    descriptor::Planet* descr = static_cast<descriptor::Planet*>(rand(descriptor::Type::PLANET));
    assert(descr);
    return descr;
}
descriptor::WormHole*
Descriptors::randWormHole() const
{
    descriptor::WormHole* descr = static_cast<descriptor::WormHole*>(rand(descriptor::Type::WORMHOLE));
    assert(descr);
    return descr;
}
descriptor::Asteroid*
Descriptors::randAsteroid() const
{
    descriptor::Asteroid* descr = static_cast<descriptor::Asteroid*>(rand(descriptor::Type::ASTEROID));
    assert(descr);
    return descr;
}
descriptor::Container*
Descriptors::randContainer() const
{
    descriptor::Container* descr = static_cast<descriptor::Container*>(rand(descriptor::Type::CONTAINER));
    assert(descr);
    return descr;
}
descriptor::Bullet*
Descriptors::randBullet() const
{
    descriptor::Bullet* descr = static_cast<descriptor::Bullet*>(rand(descriptor::Type::BULLET));
    assert(descr);
    return descr;
}

descriptor::Npc*
Descriptors::randNpc() const
{
    descriptor::Npc* descr = static_cast<descriptor::Npc*>(rand(descriptor::Type::NPC));
    assert(descr);
    return descr;
}

descriptor::Ship*
Descriptors::randShip() const
{
    descriptor::Ship* descr = static_cast<descriptor::Ship*>(rand(descriptor::Type::SHIP));
    assert(descr);
    return descr;
}
descriptor::Satellite*
Descriptors::randSatellite() const
{
    descriptor::Satellite* descr = static_cast<descriptor::Satellite*>(rand(descriptor::Type::SATELLITE));
    assert(descr);
    return descr;
}
descriptor::SpaceStation*
Descriptors::randSpaceStation() const
{
    descriptor::SpaceStation* descr = static_cast<descriptor::SpaceStation*>(rand(descriptor::Type::SPACESTATION));
    assert(descr);
    return descr;
}

// dock
descriptor::Kosmoport*
Descriptors::randKosmoport() const
{
    descriptor::Kosmoport* descr = static_cast<descriptor::Kosmoport*>(rand(descriptor::Type::KOSMOPORT));
    assert(descr);
    return descr;
}
descriptor::NatureLand*
Descriptors::randNatureLand() const
{
    descriptor::NatureLand* descr = static_cast<descriptor::NatureLand*>(rand(descriptor::Type::NATURELAND));
    assert(descr);
    return descr;
}
descriptor::Angar*
Descriptors::randAngar() const
{
    descriptor::Angar* descr = static_cast<descriptor::Angar*>(rand(descriptor::Type::ANGAR));
    assert(descr);
    return descr;
}
descriptor::Store*
Descriptors::randStore() const
{
    descriptor::Store* descr = static_cast<descriptor::Store*>(rand(descriptor::Type::STORE));
    assert(descr);
    return descr;
}
descriptor::Shop*
Descriptors::randShop() const
{
    descriptor::Shop* descr = static_cast<descriptor::Shop*>(rand(descriptor::Type::SHOP));
    assert(descr);
    return descr;
}
descriptor::Goverment*
Descriptors::randGoverment() const
{
    descriptor::Goverment* descr = static_cast<descriptor::Goverment*>(rand(descriptor::Type::GOVERMENT));
    assert(descr);
    return descr;
}

// items
descriptor::item::Scaner*
Descriptors::randScaner() const
{
    descriptor::item::Scaner* descr = static_cast<descriptor::item::Scaner*>(rand(descriptor::Type::SCANER_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Drive*
Descriptors::randDrive() const
{
    descriptor::item::Drive* descr = static_cast<descriptor::item::Drive*>(rand(descriptor::Type::DRIVE_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Bak*
Descriptors::randBak() const
{
    descriptor::item::Bak* descr = static_cast<descriptor::item::Bak*>(rand(descriptor::Type::BAK_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Droid*
Descriptors::randDroid() const
{
    descriptor::item::Droid* descr = static_cast<descriptor::item::Droid*>(rand(descriptor::Type::DROID_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Grapple*
Descriptors::randGrapple() const
{
    descriptor::item::Grapple* descr = static_cast<descriptor::item::Grapple*>(rand(descriptor::Type::GRAPPLE_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Lazer*
Descriptors::randLazer() const
{
    descriptor::item::Lazer* descr = static_cast<descriptor::item::Lazer*>(rand(descriptor::Type::LAZER_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Protector*
Descriptors::randProtector() const
{
    descriptor::item::Protector* descr = static_cast<descriptor::item::Protector*>(rand(descriptor::Type::PROTECTOR_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Radar*
Descriptors::randRadar() const
{
    descriptor::item::Radar* descr = static_cast<descriptor::item::Radar*>(rand(descriptor::Type::RADAR_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Rocket*
Descriptors::randRocket() const
{
    descriptor::item::Rocket* descr = static_cast<descriptor::item::Rocket*>(rand(descriptor::Type::ROCKET_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::item::Goods*
Descriptors::randGoods() const
{
    descriptor::item::Goods* descriptor = static_cast<descriptor::item::Goods*>(rand(descriptor::Type::GOODS));
    assert(descriptor);
    return descriptor;
}

// parts
descriptor::Turrel*
Descriptors::randTurrel() const
{
    descriptor::Turrel* descr = static_cast<descriptor::Turrel*>(rand(descriptor::Type::TURREL));
    assert(descr);
    return descr;
}

descriptor::Galaxy*
Descriptors::galaxy(int_t id) const
{
    descriptor::Galaxy* descr = static_cast<descriptor::Galaxy*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Sector*
Descriptors::sector(int_t id) const
{
    descriptor::Sector* descr = static_cast<descriptor::Sector*>(get(id));
    assert(descr);
    return descr;
}
descriptor::StarSystem*
Descriptors::starSystem(int_t id) const
{
    descriptor::StarSystem* descr = static_cast<descriptor::StarSystem*>(get(id));
    assert(descr);
    return descr;
}
descriptor::HyperSpace*
Descriptors::hyperSpace(int_t id) const
{
    descriptor::HyperSpace* descr = static_cast<descriptor::HyperSpace*>(get(id));
    assert(descr);
    return descr;
}

descriptor::Star*
Descriptors::star(int_t id) const
{
    descriptor::Star* descr = static_cast<descriptor::Star*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Planet*
Descriptors::planet(int_t id) const
{
    descriptor::Planet* descr = static_cast<descriptor::Planet*>(get(id));
    assert(descr);
    return descr;
}
descriptor::WormHole*
Descriptors::wormHole(int_t id) const
{
    descriptor::WormHole* descr = static_cast<descriptor::WormHole*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Asteroid*
Descriptors::asteroid(int_t id) const
{
    descriptor::Asteroid* descr = static_cast<descriptor::Asteroid*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Container*
Descriptors::container(int_t id) const
{
    descriptor::Container* descr = static_cast<descriptor::Container*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Bullet*
Descriptors::bullet(int_t id) const
{
    descriptor::Bullet* descr = static_cast<descriptor::Bullet*>(get(id));
    assert(descr);
    return descr;
}

descriptor::Npc*
Descriptors::npc(int_t id) const
{
    descriptor::Npc* descr = static_cast<descriptor::Npc*>(get(id));
    assert(descr);
    return descr;
}

descriptor::Ship*
Descriptors::ship(int_t id) const
{
    descriptor::Ship* descr = static_cast<descriptor::Ship*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Satellite*
Descriptors::satellite(int_t id) const
{
    descriptor::Satellite* descr = static_cast<descriptor::Satellite*>(get(id));
    assert(descr);
    return descr;
}
descriptor::SpaceStation*
Descriptors::spaceStation(int_t id) const
{
    descriptor::SpaceStation* descr = static_cast<descriptor::SpaceStation*>(get(id));
    assert(descr);
    return descr;
}

// dock
descriptor::Kosmoport*
Descriptors::kosmoport(int_t id) const
{
    descriptor::Kosmoport* descr = static_cast<descriptor::Kosmoport*>(get(id));
    assert(descr);
    return descr;
}
descriptor::NatureLand*
Descriptors::natureLand(int_t id) const
{
    descriptor::NatureLand* descr = static_cast<descriptor::NatureLand*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Angar*
Descriptors::angar(int_t id) const
{
    descriptor::Angar* descr = static_cast<descriptor::Angar*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Store*
Descriptors::store(int_t id) const
{
    descriptor::Store* descr = static_cast<descriptor::Store*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Shop*
Descriptors::shop(int_t id) const
{
    descriptor::Shop* descr = static_cast<descriptor::Shop*>(get(id));
    assert(descr);
    return descr;
}
descriptor::Goverment*
Descriptors::goverment(int_t id) const
{
    descriptor::Goverment* descr = static_cast<descriptor::Goverment*>(get(id));
    assert(descr);
    return descr;
}


// items
descriptor::item::Scaner*
Descriptors::scaner(int_t id) const
{
    descriptor::item::Scaner* descr = static_cast<descriptor::item::Scaner*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Drive*
Descriptors::drive(int_t id) const
{
    descriptor::item::Drive* descr = static_cast<descriptor::item::Drive*>(get(id));
    assert(descr);
    return descr;
}
descriptor::item::Bak*
Descriptors::bak(int_t id) const
{
    descriptor::item::Bak* descr = static_cast<descriptor::item::Bak*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Droid*
Descriptors::droid(int_t id) const
{
    descriptor:: item::Droid* descr = static_cast<descriptor::item::Droid*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Grapple*
Descriptors::grapple(int_t id) const
{
    descriptor::item::Grapple* descr = static_cast<descriptor::item::Grapple*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Lazer*
Descriptors::lazer(int_t id) const
{
    descriptor::item::Lazer* descr = static_cast<descriptor::item::Lazer*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Protector*
Descriptors::protector(int_t id) const
{
    descriptor::item::Protector* descr = static_cast<descriptor::item::Protector*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Radar*
Descriptors::radar(int_t id) const
{
    descriptor::item::Radar* descr = static_cast<descriptor::item::Radar*>(get(id));
    assert(descr);
    return descr;
}

descriptor::item::Rocket*
Descriptors::rocket(int_t id) const
{
    descriptor::item::Rocket* descr = static_cast<descriptor::item::Rocket*>(get(id));
    assert(descr);
    return descr;
}

// other
descriptor::item::Goods*
Descriptors::goods(int_t id) const
{
    descriptor::item::Goods* descr = static_cast<descriptor::item::Goods*>(get(id));
    assert(descr);
    return descr;
}


descriptor::Mesh*
Descriptors::mesh(int_t id) const
{
    descriptor::Mesh* mesh = m_meshes->get(id);
    assert(mesh);
    return mesh;
}

descriptor::Material*
Descriptors::material(int_t id) const
{
    descriptor::Material* material = m_materials->get(id);
    assert(material);
    return material;
}

descriptor::Mesh*
Descriptors::randMesh(mesh::Type type) const
{
    descriptor::Mesh* mesh = m_meshes->random(int_t(type));
    assert(mesh);
    return mesh;
}

descriptor::Material*
Descriptors::randMaterial(texture::Type type) const
{
    descriptor::Material* material = m_materials->random(int_t(type));
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
        descriptor::genBullet(); // nested for rocket, so must be generated firstly
    }
    descriptor::item::genGoods();

    int base = 1;
    int num = base * 20;
    // items
    for(int i=0; i<num; ++i) {
        descriptor::item::genBak();
        descriptor::item::genDrive();
        descriptor::item::genDroid();
        descriptor::item::genGrapple();
        descriptor::item::genProtector();
        descriptor::item::genRadar();
        descriptor::item::genScaner();
        descriptor::item::genLazer();
        descriptor::item::genRocket();
//        add(getNewBomb());
    }

    num = base * 10;
    // spaceobjects
    for(int i=0; i<num; ++i) {
        descriptor::genShip();
        descriptor::genSpaceStation();
        descriptor::genSatellite();
        descriptor::genStar();
        descriptor::genPlanet();
        descriptor::genAsteroid();
        descriptor::genContainer();
    }

    // world
    num = base * 10;
    for(int i=0; i<num; ++i) {
        descriptor::genStarSystem();
    }

    // npc
    num = 5;
    for(int i=0; i<num; ++i) {
        descriptor::genNpc();
    }

    num = 4;
    for(int i=0; i<num; ++i) {
        const auto& ids = __ids(descriptor::Type::STARSYSTEM).random(5);
        descriptor::genSector(ids);
    }

    const auto& ids = __ids(descriptor::Type::SECTOR).random(2);
    descriptor::genGalaxy(ids);

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

    for (std::map<int_t, descriptor::Base*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it) {
        delete it->second;
    }

    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Descriptors::__resolveId(descriptor::Base* descr) {

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
Descriptors::__ids(descriptor::Type type) const
{
    ceti::pack<int_t> result;

    std::map<descriptor::Type, std::vector<descriptor::Base*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it != m_descriptorsTypes.end()) {
        const std::vector<descriptor::Base*>& descriptors = it->second;
        for (descriptor::Base* descr: descriptors) {
            result.add(descr->id());
        }
    }
    return result;
}

} // namespace manager
} // namespace core
