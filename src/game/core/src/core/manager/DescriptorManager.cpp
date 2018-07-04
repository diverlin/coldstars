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
      m_meshes(new Collector<core::MeshDescr>(""))
    , m_materials(new Collector<core::MaterialDescr>(""))
{

}

void Descriptors::init()
{
    bool force_generation = false;
    if (ceti::filesystem::is_file_exists(descriptors_fname) && !force_generation) {
        __load();
    } else {
       __generate();
       __save();
    }

//#ifdef USE_FAILBACK_RESOURCES
//    __resolveId(m_meshes->failback());
//    __resolveId(m_materials->failback());
//#endif // USE_FAILBACK_RESOURCES
}

void
Descriptors::add(core::BaseDescr* descr)
{
    __resolveId(descr);

    const int_t id = descr->id();
    core::Type type = descr->type();

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
            std::vector<core::BaseDescr*> vector;
            vector.push_back(descr);
            m_descriptorsTypes[type] = vector;
        }
    }
}

void
Descriptors::add(core::MeshDescr* descr)
{
    __resolveId(descr);
    m_meshes->add(descr);
}

void
Descriptors::add(core::MaterialDescr* descr)
{
    __resolveId(descr);
    m_materials->add(descr);
}

bool
Descriptors::hasType(core::Type type) const
{
    std::map<core::Type, std::vector<core::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    return (it != m_descriptorsTypes.end());
}

core::BaseDescr*
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

core::BaseDescr*
Descriptors::rand(core::Type type) const
{
    std::map<core::Type, std::vector<core::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it == m_descriptorsTypes.end()) {
        assert(false);
        throw std::runtime_error("Base* Manager::randdescriptor type = " + to_string(type) + " doesn't exist");
    }
    core::BaseDescr* descr = meti::rand::get_element_or_die(it->second);
    assert(descr);
    return descr;
}

core::GalaxyDescr*
Descriptors::randGalaxy() const
{
    core::GalaxyDescr* descr = static_cast<core::GalaxyDescr*>(rand(core::Type::GALAXY));
    assert(descr);
    return descr;
}
core::SectorDescr*
Descriptors::randSector() const
{
    core::SectorDescr* descr = static_cast<core::SectorDescr*>(rand(core::Type::SECTOR));
    assert(descr);
    return descr;
}
core::StarSystemDescr*
Descriptors::randStarSystem() const
{
    core::StarSystemDescr* descr = static_cast<core::StarSystemDescr*>(rand(core::Type::STARSYSTEM));
    assert(descr);
    return descr;
}
core::HyperSpaceDescr*
Descriptors::randHyperSpace() const
{
    core::HyperSpaceDescr* descr = static_cast<core::HyperSpaceDescr*>(rand(core::Type::HYPERSPACE));
    assert(descr);
    return descr;
}

core::StarDescr*
Descriptors::randStar() const
{
    core::StarDescr* descr = static_cast<core::StarDescr*>(rand(core::Type::STAR));
    assert(descr);
    return descr;
}
core::PlanetDescr*
Descriptors::randPlanet() const
{
    core::PlanetDescr* descr = static_cast<core::PlanetDescr*>(rand(core::Type::PLANET));
    assert(descr);
    return descr;
}
core::WormHoleDescr*
Descriptors::randWormHole() const
{
    core::WormHoleDescr* descr = static_cast<core::WormHoleDescr*>(rand(core::Type::WORMHOLE));
    assert(descr);
    return descr;
}
core::AsteroidDescr*
Descriptors::randAsteroid() const
{
    core::AsteroidDescr* descr = static_cast<core::AsteroidDescr*>(rand(core::Type::ASTEROID));
    assert(descr);
    return descr;
}
core::ContainerDescr*
Descriptors::randContainer() const
{
    core::ContainerDescr* descr = static_cast<core::ContainerDescr*>(rand(core::Type::CONTAINER));
    assert(descr);
    return descr;
}
core::BulletDescr*
Descriptors::randBullet() const
{
    core::BulletDescr* descr = static_cast<core::BulletDescr*>(rand(core::Type::BULLET));
    assert(descr);
    return descr;
}

