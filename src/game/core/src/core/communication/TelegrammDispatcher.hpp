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

namespace core {
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

class TelegrammHandler
{
public:
    TelegrammHandler() {}
    void add(Telegramm&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();

protected:
    virtual bool _process(const Telegramm&);

private:
    bool m_log = true;
    sf::Clock m_clock;
    std::set<Telegramm> m_telegramms;

    double __currentTime() const;
    void __log(const std::string&) const;
};

} // namespace comm
} // namespace core
