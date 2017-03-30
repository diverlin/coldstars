#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/descriptor/Hit.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/descriptor/comm/Creation.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>
#include <core/descriptor/AddToStarsystemDescriptor.hpp>

#include <core/spaceobject/ALL>

#include <world/starsystem.hpp>

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
    builder::StarSystem::gen(data.obDescriptor(), data.obId());
}

void createShipEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::Ship::gen(data.obDescriptor(), data.obId());
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
    builder::item::Bak::gen(data.obDescriptor(), data.obId());
}

// items
void createDriveEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Drive::gen(data.obDescriptor(), data.obId());
}
void createDroidEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Droid::gen(data.obDescriptor(), data.obId());
}
void createGrappleEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Grapple::gen(data.obDescriptor(), data.obId());
}
void createProtectorEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Protector::gen(data.obDescriptor(), data.obId());
}
void createScanerEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Scaner::gen(data.obDescriptor(), data.obId());
}
void createRadarEvent(const comm::Message& message) {
    descriptor::comm::Creation data(message.data());
    builder::item::Radar::gen(data.obDescriptor(), data.obId());
}
// item

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


    /** OTHER */
    case comm::Message::Type::HIT: hitEvent(message); break;
    case comm::Message::Type::EXPLOSION: explosionEvent(message); break;
    }
}



