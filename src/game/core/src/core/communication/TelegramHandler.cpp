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

#include <core/communication/Events.hpp>

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


namespace {

/** TRANSITION */
void addSectorToGalaxyEvent(const comm::Telegram& telegram) {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addSectorToGalaxy(data.object(), data.parent(), data.position());
}

void addStarSystemToSectorEvent(const comm::Telegram& telegram) {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addStarSystemToSector(data.object(), data.parent(), data.position());
}
void addNpcToShipEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addNpcToShip(data.object(), data.parent());
}

// items
void mountItemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::mountItem(data.object(), data.parent());
}
void loadItemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::loadItem(data.object(), data.parent());
}
/** */


/** CREATE */
void createGalaxyEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGalaxy(data.descriptor(), data.object());
}
void createSectorEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createSector(data.descriptor(), data.object());
}
void createStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createStarSystem(data.descriptor(), data.object());
}
void createNpcEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createNpc(data.descriptor(), data.object());
}

// spaceobjects
void createStarEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createStar(data.descriptor(), data.object());
}
void createPlanetEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createPlanet(data.descriptor(), data.object());
}
void createAsteroidEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createAsteroid(data.descriptor(), data.object());
}
void createShipEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createShip(data.descriptor(), data.object());
}

// items
void createBombEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBomb(data.descriptor(), data.object());
}

void createGoodsEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateGoodsPack data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGoods(data.descriptor(), data.object());
}
void createContainerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateContainer data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createContainer(data.descriptor(), data.object(), data.item());
}
void createBulletEvent(const comm::Telegram& telegramm) {
    descriptor::comm::CreateBullet data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBullet(data.owner(), data.weapon(), data.target());
}

// items
void createBakEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBak(data.descriptor(), data.object());
}
void createDriveEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createDrive(data.descriptor(), data.object());
}
void createDroidEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createDroid(data.descriptor(), data.object());
}
void createGrappleEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGrapple(data.descriptor(), data.object());
}
void createProtectorEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createProtector(data.descriptor(), data.object());
}
void createScanerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createScaner(data.descriptor(), data.object());
}
void createRadarEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createRadar(data.descriptor(), data.object());
}
void createLazerEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createLazer(data.descriptor(), data.object());
}
void createRocketEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Creation data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createRocket(data.descriptor(), data.object());
}
/** */

/** ADD TO STARSYSTEM */
void addStarToStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addStarToStarSystem(data.object(), data.parent());
}
void addPlanetToStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::AddingPositional data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addPlanetToStarSystem(data.object(), data.parent());
}
void addAsteroidToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addAsteroidToStarSystem(data.object, data.starsystem);
}

void addShipToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addShipToStarSystem(data.object, data.starsystem, data.position);
}
void addContainerToStarSystemEvent(const comm::Telegram& telegramm) {
    AddToStarsystemDescriptor data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addContainerToStarSystem(data.object, data.starsystem, data.position, data.impulse);
}

/** DOCK */
void _doDock(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::dockShip(data.object(), data.target());
}
void _doLaunch(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::launchShip(data.object(), data.target());
}

/** JUMP */
void _doJumpIn(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::jumpIn(data.object());
}
void _doJumpOut(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::jumpOut(data.object(), data.target());
}

/** DROP/TAKE */
void _doDropItem(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::dropItem(data.object(), data.target());
}
void _doTakeContainer(const comm::Telegram& telegramm) {
    descriptor::comm::Pair data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::takeContainer(data.object(), data.target());
}

/** */

void hitEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Hit data(telegramm.data());
    ///LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::hitSpaceObject(data.target(), data.damage());
}
void explosionEvent(const comm::Telegram& telegramm) {
    descriptor::Explosion data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::explode(data.starsystem, data.center, data.damage, data.radius);
}

// GARBAGE
void garbageSpaceObjectEvent(const comm::Telegram& telegramm) {
    descriptor::comm::Object data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::garbageSpaceObject(data.object());
}

// REMOVE
void removeSpaceObjectFromStarSystemEvent(const comm::Telegram& telegramm) {
    descriptor::comm::StarSystemTransition data(telegramm.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::removeSpaceObjectFromStarSystem(data.object(), data.starsystem());
}

} // namespace


