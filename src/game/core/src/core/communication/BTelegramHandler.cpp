#include "TelegramHandler.hpp"

#include <core/descriptor/comm/ALL>
#include <core/communication/Events.hpp>

#include <ceti/Logger.hpp>

namespace core {
namespace comm {

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
    for(auto it = m_telegrams.begin(); it != m_telegrams.end(); ++it) {
        const Telegram& telegram = *it;
        if (telegram.dispatchTime() < __currentTime()) {
            _process(telegram);
            m_telegrams.erase(it);
            break;
        }
    }
}


/** TRANSITION */
void BTelegramHandler::_addSectorToGalaxy(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addSectorToGalaxy(data.object(), data.parent(), data.position());
}

void BTelegramHandler::_addStarSystemToSector(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addStarSystemToSector(data.object(), data.parent(), data.position());
}
void BTelegramHandler::_addNpcToShip(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addNpcToShip(data.object(), data.parent());
}

// items
void BTelegramHandler::_mountItem(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::mountItem(data.object(), data.parent());
}
void BTelegramHandler::_loadItem(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::loadItem(data.object(), data.parent());
}
/** */


/** CREATE */
void BTelegramHandler::_createGalaxy(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGalaxy(data.descriptor(), data.object());
}
void BTelegramHandler::_createSector(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createSector(data.descriptor(), data.object());
}
void BTelegramHandler::_createStarSystem(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createStarSystem(data.descriptor(), data.object());
}
void BTelegramHandler::_createNpc(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createNpc(data.descriptor(), data.object());
}

// spaceobjects
void BTelegramHandler::_createStar(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createStar(data.descriptor(), data.object());
}
void BTelegramHandler::_createPlanet(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createPlanet(data.descriptor(), data.object());
}
void BTelegramHandler::_createAsteroid(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createAsteroid(data.descriptor(), data.object());
}
void BTelegramHandler::_createShip(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createShip(data.descriptor(), data.object());
}

// items
void BTelegramHandler::_createBomb(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBomb(data.descriptor(), data.object());
}

void BTelegramHandler::_createGoods(const comm::Telegram& telegram) const {
    descriptor::comm::CreateGoodsPack data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGoods(data.descriptor(), data.object());
}
void BTelegramHandler::_createContainer(const comm::Telegram& telegram) const {
    descriptor::comm::CreateContainer data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createContainer(data.descriptor(), data.object(), data.item());
}
void BTelegramHandler::_createBullet(const comm::Telegram& telegram) const {
    descriptor::comm::CreateBullet data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBullet(data.owner(), data.weapon(), data.target());
}

// items
void BTelegramHandler::_createBak(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createBak(data.descriptor(), data.object());
}
void BTelegramHandler::_createDrive(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createDrive(data.descriptor(), data.object());
}
void BTelegramHandler::_createDroid(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createDroid(data.descriptor(), data.object());
}
void BTelegramHandler::_createGrapple(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createGrapple(data.descriptor(), data.object());
}
void BTelegramHandler::_createProtector(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createProtector(data.descriptor(), data.object());
}
void BTelegramHandler::_createScaner(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createScaner(data.descriptor(), data.object());
}
void BTelegramHandler::_createRadar(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createRadar(data.descriptor(), data.object());
}
void BTelegramHandler::_createLazer(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createLazer(data.descriptor(), data.object());
}
void BTelegramHandler::_createRocket(const comm::Telegram& telegram) const {
    descriptor::comm::Creation data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::createRocket(data.descriptor(), data.object());
}
/** */

/** ADD TO STARSYSTEM */
void BTelegramHandler::_addStarToStarSystem(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addStarToStarSystem(data.object(), data.parent());
}
void BTelegramHandler::_addPlanetToStarSystem(const comm::Telegram& telegram) const {
    descriptor::comm::AddingPositional data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addPlanetToStarSystem(data.object(), data.parent());
}
void BTelegramHandler::_addAsteroidToStarSystem(const comm::Telegram& telegram) const {
    AddToStarsystemDescriptor data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addAsteroidToStarSystem(data.object, data.starsystem);
}

void BTelegramHandler::_addShipToStarSystem(const comm::Telegram& telegram) const {
    AddToStarsystemDescriptor data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addShipToStarSystem(data.object, data.starsystem, data.position);
}
void BTelegramHandler::_addContainerToStarSystem(const comm::Telegram& telegram) const {
    AddToStarsystemDescriptor data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::addContainerToStarSystem(data.object, data.starsystem, data.position, data.impulse);
}

/** DOCK */
void BTelegramHandler::_dockShip(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::dockShip(data.object(), data.target());
}
void BTelegramHandler::_launchShip(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::launchShip(data.object(), data.target());
}

/** JUMP */
void BTelegramHandler::_jumpIn(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::jumpIn(data.object());
}
void BTelegramHandler::_jumpOut(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::jumpOut(data.object(), data.target());
}

/** DROP/TAKE */
void BTelegramHandler::_dropItem(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::dropItem(data.object(), data.target());
}
void BTelegramHandler::_pickContainer(const comm::Telegram& telegram) const {
    descriptor::comm::Pair data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::takeContainer(data.object(), data.target());
}

/** */

void BTelegramHandler::_hit(const comm::Telegram& telegram) const {
    descriptor::comm::Hit data(telegram.data());
    ///LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::hitSpaceObject(data.target(), data.damage());
}
void BTelegramHandler::_explode(const comm::Telegram& telegram) const {
    assert(false);
//    descriptor::Explosion data(telegram.data());
//    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
//    event::explode(data.starsystem, data.center, data.damage, data.radius);
}

// GARBAGE
void BTelegramHandler::_garbageSpaceObject(const comm::Telegram& telegram) const {
    descriptor::comm::Object data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::garbageSpaceObject(data.object());
}

// REMOVE
void BTelegramHandler::_removeSpaceObjectFromStarSystem(const comm::Telegram& telegram) const {
    descriptor::comm::StarSystemTransition data(telegram.data());
    LOG_COMM(__FUNCTION__+std::string("(), ")+data.info());
    event::removeSpaceObjectFromStarSystem(data.object(), data.starsystem());
}

} // namespace comm
} // namespace core

