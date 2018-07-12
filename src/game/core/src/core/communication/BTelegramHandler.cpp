#include "TelegramHandler.hpp"

#include <core/communication/descriptor/ALL>
#include <core/communication/Events.hpp>

#include <ceti/Logger.hpp>

namespace core {

void BTelegramHandler::add(Telegram& telegram)
{
//    if (telegram.delay() < 0) {
//        //_process(telegram); // cause error while simulation server+client on single machine
//    } else {
        telegram.setDispatchTime(__currentTime() + telegram.delay());
        m_telegrams.push_back(telegram);
//    }
}

double BTelegramHandler::__currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void BTelegramHandler::runLoop()
{
    while(!m_telegrams.empty()) {
        update();
    }
}

void BTelegramHandler::update()
{ 
    for(auto it = m_telegrams.begin(); it != m_telegrams.end();) {
        const Telegram& telegram = *it;
        if (telegram.dispatchTime() < __currentTime()) {
            _process(telegram);
            it = m_telegrams.erase(it);
        } else {
            ++it;
        }
    }
}


/** TRANSITION */
void BTelegramHandler::_addStarSystemToGalaxy(const Telegram& telegram) const {
    AddPositionalComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addStarSystemToGalaxy(data.firstId(), data.parent(), data.position());
}

void BTelegramHandler::_addNpcToShip(const Telegram& telegram) const {
    DoubleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addNpcToShip(data.firstId(), data.secondId());
}

// items
void BTelegramHandler::_mountItem(const Telegram& telegram) const {
    DoubleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::mountItem(data.firstId(), data.secondId());
}
void BTelegramHandler::_loadItem(const Telegram& telegram) const {
    DoubleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::loadItem(data.firstId(), data.secondId());
}
/** */


/** CREATE */
void BTelegramHandler::_createGalaxy(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createGalaxy(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createStarSystem(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createStarSystem(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createNpc(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createNpc(data.descriptor(), data.firstId());
}

// spaceobjects
void BTelegramHandler::_createStar(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createStar(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createPlanet(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createPlanet(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createAsteroid(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createAsteroid(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createShip(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createShip(data.descriptor(), data.firstId());
}

// items
void BTelegramHandler::_createBomb(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createBomb(data.descriptor(), data.firstId());
}

void BTelegramHandler::_createGoods(const Telegram& telegram) const {
    CreateGoodsPackComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createGoods(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createContainer(const Telegram& telegram) const {
    CreateContainerComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createContainer(data.descriptor(), data.firstId(), data.item());
}
void BTelegramHandler::_createBullet(const Telegram& telegram) const {
    CreateBulletComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createBullet(data.owner(), data.weapon(), data.target());
}

// items
void BTelegramHandler::_createBak(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createBak(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createDrive(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createDrive(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createDroid(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createDroid(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createGrapple(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createGrapple(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createProtector(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createProtector(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createScaner(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createScaner(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createRadar(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createRadar(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createLazer(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createLazer(data.descriptor(), data.firstId());
}
void BTelegramHandler::_createRocket(const Telegram& telegram) const {
    CreateComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::createRocket(data.descriptor(), data.firstId());
}
/** */

/** ADD TO STARSYSTEM */
void BTelegramHandler::_addStarToStarSystem(const Telegram& telegram) const {
    AddPositionalComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addStarToStarSystem(data.firstId(), data.parent());
}
void BTelegramHandler::_addPlanetToStarSystem(const Telegram& telegram) const {
    AddPositionalComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addPlanetToStarSystem(data.firstId(), data.parent());
}
void BTelegramHandler::_addAsteroidToStarSystem(const Telegram& telegram) const {
    AddToStarsystemComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addAsteroidToStarSystem(data.firstId(), data.parent());
}

void BTelegramHandler::_addShipToStarSystem(const Telegram& telegram) const {
    AddToStarsystemComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addShipToStarSystem(data.firstId(), data.parent(), data.position());
}
void BTelegramHandler::_addContainerToStarSystem(const Telegram& telegram) const {
    AddToStarsystemComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::addContainerToStarSystem(data.firstId(), data.parent(), data.position(), data.impulse);
}

/** DOCK */
void BTelegramHandler::_dockShip(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::dockShip(data.firstId(), data.target());
}
void BTelegramHandler::_launchShip(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::launchShip(data.firstId(), data.target());
}

/** JUMP */
void BTelegramHandler::_jumpIn(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::jumpIn(data.firstId());
}
void BTelegramHandler::_jumpOut(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::jumpOut(data.firstId(), data.target());
}

/** DROP/TAKE */
void BTelegramHandler::_dropItem(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::dropItem(data.firstId(), data.target());
}
void BTelegramHandler::_pickContainer(const Telegram& telegram) const {
    DockComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::takeContainer(data.firstId(), data.target());
}

/** */

void BTelegramHandler::_hit(const Telegram& telegram) const {
    HitComDescr data(telegram.data());
    ///LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::hitSpaceObject(data.target(), data.damage());
}
void BTelegramHandler::_explode(const Telegram& telegram) const {
    assert(false);
//    Explosion data(telegram.data());
//    LOG_COMM(data.info());
//    event::explode(data.starsystem, data.center, data.damage, data.radius);
}

// GARBAGE
void BTelegramHandler::_garbageSpaceObject(const Telegram& telegram) const {
    SingleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::garbageSpaceObject(data.firstId());
}

// REMOVE
void BTelegramHandler::_removeSpaceObjectFromStarSystem(const Telegram& telegram) const {
    DoubleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::removeSpaceObjectFromStarSystem(data.firstId(), data.secondId());
}

// MOVE
void BTelegramHandler::_moveVehicle(const Telegram& telegram) const {
    MoveVehicleComDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::moveVehicle(data.firstId(), data.position());
}

// game states
void BTelegramHandler::_endTurn(const Telegram&) const
{
    LOG_COMM_DIP1("");
    event::endTurn();
}

void BTelegramHandler::_vehicleTargetSpaceOject(const Telegram& telegram) const
{
    DoubleIdDescr data(telegram.data());
    LOG_COMM_DIP1(data.info());
    event::targetSpaceObject(data.firstId(), data.secondId());
}

} // namespace core