core::NpcDescr*
Descriptors::randNpc() const
{
    core::NpcDescr* descr = static_cast<core::NpcDescr*>(rand(core::Type::NPC));
    assert(descr);
    return descr;
}

core::ShipDescr*
Descriptors::randShip() const
{
    core::ShipDescr* descr = static_cast<core::ShipDescr*>(rand(core::Type::SHIP));
    assert(descr);
    return descr;
}
core::SatelliteDescr*
Descriptors::randSatellite() const
{
    core::SatelliteDescr* descr = static_cast<core::SatelliteDescr*>(rand(core::Type::SATELLITE));
    assert(descr);
    return descr;
}
core::SpaceStationDescr*
Descriptors::randSpaceStation() const
{
    core::SpaceStationDescr* descr = static_cast<core::SpaceStationDescr*>(rand(core::Type::SPACESTATION));
    assert(descr);
    return descr;
}

// dock
core::KosmoportDescr*
Descriptors::randKosmoport() const
{
    core::KosmoportDescr* descr = static_cast<core::KosmoportDescr*>(rand(core::Type::KOSMOPORT));
    assert(descr);
    return descr;
}
core::NatureLandDescr*
Descriptors::randNatureLand() const
{
    core::NatureLandDescr* descr = static_cast<core::NatureLandDescr*>(rand(core::Type::NATURELAND));
    assert(descr);
    return descr;
}
core::AngarDescr*
Descriptors::randAngar() const
{
    core::AngarDescr* descr = static_cast<core::AngarDescr*>(rand(core::Type::ANGAR));
    assert(descr);
    return descr;
}
core::StoreDescr*
Descriptors::randStore() const
{
    core::StoreDescr* descr = static_cast<core::StoreDescr*>(rand(core::Type::STORE));
    assert(descr);
    return descr;
}
core::ShopDescr*
Descriptors::randShop() const
{
    core::ShopDescr* descr = static_cast<core::ShopDescr*>(rand(core::Type::SHOP));
    assert(descr);
    return descr;
}
core::GovermentDescr*
Descriptors::randGoverment() const
{
    core::GovermentDescr* descr = static_cast<core::GovermentDescr*>(rand(core::Type::GOVERMENT));
    assert(descr);
    return descr;
}

// items
core::ScanerDescr*
Descriptors::randScaner() const
{
    core::ScanerDescr* descr = static_cast<core::ScanerDescr*>(rand(core::Type::SCANER_EQUIPMENT));
    assert(descr);
    return descr;
}

core::DriveDescr*
Descriptors::randDrive() const
{
    core::DriveDescr* descr = static_cast<core::DriveDescr*>(rand(core::Type::DRIVE_EQUIPMENT));
    assert(descr);
    return descr;
}

core::BakDescr*
Descriptors::randBak() const
{
    core::BakDescr* descr = static_cast<core::BakDescr*>(rand(core::Type::BAK_EQUIPMENT));
    assert(descr);
    return descr;
}

core::DroidDescr*
Descriptors::randDroid() const
{
    core::DroidDescr* descr = static_cast<core::DroidDescr*>(rand(core::Type::DROID_EQUIPMENT));
    assert(descr);
    return descr;
}

core::GrappleDescr*
Descriptors::randGrapple() const
{
    core::GrappleDescr* descr = static_cast<core::GrappleDescr*>(rand(core::Type::GRAPPLE_EQUIPMENT));
    assert(descr);
    return descr;
}

core::LazerDescr*
Descriptors::randLazer() const
{
    core::LazerDescr* descr = static_cast<core::LazerDescr*>(rand(core::Type::LAZER_EQUIPMENT));
    assert(descr);
    return descr;
}

