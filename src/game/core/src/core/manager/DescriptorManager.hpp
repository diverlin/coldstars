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

#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/descriptor/world/SectorDescriptor.hpp>
#include <core/descriptor/world/StarSystemDescriptor.hpp>

#include <core/descriptor/spaceobject/Container.hpp>

#include <core/descriptor/Mesh.hpp>
#include <core/descriptor/Texture.hpp>
#include <core/resource/Collector.hpp>
#include <core/type/MeshType.hpp>
#include <core/type/TextureType.hpp>

#include <ceti/Pack.hpp>
#include <ceti/descriptor/Base.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <string>

namespace core {

class GalaxyDescr;
class SectorDescr;
class StarSystemDescr;
class HyperSpaceDescr;

class StarDescr;
class PlanetDescr;
class WormHoleDescr;
class AsteroidDescr;
class ContainerDescr;
class BulletDescr;
class NpcDescr;
class ShipDescr;
class SpaceStationDescr;
class SatelliteDescr;

// dock
class KosmoportDescr;
class NatureLandDescr;
class AngarDescr;
class StoreDescr;
class ShopDescr;
class GovermentDescr;

class ScanerDescr;
class DriveDescr;
class BakDescr;
class DroidDescr;
class GrappleDescr;
class LazerDescr;
class ProtectorDescr;
class RadarDescr;
class RocketDescr;

class GoodsDescr;

class TurrelDescr;

} // descriptor

namespace core {
namespace manager {

class Descriptors
{
public:
    Descriptors();
    Descriptors(const Descriptors&) = delete;
    ~Descriptors() = default;
    Descriptors& operator=(const Descriptors&) = delete;

    void add(core::BaseDescr*);
    void add(core::MeshDescr*);
    void add(core::MaterialDescr*);

    core::BaseDescr* get(int_t) const;
    core::BaseDescr* rand(core::Type) const;
    bool hasType(core::Type) const;

    core::GalaxyDescr* randGalaxy() const;
    core::SectorDescr* randSector() const;
    core::StarSystemDescr* randStarSystem() const;
    core::HyperSpaceDescr* randHyperSpace() const;

    core::StarDescr* randStar() const;
    core::PlanetDescr* randPlanet() const;
    core::WormHoleDescr* randWormHole() const;
    core::AsteroidDescr* randAsteroid() const;
    core::ContainerDescr* randContainer() const;
    core::BulletDescr* randBullet() const;
    core::NpcDescr* randNpc() const;
    core::ShipDescr* randShip() const;
    core::SatelliteDescr* randSatellite() const;
    core::SpaceStationDescr* randSpaceStation() const;

    // dock
    core::KosmoportDescr* randKosmoport() const;
    core::NatureLandDescr* randNatureLand() const;
    core::AngarDescr* randAngar() const;
    core::StoreDescr* randStore() const;
    core::ShopDescr* randShop() const;
    core::GovermentDescr* randGoverment() const;

    core::ScanerDescr* randScaner() const;
    core::DriveDescr* randDrive() const;
    core::BakDescr* randBak() const;
    core::DroidDescr* randDroid() const;
    core::GrappleDescr* randGrapple() const;
    core::LazerDescr* randLazer() const;
    core::ProtectorDescr* randProtector() const;
    core::RadarDescr* randRadar() const;
    core::RocketDescr* randRocket() const;

    // other
    core::GoodsDescr* randGoods() const;

    core::TurrelDescr* randTurrel() const;

    core::GalaxyDescr* galaxy(int_t) const;
    core::SectorDescr* sector(int_t) const;
    core::StarSystemDescr* starSystem(int_t) const;
    core::HyperSpaceDescr* hyperSpace(int_t) const;

    core::StarDescr* star(int_t) const;
    core::PlanetDescr* planet(int_t) const;
    core::WormHoleDescr* wormHole(int_t) const;
    core::AsteroidDescr* asteroid(int_t) const;
    core::ContainerDescr* container(int_t) const;
    core::BulletDescr* bullet(int_t) const;
    core::NpcDescr* npc(int_t) const;
    core::ShipDescr* ship(int_t) const;
    core::SatelliteDescr* satellite(int_t) const;
    core::SpaceStationDescr* spaceStation(int_t) const;

    // dock
    core::KosmoportDescr* kosmoport(int_t) const;
    core::NatureLandDescr* natureLand(int_t) const;
    core::AngarDescr* angar(int_t) const;
    core::StoreDescr* store(int_t) const;
    core::ShopDescr* shop(int_t) const;
    core::GovermentDescr* goverment(int_t) const;

    core::ScanerDescr* scaner(int_t) const;
    core::DriveDescr* drive(int_t) const;
    core::BakDescr* bak(int_t) const;
    core::DroidDescr* droid(int_t) const;
    core::GrappleDescr* grapple(int_t) const;
    core::LazerDescr* lazer(int_t) const;
    core::ProtectorDescr* protector(int_t) const;
    core::RadarDescr* radar(int_t) const;
    core::RocketDescr* rocket(int_t) const;
    // other
    core::GoodsDescr* goods(int_t) const;

    core::MeshDescr* mesh(int_t) const;
    core::MaterialDescr* material(int_t) const;

    core::MeshDescr* randMesh(mesh::Type) const;
    core::MaterialDescr* randMaterial(texture::Type) const;

    Collector<core::MeshDescr>* meshes() const { return m_meshes; }
    Collector<core::MaterialDescr>* materials() const { return m_materials; }

private:
    Collector<core::MeshDescr>* m_meshes = nullptr;
    Collector<core::MaterialDescr>* m_materials = nullptr;

    std::map<int_t, core::BaseDescr*> m_descriptors;
    std::map<core::Type, std::vector<core::BaseDescr*>> m_descriptorsTypes;

    void __generate();
//    void clear();

    void __clear();
    void __save();
    void __load();

    void __resolveId(core::BaseDescr*);
    void __resolveId(ceti::BaseDescr*);

    ceti::pack<int_t> __ids(core::Type) const;

    IdGenerator m_idGenerator;
}; 

} // namespace manager
} // namespace core
