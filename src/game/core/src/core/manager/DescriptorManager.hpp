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

class Galaxy;
class Sector;
class StarSystem;
class HyperSpace;

class Star;
class Planet;
class WormHole;
class Asteroid;
class Container;
class Bullet;
class Npc;
class Ship;
class SpaceStation;
class Satellite;

// dock
class Kosmoport;
class NatureLand;
class Angar;
class Store;
class Shop;
class Goverment;

class Scaner;
class Drive;
class Bak;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;

class Goods;

class Turrel;

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

    void add(descriptor::Base*);
    void add(descriptor::Mesh*);
    void add(descriptor::Material*);

    descriptor::Base* get(int_t) const;
    descriptor::Base* rand(descriptor::Type) const;
    bool hasType(descriptor::Type) const;

    descriptor::Galaxy* randGalaxy() const;
    descriptor::Sector* randSector() const;
    descriptor::StarSystem* randStarSystem() const;
    descriptor::HyperSpace* randHyperSpace() const;

    descriptor::Star* randStar() const;
    descriptor::Planet* randPlanet() const;
    descriptor::WormHole* randWormHole() const;
    descriptor::Asteroid* randAsteroid() const;
    descriptor::Container* randContainer() const;
    descriptor::Bullet* randBullet() const;
    descriptor::Npc* randNpc() const;
    descriptor::Ship* randShip() const;
    descriptor::Satellite* randSatellite() const;
    descriptor::SpaceStation* randSpaceStation() const;

    // dock
    descriptor::Kosmoport* randKosmoport() const;
    descriptor::NatureLand* randNatureLand() const;
    descriptor::Angar* randAngar() const;
    descriptor::Store* randStore() const;
    descriptor::Shop* randShop() const;
    descriptor::Goverment* randGoverment() const;

    descriptor::Scaner* randScaner() const;
    descriptor::Drive* randDrive() const;
    descriptor::Bak* randBak() const;
    descriptor::Droid* randDroid() const;
    descriptor::Grapple* randGrapple() const;
    descriptor::Lazer* randLazer() const;
    descriptor::Protector* randProtector() const;
    descriptor::Radar* randRadar() const;
    descriptor::Rocket* randRocket() const;

    // other
    descriptor::Goods* randGoods() const;

    descriptor::Turrel* randTurrel() const;

    descriptor::Galaxy* galaxy(int_t) const;
    descriptor::Sector* sector(int_t) const;
    descriptor::StarSystem* starSystem(int_t) const;
    descriptor::HyperSpace* hyperSpace(int_t) const;

    descriptor::Star* star(int_t) const;
    descriptor::Planet* planet(int_t) const;
    descriptor::WormHole* wormHole(int_t) const;
    descriptor::Asteroid* asteroid(int_t) const;
    descriptor::Container* container(int_t) const;
    descriptor::Bullet* bullet(int_t) const;
    descriptor::Npc* npc(int_t) const;
    descriptor::Ship* ship(int_t) const;
    descriptor::Satellite* satellite(int_t) const;
    descriptor::SpaceStation* spaceStation(int_t) const;

    // dock
    descriptor::Kosmoport* kosmoport(int_t) const;
    descriptor::NatureLand* natureLand(int_t) const;
    descriptor::Angar* angar(int_t) const;
    descriptor::Store* store(int_t) const;
    descriptor::Shop* shop(int_t) const;
    descriptor::Goverment* goverment(int_t) const;

    descriptor::Scaner* scaner(int_t) const;
    descriptor::Drive* drive(int_t) const;
    descriptor::Bak* bak(int_t) const;
    descriptor::Droid* droid(int_t) const;
    descriptor::Grapple* grapple(int_t) const;
    descriptor::Lazer* lazer(int_t) const;
    descriptor::Protector* protector(int_t) const;
    descriptor::Radar* radar(int_t) const;
    descriptor::Rocket* rocket(int_t) const;
    // other
    descriptor::Goods* goods(int_t) const;

    descriptor::Mesh* mesh(int_t) const;
    descriptor::Material* material(int_t) const;

    descriptor::Mesh* randMesh(mesh::Type) const;
    descriptor::Material* randMaterial(texture::Type) const;

    Collector<descriptor::Mesh>* meshes() const { return m_meshes; }
    Collector<descriptor::Material>* materials() const { return m_materials; }

    void generate();
    void clear();

private:
    Collector<descriptor::Mesh>* m_meshes = nullptr;
    Collector<descriptor::Material>* m_materials = nullptr;

    std::map<int_t, descriptor::Base*> m_descriptors;
    std::map<descriptor::Type, std::vector<descriptor::Base*>> m_descriptorsTypes;

    void __clear();
    void __save();
    void __load();

    void __resolveId(descriptor::Base*);
    void __resolveId(ceti::descriptor::Base*);

    ceti::pack<int_t> __ids(descriptor::Type) const;

    IdGenerator m_idGenerator;
}; 

} // namespace manager
} // namespace core