core::ProtectorDescr*
Descriptors::randProtector() const
{
    core::ProtectorDescr* descr = static_cast<core::ProtectorDescr*>(rand(core::Type::PROTECTOR_EQUIPMENT));
    assert(descr);
    return descr;
}

core::RadarDescr*
Descriptors::randRadar() const
{
    core::RadarDescr* descr = static_cast<core::RadarDescr*>(rand(core::Type::RADAR_EQUIPMENT));
    assert(descr);
    return descr;
}

core::RocketDescr*
Descriptors::randRocket() const
{
    core::RocketDescr* descr = static_cast<core::RocketDescr*>(rand(core::Type::ROCKET_EQUIPMENT));
    assert(descr);
    return descr;
}

core::GoodsDescr*
Descriptors::randGoods() const
{
    GoodsDescr* descriptor = static_cast<GoodsDescr*>(rand(Type::GOODS));
    assert(descriptor);
    return descriptor;
}

// parts
core::TurrelDescr*
Descriptors::randTurrel() const
{
    core::TurrelDescr* descr = static_cast<core::TurrelDescr*>(rand(core::Type::TURREL));
    assert(descr);
    return descr;
}

core::GalaxyDescr*
Descriptors::galaxy(int_t id) const
{
    core::GalaxyDescr* descr = static_cast<core::GalaxyDescr*>(get(id));
    assert(descr);
    return descr;
}
core::SectorDescr*
Descriptors::sector(int_t id) const
{
    core::SectorDescr* descr = static_cast<core::SectorDescr*>(get(id));
    assert(descr);
    return descr;
}
core::StarSystemDescr*
Descriptors::starSystem(int_t id) const
{
    core::StarSystemDescr* descr = static_cast<core::StarSystemDescr*>(get(id));
    assert(descr);
    return descr;
}
core::HyperSpaceDescr*
Descriptors::hyperSpace(int_t id) const
{
    core::HyperSpaceDescr* descr = static_cast<core::HyperSpaceDescr*>(get(id));
    assert(descr);
    return descr;
}

core::StarDescr*
Descriptors::star(int_t id) const
{
    core::StarDescr* descr = static_cast<core::StarDescr*>(get(id));
    assert(descr);
    return descr;
}
core::PlanetDescr*
Descriptors::planet(int_t id) const
{
    core::PlanetDescr* descr = static_cast<core::PlanetDescr*>(get(id));
    assert(descr);
    return descr;
}
core::WormHoleDescr*
Descriptors::wormHole(int_t id) const
{
    core::WormHoleDescr* descr = static_cast<core::WormHoleDescr*>(get(id));
    assert(descr);
    return descr;
}
core::AsteroidDescr*
Descriptors::asteroid(int_t id) const
{
    core::AsteroidDescr* descr = static_cast<core::AsteroidDescr*>(get(id));
    assert(descr);
    return descr;
}
core::ContainerDescr*
Descriptors::container(int_t id) const
{
    core::ContainerDescr* descr = static_cast<core::ContainerDescr*>(get(id));
    assert(descr);
    return descr;
}
core::BulletDescr*
Descriptors::bullet(int_t id) const
{
    core::BulletDescr* descr = static_cast<core::BulletDescr*>(get(id));
    assert(descr);
    return descr;
}

core::NpcDescr*
Descriptors::npc(int_t id) const
{
    core::NpcDescr* descr = static_cast<core::NpcDescr*>(get(id));
    assert(descr);
    return descr;
}

core::ShipDescr*
Descriptors::ship(int_t id) const
{
    core::ShipDescr* descr = static_cast<core::ShipDescr*>(get(id));
    assert(descr);
    return descr;
}
core::SatelliteDescr*
Descriptors::satellite(int_t id) const
{
    core::SatelliteDescr* descr = static_cast<core::SatelliteDescr*>(get(id));
    assert(descr);
    return descr;
}
core::SpaceStationDescr*
Descriptors::spaceStation(int_t id) const
{
    core::SpaceStationDescr* descr = static_cast<core::SpaceStationDescr*>(get(id));
    assert(descr);
    return descr;
}

