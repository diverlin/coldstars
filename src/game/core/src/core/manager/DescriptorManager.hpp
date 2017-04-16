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

namespace item {
class Scaner;
class Drive;
class Bak;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
} // namespace item

class Manager
{
private:
    Manager();
    Manager(const Manager&) = delete;
    ~Manager() = default;
    Manager& operator=(const Manager&) = delete;

public:
    static Manager& get();

    void add(Base*);
    void add(Mesh*);
    void add(Material*);

    Base* get(int_t) const;
    Base* rand(Type) const;
    bool hasType(Type) const;

    Galaxy* randGalaxy() const;
    Sector* randSector() const;
    StarSystem* randStarSystem() const;
    HyperSpace* randHyperSpace() const;

    Star* randStar() const;
    Planet* randPlanet() const;
    WormHole* randWormHole() const;
    Asteroid* randAsteroid() const;
    Container* randContainer() const;
    Npc* randNpc() const;
    Ship* randShip() const;
    Satellite* randSatellite() const;
    SpaceStation* randSpaceStation() const;

    // dock
    Kosmoport* randKosmoport() const;
    NatureLand* randNatureLand() const;
    Angar* randAngar() const;
    Store* randStore() const;
    Shop* randShop() const;
    Goverment* randGoverment() const;

    item::Scaner* randScaner() const;
    item::Drive* randDrive() const;
    item::Bak* randBak() const;
    item::Droid* randDroid() const;
    item::Grapple* randGrapple() const;
    item::Lazer* randLazer() const;
    item::Protector* randProtector() const;
    item::Radar* randRadar() const;
    item::Rocket* randRocket() const;

    Galaxy* galaxy(int_t) const;
    Sector* sector(int_t) const;
    StarSystem* starSystem(int_t) const;
    HyperSpace* hyperSpace(int_t) const;

    Star* star(int_t) const;
    Planet* planet(int_t) const;
    WormHole* wormHole(int_t) const;
    Asteroid* asteroid(int_t) const;
    Container* container(int_t) const;
    Npc* npc(int_t) const;
    Ship* ship(int_t) const;
    Satellite* satellite(int_t) const;
    SpaceStation* spaceStation(int_t) const;

    // dock
    Kosmoport* kosmoport(int_t) const;
    NatureLand* natureLand(int_t) const;
    Angar* angar(int_t) const;
    Store* store(int_t) const;
    Shop* shop(int_t) const;
    Goverment* goverment(int_t) const;

    item::Scaner* scaner(int_t) const;
    item::Drive* drive(int_t) const;
    item::Bak* bak(int_t) const;
    item::Droid* droid(int_t) const;
    item::Grapple* grapple(int_t) const;
    item::Lazer* lazer(int_t) const;
    item::Protector* protector(int_t) const;
    item::Radar* radar(int_t) const;
    item::Rocket* rocket(int_t) const;

    Mesh* mesh(int_t) const;
    Material* material(int_t) const;

    Mesh* randMesh(mesh::Type) const;
    Material* randMaterial(texture::Type) const;

    Collector<Mesh>* meshes() const { return m_meshes; }
    Collector<Material>* materials() const { return m_materials; }

    void generate();
    void clear();

private:
    Collector<Mesh>* m_meshes = nullptr;
    Collector<Material>* m_materials = nullptr;

    std::map<int_t, Base*> m_descriptors;
    std::map<Type, std::vector<Base*>> m_descriptorsTypes;

    void __clear();
    void __save();
    void __load();

    void __resolveId(Base*);
    void __resolveId(ceti::descriptor::Base*);

    ceti::pack<int_t> __ids(Type) const;

    IdGenerator m_idGenerator;
}; 

} // namespace descriptor