void TelegramHandler::_process(const comm::Telegram& telegram) const
{
    LOG_COMM("--server: process telegramm="+telegram::to_string(telegram.type()));

    switch(telegram.type()) {
    /** CREATE */
    case telegram::Type::CREATE_GALAXY: createGalaxyEvent(telegram); break;
    case telegram::Type::CREATE_SECTOR: createSectorEvent(telegram); break;
    case telegram::Type::CREATE_STARSYSTEM: createStarSystemEvent(telegram); break;
    case telegram::Type::CREATE_NPC: createNpcEvent(telegram); break;
    // spaceobjects
    case telegram::Type::CREATE_STAR: createStarEvent(telegram); break;
    case telegram::Type::CREATE_PLANET: createPlanetEvent(telegram); break;
    case telegram::Type::CREATE_ASTEROID: createAsteroidEvent(telegram); break;
    case telegram::Type::CREATE_SHIP: createShipEvent(telegram); break;
    case telegram::Type::CREATE_BOMB: createBombEvent(telegram); break;
    case telegram::Type::CREATE_GOODS: createGoodsEvent(telegram); break;
    case telegram::Type::CREATE_CONTAINER: createContainerEvent(telegram); break;
    case telegram::Type::CREATE_BULLET: createBulletEvent(telegram); break;
    // items
    case telegram::Type::CREATE_BAK: createBakEvent(telegram); break;
    case telegram::Type::CREATE_DRIVE: createDriveEvent(telegram); break;
    case telegram::Type::CREATE_DROID: createDroidEvent(telegram); break;
    case telegram::Type::CREATE_GRAPPLE: createGrappleEvent(telegram); break;
    case telegram::Type::CREATE_PROTECTOR: createProtectorEvent(telegram); break;
    case telegram::Type::CREATE_SCANER: createScanerEvent(telegram); break;
    case telegram::Type::CREATE_RADAR: createRadarEvent(telegram); break;
    case telegram::Type::CREATE_LAZER: createLazerEvent(telegram); break;
    case telegram::Type::CREATE_ROCKET: createRocketEvent(telegram); break;
        /** */

    case telegram::Type::MOUNT_ITEM: mountItemEvent(telegram); break;
    case telegram::Type::LOAD_ITEM: loadItemEvent(telegram); break;

    /** TRANSITION */
    case telegram::Type::ADD_SECTOR_TO_GALAXY: addSectorToGalaxyEvent(telegram); break;
    case telegram::Type::ADD_STARSYSTEM_TO_SECTOR: addStarSystemToSectorEvent(telegram); break;
    /** */

    /** ADD TO STARSYSTEM */
    case telegram::Type::ADD_STAR_TO_STARSYSTEM: addStarToStarSystemEvent(telegram); break;
    case telegram::Type::ADD_PLANET_TO_STARSYSTEM: addPlanetToStarSystemEvent(telegram); break;
    case telegram::Type::ADD_ASTEROID_TO_STARSYSTEM: addAsteroidToStarSystemEvent(telegram); break;
    case telegram::Type::ADD_SHIP_TO_STARSYSTEM: addShipToStarSystemEvent(telegram); break;
    case telegram::Type::ADD_CONTAINER_TO_STARSYSTEM: addContainerToStarSystemEvent(telegram); break;
    case telegram::Type::ADD_NPC_TO_SHIP: addNpcToShipEvent(telegram); break;

    /** REMOVE FROM STARSYSTEM */
    case telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: removeSpaceObjectFromStarSystemEvent(telegram); break;

    /** DOCK */
    case telegram::Type::DOCK_SHIP: _doDock(telegram); break;
    case telegram::Type::LAUNCH_SHIP: _doLaunch(telegram); break;

    /** JUMP **/
    case telegram::Type::JUMP_IN: _doJumpIn(telegram); break;
    case telegram::Type::JUMP_OUT: _doJumpOut(telegram); break;

    /** DROP/TAKE */
    case telegram::Type::DROP_ITEM: _doDropItem(telegram); break;
    case telegram::Type::TAKE_CONTAINER: _doTakeContainer(telegram); break;

    /** OTHER */
    case telegram::Type::HIT: hitEvent(telegram); break;
    //case telegram::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegramm); break;

    /* GARBAGE */
    case telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE: garbageSpaceObjectEvent(telegram); break;
    default: {
        assert(false);
        break;
    }
    }
}

} // namespace comm
} // namespace core