// dock
core::KosmoportDescr*
Descriptors::kosmoport(int_t id) const
{
    core::KosmoportDescr* descr = static_cast<core::KosmoportDescr*>(get(id));
    assert(descr);
    return descr;
}
core::NatureLandDescr*
Descriptors::natureLand(int_t id) const
{
    core::NatureLandDescr* descr = static_cast<core::NatureLandDescr*>(get(id));
    assert(descr);
    return descr;
}
core::AngarDescr*
Descriptors::angar(int_t id) const
{
    core::AngarDescr* descr = static_cast<core::AngarDescr*>(get(id));
    assert(descr);
    return descr;
}
core::StoreDescr*
Descriptors::store(int_t id) const
{
    core::StoreDescr* descr = static_cast<core::StoreDescr*>(get(id));
    assert(descr);
    return descr;
}
core::ShopDescr*
Descriptors::shop(int_t id) const
{
    core::ShopDescr* descr = static_cast<core::ShopDescr*>(get(id));
    assert(descr);
    return descr;
}
core::GovermentDescr*
Descriptors::goverment(int_t id) const
{
    core::GovermentDescr* descr = static_cast<core::GovermentDescr*>(get(id));
    assert(descr);
    return descr;
}


// items
core::ScanerDescr*
Descriptors::scaner(int_t id) const
{
    core::ScanerDescr* descr = static_cast<core::ScanerDescr*>(get(id));
    assert(descr);
    return descr;
}

core::DriveDescr*
Descriptors::drive(int_t id) const
{
    core::DriveDescr* descr = static_cast<core::DriveDescr*>(get(id));
    assert(descr);
    return descr;
}
core::BakDescr*
Descriptors::bak(int_t id) const
{
    core::BakDescr* descr = static_cast<core::BakDescr*>(get(id));
    assert(descr);
    return descr;
}

core::DroidDescr*
Descriptors::droid(int_t id) const
{
    core:: DroidDescr* descr = static_cast<core::DroidDescr*>(get(id));
    assert(descr);
    return descr;
}

core::GrappleDescr*
Descriptors::grapple(int_t id) const
{
    core::GrappleDescr* descr = static_cast<core::GrappleDescr*>(get(id));
    assert(descr);
    return descr;
}

core::LazerDescr*
Descriptors::lazer(int_t id) const
{
    core::LazerDescr* descr = static_cast<core::LazerDescr*>(get(id));
    assert(descr);
    return descr;
}

core::ProtectorDescr*
Descriptors::protector(int_t id) const
{
    core::ProtectorDescr* descr = static_cast<core::ProtectorDescr*>(get(id));
    assert(descr);
    return descr;
}

core::RadarDescr*
Descriptors::radar(int_t id) const
{
    core::RadarDescr* descr = static_cast<core::RadarDescr*>(get(id));
    assert(descr);
    return descr;
}

core::RocketDescr*
Descriptors::rocket(int_t id) const
{
    core::RocketDescr* descr = static_cast<core::RocketDescr*>(get(id));
    assert(descr);
    return descr;
}

// other
core::GoodsDescr*
Descriptors::goods(int_t id) const
{
    core::GoodsDescr* descr = static_cast<core::GoodsDescr*>(get(id));
    assert(descr);
    return descr;
}


core::MeshDescr*
Descriptors::mesh(int_t id) const
{
    core::MeshDescr* mesh = m_meshes->get(id);
    assert(mesh);
    return mesh;
}

core::MaterialDescr*
Descriptors::material(int_t id) const
{
    core::MaterialDescr* material = m_materials->get(id);
    assert(material);
    return material;
}

core::MeshDescr*
Descriptors::randMesh(mesh::Type type) const
{
    core::MeshDescr* mesh = m_meshes->random(int_t(type));
    assert(mesh);
    return mesh;
}

