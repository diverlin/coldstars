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
bool doDockShip(int_t, int_t);
bool doLaunchShip(int_t, int_t);
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

