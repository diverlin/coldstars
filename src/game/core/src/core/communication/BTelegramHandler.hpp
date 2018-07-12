#pragma once


#include <communication/Telegram.hpp>

#include <SFML/System/Clock.hpp>

#include <vector>

namespace core {

class BTelegramHandler
{
public:
    BTelegramHandler(const Machine& machine):m_machine(machine) {}
    virtual ~BTelegramHandler() {}

    void add(Telegram&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();

    int telegramsNum() const { return m_telegrams.size(); }

    const Machine& machine() const { return m_machine; }

protected:
    virtual void _process(const Telegram&) const = 0;

    /** TRANSITION */
    void _addStarSystemToGalaxy(const Telegram& telegram) const;
    void _addNpcToShip(const Telegram&) const;

    // items
    void _mountItem(const Telegram&) const;
    void _loadItem(const Telegram&) const;
    /** */

    /** CREATE */
    void _createGalaxy(const Telegram&) const;
    void _createSector(const Telegram&) const;
    void _createStarSystem(const Telegram&) const;
    void _createNpc(const Telegram&) const;

    // spaceobjects
    void _createStar(const Telegram&) const;
    void _createPlanet(const Telegram&) const;
    void _createAsteroid(const Telegram&) const;
    void _createShip(const Telegram&) const;

    // items
    void _createBomb(const Telegram&) const;
    void _createGoods(const Telegram&) const;
    void _createContainer(const Telegram&) const;
    void _createBullet(const Telegram&) const;

    // items
    void _createBak(const Telegram&) const;
    void _createDrive(const Telegram&) const;
    void _createDroid(const Telegram&) const;
    void _createGrapple(const Telegram&) const;
    void _createProtector(const Telegram&) const;
    void _createScaner(const Telegram&) const;
    void _createRadar(const Telegram&) const;
    void _createLazer(const Telegram&) const;
    void _createRocket(const Telegram&) const;
    /** */

    /** ADD TO STARSYSTEM */
    void _addStarToStarSystem(const Telegram&) const;
    void _addPlanetToStarSystem(const Telegram&) const;
    void _addAsteroidToStarSystem(const Telegram&) const;
    void _addShipToStarSystem(const Telegram&) const;
    void _addContainerToStarSystem(const Telegram&) const;

    /** DOCK */
    void _dockShip(const Telegram&) const;
    void _launchShip(const Telegram&) const;

    /** JUMP */
    void _jumpIn(const Telegram&) const;
    void _jumpOut(const Telegram&) const;

    /** DROP/TAKE */
    void _dropItem(const Telegram&) const;
    void _pickContainer(const Telegram&) const;
    /** */

    void _hit(const Telegram&) const;
    void _explode(const Telegram&) const;

    // GARBAGE
    void _garbageSpaceObject(const Telegram&) const;

    // game states
    void _endTurn(const Telegram&) const;

    // REMOVE
    void _removeSpaceObjectFromStarSystem(const Telegram&) const;

    // move
    void _moveVehicle(const Telegram&) const;

    void _vehicleTargetSpaceOject(const Telegram& telegram) const;

private:
    Machine m_machine = Machine::SERVER;
    sf::Clock m_clock;
    std::vector<Telegram> m_telegrams;

    double __currentTime() const;
};

} // namespace core
