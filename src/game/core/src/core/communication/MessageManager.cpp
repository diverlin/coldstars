#include "MessageManager.hpp"

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

void MessageManager::add(comm::Message&& message)
{
    if (message.delay() < 0) {
        process(message);
    } else {
        message.setDispatchTime(currentTime() + message.delay());
        m_messages_queue.insert(message);
    }
}

double MessageManager::currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void MessageManager::runLoop()
{
    while(!m_messages_queue.empty()) {
        update();
    }
}

void MessageManager::update()
{ 
    for ( auto it = m_messages_queue.begin(); it != m_messages_queue.end(); ++it ) {
        const comm::Message& message = *it;
        if (message.dispatchTime() < currentTime()) {
            process(message);
            m_messages_queue.erase(it);
        }
    }
}

namespace {

void createStarSystemEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::StarSystem::gen(data.descriptor(), data.object());
}

void createShipEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::Ship::gen(data.descriptor(), data.object());
}

void createBombEvent(const comm::Message& message) {
    assert(false);
//        core::global::get().bombBuilder().gen(message.data);
}

void createContainerEvent(const comm::Message& message) {
    assert(false);
//        core::global::get().containerBuilder().gen(message.data);
}

// items
void createBakEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Bak::gen(data.descriptor(), data.object());
}

// items
void createDriveEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Drive::gen(data.descriptor(), data.object());
}
void createDroidEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Droid::gen(data.descriptor(), data.object());
}
void createGrappleEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Grapple::gen(data.descriptor(), data.object());
}
void createProtectorEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Protector::gen(data.descriptor(), data.object());
}
void createScanerEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Scaner::gen(data.descriptor(), data.object());
}
void createRadarEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Radar::gen(data.descriptor(), data.object());
}
// item

/** ADD TO STARSYSTEM */
void addShipToStarSystemEvent(const comm::Message& message) {
    AddToStarsystemDescriptor descriptor(message.data());
    control::StarSystem* starsystem = EntityManager::get().starsystem(descriptor.owner);
    control::Ship* ship = EntityManager::get().ship(descriptor.object);
    starsystem->add(ship);
}
void addContainerToStarSystemEvent(const comm::Message& message) {
    AddToStarsystemDescriptor descriptor(message.data());
    control::StarSystem* starsystem = EntityManager::get().starsystem(descriptor.owner);
    control::Container* container = EntityManager::get().container(descriptor.object);
    starsystem->add(container);
}

/** DOCK */
void _doDock(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doDockShip(descr.object(), descr.target());
}
void _doLaunch(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doLaunchShip(descr.object(), descr.target());
}

/** JUMP */
void _doJumpIn(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doJumpIn(descr.object());
}
void _doJumpOut(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doJumpOut(descr.object(), descr.target());
}

/** DROP/TAKE */
void _doDropItem(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doDropItem(descr.object(), descr.target());
}
void _doTakeContainer(const comm::Message& message) {
    descriptor::comm::Pair descr(message.data());
    event::doTakeContainer(descr.object(), descr.target());
}

/** */

void hitEvent(const comm::Message& message) {
    descriptor::Hit descr(message.data());
    control::SpaceObject* ob = EntityManager::get().spaceObject(descr.target());
    ob->hit(descr.damage());
}
void explosionEvent(const comm::Message& message) {
    descriptor::Explosion descriptor(message.data());
    control::StarSystem* starsystem = EntityManager::get().starsystem(descriptor.starsystem_id);
    Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
}

} // namespace


namespace event {

/** DOCK */
void doDockShip(int_t object, int_t destination) {
    control::Ship* ship = EntityManager::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = EntityManager::get().land(destination);
    land->add(ship);
}

void doLaunchShip(int_t object, int_t destination) {
    control::Ship* ship = EntityManager::get().ship(object);

    // remove
    control::Land* land = EntityManager::get().land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void doJumpIn(int_t object) {
    control::Ship* ship = EntityManager::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = EntityManager::get().hyperspace();
    hyper->add(ship);
}
void doJumpOut(int_t object, int_t destination) {
    control::Ship* ship = EntityManager::get().ship(object);

    // remove
    control::HyperSpace* hyper = EntityManager::get().hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = EntityManager::get().starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void doDropItem(int_t object, int_t target) {
    control::Ship* ship = EntityManager::get().ship(object);
    control::Item* item = EntityManager::get().item(target);

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
    control::Ship* ship = EntityManager::get().ship(object);
    control::Container* container = EntityManager::get().container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->killSilently();
}

void doShoot(int_t object, int_t item) {
    control::Ship* ship = EntityManager::get().ship(object);
    control::item::Weapon* weapon = EntityManager::get().weapon(item);

    weapon->fire();
}


} // namespace event

void MessageManager::process(const comm::Message& message)
{
    switch(message.type()) {
    /** CREATE */
    case comm::Message::Type::CREATE_STARSYSTEM: createStarSystemEvent(message); break;
    case comm::Message::Type::CREATE_SHIP: createShipEvent(message); break;
    case comm::Message::Type::CREATE_BOMB: createBombEvent(message); break;
    case comm::Message::Type::CREATE_CONTAINER: createContainerEvent(message); break;
    // items
    case comm::Message::Type::CREATE_BAK: createBakEvent(message); break;
    case comm::Message::Type::CREATE_DRIVE: createDriveEvent(message); break;
    case comm::Message::Type::CREATE_DROID: createDroidEvent(message); break;
    case comm::Message::Type::CREATE_GRAPPLE: createGrappleEvent(message); break;
    case comm::Message::Type::CREATE_PROTECTOR: createProtectorEvent(message); break;
    case comm::Message::Type::CREATE_SCANER: createScanerEvent(message); break;
    case comm::Message::Type::CREATE_RADAR: createRadarEvent(message); break;

    /** ADD TO STARSYSTEM */
    case comm::Message::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(message); break;
    case comm::Message::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(message); break;

    /** DOCK */
    case comm::Message::Type::DOCK_SHIP: _doDock(message); break;
    case comm::Message::Type::LAUNCH_SHIP: _doLaunch(message); break;

    /** JUMP **/
    case comm::Message::Type::JUMP_IN: _doJumpIn(message); break;
    case comm::Message::Type::JUMP_OUT: _doJumpOut(message); break;

    /** DROP/TAKE */
    case comm::Message::Type::DROP_ITEM: _doDropItem(message); break;
    case comm::Message::Type::TAKE_CONTAINER: _doTakeContainer(message); break;

    /** OTHER */
    case comm::Message::Type::HIT: hitEvent(message); break;
    case comm::Message::Type::EXPLOSION: explosionEvent(message); break;
    }
}



