#pragma once


#include <communication/Telegram.hpp>

#include <SFML/System/Clock.hpp>

#include <vector>

namespace core {
namespace comm {

class BTelegramHandler
{
public:
    BTelegramHandler(const Machine& machine):m_machine(machine) {}
    virtual ~BTelegramHandler() {}

    void add(Telegram&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();


    const Machine& machine() const { return m_machine; }

protected:
    virtual void _process(const Telegram&) const = 0;

    /** TRANSITION */
    void _addSectorToGalaxy(const comm::Telegram& telegram) const;
    void _addStarSystemToSector(const comm::Telegram& telegram) const;
    void _addNpcToShip(const comm::Telegram&) const;

    // items
    void _mountItem(const comm::Telegram&) const;
    void _loadItem(const comm::Telegram&) const;
    /** */

    /** CREATE */
    void _createGalaxy(const comm::Telegram&) const;
    void _createSector(const comm::Telegram&) const;
    void _createStarSystem(const comm::Telegram&) const;
    void _createNpc(const comm::Telegram&) const;

    // spaceobjects
    void _createStar(const comm::Telegram&) const;
    void _createPlanet(const comm::Telegram&) const;
    void _createAsteroid(const comm::Telegram&) const;
    void _createShip(const comm::Telegram&) const;

    // items
    void _createBomb(const comm::Telegram&) const;
    void _createGoods(const comm::Telegram&) const;
    void _createContainer(const comm::Telegram&) const;
    void _createBullet(const comm::Telegram&) const;

    // items
    void _createBak(const comm::Telegram&) const;
    void _createDrive(const comm::Telegram&) const;
    void _createDroid(const comm::Telegram&) const;
    void _createGrapple(const comm::Telegram&) const;
    void _createProtector(const comm::Telegram&) const;
    void _createScaner(const comm::Telegram&) const;
    void _createRadar(const comm::Telegram&) const;
    void _createLazer(const comm::Telegram&) const;
    void _createRocket(const comm::Telegram&) const;
    /** */

    /** ADD TO STARSYSTEM */
    void _addStarToStarSystem(const comm::Telegram&) const;
    void _addPlanetToStarSystem(const comm::Telegram&) const;
    void _addAsteroidToStarSystem(const comm::Telegram&) const;
    void _addShipToStarSystem(const comm::Telegram&) const;
    void _addContainerToStarSystem(const comm::Telegram&) const;

    /** DOCK */
    void _dockShip(const comm::Telegram&) const;
    void _launchShip(const comm::Telegram&) const;

    /** JUMP */
    void _jumpIn(const comm::Telegram&) const;
    void _jumpOut(const comm::Telegram&) const;

    /** DROP/TAKE */
    void _dropItem(const comm::Telegram&) const;
    void _pickContainer(const comm::Telegram&) const;
    /** */

    void _hit(const comm::Telegram&) const;
    void _explode(const comm::Telegram&) const;

    // GARBAGE
    void _garbageSpaceObject(const comm::Telegram&) const;

    // game states
    void _endTurn(const comm::Telegram&) const;

    // REMOVE
    void _removeSpaceObjectFromStarSystem(const comm::Telegram&) const;

    // move
    void _moveVehicle(const comm::Telegram&) const;

private:
    Machine m_machine = Machine::SERVER;
    sf::Clock m_clock;
    std::vector<Telegram> m_telegrams;

    double __currentTime() const;
};

} // namespace comm
} // namespace core
