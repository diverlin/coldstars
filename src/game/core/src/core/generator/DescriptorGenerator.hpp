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

namespace core {

class GalaxyDescr;
class SectorDescr;
class StarSystemDescr;
class HyperSpaceDescr;

class StarDescr;
class PlanetDescr;
class WormHoleDescr;
class AsteroidDescr;
class NpcDescr;
class ShipDescr;
class SpaceStationDescr;
class SatelliteDescr;
class ContainerDescr;
class BulletDescr;

// dock
class KosmoportDescr;
class NatureLandDescr;
class AngarDescr;
class StoreDescr;
class ShopDescr;
class GovermentDescr;

class BakDescr;
class DriveDescr;
class DroidDescr;
class GrappleDescr;
class LazerDescr;
class ProtectorDescr;
class RadarDescr;
class RocketDescr;
class ScanerDescr;

// other
class GoodsDescr;

// parts
class TurrelDescr;

/* world */
core::GalaxyDescr* genGalaxy(const std::vector<int_t>&);
core::SectorDescr* genSector(const std::vector<int_t>&);
core::StarSystemDescr* genStarSystem(race::Type race = race::Type::NONE);
core::HyperSpaceDescr* genHyperSpace();

/* spaceobjects */
core::StarDescr* genStar();
core::PlanetDescr* genPlanet();
core::WormHoleDescr* genWormHole();
core::AsteroidDescr* genAsteroid();

core::NpcDescr* genNpc();
core::ShipDescr* genShip();
core::SpaceStationDescr* genSpaceStation();
core::SatelliteDescr* genSatellite();

core::ContainerDescr* genContainer();
core::BulletDescr* genBullet();

// dock
KosmoportDescr* genKosmoport(race::Type race = race::Type::NONE);
NatureLandDescr* genNatureLand();
AngarDescr* genAngar(race::Type race = race::Type::NONE);
StoreDescr* genStore(race::Type race = race::Type::NONE);
ShopDescr* genShop(race::Type race = race::Type::NONE);
GovermentDescr* genGoverment(race::Type race = race::Type::NONE);

/* items */
BakDescr* genBak(int race = NONE, int tech_level = NONE);
DriveDescr* genDrive(int race = NONE, int tech_level = NONE);
DroidDescr* genDroid(int race = NONE, int tech_level = NONE);
GrappleDescr* genGrapple(int race = NONE, int tech_level = NONE);
LazerDescr* genLazer(int race = NONE, int tech_level = NONE);
ProtectorDescr* genProtector(int race = NONE, int tech_level = NONE);
RadarDescr* genRadar(int race = NONE, int tech_level = NONE);
RocketDescr* genRocket(int race = NONE, int tech_level = NONE);
ScanerDescr* genScaner(int race = NONE, int tech_level = NONE);

// other
GoodsDescr* genGoods();
//Bomb* genBomb(int damage = NONE, int radius = NONE);

//parts
TurrelDescr* genTurrel();

} // namespace core