core::MaterialDescr*
Descriptors::randMaterial(texture::Type type) const
{
    core::MaterialDescr* material = m_materials->random(int_t(type));
    assert(material);
    return material;
}

void
Descriptors::__save()
{
    ceti::filesystem::touch_file(descriptors_fname);

    std::fstream filestream;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        for(const auto& it: m_descriptors) {
            core::BaseDescr* descr = it.second;
            filestream<<to_string(descr->type())<<"|"<<
                        std::to_string(int(descr->type()))<<"|"<<
                        descr->data()<<std::endl;
        }
    } else {
        throw std::runtime_error("not able to open file="+descriptors_fname);
    }
    filestream.close();
}

void
Descriptors::__load()
{
    __clear();

    std::fstream filestream;
    std::string line;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            if (!line.empty()) {
                auto vdata = ceti::split(line, "|");
                std::string data = "";
                if (vdata.size() == 3) {
                    Type type = Type(std::atoi(vdata[1].c_str()));
                    data = vdata[2];
                    core::BaseDescr* descr = __build_descriptor(type, data);
                    add(descr);
                }
            } else {
                //assert(false);
            }
        }
    }
    filestream.close();
}


core::BaseDescr*
Descriptors::__build_descriptor(Type type, const std::string& data) const
{
    core::BaseDescr* descr = nullptr;
    switch(type) {
//    case Type::GALAXY:         { descr = new GalaxyDescr(data); break; }
    case Type::STARSYSTEM:     { descr = new StarSystemDescr(data); break; }
//    case Type::SECTOR:     { descr = new SectorDescr(data); break; }

    // pilots
    case Type::NPC:             { descr = new NpcDescr(data); break; }

    // space object
    case Type::STAR:         { descr = new StarDescr(data); break; }
    case Type::ASTEROID:     { descr = new AsteroidDescr(data); break; }
    case Type::PLANET:       { descr = new PlanetDescr(data); break; }
    case Type::WORMHOLE:     { descr = new WormHoleDescr(data); break; }
    case Type::SHIP:         { descr = new ShipDescr(data); break; }
    case Type::SPACESTATION: { descr = new SpaceStationDescr(data); break; }
    case Type::SATELLITE:    { descr = new SatelliteDescr(data); break; }
    case Type::CONTAINER:    { descr = new ContainerDescr(data); break; }
    case Type::BULLET:       { descr = new BulletDescr(data); break; }

    // equipment
    case Type::LAZER_EQUIPMENT:     { descr = new LazerDescr(data); break; }
    case Type::ROCKET_EQUIPMENT:    { descr = new RocketDescr(data); break; }
    case Type::DRIVE_EQUIPMENT:     { descr = new DriveDescr(data); break; }
    case Type::RADAR_EQUIPMENT:     { descr = new RadarDescr(data); break; }
    case Type::BAK_EQUIPMENT:       { descr = new BakDescr(data); break; }
//    case Type::ENERGIZER_EQUIPMENT: { descr = new EnergizerDescr(data); break; }
    case Type::PROTECTOR_EQUIPMENT: { descr = new ProtectorDescr(data); break; }
    case Type::DROID_EQUIPMENT:     { descr = new DroidDescr(data); break; }
//    case Type::FREEZER_EQUIPMENT:   { descr = new FreezerDescr(data); break; }
    case Type::GRAPPLE_EQUIPMENT:   { descr = new GrappleDescr(data); break; }
    case Type::SCANER_EQUIPMENT:    { descr = new ScanerDescr(data); break; }

    // module
//    case Type::LAZER_MODULE:     { return "Type::LAZER_MODULE"; break; }
//    case Type::ROCKET_MODULE:     { return "Type::ROCKET_MODULE"; break; }
//    case Type::DRIVE_MODULE:     { return "Type::DRIVE_MODULE"; break; }
//    case Type::RADAR_MODULE:     { return "Type::RADAR_MODULE"; break; }
//    case Type::BAK_MODULE:         { return "Type::BAK_MODULE"; break; }
//    case Type::ENERGIZER_MODULE: { return "Type::ENERGIZER_MODULE"; break; }
//    case Type::PROTECTOR_MODULE: { return "Type::PROTECTOR_MODULE"; break; }
//    case Type::DROID_MODULE:     { return "Type::DROID_MODULE"; break; }
//    case Type::FREEZER_MODULE:     { return "Type::FREEZER_MODULE"; break; }
//    case Type::GRAPPLE_MODULE:     { return "Type::GRAPPLE_MODULE"; break; }
//    case Type::SCANER_MODULE:     { return "Type::SCANER_MODULE"; break; }

//    // artefact
//    case Type::GRAVITY_ARTEFACT:     { return "Type::GRAVITY_ARTEFACT"; break; }
//    case Type::PROTECTOR_ARTEFACT:     { return "Type::PROTECTOR_ARTEFACT"; break; }

//    // other
//    case Type::HIT:     { return "Type::HIT"; }
         default: std::cout<<to_string(type)<<std::endl; assert(false);
    }

    return descr;
}

