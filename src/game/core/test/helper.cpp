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

#include "helper.hpp"

#include <core/generator/DescriptorGenerator.hpp>

#include <core/descriptor/world/StarSystemDescriptor.hpp>
#include <core/world/starsystem.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>

#include <core/spaceobject/ALL>
#include <core/builder/spaceobject/ALL>
#include <core/model/spaceobject/ALL>

// Bak
#include <core/builder/item/equipment/BakBuilder.hpp>
#include <core/descriptor/item/equipment/Bak.hpp>
#include <core/model/item/equipment/Bak.hpp>
#include <core/item/equipment/Bak.hpp>

// Drive
#include <core/builder/item/equipment/DriveBuilder.hpp>
#include <core/descriptor/item/equipment/Drive.hpp>
#include <core/model/item/equipment/Drive.hpp>
#include <core/item/equipment/Drive.hpp>

// Droid
#include <core/builder/item/equipment/DroidBuilder.hpp>
#include <core/descriptor/item/equipment/Droid.hpp>
#include <core/model/item/equipment/Droid.hpp>
#include <core/item/equipment/Droid.hpp>

// Grapple
#include <core/builder/item/equipment/GrappleBuilder.hpp>
#include <core/descriptor/item/equipment/Grapple.hpp>
#include <core/model/item/equipment/Grapple.hpp>
#include <core/item/equipment/Grapple.hpp>

// Lazer
#include <core/builder/item/equipment/LazerBuilder.hpp>
#include <core/descriptor/item/equipment/Lazer.hpp>
#include <core/model/item/equipment/Lazer.hpp>
#include <core/item/equipment/Lazer.hpp>

// Protector
#include <core/builder/item/equipment/ProtectorBuilder.hpp>
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/model/item/equipment/Protector.hpp>
#include <core/item/equipment/Protector.hpp>

// Radar
#include <core/builder/item/equipment/RadarBuilder.hpp>
#include <core/descriptor/item/equipment/Radar.hpp>
#include <core/model/item/equipment/Radar.hpp>
#include <core/item/equipment/Radar.hpp>

// Rocket
#include <core/builder/item/equipment/RocketBuilder.hpp>
#include <core/descriptor/item/equipment/Rocket.hpp>
#include <core/model/item/equipment/Rocket.hpp>
#include <core/item/equipment/Rocket.hpp>

// Scaner
#include <core/builder/item/equipment/ScanerBuilder.hpp>
#include <core/descriptor/item/equipment/Scaner.hpp>
#include <core/model/item/equipment/Scaner.hpp>
#include <core/item/equipment/Scaner.hpp>

#include <gtest/gtest.h>

//namespace test {

//control::StarSystem*
//genStarSystem() {
//    control::StarSystem* starsystem = builder::StarSystem::gen();
//    assert(starsystem);
//    return starsystem;
//}

//control::Star*
//genStar() {
//    model::Star* model = builder::Star::gen();
//    control::Star* star = new control::Star(model);
//    assert(star);
//    return star;
//}

//control::Planet*
//genPlanet() {
//    model::Planet* model = builder::Planet::gen();
//    control::Planet* planet = new control::Planet(model);
//    assert(planet);
//    return planet;
//}

//control::WormHole*
//genWormHole() {
//    model::WormHole* model = builder::WormHole::gen();
//    control::WormHole* wormhole = new control::WormHole(model);
//    assert(wormhole);
//    return wormhole;
//}

//control::Asteroid*
//genAsteroid() {
//    model::Asteroid* model = builder::Asteroid::gen();
//    control::Asteroid* asteroid = new control::Asteroid(model);
//    assert(asteroid);
//    return asteroid;
//}

//control::Container*
//genContainer() {
//    model::Container* model = builder::Container::gen();
//    control::Container* container = new control::Container(model);
//    assert(container);
//    return container;
//}

//control::SpaceStation*
//genSpaceStation() {
//    model::SpaceStation* model = builder::SpaceStation::gen();
//    control::SpaceStation* spacestation = new control::SpaceStation(model);
//    assert(spacestation);
//    return spacestation;
//}

//control::Ship*
//genShip() {
//    model::Ship* model = builder::Ship::gen();
//    control::Ship* ship = new control::Ship(model);
//    assert(ship);
//    return ship;
//}

//control::Satellite*
//genSatellite() {
//    model::Satellite* model = builder::Satellite::gen();
//    control::Satellite* satellite = new control::Satellite(model);
//    assert(satellite);
//    return satellite;
//}

//namespace item {

//control::item::Bak*
//genBak() {
//    model::item::Bak* model = builder::item::Bak::gen();
//    control::item::Bak* bak = new control::item::Bak(model);
//    assert(bak);
//    return bak;
//}

//control::item::Drive*
//genDrive() {
//    model::item::Drive* model = builder::item::Drive::gen();
//    control::item::Drive* drive = new control::item::Drive(model);
//    assert(drive);
//    return drive;
//}

//control::item::Droid*
//genDroid() {
//    model::item::Droid* model = builder::item::Droid::gen();
//    control::item::Droid* droid = new control::item::Droid(model);
//    assert(droid);
//    return droid;
//}

//control::item::Grapple*
//genGrapple() {
//    model::item::Grapple* model = builder::item::Grapple::gen();
//    control::item::Grapple* grapple = new control::item::Grapple(model);
//    assert(grapple);
//    return grapple;
//}

//control::item::Lazer*
//genLazer() {
//    model::item::Lazer* model = builder::item::Lazer::gen();
//    control::item::Lazer* lazer = new control::item::Lazer(model);
//    assert(lazer);
//    return lazer;
//}

//control::item::Protector*
//genProtector() {
//    model::item::Protector* model = builder::item::Protector::gen();
//    control::item::Protector* protector = new control::item::Protector(model);
//    assert(protector);
//    return protector;
//}

//control::item::Radar*
//genRadar() {
//    model::item::Radar* model = builder::item::Radar::gen();
//    control::item::Radar* radar = new control::item::Radar(model);
//    assert(radar);
//    return radar;
//}

//control::item::Rocket*
//genRocket() {
//    model::item::Rocket* model = builder::item::Rocket::gen();
//    control::item::Rocket* rocket = new control::item::Rocket(model);
//    assert(rocket);
//    return rocket;
//}

//control::item::Scaner*
//genScaner() {
//    model::item::Scaner* model = builder::item::Scaner::gen();
//    control::item::Scaner* scaner = new control::item::Scaner(model);
//    assert(scaner);
//    return scaner;
//}

//} // namespace item

//} // namespace test
