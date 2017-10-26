#include "TelegramHandler.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityType.hpp> // test

#include <core/session/Session.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>

#include <core/descriptor/Base.hpp>

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

//#include <core/communication/Events.hpp>

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

void TelegramHandler::_process(const comm::Telegram& telegram) const
{
    LOG_COMM("--server: process telegram="+telegram::to_string(telegram.type()));

    switch(telegram.type()) {
    /** CREATE */
    case telegram::Type::CREATE_GALAXY: _createGalaxy(telegram); break;
    case telegram::Type::CREATE_SECTOR: _createSector(telegram); break;
    case telegram::Type::CREATE_STARSYSTEM: _createStarSystem(telegram); break;
    case telegram::Type::CREATE_NPC: _createNpc(telegram); break;
    // spaceobjects
    case telegram::Type::CREATE_STAR: _createStar(telegram); break;
    case telegram::Type::CREATE_PLANET: _createPlanet(telegram); break;
    case telegram::Type::CREATE_ASTEROID: _createAsteroid(telegram); break;
    case telegram::Type::CREATE_SHIP: _createShip(telegram); break;
    case telegram::Type::CREATE_BOMB: _createBomb(telegram); break;
    case telegram::Type::CREATE_GOODS: _createGoods(telegram); break;
    case telegram::Type::CREATE_CONTAINER: _createContainer(telegram); break;
    case telegram::Type::CREATE_BULLET: _createBullet(telegram); break;
    // items
    case telegram::Type::CREATE_BAK: _createBak(telegram); break;
    case telegram::Type::CREATE_DRIVE: _createDrive(telegram); break;
    case telegram::Type::CREATE_DROID: _createDroid(telegram); break;
    case telegram::Type::CREATE_GRAPPLE: _createGrapple(telegram); break;
    case telegram::Type::CREATE_PROTECTOR: _createProtector(telegram); break;
    case telegram::Type::CREATE_SCANER: _createScaner(telegram); break;
    case telegram::Type::CREATE_RADAR: _createRadar(telegram); break;
    case telegram::Type::CREATE_LAZER: _createLazer(telegram); break;
    case telegram::Type::CREATE_ROCKET: _createRocket(telegram); break;
        /** */

    case telegram::Type::MOUNT_ITEM: _mountItem(telegram); break;
    case telegram::Type::LOAD_ITEM: _loadItem(telegram); break;

    /** TRANSITION */
    case telegram::Type::ADD_SECTOR_TO_GALAXY: _addSectorToGalaxy(telegram); break;
    case telegram::Type::ADD_STARSYSTEM_TO_SECTOR: _addStarSystemToSector(telegram); break;
    /** */

    /** ADD TO STARSYSTEM */
    case telegram::Type::ADD_STAR_TO_STARSYSTEM: _addStarToStarSystem(telegram); break;
    case telegram::Type::ADD_PLANET_TO_STARSYSTEM: _addPlanetToStarSystem(telegram); break;
    case telegram::Type::ADD_ASTEROID_TO_STARSYSTEM: _addAsteroidToStarSystem(telegram); break;
    case telegram::Type::ADD_SHIP_TO_STARSYSTEM: _addShipToStarSystem(telegram); break;
    case telegram::Type::ADD_CONTAINER_TO_STARSYSTEM: _addContainerToStarSystem(telegram); break;
    case telegram::Type::ADD_NPC_TO_SHIP: _addNpcToShip(telegram); break;

    /** REMOVE FROM STARSYSTEM */
    case telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: _removeSpaceObjectFromStarSystem(telegram); break;

    /** DOCK */
    case telegram::Type::DOCK_SHIP: _dockShip(telegram); break;
    case telegram::Type::LAUNCH_SHIP: _launchShip(telegram); break;

    /** JUMP **/
    case telegram::Type::JUMP_IN: _jumpIn(telegram); break;
    case telegram::Type::JUMP_OUT: _jumpOut(telegram); break;

    /** DROP/TAKE */
    case telegram::Type::DROP_ITEM: _dropItem(telegram); break;
    case telegram::Type::TAKE_CONTAINER: _pickContainer(telegram); break;

    /** OTHER */
    case telegram::Type::HIT: _hit(telegram); break;
    //case telegram::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegram); break;

    /* GARBAGE */
    case telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE: _garbageSpaceObject(telegram); break;
    default: {
        assert(false);
        break;
    }
    }
}

} // namespace comm
} // namespace core

