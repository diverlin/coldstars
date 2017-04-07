#pragma once


#include <communication/Message.hpp>

#include <SFML/System/Clock.hpp>

#include <set>

class StarSystemDescriptor;
class VehicleDescriptor;
class BombDescriptor;
class ContainerDescriptor;
class HitDescriptor;
class ExplosionDescriptor;
class AddToStarsystemDescriptor;

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
} // namespace event

class MessageManager
{
public:
    MessageManager() {}
    void add(comm::Message&& message);

    void runLoop();
    void update();

private:
    sf::Clock m_clock;
    std::set<comm::Message> m_messages_queue;

    double currentTime() const;
    void process(const comm::Message& message);
};

