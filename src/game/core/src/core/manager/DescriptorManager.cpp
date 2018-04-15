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
      m_meshes(new Collector<descriptor::MeshDescr>(""))
    , m_materials(new Collector<descriptor::MaterialDescr>(""))
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
Descriptors::add(descriptor::BaseDescr* descr)
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
            std::vector<descriptor::BaseDescr*> vector;
            vector.push_back(descr);
            m_descriptorsTypes[type] = vector;
        }
    }
}

void
Descriptors::add(descriptor::MeshDescr* descr)
{
    __resolveId(descr);
    m_meshes->add(descr);
}

void
Descriptors::add(descriptor::MaterialDescr* descr)
{
    __resolveId(descr);
    m_materials->add(descr);
}

bool
Descriptors::hasType(descriptor::Type type) const
{
    std::map<descriptor::Type, std::vector<descriptor::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    return (it != m_descriptorsTypes.end());
}

descriptor::BaseDescr*
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

descriptor::BaseDescr*
Descriptors::rand(descriptor::Type type) const
{
    std::map<descriptor::Type, std::vector<descriptor::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it == m_descriptorsTypes.end()) {
        throw std::runtime_error("Base* Manager::randdescriptor type = " + to_string(type) + " doesn't exist");
    }
    descriptor::BaseDescr* descr = meti::rand::get_element_or_die(it->second);
    assert(descr);
    return descr;
}

descriptor::GalaxyDescr*
Descriptors::randGalaxy() const
{
    descriptor::GalaxyDescr* descr = static_cast<descriptor::GalaxyDescr*>(rand(descriptor::Type::GALAXY));
    assert(descr);
    return descr;
}
descriptor::SectorDescr*
Descriptors::randSector() const
{
    descriptor::SectorDescr* descr = static_cast<descriptor::SectorDescr*>(rand(descriptor::Type::SECTOR));
    assert(descr);
    return descr;
}
descriptor::StarSystemDescr*
Descriptors::randStarSystem() const
{
    descriptor::StarSystemDescr* descr = static_cast<descriptor::StarSystemDescr*>(rand(descriptor::Type::STARSYSTEM));
    assert(descr);
    return descr;
}
descriptor::HyperSpaceDescr*
Descriptors::randHyperSpace() const
{
    descriptor::HyperSpaceDescr* descr = static_cast<descriptor::HyperSpaceDescr*>(rand(descriptor::Type::HYPERSPACE));
    assert(descr);
    return descr;
}

descriptor::StarDescr*
Descriptors::randStar() const
{
    descriptor::StarDescr* descr = static_cast<descriptor::StarDescr*>(rand(descriptor::Type::STAR));
    assert(descr);
    return descr;
}
descriptor::PlanetDescr*
Descriptors::randPlanet() const
{
    descriptor::PlanetDescr* descr = static_cast<descriptor::PlanetDescr*>(rand(descriptor::Type::PLANET));
    assert(descr);
    return descr;
}
descriptor::WormHoleDescr*
Descriptors::randWormHole() const
{
    descriptor::WormHoleDescr* descr = static_cast<descriptor::WormHoleDescr*>(rand(descriptor::Type::WORMHOLE));
    assert(descr);
    return descr;
}
descriptor::AsteroidDescr*
Descriptors::randAsteroid() const
{
    descriptor::AsteroidDescr* descr = static_cast<descriptor::AsteroidDescr*>(rand(descriptor::Type::ASTEROID));
    assert(descr);
    return descr;
}
descriptor::ContainerDescr*
Descriptors::randContainer() const
{
    descriptor::ContainerDescr* descr = static_cast<descriptor::ContainerDescr*>(rand(descriptor::Type::CONTAINER));
    assert(descr);
    return descr;
}
descriptor::BulletDescr*
Descriptors::randBullet() const
{
    descriptor::BulletDescr* descr = static_cast<descriptor::BulletDescr*>(rand(descriptor::Type::BULLET));
    assert(descr);
    return descr;
}