void
Descriptors::__clear()
{
    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Descriptors::__generate()
{
    __clear();

    for (int i=0; i<5; ++i) {
        core::genBullet(); // nested for rocket, so must be generated firstly
    }
    //core::genGoods();

    int base = 1;
    int num = base * 20;
    // items
    for(int i=0; i<num; ++i) {
        core::genBak();
        core::genDrive();
        core::genDroid();
        core::genGrapple();
        core::genProtector();
        core::genRadar();
        core::genScaner();
        core::genLazer();
        core::genRocket();
//        add(getNewBomb());
    }

    num = base * 10;
    // spaceobjects
    for(int i=0; i<num; ++i) {
        core::genShip();
        core::genSpaceStation();
        core::genSatellite();
        core::genStar();
        core::genPlanet();
        core::genAsteroid();
        core::genContainer();
    }

    // world
    num = base * 10;
    for(int i=0; i<num; ++i) {
        core::genStarSystem();
    }

    // npc
    num = 5;
    for(int i=0; i<num; ++i) {
        core::genNpc();
    }

    num = 4;
    for(int i=0; i<num; ++i) {
        const auto& ids = __ids(core::Type::STARSYSTEM).random(5);
        core::genSector(ids);
    }

    const auto& ids = __ids(core::Type::SECTOR).random(2);
    core::genGalaxy(ids);
}

//void
//Descriptors::clear()
//{
//    if (m_meshes) {
//        assert(false);
//        //m_meshes->clear();
//        m_meshes = nullptr;
//    }
//    if (m_materials) {
//        assert(false);
//        //m_materials->clear();
//        m_materials = nullptr;
//    }

//    for (std::map<int_t, core::BaseDescr*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it) {
//        delete it->second;
//    }

//    m_descriptors.clear();
//    m_descriptorsTypes.clear();
//}

void
Descriptors::__resolveId(core::BaseDescr* descr) {

    if (descr->id() == NONE) {
        descr->setId(m_idGenerator.nextId());
    }
}

void
Descriptors::__resolveId(ceti::BaseDescr* descr) {
    if (descr->id() == NONE) {
        descr->setId(m_idGenerator.nextId());
    }
}

ceti::pack<int_t>
Descriptors::__ids(core::Type type) const
{
    ceti::pack<int_t> result;

    std::map<core::Type, std::vector<core::BaseDescr*>>::const_iterator it = m_descriptorsTypes.find(type);
    if (it != m_descriptorsTypes.end()) {
        const std::vector<core::BaseDescr*>& descriptors = it->second;
        for (core::BaseDescr* descr: descriptors) {
            result.add(descr->id());
        }
    }
    return result;
}

} // namespace manager
} // namespace core
