#include "TelegrammDispatcher.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/descriptor/comm/Hit.hpp>
#include <core/descriptor/comm/Dock.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>
#include <core/descriptor/comm/AddingPositional.hpp>

#include <core/manager/Session.hpp>
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

void TelegrammHandler::add(Telegramm& telegramm)
{
//    if (telegramm.delay() < 0) {
//        //_process(telegramm); // cause error while simulation server+client on single machine
//    } else {
        telegramm.setDispatchTime(__currentTime() + telegramm.delay());
        m_telegramms.insert(telegramm);
//    }
}

double TelegrammHandler::__currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void TelegrammHandler::runLoop()
{
    while(!m_telegramms.empty()) {
        update();
    }
}

void TelegrammHandler::update()
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

/** TRANSITION */
void addSectorToGalaxyEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::Galaxy* galaxy = shortcuts::entities()->galaxy(data.parent());
    control::Sector* sector = shortcuts::entities()->sector(data.object());
    galaxy->add(sector, data.position());
    LOG(__FUNCTION__+data.info());
}

void addStarSystemToSectorEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::Sector* sector = shortcuts::entities()->sector(data.parent());
    control::StarSystem* starsystem = shortcuts::entities()->starsystem(data.object());
    sector->add(starsystem, data.position());
    LOG(__FUNCTION__+data.info());
}
void addNpcToShipEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::Ship* ship = shortcuts::entities()->ship(data.parent());
    control::Npc* npc = shortcuts::entities()->npc(data.object());
    ship->bindNpc(npc);
    LOG(__FUNCTION__+data.info());
}


void mountItemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::Ship* ship = shortcuts::entities()->ship(data.parent());
    control::Item* item = shortcuts::entities()->item(data.object());
    ship->mount(item);
    LOG(__FUNCTION__+data.info());
}
void loadItemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::Ship* ship = shortcuts::entities()->ship(data.parent());
    control::Item* item = shortcuts::entities()->item(data.object());
    ship->load(item);
    LOG(__FUNCTION__+data.info());
}
/** */


/** CREATE */
void createGalaxyEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Galaxy* galaxy = builder::Galaxy::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(galaxy);
    core::shortcuts::entities()->setGalaxy(galaxy);
    LOG(__FUNCTION__+data.info());
}

void createSectorEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Sector* sector = builder::Sector::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(sector);
    LOG(__FUNCTION__+data.info());
}

void createStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::StarSystem* starsystem = builder::StarSystem::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(starsystem);
    LOG(__FUNCTION__+data.info());
}
void createNpcEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Npc* npc = builder::Npc::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(npc);
    LOG(__FUNCTION__+data.info());
}

// spaceobjects
void createStarEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Star* star = builder::Star::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(star);
    LOG(__FUNCTION__+data.info());
}

void createPlanetEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Planet* planet = builder::Planet::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(planet);
    LOG(__FUNCTION__+data.info());
}

void createAsteroidEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::Asteroid* asteroid = builder::Asteroid::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(asteroid);
    LOG(__FUNCTION__+data.info());
}
void createShipEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    builder::Ship::gen(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}

void createBombEvent(const comm::Telegramm& telegramm) {
    assert(false);
//        core::global::get().bombBuilder().gen(telegramm.data);
    //LOG(__FUNCTION__+data.info());
}

void createGoodsEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateGoodsPack data(telegramm.data());
    control::item::Goods* goods = builder::item::Goods::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(goods);
    LOG(__FUNCTION__+data.info());
}
void createContainerEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateContainer data(telegramm.data());
    builder::Container::gen(data.descriptor(), data.object(), data.item());
    LOG(__FUNCTION__+data.info());
}
void createBulletEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::CreateBullet data(telegramm.data());
    control::Vehicle* vehicle = Sessions::get().session()->entity()->vehicle(data.owner());
    control::item::Rocket* rocket = Sessions::get().session()->entity()->rocket(data.weapon());
    control::SpaceObject* target = Sessions::get().session()->entity()->spaceObject(data.target());
    assert(rocket->type() == entity::Type::ROCKET_EQUIPMENT);

    descriptor::Bullet* bullet_descriptor = core::shortcuts::descriptors()->bullet(rocket->descriptor()->bulletDescriptor());
    control::Bullet* bullet = builder::Bullet::gen(bullet_descriptor, rocket->damage());
    bullet->setOwnerId(vehicle->id());
    bullet->setTarget(target);
    vehicle->starsystem()->add(bullet, vehicle->position(), vehicle->direction());
    LOG(__FUNCTION__+data.info());
}

// items
void createBakEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Bak* bak = builder::item::Bak::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(bak);
    LOG(__FUNCTION__+data.info());
}
void createDriveEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Drive* drive = builder::item::Drive::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(drive);
    LOG(__FUNCTION__+data.info());
}
void createDroidEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Droid* droid = builder::item::Droid::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(droid);
    LOG(__FUNCTION__+data.info());
}
void createGrappleEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Grapple* grapple = builder::item::Grapple::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(grapple);
    LOG(__FUNCTION__+data.info());
}
void createProtectorEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Protector* protector = builder::item::Protector::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(protector);
    LOG(__FUNCTION__+data.info());
}
void createScanerEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Scaner* scaner = builder::item::Scaner::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(scaner);
    LOG(__FUNCTION__+data.info());
}
void createRadarEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Radar* radar = builder::item::Radar::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(radar);
    LOG(__FUNCTION__+data.info());
}
void createLazerEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Lazer* lazer = builder::item::Lazer::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(lazer);
    LOG(__FUNCTION__+data.info());
}
void createRocketEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    control::item::Rocket* rocket = builder::item::Rocket::gen(data.descriptor(), data.object());
    core::shortcuts::entities()->add(rocket);
    LOG(__FUNCTION__+data.info());
}
/** */

