#pragma once


#include <communication/Telegramm.hpp>

#include <SFML/System/Clock.hpp>

#include <set>

class StarSystemDescriptor;
class VehicleDescriptor;
class BombDescriptor;
class ContainerDescriptor;
class HitDescriptor;
class ExplosionDescriptor;
class AddToStarsystemDescriptor;

namespace comm {

namespace event {
/** DOCK */
void doDockShip(int_t, int_t);
void doLaunchShip(int_t, int_t);
/** JUMP */
void doJumpIn(int_t);
void doJumpOut(int_t, int_t);
/** DROP/TAKE */
void doDropItem(int_t, int_t);
void doTakeContainer(int_t, int_t);
/** SHOOT */
void doShoot(int_t, int_t);
} // namespace event

class TelegrammManager
{
public:
    TelegrammManager() {}
    void add(comm::Telegramm&&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();

private:
    sf::Clock m_clock;
    std::set<comm::Telegramm> m_telegramms;

    double currentTime() const;
    void process(const comm::Telegramm&);
};

} // namespace comm
