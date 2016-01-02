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

class MessageManager
{
    public:
        MessageManager() {}
        void add(Message&& message);

        void runLoop();
        bool update();
        
    private:
        sf::Clock m_clock;
        std::set<Message> m_messages_queue;

        double currentTime() const;
        void process(const Message& message);
};

