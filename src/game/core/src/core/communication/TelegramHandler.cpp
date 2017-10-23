#include "TelegramHandler.hpp"

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

void TelegramHandler::add(Telegram& telegramm)
{
//    if (telegramm.delay() < 0) {
//        //_process(telegramm); // cause error while simulation server+client on single machine
//    } else {
        telegramm.setDispatchTime(__currentTime() + telegramm.delay());
        m_telegramms.insert(telegramm);
//    }
}

double TelegramHandler::__currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void TelegramHandler::runLoop()
{
    while(!m_telegramms.empty()) {
        update();
    }
}

void TelegramHandler::update()
{ 
    for(auto it = m_telegramms.begin(); it != m_telegramms.end(); ++it) {
        const Telegram& telegramm = *it;
        if (telegramm.dispatchTime() < __currentTime()) {
            _process(telegramm);
            m_telegramms.erase(it);
            return;
        }
    }
}


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
    control::Container* container = Sessions::get().session()->entitiesManager()->container(object);
    control::StarSystem* starsystem = Sessions::get().session()->entitiesManager()->starsystem(parent);
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
    control::SpaceObject* object = Sessions::get().session()->entitiesManager()->spaceObject(object_id);
    object->die();
    Sessions::get().session()->garbageManager()->add(object);
}

// REMOVE
void removeSpaceObjectFromStarSystem(int_t object_id, int_t parent) {
    control::SpaceObject* object = core::shortcuts::entities()->spaceObject(object_id);
    control::StarSystem* starsystem = core::shortcuts::entities()->starsystem(parent);
    starsystem->remove(object);
}


/** DOCK */
void dockShip(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    starsystem->remove(ship);

    // add
    control::Land* land = Sessions::get().session()->entitiesManager()->land(destination);
    land->add(ship);
}

void launchShip(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);

    // remove
    control::Land* land = Sessions::get().session()->entitiesManager()->land(destination);
    land->remove(ship);

    // add
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->add(ship, land->owner()->position());
}

/** JUMP */
void jumpIn(int_t object) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(ship);

    // add
    control::HyperSpace* hyper = Sessions::get().session()->entitiesManager()->hyperspace();
    hyper->add(ship);
}
void jumpOut(int_t object, int_t destination) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);

    // remove
    control::HyperSpace* hyper = Sessions::get().session()->entitiesManager()->hyperspace();
    hyper->remove(ship);

    // add
    control::StarSystem* starsystem = Sessions::get().session()->entitiesManager()->starsystem(destination); // probably can be used from navigator
    starsystem->add(ship /*, position implement entry point here */);
}

/** DROP/TAKE */
void dropItem(int_t object, int_t target) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);
    control::Item* item = Sessions::get().session()->entitiesManager()->item(target);

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
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);
    control::Container* container = Sessions::get().session()->entitiesManager()->container(target);

    // remove
    control::StarSystem* starsystem = ship->starsystem();
    assert(starsystem);
    starsystem->remove(container);

    // add
    ship->load(container->item());
    container->die();
}

void shoot(int_t object, int_t item) {
    control::Ship* ship = Sessions::get().session()->entitiesManager()->ship(object);
    control::item::Weapon* weapon = Sessions::get().session()->entitiesManager()->weapon(item);

    weapon->fire(weapon->slot()->target());

    //    if (target()->isAlive() == false) {
    //        vehicleOwner()->npc()->addExpirience(target()->givenExpirience(), show_effect);
    //    }
}

} // namespace event

namespace {

/** TRANSITION */
void addSectorToGalaxyEvent(const comm::Telegram& telegram) {
    descriptor::comm::AddingPositional data(telegram.data());
    event::addSectorToGalaxy(data.object(), data.parent(), data.position());
    LOG(__FUNCTION__+data.info());
}

void addStarSystemToSectorEvent(const comm::Telegram& telegram) {
    descriptor::comm::AddingPositional data(telegram.data());
    event::addStarSystemToSector(data.object(), data.parent(), data.position());
    LOG(__FUNCTION__+data.info());
}
void addNpcToShipEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    event::addNpcToShip(data.object(), data.parent());
    LOG(__FUNCTION__+data.info());
}

