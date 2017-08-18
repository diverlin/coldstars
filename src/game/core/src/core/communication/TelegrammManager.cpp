#include "TelegrammManager.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/descriptor/comm/Hit.hpp>
#include <core/descriptor/comm/Dock.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>

#include <core/descriptor/Base.hpp>
#include <core/descriptor/comm/Creation.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>

#include <core/spaceobject/ALL>
#include <core/item/equipment/Weapon.hpp>

#include <core/world/starsystem.hpp>
#include <core/world/HyperSpace.hpp>

#include <core/builder/spaceobject/ALL>

#include <core/builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
#include <core/builder/item/artefact/ALL>
#endif // USE_ARTEFACTS
#include <core/builder/item/other/ALL>

#include <core/builder/world/StarSystemBuilder.hpp>

namespace core {
namespace comm {

void TelegrammManager::add(Telegramm& telegramm)
{
    if (telegramm.delay() < 0) {
        _process(telegramm);
    } else {
        telegramm.setDispatchTime(__currentTime() + telegramm.delay());
        m_telegramms.insert(telegramm);
    }
}

double TelegrammManager::__currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void TelegrammManager::runLoop()
{
    while(!m_telegramms.empty()) {
        update();
    }
}

void TelegrammManager::update()
{ 
    for ( auto it = m_telegramms.begin(); it != m_telegramms.end(); ++it ) {
        const Telegramm& telegramm = *it;
        if (telegramm.dispatchTime() < __currentTime()) {
            _process(telegramm);
            m_telegramms.erase(it);
        }
    }
}

namespace {

// spaceobjects
void createStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::StarSystem::gen(data.descriptor(), data.object());
}

void createShipEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::Ship::gen(data.descriptor(), data.object());
}

void createBombEvent(const comm::Telegramm& telegramm) {
    assert(false);
//        core::global::get().bombBuilder().gen(telegramm.data);
}

void createMineralEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Container data(telegramm.data());
    builder::Container::gen(data.descriptor(), data.object(), data.mass());
}
void createContainerEvent(const comm::Telegramm& telegramm) {
    assert(false);
//        core::global::get().containerBuilder().gen(telegramm.data);
}

// items
void createBakEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Bak::gen(data.descriptor(), data.object());
}
void createDriveEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Drive::gen(data.descriptor(), data.object());
}
void createDroidEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Droid::gen(data.descriptor(), data.object());
}
void createGrappleEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Grapple::gen(data.descriptor(), data.object());
}
void createProtectorEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Protector::gen(data.descriptor(), data.object());
}
void createScanerEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Scaner::gen(data.descriptor(), data.object());
}
void createRadarEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::item::Radar::gen(data.descriptor(), data.object());
}

/** ADD TO STARSYSTEM */
void addShipToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor descriptor(telegramm.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.starsystem);
    control::Ship* ship = manager::Entities::get().ship(descriptor.object);
    starsystem->add(ship);
}
void addContainerToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor descriptor(telegramm.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.starsystem);
    control::Container* container = manager::Entities::get().container(descriptor.object);
    container->addImpulse(descriptor.impulse);
    starsystem->add(container, descriptor.position);
}

/** DOCK */
void _doDock(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doDockShip(descr.object(), descr.target());
}
void _doLaunch(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doLaunchShip(descr.object(), descr.target());
}

/** JUMP */
void _doJumpIn(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doJumpIn(descr.object());
}
void _doJumpOut(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doJumpOut(descr.object(), descr.target());
}

/** DROP/TAKE */
void _doDropItem(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doDropItem(descr.object(), descr.target());
}
void _doTakeContainer(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair descr(telegramm.data());
    event::doTakeContainer(descr.object(), descr.target());
}

/** */

void hitEvent(const comm::Telegramm& telegramm) {
    descriptor::Hit descr(telegramm.data());
    control::SpaceObject* ob = manager::Entities::get().spaceObject(descr.target());
    ob->hit(descr.damage());
}
void explosionEvent(const comm::Telegramm& telegramm) {
    descriptor::Explosion descriptor(telegramm.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.starsystem_id);
    Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
}

