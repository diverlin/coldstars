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
#include <core/item/equipment/Rocket.hpp>
#include <core/descriptor/item/equipment/Rocket.hpp>

#include <core/world/starsystem.hpp>
#include <core/world/HyperSpace.hpp>

#include <core/builder/spaceobject/ALL>

#include <core/builder/item/ALL>
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

void createGoodsEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateGoodsPack descriptor(telegramm.data());
    builder::item::Goods::gen(descriptor.descriptor(), descriptor.object());
}
void createContainerEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateContainer descriptor(telegramm.data());
    builder::Container::gen(descriptor.descriptor(), descriptor.object(), descriptor.item());
}
void createBulletEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateBullet descriptor(telegramm.data());
    control::Vehicle* vehicle = manager::Entity::get().vehicle(descriptor.owner());
    control::item::Rocket* rocket = manager::Entity::get().rocket(descriptor.weapon());
    control::SpaceObject* target = manager::Entity::get().spaceObject(descriptor.target());
    assert(rocket->type() == entity::Type::ROCKET_EQUIPMENT);

    descriptor::Bullet* bullet_descriptor = descriptor::Manager::get().bullet(rocket->descriptor()->bulletDescriptor());
    control::Bullet* bullet = builder::Bullet::gen(bullet_descriptor);
    bullet->setOwnerId(vehicle->id());
    bullet->setTarget(target);
    vehicle->starsystem()->add(bullet, vehicle->position(), vehicle->direction());
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
    control::StarSystem* starsystem = manager::Entity::get().starsystem(descriptor.starsystem);
    control::Ship* ship = manager::Entity::get().ship(descriptor.object);
    starsystem->add(ship);
}
void addContainerToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor descriptor(telegramm.data());
    control::StarSystem* starsystem = manager::Entity::get().starsystem(descriptor.starsystem);
    control::Container* container = manager::Entity::get().container(descriptor.object);
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
    descriptor::comm::Hit descriptor(telegramm.data());
    control::SpaceObject* ob = manager::Entity::get().spaceObject(descriptor.target());
    ob->hit(descriptor.damage());
}
void explosionEvent(const comm::Telegramm& telegramm) {
    descriptor::Explosion descriptor(telegramm.data());
    control::StarSystem* starsystem = manager::Entity::get().starsystem(descriptor.starsystem_id);
    Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
}

// GARBAGE
void garbageSpaceObjectEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Object descriptor(telegramm.data());
    control::SpaceObject* object = manager::Entity::get().spaceObject(descriptor.object());
    object->die();
    manager::Garbage::get().add(object);
}

// REMOVE
void removeSpaceObjectFromStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::StarSystemTransition descriptor(telegramm.data());
    control::SpaceObject* object = manager::Entity::get().spaceObject(descriptor.object());
    control::StarSystem* starsystem = manager::Entity::get().starsystem(descriptor.starsystem());
    starsystem->remove(object);
}

} // namespace


namespace event {

/** DOCK */
void doDockShip(int_t object, int_t destination) {
    control::Ship* ship = manager::Entity::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = manager::Entity::get().land(destination);
    land->add(ship);
}

void doLaunchShip(int_t object, int_t destination) {
    control::Ship* ship = manager::Entity::get().ship(object);

    // remove
    control::Land* land = manager::Entity::get().land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void doJumpIn(int_t object) {
    control::Ship* ship = manager::Entity::get().ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = manager::Entity::get().hyperspace();
    hyper->add(ship);
}
void doJumpOut(int_t object, int_t destination) {
    control::Ship* ship = manager::Entity::get().ship(object);

    // remove
    control::HyperSpace* hyper = manager::Entity::get().hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = manager::Entity::get().starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void doDropItem(int_t object, int_t target) {
    control::Ship* ship = manager::Entity::get().ship(object);
    control::Item* item = manager::Entity::get().item(target);

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
    control::Ship* ship = manager::Entity::get().ship(object);
    control::Container* container = manager::Entity::get().container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->die();
}

void doShoot(int_t object, int_t item) {
    control::Ship* ship = manager::Entity::get().ship(object);
    control::item::Weapon* weapon = manager::Entity::get().weapon(item);

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
    case comm::Telegramm::Type::CREATE_GOODS: createGoodsEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_CONTAINER: createContainerEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_BULLET: createBulletEvent(telegramm); return true;
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

    /** REMOVE FROM STARSYSTEM */
    case comm::Telegramm::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: removeSpaceObjectFromStarSystemEvent(telegramm); return true;

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
    //case comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegramm); return true;

    /* GARBAGE */
    case comm::Telegramm::Type::ADD_SPACEOBJECT_TO_GARBAGE: garbageSpaceObjectEvent(telegramm); return true;
    }

    return false;
}

} // namespace comm
} // namespace core

