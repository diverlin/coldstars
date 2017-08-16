#include "TelegrammManager.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/descriptor/comm/Hit.hpp>
#include <core/descriptor/comm/Dock.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/descriptor/comm/Creation.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>

#include <core/spaceobject/ALL>
#include <core/item/equipment/Weapon.hpp>

#include <world/starsystem.hpp>

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

#include <core/world/starsystem.hpp>

namespace comm {

void TelegrammManager::add(comm::Telegramm&& message)
{
    if (message.delay() < 0) {
        process(message);
    } else {
        message.setDispatchTime(currentTime() + message.delay());
        m_telegramms_queue.insert(message);
    }
}

double TelegrammManager::currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void TelegrammManager::runLoop()
{
    while(!m_telegramms_queue.empty()) {
        update();
    }
}

void TelegrammManager::update()
{ 
    for ( auto it = m_telegramms_queue.begin(); it != m_telegramms_queue.end(); ++it ) {
        const comm::Telegramm& message = *it;
        if (message.dispatchTime() < currentTime()) {
            process(message);
            m_telegramms_queue.erase(it);
        }
    }
}

namespace {

void createStarSystemEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::StarSystem::gen(data.descriptor(), data.object());
}

void createShipEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::Ship::gen(data.descriptor(), data.object());
}

void createBombEvent(const comm::Telegramm& message) {
    assert(false);
//        core::global::get().bombBuilder().gen(message.data);
}

void createContainerEvent(const comm::Telegramm& message) {
    assert(false);
//        core::global::get().containerBuilder().gen(message.data);
}

// items
void createBakEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Bak::gen(data.descriptor(), data.object());
}

// items
void createDriveEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Drive::gen(data.descriptor(), data.object());
}
void createDroidEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Droid::gen(data.descriptor(), data.object());
}
void createGrappleEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Grapple::gen(data.descriptor(), data.object());
}
void createProtectorEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Protector::gen(data.descriptor(), data.object());
}
void createScanerEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Scaner::gen(data.descriptor(), data.object());
}
void createRadarEvent(const comm::Telegramm& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Radar::gen(data.descriptor(), data.object());
}
// item

/** ADD TO STARSYSTEM */
void addShipToStarSystemEvent(const comm::Telegramm& message) {
    AddToStarsystemDescriptor descriptor(message.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.owner);
    control::Ship* ship = manager::Entities::get().ship(descriptor.object);
    starsystem->add(ship);
}
void addContainerToStarSystemEvent(const comm::Telegramm& message) {
    AddToStarsystemDescriptor descriptor(message.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.owner);
    control::Container* container = manager::Entities::get().container(descriptor.object);
    starsystem->add(container);
}

/** DOCK */
void _doDock(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doDockShip(descr.object(), descr.target());
}
void _doLaunch(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doLaunchShip(descr.object(), descr.target());
}

/** JUMP */
void _doJumpIn(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doJumpIn(descr.object());
}
void _doJumpOut(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doJumpOut(descr.object(), descr.target());
}

/** DROP/TAKE */
void _doDropItem(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doDropItem(descr.object(), descr.target());
}
void _doTakeContainer(const comm::Telegramm& message) {
    descriptor::comm::Pair descr(message.data());
    event::doTakeContainer(descr.object(), descr.target());
}

/** */

void hitEvent(const comm::Telegramm& message) {
    descriptor::Hit descr(message.data());
    control::SpaceObject* ob = manager::Entities::get().spaceObject(descr.target());
    ob->hit(descr.damage());
}
void explosionEvent(const comm::Telegramm& message) {
    descriptor::Explosion descriptor(message.data());
    control::StarSystem* starsystem = manager::Entities::get().starsystem(descriptor.starsystem_id);
    Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
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
    container->killSilently();
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

void TelegrammManager::process(const comm::Telegramm& telegramm)
{
    switch(telegramm.type()) {
    /** CREATE */
    case comm::Telegramm::Type::CREATE_STARSYSTEM: createStarSystemEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_SHIP: createShipEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_BOMB: createBombEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_CONTAINER: createContainerEvent(telegramm); break;
    // items
    case comm::Telegramm::Type::CREATE_BAK: createBakEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_DRIVE: createDriveEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_DROID: createDroidEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_GRAPPLE: createGrappleEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_PROTECTOR: createProtectorEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_SCANER: createScanerEvent(telegramm); break;
    case comm::Telegramm::Type::CREATE_RADAR: createRadarEvent(telegramm); break;

    /** ADD TO STARSYSTEM */
    case comm::Telegramm::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(telegramm); break;
    case comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(telegramm); break;

    /** DOCK */
    case comm::Telegramm::Type::DOCK_SHIP: _doDock(telegramm); break;
    case comm::Telegramm::Type::LAUNCH_SHIP: _doLaunch(telegramm); break;

    /** JUMP **/
    case comm::Telegramm::Type::JUMP_IN: _doJumpIn(telegramm); break;
    case comm::Telegramm::Type::JUMP_OUT: _doJumpOut(telegramm); break;

    /** DROP/TAKE */
    case comm::Telegramm::Type::DROP_ITEM: _doDropItem(telegramm); break;
    case comm::Telegramm::Type::TAKE_CONTAINER: _doTakeContainer(telegramm); break;

    /** OTHER */
    case comm::Telegramm::Type::HIT: hitEvent(telegramm); break;
    case comm::Telegramm::Type::EXPLOSION: explosionEvent(telegramm); break;
    }
}

} // namespace comm


