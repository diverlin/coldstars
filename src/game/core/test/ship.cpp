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

#include <core/model/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Container.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <core/manager/EntityManager.hpp>

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

TEST(ship, equip)
{
    control::Ship* ship = builder::Ship::gen();

    control::item::Bak* bak = builder::item::Bak::gen();
    control::item::Drive* drive = builder::item::Drive::gen();
    control::item::Droid* droid = builder::item::Droid::gen();
    control::item::Grapple* grapple = builder::item::Grapple::gen();
    control::item::Lazer* lazer = builder::item::Lazer::gen();
    control::item::Protector* protector = builder::item::Protector::gen();
    control::item::Radar* radar = builder::item::Radar::gen();
    control::item::Rocket* rocket = builder::item::Rocket::gen();
    control::item::Scaner* scaner = builder::item::Scaner::gen();

    ship->manage(bak);
    ship->manage(drive);
    ship->manage(droid);
    ship->manage(grapple);
    ship->manage(lazer);
    ship->manage(protector);
    ship->manage(radar);
    ship->manage(rocket);
    ship->manage(scaner);
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
    EXPECT_EQ(ship->model()->place(), place::Type::KOSMOS);

    /* drop item to space */
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship->dropItemToSpace(entity::Type::DRIVE_SLOT));
    EXPECT_EQ(starsystem->containers().size(), 1);
    assert(starsystem->containers()[0]);

    control::Container* container = starsystem->containers()[0];
    EXPECT_EQ(container->position(), pos);
    EXPECT_EQ(container->model()->place(), place::Type::KOSMOS);
    EXPECT_EQ(container->itemSlot()->item(), drive);
}

TEST(ship, base_ship_shoot)
{
    /* create objects */
    control::StarSystem* starsystem = builder::StarSystem::gen();
    control::Ship* ship1 = builder::Ship::gen();
    control::Ship* ship2 = builder::Ship::gen();

    float distance = 10.0f;

    /* add objects */
    starsystem->add(ship1, /*pos=*/glm::vec3(0.0f), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));
    starsystem->add(ship2, /*pos=*/glm::vec3(distance), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));

    /* initiate shoot */
    ship1->prepareWeapons();
    ship1->weaponComplex().activateWeapons();
    ship1->setWeaponTarget(ship2->model());
    int damage = ship1->guessDamage(distance) * ship2->adjustDissipateFilter();
    int armor_init = ship2->model()->armor();
    ship1->fire(/*timer=*/0, /*rate=*/1.0);
    EXPECT_TRUE((armor_init - damage) - ship2->model()->armor() <= 1);
}

TEST(ship, criticalDamage)
{
    /* create objects */
    control::Ship* ship = builder::Ship::gen();

    ship->hit(ship->criticalDamage());
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

void compareVehicleControls(control::Vehicle* c1, control::Vehicle* c2)
{
    EXPECT_EQ(c1->properties().free_space, c2->properties().free_space);
    EXPECT_EQ(c1->properties().protection, c2->properties().protection);
    EXPECT_EQ(c1->properties().radar, c2->properties().radar);
    EXPECT_EQ(c1->properties().speed, c2->properties().speed);
    EXPECT_EQ(c1->properties().energy, c2->properties().energy);
    EXPECT_EQ(c1->properties().hyper, c2->properties().hyper);
    EXPECT_EQ(c1->properties().repair, c2->properties().repair);
    EXPECT_EQ(c1->properties().freeze, c2->properties().freeze);
    EXPECT_EQ(c1->properties().scan, c2->properties().scan);
    EXPECT_EQ(c1->properties().grab_strength, c2->properties().grab_strength);
    EXPECT_EQ(c1->properties().grab_radius, c2->properties().grab_radius);
    EXPECT_EQ(c1->properties().temperature, c2->properties().temperature);
    EXPECT_EQ(c1->properties().artefact_gravity, c2->properties().artefact_gravity);
    EXPECT_EQ(c1->properties().artefact_protection, c2->properties().artefact_protection);
    EXPECT_EQ(c1->properties().total_damage, c2->properties().total_damage);
    EXPECT_EQ(c1->properties().fire_radius_min, c2->properties().fire_radius_min);
    EXPECT_EQ(c1->properties().fire_radius_max, c2->properties().fire_radius_max);
    EXPECT_EQ(c1->properties().equipment_radar, c2->properties().equipment_radar);
    EXPECT_EQ(c1->properties().shield_effect_enabled, c2->properties().shield_effect_enabled);
    EXPECT_EQ(c1->properties().hibernate_mode_enabled, c2->properties().hibernate_mode_enabled);
}

void compareShipControls(control::Ship* c1, control::Ship* c2)
{
    compareVehicleControls(c1, c2);
}

} // namespace


void testShipClone(control::Ship* ship)
{
    model::Ship* model = new model::Ship(ship->model()->data());
    control::Ship* clone = new control::Ship(model, ship->descriptor());

    compareShipModels(ship->model(), model);
    compareShipControls(ship, clone);
}

TEST(ship, clone)
{
    // items
    control::item::Bak* bak = builder::item::Bak::gen();
    control::item::Drive* drive = builder::item::Drive::gen();
    control::item::Scaner* scaner = builder::item::Scaner::gen();
    control::item::Droid* droid = builder::item::Droid::gen();
    control::item::Radar* radar = builder::item::Radar::gen();
    control::item::Protector* protector = builder::item::Protector::gen();
    control::item::Protector* protector2 = builder::item::Protector::gen();
    control::item::Lazer* lazer = builder::item::Lazer::gen();
    //control::item::Rocket* rocket = builder::item::Rocket::gen();

    control::Ship* ship = builder::Ship::gen();
    ship->manage(bak);
    ship->manage(drive);
    ship->manage(scaner);
    ship->manage(droid);
    ship->manage(radar);
    ship->manage(protector);
    ship->load(protector2);
    ship->load(lazer);
    //ship->load(rocket);

    testShipClone(ship);
}



