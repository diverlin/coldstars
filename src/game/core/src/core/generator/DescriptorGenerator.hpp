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

#include <core/type/RaceType.hpp>

#include <ceti/type/IdType.hpp>

#include <vector>

namespace descriptor {

class Galaxy;
class Sector;
class StarSystem;
class HyperSpace;

class Star;
class Planet;
class WormHole;
class Asteroid;
class Npc;
class Ship;
class SpaceStation;
class Satellite;
class Container;

// dock
class Kosmoport;
class NatureLand;
class Angar;
class Store;
class Shop;
class Goverment;

namespace item {
class Bak;
class Drive;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
class Scaner;
} // namespace item

// parts
class Turrel;

/* world */
descriptor::Galaxy* genGalaxy(const std::vector<int_t>&);
descriptor::Sector* genSector(const std::vector<int_t>&);
descriptor::StarSystem* genStarSystem(race::Type race = race::Type::NONE);
descriptor::HyperSpace* genHyperSpace();

/* spaceobjects */
descriptor::Star* genStar();
descriptor::Planet* genPlanet();
descriptor::WormHole* genWormHole();
descriptor::Asteroid* genAsteroid();

descriptor::Npc* genNpc();
descriptor::Ship* genShip();
descriptor::SpaceStation* genSpaceStation();
descriptor::Satellite* genSatellite();

descriptor::Container* genContainer();

// dock
Kosmoport* genKosmoport(race::Type race = race::Type::NONE);
NatureLand* genNatureLand();
Angar* genAngar(race::Type race = race::Type::NONE);
Store* genStore(race::Type race = race::Type::NONE);
Shop* genShop(race::Type race = race::Type::NONE);
Goverment* genGoverment(race::Type race = race::Type::NONE);

/* items */
namespace item {
Bak* genBak(int race = NONE, int tech_level = NONE);
Drive* genDrive(int race = NONE, int tech_level = NONE);
Droid* genDroid(int race = NONE, int tech_level = NONE);
Grapple* genGrapple(int race = NONE, int tech_level = NONE);
Lazer* genLazer(int race = NONE, int tech_level = NONE);
Protector* genProtector(int race = NONE, int tech_level = NONE);
Radar* genRadar(int race = NONE, int tech_level = NONE);
Rocket* genRocket(int race = NONE, int tech_level = NONE);
Scaner* genScaner(int race = NONE, int tech_level = NONE);
//Bomb* genBomb(int damage = NONE, int radius = NONE);
} // namespace item

//parts
Turrel* genTurrel();

} // namespace descriptor