descriptor::NpcDescr*
Descriptors::randNpc() const
{
    descriptor::NpcDescr* descr = static_cast<descriptor::NpcDescr*>(rand(descriptor::Type::NPC));
    assert(descr);
    return descr;
}

descriptor::ShipDescr*
Descriptors::randShip() const
{
    descriptor::ShipDescr* descr = static_cast<descriptor::ShipDescr*>(rand(descriptor::Type::SHIP));
    assert(descr);
    return descr;
}
descriptor::SatelliteDescr*
Descriptors::randSatellite() const
{
    descriptor::SatelliteDescr* descr = static_cast<descriptor::SatelliteDescr*>(rand(descriptor::Type::SATELLITE));
    assert(descr);
    return descr;
}
descriptor::SpaceStationDescr*
Descriptors::randSpaceStation() const
{
    descriptor::SpaceStationDescr* descr = static_cast<descriptor::SpaceStationDescr*>(rand(descriptor::Type::SPACESTATION));
    assert(descr);
    return descr;
}

// dock
descriptor::KosmoportDescr*
Descriptors::randKosmoport() const
{
    descriptor::KosmoportDescr* descr = static_cast<descriptor::KosmoportDescr*>(rand(descriptor::Type::KOSMOPORT));
    assert(descr);
    return descr;
}
descriptor::NatureLandDescr*
Descriptors::randNatureLand() const
{
    descriptor::NatureLandDescr* descr = static_cast<descriptor::NatureLandDescr*>(rand(descriptor::Type::NATURELAND));
    assert(descr);
    return descr;
}
descriptor::AngarDescr*
Descriptors::randAngar() const
{
    descriptor::AngarDescr* descr = static_cast<descriptor::AngarDescr*>(rand(descriptor::Type::ANGAR));
    assert(descr);
    return descr;
}
descriptor::StoreDescr*
Descriptors::randStore() const
{
    descriptor::StoreDescr* descr = static_cast<descriptor::StoreDescr*>(rand(descriptor::Type::STORE));
    assert(descr);
    return descr;
}
descriptor::ShopDescr*
Descriptors::randShop() const
{
    descriptor::ShopDescr* descr = static_cast<descriptor::ShopDescr*>(rand(descriptor::Type::SHOP));
    assert(descr);
    return descr;
}
descriptor::GovermentDescr*
Descriptors::randGoverment() const
{
    descriptor::GovermentDescr* descr = static_cast<descriptor::GovermentDescr*>(rand(descriptor::Type::GOVERMENT));
    assert(descr);
    return descr;
}

