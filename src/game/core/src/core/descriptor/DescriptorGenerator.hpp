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

#include <ceti/type/IdType.hpp>

#include <vector>

namespace descriptor {

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

class Galaxy;
class Sector;
class Starsystem;
class Star;
class Planet;
class Asteroid;
class Ship;
class SpaceStation;
class Satellite;
class BaseOLD; // TODO: remove this

/* world */
descriptor::Galaxy* getNewGalaxy(const std::vector<int_t>&);
descriptor::Sector* getNewSector(const std::vector<int_t>&);
descriptor::Starsystem* getNewStarsystem(int race = NONE);

/* spaceobjects */
descriptor::Star* getNewStar();
descriptor::Planet* getNewPlanet();
descriptor::Asteroid* getNewAsteroid();
descriptor::Ship* getNewShip();
descriptor::SpaceStation* getNewSpaceStation();
descriptor::Satellite* getNewSatellite();
descriptor::BaseOLD* getNewContainer();

/* items */
namespace item {
descriptor::item::Bak* getNewBak(int race = NONE, int tech_level = NONE);
descriptor::item::Drive* getNewDrive(int race = NONE, int tech_level = NONE);
descriptor::item::Droid* getNewDroid(int race = NONE, int tech_level = NONE);
descriptor::item::Grapple* getNewGrapple(int race = NONE, int tech_level = NONE);
descriptor::item::Lazer* getNewLazer(int race = NONE, int tech_level = NONE);
descriptor::item::Protector* getNewProtector(int race = NONE, int tech_level = NONE);
descriptor::item::Radar* getNewRadar(int race = NONE, int tech_level = NONE);
descriptor::item::Rocket* getNewRocket(int race = NONE, int tech_level = NONE);
descriptor::item::Scaner* getNewScaner(int race = NONE, int tech_level = NONE);
} // namespace item

descriptor::BaseOLD* getNewBomb(int damage = NONE, int radius = NONE);

} // namespace descriptor
