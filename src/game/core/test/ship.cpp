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

#include <core/type/PlaceType.hpp>
#include <core/common/Global.hpp>

#include <core/descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/starsystem.hpp>
#include <core/item/equipment/ALL>
#include <core/spaceobject/ALL>
#include <core/slot/ItemSlot.hpp>

#include <core/model/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Container.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <core/manager/EntityManager.hpp>
#include <core/communication/MessageManager.hpp>

#include <gtest/gtest.h>

TEST(ship, create)
{
    control::Ship* ship = builder::Ship::gen();

    EXPECT_EQ(ship->descriptor()->bakSlotNum(), ship->bakSlots().size());
    EXPECT_EQ(ship->descriptor()->driveSlotNum(), ship->driveSlots().size());
    EXPECT_EQ(ship->descriptor()->radarSlotNum(), ship->radarSlots().size());
    EXPECT_EQ(ship->descriptor()->scanerSlotNum(), ship->scanerSlots().size());
    EXPECT_EQ(ship->descriptor()->grappleSlotNum(), ship->grappleSlots().size());
    EXPECT_EQ(ship->descriptor()->droidSlotNum(), ship->droidSlots().size());
    EXPECT_EQ(ship->descriptor()->protectorSlotNum(), ship->protectorSlots().size());
    EXPECT_EQ(ship->descriptor()->weaponSlotNum(), ship->weaponSlots().size());
    EXPECT_EQ(ship->descriptor()->cargoSlotNum(), ship->cargoSlots().size());
}

TEST(ship, drop_item_to_space)
{
    /* create objects */
    control::StarSystem* starsystem = builder::StarSystem::gen();
    control::Ship* ship = builder::Ship::gen();

    /* equip ship */
    control::item::Drive* drive = builder::item::Drive::gen();
    ship->manage(drive);

    /* add ship */
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship->model()->place(), place::Type::NONE);
    starsystem->add(ship, pos, dir);
    EXPECT_EQ(ship->model()->place(), place::Type::SPACE);

    /* drop item to space */
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship->dropItemToSpace(entity::Type::DRIVE_SLOT));
    EXPECT_EQ(starsystem->containers().size(), 1);
    assert(starsystem->containers()[0]);

    control::Container* container = starsystem->containers()[0];
    EXPECT_EQ(container->position(), pos);
    EXPECT_EQ(container->model()->place(), place::Type::SPACE);
    EXPECT_EQ(container->itemSlot()->item(), drive);
}

TEST(ship, base_shoot_to_ship)
{
    /* create objects */
    control::Ship* ship1 = builder::Ship::gen();
    control::Ship* ship2 = builder::Ship::gen();

    /* initiate shoot */
    ship1->prepareWeapons();
    ship1->selectAllWeapons();
    ship1->setWeaponTarget(ship2);

    int actual_damage = ship1->guessDamage() * ship2->adjustDissipateFilter();
    int armor_init = ship2->model()->armor();

    ship1->fire(/*timer=*/0, /*rate=*/1.0);

    EXPECT_TRUE((armor_init - actual_damage) - ship2->model()->armor() <= 1);
}

TEST(ship, kill)
{
    /* create objects */
    control::Ship* ship = builder::Ship::gen();

    ship->hit(100000);
    EXPECT_EQ(0, ship->model()->armor());
}

