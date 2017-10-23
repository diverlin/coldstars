#pragma once


#include <communication/Telegram.hpp>

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
void dockShip(int_t, int_t);
void launchShip(int_t, int_t);
/** JUMP */
void jumpIn(int_t);
void jumpOut(int_t, int_t);
/** DROP/TAKE */
void dropItem(int_t, int_t);
void takeContainer(int_t, int_t);
/** SHOOT */
void shoot(int_t, int_t);
} // namespace event

class TelegramHandler
{
public:
    TelegramHandler() {}
    void add(Telegram&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();

protected:
    virtual bool _process(const Telegram&);

private:
    bool m_log = true;
    sf::Clock m_clock;
    std::set<Telegram> m_telegramms;

    double __currentTime() const;
    void __log(const std::string&) const;
};

} // namespace comm
} // namespace core