// REMOVE
void removeAsteroidEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Object remove(telegramm.data());
    control::Asteroid* asteroid = manager::Entities::get().asteroid(remove.object());
    asteroid->die();
    asteroid->starsystem()->remove(asteroid);
    manager::Garbage::get().add(asteroid);
}

} // namespace


namespace event {

/** DOCK */
void doDockShip(int_t object, int_t destination) {
    control::Ship* ship = manager::Entities::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = manager::Entities::get().land(destination);
    land->add(ship);
}

void doLaunchShip(int_t object, int_t destination) {
    control::Ship* ship = manager::Entities::get().ship(object);

    // remove
    control::Land* land = manager::Entities::get().land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void doJumpIn(int_t object) {
    control::Ship* ship = manager::Entities::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = manager::Entities::get().hyperspace();
    hyper->add(ship);
}
void doJumpOut(int_t object, int_t destination) {
    control::Ship* ship = manager::Entities::get().ship(object);

    // remove
    control::HyperSpace* hyper = manager::Entities::get().hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = manager::Entities::get().starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void doDropItem(int_t object, int_t target) {
    control::Ship* ship = manager::Entities::get().ship(object);
    control::Item* item = manager::Entities::get().item(target);

    // remove
    ship->remove(item);

    // add
    control::Container* container = builder::Container::gen();
    container->insert(item);
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(container, ship->position());
}

void doTakeContainer(int_t object, int_t target) {
    control::Ship* ship = manager::Entities::get().ship(object);
    control::Container* container = manager::Entities::get().container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->die();
}

void doShoot(int_t object, int_t item) {
    control::Ship* ship = manager::Entities::get().ship(object);
    control::item::Weapon* weapon = manager::Entities::get().weapon(item);

    weapon->fire();

    //    if (target()->isAlive() == false) {
    //        vehicleOwner()->npc()->addExpirience(target()->givenExpirience(), show_effect);
    //    }
}


} // namespace event

bool TelegrammManager::_process(const comm::Telegramm& telegramm)
{
    switch(telegramm.type()) {
    /** CREATE */
    // spaceobjects
    case comm::Telegramm::Type::CREATE_STARSYSTEM: createStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_SHIP: createShipEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_BOMB: createBombEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_MINERAL: createMineralEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_CONTAINER: createContainerEvent(telegramm); return true;
    // items
    case comm::Telegramm::Type::CREATE_BAK: createBakEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_DRIVE: createDriveEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_DROID: createDroidEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_GRAPPLE: createGrappleEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_PROTECTOR: createProtectorEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_SCANER: createScanerEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_RADAR: createRadarEvent(telegramm); return true;
    /** */

    /** ADD TO STARSYSTEM */
    case comm::Telegramm::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(telegramm); return true;

    /** DOCK */
    case comm::Telegramm::Type::DOCK_SHIP: _doDock(telegramm); return true;
    case comm::Telegramm::Type::LAUNCH_SHIP: _doLaunch(telegramm); return true;

    /** JUMP **/
    case comm::Telegramm::Type::JUMP_IN: _doJumpIn(telegramm); return true;
    case comm::Telegramm::Type::JUMP_OUT: _doJumpOut(telegramm); return true;

    /** DROP/TAKE */
    case comm::Telegramm::Type::DROP_ITEM: _doDropItem(telegramm); return true;
    case comm::Telegramm::Type::TAKE_CONTAINER: _doTakeContainer(telegramm); return true;

    /** OTHER */
    case comm::Telegramm::Type::HIT: hitEvent(telegramm); return true;
    case comm::Telegramm::Type::EXPLOSION: explosionEvent(telegramm); return true;

    /* REMOVE */
    case comm::Telegramm::Type::REMOVE_ASTEROID: removeAsteroidEvent(telegramm); return true;
    }

    return false;
}

} // namespace comm
} // namespace core

