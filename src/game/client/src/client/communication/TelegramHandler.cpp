#include "TelegramHandler.hpp"

#include <core/descriptor/comm/Creation.hpp>
#include <core/pilot/Npc.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>

#include <client/resources/Utils.hpp>
#include <client/common/global.hpp>
#include <client/view/StarSystem.hpp>

//#include <core/builder/pilot/PlayerBuilder.hpp>
#include <client/pilot/Player.hpp>

#include <ceti/Logger.hpp>

#include <jeti/particlesystem/Explosion.hpp>

#include <memory>

namespace client {
namespace comm {

void TelegramHandler::_process(const core::comm::Telegram& telegram) const
{
    LOG_COMM("--client: process telegram="+telegram::to_string(telegram.type()));

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



    // unique client
    case telegram::Type::CREATE_PLAYER: _createPlayer(telegram); break;
    case telegram::Type::CREATE_EXPLOSION_EFFECT: _createExplosionEffect(telegram); break;
    default: {
        assert(false);
        break;
    }
    }
}

// player
void TelegramHandler::_createPlayer(const core::comm::Telegram& telegram) const {
//    descriptor::comm::CreatePlayer data(telegram.data());

//    client::Player* player = new client::Player(data.player());
//    control::Npc* npc = core::shortcuts::entities()->npc(data.npc());
//    player->setNpc(npc);
//    client::global::get().setPlayer(player);
}

void TelegramHandler::_createExplosionEffect(const core::comm::Telegram& telegram) const {
    descriptor::comm::effect::Explosion descriptor(telegram.data());
    std::shared_ptr<jeti::particlesystem::Explosion> explosion(jeti::particlesystem::genExplosion(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), descriptor.size()));
    client::global::get().view().add(explosion, descriptor.position());
}

} // namespace comm
} // namespace client


