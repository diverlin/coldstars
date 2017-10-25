#include "TelegramHandler.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/descriptor/comm/Hit.hpp>
#include <core/descriptor/comm/Dock.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>
#include <core/descriptor/comm/AddingPositional.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>

#include <core/descriptor/Base.hpp>
#include <core/descriptor/comm/Creation.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>

#include <core/spaceobject/ALL>
#include <core/item/ALL>
#include <core/pilot/Npc.hpp>
#include <core/descriptor/item/equipment/Rocket.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/world/galaxy.hpp>
#include <core/world/Sector.hpp>
#include <core/world/starsystem.hpp>
#include <core/world/HyperSpace.hpp>

#include <core/builder/world/ALL>
#include <core/builder/spaceobject/ALL>
#include <core/builder/pilot/NpcBuilder.hpp>

#include <core/builder/item/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
#include <core/builder/item/artefact/ALL>
#endif // USE_ARTEFACTS
#include <core/builder/item/other/ALL>

#include <core/builder/world/StarSystemBuilder.hpp>

#include <ceti/Logger.hpp>

namespace core {
namespace comm {
namespace event {

/** TRANSITION */
void addSectorToGalaxy(int_t object, int_t parent, const glm::vec3& position)
{
    control::Sector* sector = shortcuts::entities()->sector(object);
    control::Galaxy* galaxy = shortcuts::entities()->galaxy(parent);
    galaxy->add(sector, position);
}
void addStarSystemToSector(int_t object, int_t parent, const glm::vec3& position) {
    control::StarSystem* starsystem = shortcuts::entities()->starsystem(object);
    control::Sector* sector = shortcuts::entities()->sector(parent);
    sector->add(starsystem, position);
}
void addNpcToShip(int_t object, int_t parent) {
    control::Npc* npc = shortcuts::entities()->npc(object);
    control::Ship* ship = shortcuts::entities()->ship(parent);
    ship->bindNpc(npc);
}

// items
void mountItem(int_t object, int_t parent) {
    control::Ship* ship = shortcuts::entities()->ship(parent);
    control::Item* item = shortcuts::entities()->item(object);
    ship->mount(item);
}
void loadItem(int_t object, int_t parent) {
    control::Item* item = shortcuts::entities()->item(object);
    control::Ship* ship = shortcuts::entities()->ship(parent);
    ship->load(item);
}
/** */

/** CREATE */
void createGalaxy(int_t descriptor, int_t object) {
    control::Galaxy* galaxy = builder::Galaxy::gen(descriptor, object);
    core::shortcuts::entities()->add(galaxy);
    core::shortcuts::entities()->setGalaxy(galaxy);
}
void createSector(int_t descriptor, int_t object) {
    control::Sector* sector = builder::Sector::gen(descriptor, object);
    core::shortcuts::entities()->add(sector);
}
void createStarSystem(int_t descriptor, int_t object) {
    control::StarSystem* starsystem = builder::StarSystem::gen(descriptor, object);
    core::shortcuts::entities()->add(starsystem);
}
void createNpc(int_t descriptor, int_t object) {
    control::Npc* npc = builder::Npc::gen(descriptor, object);
    core::shortcuts::entities()->add(npc);
}

// spaceobjects
void createStar(int_t descriptor, int_t object) {
    control::Star* star = builder::Star::gen(descriptor, object);
    core::shortcuts::entities()->add(star);
}
void createPlanet(int_t descriptor, int_t object) {
    control::Planet* planet = builder::Planet::gen(descriptor, object);
    core::shortcuts::entities()->add(planet);
}
void createAsteroid(int_t descriptor, int_t object) {
    control::Asteroid* asteroid = builder::Asteroid::gen(descriptor, object);
    core::shortcuts::entities()->add(asteroid);
}
void createShip(int_t descriptor, int_t object) {
    control::Ship* ship = builder::Ship::gen(descriptor, object);
    core::shortcuts::entities()->add(ship);
}

void createBomb(int_t descriptor, int_t object) {
    assert(false);
}

void createGoods(int_t descriptor, int_t object) {
    control::item::Goods* goods = builder::item::Goods::gen(descriptor, object);
    assert(false);
    core::shortcuts::entities()->add(goods); // is it needed?
}
void createContainer(int_t descriptor, int_t object, int_t item) {
    control::Container* container = builder::Container::gen(descriptor, object, item);
    core::shortcuts::entities()->add(container);
}

void createBullet(int_t owner, int_t weapon, int_t target_id) {
    control::Vehicle* vehicle = core::shortcuts::entities()->vehicle(owner);
    control::item::Rocket* rocket = core::shortcuts::entities()->rocket(weapon);
    control::SpaceObject* target = core::shortcuts::entities()->spaceObject(target_id);
    assert(rocket->type() == entity::Type::ROCKET_EQUIPMENT);

    descriptor::Bullet* bullet_descriptor = core::shortcuts::descriptors()->bullet(rocket->descriptor()->bulletDescriptor());
    control::Bullet* bullet = builder::Bullet::gen(bullet_descriptor, rocket->damage());
    bullet->setOwnerId(vehicle->id());
    bullet->setTarget(target);
    vehicle->starsystem()->add(bullet, vehicle->position(), vehicle->direction());
}


// items
void createBak(int_t descriptor, int_t object) {
    control::item::Bak* bak = builder::item::Bak::gen(descriptor, object);
    core::shortcuts::entities()->add(bak);
}
void createDrive(int_t descriptor, int_t object) {
    control::item::Drive* drive = builder::item::Drive::gen(descriptor, object);
    core::shortcuts::entities()->add(drive);
}
void createDroid(int_t descriptor, int_t object) {
    control::item::Droid* droid = builder::item::Droid::gen(descriptor, object);
    core::shortcuts::entities()->add(droid);
}
void createGrapple(int_t descriptor, int_t object) {
    control::item::Grapple* grapple = builder::item::Grapple::gen(descriptor, object);
    core::shortcuts::entities()->add(grapple);
}
void createProtector(int_t descriptor, int_t object) {
    control::item::Protector* protector = builder::item::Protector::gen(descriptor, object);
    core::shortcuts::entities()->add(protector);
}
void createScaner(int_t descriptor, int_t object) {
    control::item::Scaner* scaner = builder::item::Scaner::gen(descriptor, object);
    core::shortcuts::entities()->add(scaner);
}
void createRadar(int_t descriptor, int_t object) {
    control::item::Radar* radar = builder::item::Radar::gen(descriptor, object);
    core::shortcuts::entities()->add(radar);
}
void createLazer(int_t descriptor, int_t object) {
    control::item::Lazer* lazer = builder::item::Lazer::gen(descriptor, object);
    core::shortcuts::entities()->add(lazer);
}
void createRocket(int_t descriptor, int_t object) {
    control::item::Rocket* rocket = builder::item::Rocket::gen(descriptor, object);
    core::shortcuts::entities()->add(rocket);
}
/** */

void addStarToStarSystem(int_t object, int_t parent) {
    control::Star* star = core::shortcuts::entities()->star(object);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->add(star);
}
void addPlanetToStarSystem(int_t object, int_t parent) {
    control::Planet* planet = core::shortcuts::entities()->planet(object);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->add(planet);
}
void addAsteroidToStarSystem(int_t object, int_t parent) {
    control::Asteroid* asteroid = core::shortcuts::entities()->asteroid(object);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->add(asteroid);
}

void addShipToStarSystem(int_t object, int_t parent, const glm::vec3& position) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->add(ship, position);
}
void addContainerToStarSystem(int_t object, int_t parent, const glm::vec3& position, const glm::vec3& impulse) {
    control::Container* container = core::shortcuts::entities()->container(object);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    container->addImpulse(impulse);
    starsystem->add(container, position);
}

// hit
void hitSpaceObject(int_t object_id, int damage) {
    control::SpaceObject* object = core::shortcuts::entities()->spaceObject(object_id);
    object->hit(damage);
}

void explode(int_t object, const glm::vec3& center, int damage, int radius) {
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(object);
    Explosion* explosion = new Explosion(damage, radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
}

// GARBAGE
void garbageSpaceObject(int_t object_id) {
    control::SpaceObject* object = core::shortcuts::entities()->spaceObject(object_id);
    object->die();
    core::shortcuts::garbage()->add(object);
}

// REMOVE
void removeSpaceObjectFromStarSystem(int_t object_id, int_t parent) {
    control::SpaceObject* object = core::shortcuts::entities()->spaceObject(object_id);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->remove(object);
}


/** DOCK */
void dockShip(int_t object, int_t destination) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = core::shortcuts::entities()->land(destination);
    land->add(ship);
}

void launchShip(int_t object, int_t destination) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);

    // remove
    control::Land* land = core::shortcuts::entities()->land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void jumpIn(int_t object) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = core::shortcuts::entities()->hyperspace();
    hyper->add(ship);
}
void jumpOut(int_t object, int_t destination) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);

    // remove
    control::HyperSpace* hyper = core::shortcuts::entities()->hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void dropItem(int_t object, int_t target) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);
    control::Item* item = core::shortcuts::entities()->item(target);

    // remove
    ship->remove(item);

    // add
    control::Container* container = builder::Container::gen();
    container->insert(item);
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(container, ship->position());
}

void takeContainer(int_t object, int_t target) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);
    control::Container* container = core::shortcuts::entities()->container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->die();
}

void shoot(int_t object, int_t item) {
    control::Ship* ship = core::shortcuts::entities()->ship(object);
    control::item::Weapon* weapon = core::shortcuts::entities()->weapon(item);

    weapon->fire(weapon->slot()->target());

    //    if (target()->isAlive() == false) {
    //        vehicleOwner()->npc()->addExpirience(target()->givenExpirience(), show_effect);
    //    }
}

} // namespace event
} // namespace comm
} // namespace core