/** ADD TO STARSYSTEM */
void addStarToStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.parent());
    control::Star* star = Sessions::get().session()->entity()->star(data.object());
    starsystem->add(star);
    LOG(__FUNCTION__+data.info());
}
void addPlanetToStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.parent());
    control::Planet* planet = Sessions::get().session()->entity()->planet(data.object());
    starsystem->add(planet);
    LOG(__FUNCTION__+data.info());
}
void addAsteroidToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.starsystem);
    control::Asteroid* asteroid = Sessions::get().session()->entity()->asteroid(data.object);
    starsystem->add(asteroid);
    LOG(__FUNCTION__+data.info());
}

void addShipToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.starsystem);
    control::Ship* ship = Sessions::get().session()->entity()->ship(data.object);
    starsystem->add(ship);
    LOG(__FUNCTION__+data.info());
}
void addContainerToStarSystemEvent(const comm::Telegramm& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.starsystem);
    control::Container* container = Sessions::get().session()->entity()->container(data.object);
    container->addImpulse(data.impulse);
    starsystem->add(container, data.position);
    LOG(__FUNCTION__+data.info());
}

/** DOCK */
void _doDock(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doDockShip(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}
void _doLaunch(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doLaunchShip(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** JUMP */
void _doJumpIn(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doJumpIn(data.object());
    LOG(__FUNCTION__+data.info());
}
void _doJumpOut(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doJumpOut(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** DROP/TAKE */
void _doDropItem(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doDropItem(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}
void _doTakeContainer(const comm::Telegramm& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::doTakeContainer(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** */

void hitEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Hit data(telegramm.data());
    control::SpaceObject* object = Sessions::get().session()->entity()->spaceObject(data.target());
    object->hit(data.damage());
    ///LOG(__FUNCTION__+data.info());
}
void explosionEvent(const comm::Telegramm& telegramm) {
    descriptor::Explosion data(telegramm.data());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.starsystem);
    Explosion* explosion = new Explosion(data.damage, data.radius);
    assert(false);
    //        starsystem->add(explosion, descriptor.center);
    LOG(__FUNCTION__+data.info());
}

// GARBAGE
void garbageSpaceObjectEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::Object data(telegramm.data());
    control::SpaceObject* object = Sessions::get().session()->entity()->spaceObject(data.object());
    object->die();
    Sessions::get().session()->garbage()->add(object);
    LOG(__FUNCTION__+data.info());
}

// REMOVE
void removeSpaceObjectFromStarSystemEvent(const comm::Telegramm& telegramm) {
    descriptor::comm::StarSystemTransition data(telegramm.data());
    control::SpaceObject* object = Sessions::get().session()->entity()->spaceObject(data.object());
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(data.starsystem());
    starsystem->remove(object);
    LOG(__FUNCTION__+data.info());
}

} // namespace


namespace event {

/** DOCK */
void doDockShip(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = Sessions::get().session()->entity()->land(destination);
    land->add(ship);
}

void doLaunchShip(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);

    // remove
    control::Land* land = Sessions::get().session()->entity()->land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void doJumpIn(int_t object) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = Sessions::get().session()->entity()->hyperspace();
    hyper->add(ship);
}
void doJumpOut(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);

    // remove
    control::HyperSpace* hyper = Sessions::get().session()->entity()->hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = Sessions::get().session()->entity()->starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void doDropItem(int_t object, int_t target) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);
    control::Item* item = Sessions::get().session()->entity()->item(target);

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
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);
    control::Container* container = Sessions::get().session()->entity()->container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->die();
}

void doShoot(int_t object, int_t item) {
    control::Ship* ship = Sessions::get().session()->entity()->ship(object);
    control::item::Weapon* weapon = Sessions::get().session()->entity()->weapon(item);

    weapon->fire(weapon->slot()->target());

    //    if (target()->isAlive() == false) {
    //        vehicleOwner()->npc()->addExpirience(target()->givenExpirience(), show_effect);
    //    }
}

} // namespace event

bool TelegrammHandler::_process(const comm::Telegramm& telegramm)
{
    switch(telegramm.type()) {
    /** CREATE */
    case comm::Telegramm::Type::CREATE_GALAXY: createGalaxyEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_SECTOR: createSectorEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_STARSYSTEM: createStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_NPC: createNpcEvent(telegramm); return true;
    // spaceobjects
    case comm::Telegramm::Type::CREATE_STAR: createStarEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_PLANET: createPlanetEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_ASTEROID: createAsteroidEvent(telegramm); return true;
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
    case comm::Telegramm::Type::CREATE_LAZER: createLazerEvent(telegramm); return true;
    case comm::Telegramm::Type::CREATE_ROCKET: createRocketEvent(telegramm); return true;
        /** */

    case comm::Telegramm::Type::MOUNT_ITEM: mountItemEvent(telegramm); return true;
    case comm::Telegramm::Type::LOAD_ITEM: loadItemEvent(telegramm); return true;

    /** TRANSITION */
    case comm::Telegramm::Type::ADD_SECTOR_TO_GALAXY: addSectorToGalaxyEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_STARSYSTEM_TO_SECTOR: addStarSystemToSectorEvent(telegramm); return true;
    /** */

    /** ADD TO STARSYSTEM */
    case comm::Telegramm::Type::ADD_STAR_TO_STARSYSTEM: addStarToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_PLANET_TO_STARSYSTEM: addPlanetToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_ASTEROID_TO_STARSYSTEM: addAsteroidToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(telegramm); return true;
    case comm::Telegramm::Type::ADD_NPC_TO_SHIP: addNpcToShipEvent(telegramm); return true;

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