// items
descriptor::ScanerDescr*
Descriptors::randScaner() const
{
    descriptor::ScanerDescr* descr = static_cast<descriptor::ScanerDescr*>(rand(descriptor::Type::SCANER_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::DriveDescr*
Descriptors::randDrive() const
{
    descriptor::DriveDescr* descr = static_cast<descriptor::DriveDescr*>(rand(descriptor::Type::DRIVE_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::BakDescr*
Descriptors::randBak() const
{
    descriptor::BakDescr* descr = static_cast<descriptor::BakDescr*>(rand(descriptor::Type::BAK_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::DroidDescr*
Descriptors::randDroid() const
{
    descriptor::DroidDescr* descr = static_cast<descriptor::DroidDescr*>(rand(descriptor::Type::DROID_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::GrappleDescr*
Descriptors::randGrapple() const
{
    descriptor::GrappleDescr* descr = static_cast<descriptor::GrappleDescr*>(rand(descriptor::Type::GRAPPLE_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::LazerDescr*
Descriptors::randLazer() const
{
    descriptor::LazerDescr* descr = static_cast<descriptor::LazerDescr*>(rand(descriptor::Type::LAZER_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::ProtectorDescr*
Descriptors::randProtector() const
{
    descriptor::ProtectorDescr* descr = static_cast<descriptor::ProtectorDescr*>(rand(descriptor::Type::PROTECTOR_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::RadarDescr*
Descriptors::randRadar() const
{
    descriptor::RadarDescr* descr = static_cast<descriptor::RadarDescr*>(rand(descriptor::Type::RADAR_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::RocketDescr*
Descriptors::randRocket() const
{
    descriptor::RocketDescr* descr = static_cast<descriptor::RocketDescr*>(rand(descriptor::Type::ROCKET_EQUIPMENT));
    assert(descr);
    return descr;
}

descriptor::GoodsDescr*
Descriptors::randGoods() const
{
    descriptor::GoodsDescr* descriptor = static_cast<descriptor::GoodsDescr*>(rand(descriptor::Type::GOODS));
    assert(descriptor);
    return descriptor;
}

// parts
descriptor::TurrelDescr*
Descriptors::randTurrel() const
{
    descriptor::TurrelDescr* descr = static_cast<descriptor::TurrelDescr*>(rand(descriptor::Type::TURREL));
    assert(descr);
    return descr;
}

descriptor::GalaxyDescr*
Descriptors::galaxy(int_t id) const
{
    descriptor::GalaxyDescr* descr = static_cast<descriptor::GalaxyDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::SectorDescr*
Descriptors::sector(int_t id) const
{
    descriptor::SectorDescr* descr = static_cast<descriptor::SectorDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::StarSystemDescr*
Descriptors::starSystem(int_t id) const
{
    descriptor::StarSystemDescr* descr = static_cast<descriptor::StarSystemDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::HyperSpaceDescr*
Descriptors::hyperSpace(int_t id) const
{
    descriptor::HyperSpaceDescr* descr = static_cast<descriptor::HyperSpaceDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::StarDescr*
Descriptors::star(int_t id) const
{
    descriptor::StarDescr* descr = static_cast<descriptor::StarDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::PlanetDescr*
Descriptors::planet(int_t id) const
{
    descriptor::PlanetDescr* descr = static_cast<descriptor::PlanetDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::WormHoleDescr*
Descriptors::wormHole(int_t id) const
{
    descriptor::WormHoleDescr* descr = static_cast<descriptor::WormHoleDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::AsteroidDescr*
Descriptors::asteroid(int_t id) const
{
    descriptor::AsteroidDescr* descr = static_cast<descriptor::AsteroidDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::ContainerDescr*
Descriptors::container(int_t id) const
{
    descriptor::ContainerDescr* descr = static_cast<descriptor::ContainerDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::BulletDescr*
Descriptors::bullet(int_t id) const
{
    descriptor::BulletDescr* descr = static_cast<descriptor::BulletDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::NpcDescr*
Descriptors::npc(int_t id) const
{
    descriptor::NpcDescr* descr = static_cast<descriptor::NpcDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::ShipDescr*
Descriptors::ship(int_t id) const
{
    descriptor::ShipDescr* descr = static_cast<descriptor::ShipDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::SatelliteDescr*
Descriptors::satellite(int_t id) const
{
    descriptor::SatelliteDescr* descr = static_cast<descriptor::SatelliteDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::SpaceStationDescr*
Descriptors::spaceStation(int_t id) const
{
    descriptor::SpaceStationDescr* descr = static_cast<descriptor::SpaceStationDescr*>(get(id));
    assert(descr);
    return descr;
}

// dock
descriptor::KosmoportDescr*
Descriptors::kosmoport(int_t id) const
{
    descriptor::KosmoportDescr* descr = static_cast<descriptor::KosmoportDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::NatureLandDescr*
Descriptors::natureLand(int_t id) const
{
    descriptor::NatureLandDescr* descr = static_cast<descriptor::NatureLandDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::AngarDescr*
Descriptors::angar(int_t id) const
{
    descriptor::AngarDescr* descr = static_cast<descriptor::AngarDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::StoreDescr*
Descriptors::store(int_t id) const
{
    descriptor::StoreDescr* descr = static_cast<descriptor::StoreDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::ShopDescr*
Descriptors::shop(int_t id) const
{
    descriptor::ShopDescr* descr = static_cast<descriptor::ShopDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::GovermentDescr*
Descriptors::goverment(int_t id) const
{
    descriptor::GovermentDescr* descr = static_cast<descriptor::GovermentDescr*>(get(id));
    assert(descr);
    return descr;
}


// items
descriptor::ScanerDescr*
Descriptors::scaner(int_t id) const
{
    descriptor::ScanerDescr* descr = static_cast<descriptor::ScanerDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::DriveDescr*
Descriptors::drive(int_t id) const
{
    descriptor::DriveDescr* descr = static_cast<descriptor::DriveDescr*>(get(id));
    assert(descr);
    return descr;
}
descriptor::BakDescr*
Descriptors::bak(int_t id) const
{
    descriptor::BakDescr* descr = static_cast<descriptor::BakDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::DroidDescr*
Descriptors::droid(int_t id) const
{
    descriptor:: DroidDescr* descr = static_cast<descriptor::DroidDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::GrappleDescr*
Descriptors::grapple(int_t id) const
{
    descriptor::GrappleDescr* descr = static_cast<descriptor::GrappleDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::LazerDescr*
Descriptors::lazer(int_t id) const
{
    descriptor::LazerDescr* descr = static_cast<descriptor::LazerDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::ProtectorDescr*
Descriptors::protector(int_t id) const
{
    descriptor::ProtectorDescr* descr = static_cast<descriptor::ProtectorDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::RadarDescr*
Descriptors::radar(int_t id) const
{
    descriptor::RadarDescr* descr = static_cast<descriptor::RadarDescr*>(get(id));
    assert(descr);
    return descr;
}

descriptor::RocketDescr*
Descriptors::rocket(int_t id) const
{
    descriptor::RocketDescr* descr = static_cast<descriptor::RocketDescr*>(get(id));
    assert(descr);
    return descr;
}

// other
descriptor::GoodsDescr*
Descriptors::goods(int_t id) const
{
    descriptor::GoodsDescr* descr = static_cast<descriptor::GoodsDescr*>(get(id));
    assert(descr);
    return descr;
}


descriptor::MeshDescr*
Descriptors::mesh(int_t id) const
{
    descriptor::MeshDescr* mesh = m_meshes->get(id);
    assert(mesh);
    return mesh;
}

descriptor::MaterialDescr*
Descriptors::material(int_t id) const
{
    descriptor::MaterialDescr* material = m_materials->get(id);
    assert(material);
    return material;
}

descriptor::MeshDescr*
Descriptors::randMesh(mesh::Type type) const
{
    descriptor::MeshDescr* mesh = m_meshes->random(int_t(type));
    assert(mesh);
    return mesh;
}

descriptor::MaterialDescr*
Descriptors::randMaterial(texture::Type type) const
{
    descriptor::MaterialDescr* material = m_materials->random(int_t(type));
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
    descriptor::genGoods();

    int base = 1;
    int num = base * 20;
    // items
    for(int i=0; i<num; ++i) {
        descriptor::genBak();
        descriptor::genDrive();
        descriptor::genDroid();
        descriptor::genGrapple();
        descriptor::genProtector();
        descriptor::genRadar();
        descriptor::genScaner();
        descriptor::genLazer();
        descriptor::genRocket();
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

    for (std::map<int_t, descriptor::BaseDescr*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it) {
        delete it->second;
    }

    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Descriptors::__resolveId(descriptor::BaseDescr* descr) {

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

    std::map<descriptor::Type, std::vector<descriptor::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it != m_descriptorsTypes.end()) {
        const std::vector<descriptor::BaseDescr*>& descriptors = it->second;
        for (descriptor::BaseDescr* descr: descriptors) {
            result.add(descr->id());
        }
    }
    return result;
}

} // namespace manager
} // namespace core
