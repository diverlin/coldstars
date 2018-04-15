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

namespace descriptor {

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

    void add(descriptor::BaseDescr*);
    void add(descriptor::MeshDescr*);
    void add(descriptor::MaterialDescr*);

    descriptor::BaseDescr* get(int_t) const;
    descriptor::BaseDescr* rand(descriptor::Type) const;
    bool hasType(descriptor::Type) const;

    descriptor::GalaxyDescr* randGalaxy() const;
    descriptor::SectorDescr* randSector() const;
    descriptor::StarSystemDescr* randStarSystem() const;
    descriptor::HyperSpaceDescr* randHyperSpace() const;

    descriptor::StarDescr* randStar() const;
    descriptor::PlanetDescr* randPlanet() const;
    descriptor::WormHoleDescr* randWormHole() const;
    descriptor::AsteroidDescr* randAsteroid() const;
    descriptor::ContainerDescr* randContainer() const;
    descriptor::BulletDescr* randBullet() const;
    descriptor::NpcDescr* randNpc() const;
    descriptor::ShipDescr* randShip() const;
    descriptor::SatelliteDescr* randSatellite() const;
    descriptor::SpaceStationDescr* randSpaceStation() const;

    // dock
    descriptor::KosmoportDescr* randKosmoport() const;
    descriptor::NatureLandDescr* randNatureLand() const;
    descriptor::AngarDescr* randAngar() const;
    descriptor::StoreDescr* randStore() const;
    descriptor::ShopDescr* randShop() const;
    descriptor::GovermentDescr* randGoverment() const;

    descriptor::ScanerDescr* randScaner() const;
    descriptor::DriveDescr* randDrive() const;
    descriptor::BakDescr* randBak() const;
    descriptor::DroidDescr* randDroid() const;
    descriptor::GrappleDescr* randGrapple() const;
    descriptor::LazerDescr* randLazer() const;
    descriptor::ProtectorDescr* randProtector() const;
    descriptor::RadarDescr* randRadar() const;
    descriptor::RocketDescr* randRocket() const;

    // other
    descriptor::GoodsDescr* randGoods() const;

    descriptor::TurrelDescr* randTurrel() const;

    descriptor::GalaxyDescr* galaxy(int_t) const;
    descriptor::SectorDescr* sector(int_t) const;
    descriptor::StarSystemDescr* starSystem(int_t) const;
    descriptor::HyperSpaceDescr* hyperSpace(int_t) const;

    descriptor::StarDescr* star(int_t) const;
    descriptor::PlanetDescr* planet(int_t) const;
    descriptor::WormHoleDescr* wormHole(int_t) const;
    descriptor::AsteroidDescr* asteroid(int_t) const;
    descriptor::ContainerDescr* container(int_t) const;
    descriptor::BulletDescr* bullet(int_t) const;
    descriptor::NpcDescr* npc(int_t) const;
    descriptor::ShipDescr* ship(int_t) const;
    descriptor::SatelliteDescr* satellite(int_t) const;
    descriptor::SpaceStationDescr* spaceStation(int_t) const;

    // dock
    descriptor::KosmoportDescr* kosmoport(int_t) const;
    descriptor::NatureLandDescr* natureLand(int_t) const;
    descriptor::AngarDescr* angar(int_t) const;
    descriptor::StoreDescr* store(int_t) const;
    descriptor::ShopDescr* shop(int_t) const;
    descriptor::GovermentDescr* goverment(int_t) const;

    descriptor::ScanerDescr* scaner(int_t) const;
    descriptor::DriveDescr* drive(int_t) const;
    descriptor::BakDescr* bak(int_t) const;
    descriptor::DroidDescr* droid(int_t) const;
    descriptor::GrappleDescr* grapple(int_t) const;
    descriptor::LazerDescr* lazer(int_t) const;
    descriptor::ProtectorDescr* protector(int_t) const;
    descriptor::RadarDescr* radar(int_t) const;
    descriptor::RocketDescr* rocket(int_t) const;
    // other
    descriptor::GoodsDescr* goods(int_t) const;

    descriptor::MeshDescr* mesh(int_t) const;
    descriptor::MaterialDescr* material(int_t) const;

    descriptor::MeshDescr* randMesh(mesh::Type) const;
    descriptor::MaterialDescr* randMaterial(texture::Type) const;

    Collector<descriptor::MeshDescr>* meshes() const { return m_meshes; }
    Collector<descriptor::MaterialDescr>* materials() const { return m_materials; }

    void generate();
    void clear();

private:
    Collector<descriptor::MeshDescr>* m_meshes = nullptr;
    Collector<descriptor::MaterialDescr>* m_materials = nullptr;

    std::map<int_t, descriptor::BaseDescr*> m_descriptors;
    std::map<descriptor::Type, std::vector<descriptor::BaseDescr*>> m_descriptorsTypes;

    void __clear();
    void __save();
    void __load();

    void __resolveId(descriptor::BaseDescr*);
    void __resolveId(ceti::descriptor::Base*);

    ceti::pack<int_t> __ids(descriptor::Type) const;

    IdGenerator m_idGenerator;
}; 

} // namespace manager
} // namespace core