// items
void mountItemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    event::mountItem(data.object(), data.parent());
    LOG(__FUNCTION__+data.info());
}
void loadItemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    event::loadItem(data.object(), data.parent());
    LOG(__FUNCTION__+data.info());
}
/** */


/** CREATE */
void createGalaxyEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createGalaxy(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createSectorEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createSector(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createStarSystem(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createNpcEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createNpc(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}

// spaceobjects
void createStarEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createStar(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createPlanetEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createPlanet(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createAsteroidEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createAsteroid(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createShipEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createShip(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}

// items
void createBombEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createBomb(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}

void createGoodsEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateGoodsPack data(telegramm.data());
    event::createGoods(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createContainerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateContainer data(telegramm.data());
    event::createContainer(data.descriptor(), data.object(), data.item());
    LOG(__FUNCTION__+data.info());
}
void createBulletEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateBullet data(telegramm.data());
    event::createBullet(data.owner(), data.weapon(), data.target());
    LOG(__FUNCTION__+data.info());
}

// items
void createBakEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createBak(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createDriveEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createDrive(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createDroidEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createDroid(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createGrappleEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createGrapple(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createProtectorEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createProtector(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createScanerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createScaner(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createRadarEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createRadar(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createLazerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createLazer(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
void createRocketEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    event::createRocket(data.descriptor(), data.object());
    LOG(__FUNCTION__+data.info());
}
/** */

/** ADD TO STARSYSTEM */
void addStarToStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    event::addStarToStarSystem(data.object(), data.parent());
    LOG(__FUNCTION__+data.info());
}
void addPlanetToStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    event::addPlanetToStarSystem(data.object(), data.parent());
    LOG(__FUNCTION__+data.info());
}
void addAsteroidToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    event::addAsteroidToStarSystem(data.object, data.starsystem);
    LOG(__FUNCTION__+data.info());
}

void addShipToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    event::addShipToStarSystem(data.object, data.starsystem, data.position);
    LOG(__FUNCTION__+data.info());
}
void addContainerToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    event::addContainerToStarSystem(data.object, data.starsystem, data.position, data.impulse);
    LOG(__FUNCTION__+data.info());
}

/** DOCK */
void _doDock(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::dockShip(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}
void _doLaunch(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::launchShip(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** JUMP */
void _doJumpIn(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::jumpIn(data.object());
    LOG(__FUNCTION__+data.info());
}
void _doJumpOut(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::jumpOut(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** DROP/TAKE */
void _doDropItem(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::dropItem(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}
void _doTakeContainer(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    event::takeContainer(data.object(), data.target());
    LOG(__FUNCTION__+data.info());
}

/** */

void hitEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Hit data(telegramm.data());
    event::hitSpaceObject(data.target(), data.damage());
    ///LOG(__FUNCTION__+data.info());
}
void explosionEvent(const comm::Telegram& telegramm) {
    descriptor::Explosion data(telegramm.data());
    event::explode(data.starsystem, data.center, data.damage, data.radius);
    LOG(__FUNCTION__+data.info());
}

// GARBAGE
void garbageSpaceObjectEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Object data(telegramm.data());
    event::garbageSpaceObject(data.object());
    LOG(__FUNCTION__+data.info());
}

// REMOVE
void removeSpaceObjectFromStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::StarSystemTransition data(telegramm.data());
    event::removeSpaceObjectFromStarSystem(data.object(), data.starsystem());
    LOG(__FUNCTION__+data.info());
}

} // namespace


bool TelegramHandler::_process(const comm::Telegram& telegram)
{
    std::cout<<"--process telegramm="<<telegram::to_string(telegram.type())<<std::endl;

    switch(telegram.type()) {
    /** CREATE */
    case telegram::Type::CREATE_GALAXY: createGalaxyEvent(telegram); return true;
    case telegram::Type::CREATE_SECTOR: createSectorEvent(telegram); return true;
    case telegram::Type::CREATE_STARSYSTEM: createStarSystemEvent(telegram); return true;
    case telegram::Type::CREATE_NPC: createNpcEvent(telegram); return true;
    // spaceobjects
    case telegram::Type::CREATE_STAR: createStarEvent(telegram); return true;
    case telegram::Type::CREATE_PLANET: createPlanetEvent(telegram); return true;
    case telegram::Type::CREATE_ASTEROID: createAsteroidEvent(telegram); return true;
    case telegram::Type::CREATE_SHIP: createShipEvent(telegram); return true;
    case telegram::Type::CREATE_BOMB: createBombEvent(telegram); return true;
    case telegram::Type::CREATE_GOODS: createGoodsEvent(telegram); return true;
    case telegram::Type::CREATE_CONTAINER: createContainerEvent(telegram); return true;
    case telegram::Type::CREATE_BULLET: createBulletEvent(telegram); return true;
    // items
    case telegram::Type::CREATE_BAK: createBakEvent(telegram); return true;
    case telegram::Type::CREATE_DRIVE: createDriveEvent(telegram); return true;
    case telegram::Type::CREATE_DROID: createDroidEvent(telegram); return true;
    case telegram::Type::CREATE_GRAPPLE: createGrappleEvent(telegram); return true;
    case telegram::Type::CREATE_PROTECTOR: createProtectorEvent(telegram); return true;
    case telegram::Type::CREATE_SCANER: createScanerEvent(telegram); return true;
    case telegram::Type::CREATE_RADAR: createRadarEvent(telegram); return true;
    case telegram::Type::CREATE_LAZER: createLazerEvent(telegram); return true;
    case telegram::Type::CREATE_ROCKET: createRocketEvent(telegram); return true;
        /** */

    case telegram::Type::MOUNT_ITEM: mountItemEvent(telegram); return true;
    case telegram::Type::LOAD_ITEM: loadItemEvent(telegram); return true;

    /** TRANSITION */
    case telegram::Type::ADD_SECTOR_TO_GALAXY: addSectorToGalaxyEvent(telegram); return true;
    case telegram::Type::ADD_STARSYSTEM_TO_SECTOR: addStarSystemToSectorEvent(telegram); return true;
    /** */

    /** ADD TO STARSYSTEM */
    case telegram::Type::ADD_STAR_TO_STARSYSTEM: addStarToStarSystemEvent(telegram); return true;
    case telegram::Type::ADD_PLANET_TO_STARSYSTEM: addPlanetToStarSystemEvent(telegram); return true;
    case telegram::Type::ADD_ASTEROID_TO_STARSYSTEM: addAsteroidToStarSystemEvent(telegram); return true;
    case telegram::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(telegram); return true;
    case telegram::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(telegram); return true;
    case telegram::Type::ADD_NPC_TO_SHIP: addNpcToShipEvent(telegram); return true;

    /** REMOVE FROM STARSYSTEM */
    case telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: removeSpaceObjectFromStarSystemEvent(telegram); return true;

    /** DOCK */
    case telegram::Type::DOCK_SHIP: _doDock(telegram); return true;
    case telegram::Type::LAUNCH_SHIP: _doLaunch(telegram); return true;

    /** JUMP **/
    case telegram::Type::JUMP_IN: _doJumpIn(telegram); return true;
    case telegram::Type::JUMP_OUT: _doJumpOut(telegram); return true;

    /** DROP/TAKE */
    case telegram::Type::DROP_ITEM: _doDropItem(telegram); return true;
    case telegram::Type::TAKE_CONTAINER: _doTakeContainer(telegram); return true;

    /** OTHER */
    case telegram::Type::HIT: hitEvent(telegram); return true;
    //case telegram::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegramm); return true;

    /* GARBAGE */
    case telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE: garbageSpaceObjectEvent(telegram); return true;
    }

    return false;
}

} // namespace comm
} // namespace core