namespace {

void compareSpaceObjectModels(model::SpaceObject* m1, model::SpaceObject* m2)
{
    EXPECT_EQ(m1->armor(), m2->armor());
    EXPECT_EQ(m1->parent(), m2->parent());
    EXPECT_EQ(m1->starsystem(), m2->starsystem());
    EXPECT_EQ(m1->place(), m2->place());
    //EXPECT_EQ(m1->mass(), m2->mass());
    EXPECT_EQ(m1->givenExpirience(), m2->givenExpirience());

//    EXPECT_EQ(m1->properties(), m2->properties());
//    EXPECT_EQ(m1->needs(), m2->needs());
}

void compareVehileModels(model::Vehicle* m1, model::Vehicle* m2)
{
    EXPECT_EQ(m1->npc(), m2->npc());
    EXPECT_EQ(m1->dock(), m2->dock());
    EXPECT_EQ(m1->land(), m2->land());
    EXPECT_EQ(m1->items(), m2->items());

//    EXPECT_EQ(m1->properties(), m2->properties());
//    EXPECT_EQ(m1->needs(), m2->needs());

    compareSpaceObjectModels(m1, m2);
}

void compareShipModels(model::Ship* m1, model::Ship* m2)
{
    EXPECT_EQ(m1->data(), m2->data());

    compareVehileModels(m1, m2);
}

void compareVehicleProperties(const control::Vehicle::Propetries& origin, const control::Vehicle::Propetries& clone)
{
    EXPECT_EQ(origin.free_space, clone.free_space);
    EXPECT_EQ(origin.protection, clone.protection);
    EXPECT_EQ(origin.radar, clone.radar);
    EXPECT_EQ(origin.speed, clone.speed);
    EXPECT_EQ(origin.energy, clone.energy);
    EXPECT_EQ(origin.hyper, clone.hyper);
    EXPECT_EQ(origin.repair, clone.repair);
    EXPECT_EQ(origin.freeze, clone.freeze);
    EXPECT_EQ(origin.scan, clone.scan);
    EXPECT_EQ(origin.grab_strength, clone.grab_strength);
    EXPECT_EQ(origin.grab_radius, clone.grab_radius);
    EXPECT_EQ(origin.temperature, clone.temperature);
    EXPECT_EQ(origin.artefact_gravity, clone.artefact_gravity);
    EXPECT_EQ(origin.artefact_protection, clone.artefact_protection);
    EXPECT_EQ(origin.total_damage, clone.total_damage);
    EXPECT_EQ(origin.fire_radius_min, clone.fire_radius_min);
    EXPECT_EQ(origin.fire_radius_max, clone.fire_radius_max);
    EXPECT_EQ(origin.equipment_radar, clone.equipment_radar);
    EXPECT_EQ(origin.shield_effect_enabled, clone.shield_effect_enabled);
    EXPECT_EQ(origin.hibernate_mode_enabled, clone.hibernate_mode_enabled);
}

} // namespace


void testShipCloneScenario(control::Ship* ship)
{
    control::Vehicle::Propetries properties = ship->properties(); // we need copy, not reference

    model::Ship* model = new model::Ship(ship->model()->data());
    control::Ship* clone = new control::Ship(ship->descriptor(), model);

    compareShipModels(ship->model(), model);
    compareVehicleProperties(properties, clone->properties());
}

TEST(ship, equip_and_clone)
{
    control::Ship* ship = builder::Ship::gen();
    ship->manage( builder::item::Bak::gen() );
    ship->manage( builder::item::Drive::gen() );
    ship->manage( builder::item::Scaner::gen() );
    ship->manage( builder::item::Droid::gen() );
    ship->manage( builder::item::Radar::gen() );
    ship->manage( builder::item::Protector::gen() );
    ship->load( builder::item::Protector::gen() );
    ship->load( builder::item::Lazer::gen() );
    ship->load( builder::item::Rocket::gen() );

    testShipCloneScenario(ship);
}

TEST(ship, dockingEvent)
{
    // create
    control::StarSystem* starsystem = builder::StarSystem::gen();
    control::Star* star = builder::Star::gen();
    control::Planet* planet = builder::Planet::gen();
    control::Ship* ship = builder::Ship::gen();

    starsystem->add(star);
    starsystem->add(planet);
    starsystem->add(ship, planet->position());

    // starsystem
    EXPECT_EQ(1, starsystem->ships().size());

    // ship
    EXPECT_EQ(planet->position(), ship->position());
    EXPECT_EQ(place::Type::SPACE, ship->place());
    EXPECT_EQ(nullptr, ship->land());

    for (int i=0; i<2; ++i) {
        /** docking */

        // drive complex
        EXPECT_EQ(nullptr, ship->driveComplex().target());
        EXPECT_EQ(DriveComplex::Action::NONE, ship->driveComplex().action());

        ship->dock(planet);

        // drive complex
        EXPECT_EQ(planet, ship->driveComplex().target());
        EXPECT_EQ(DriveComplex::Action::DOCKING, ship->driveComplex().action());

        event::doDockShip(ship->id(), planet->land()->id());

        // starsystem
        EXPECT_EQ(0, starsystem->ships().size());

        // ship
        EXPECT_EQ(planet->position(), ship->position());
        EXPECT_EQ(place::Type::KOSMOPORT, ship->place());
        EXPECT_EQ(planet->land(), ship->land());

        /** launching */
        event::doLaunchShip(ship->id(), planet->land()->id());

        // starsystem
        EXPECT_EQ(1, starsystem->ships().size());

        // ship
        EXPECT_EQ(planet->position(), ship->position());
        EXPECT_EQ(place::Type::SPACE, ship->place());
        EXPECT_EQ(nullptr, ship->land());
    }

}

