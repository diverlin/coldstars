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

        void processMessage(const Message& message);
        double currentTime() const;
};

Message getMessage(const StarSystemDescriptor& descriptor, double delay = -1.0);
Message getMessage(const VehicleDescriptor& descriptor, double delay = -1.0);
Message getMessage(const BombDescriptor& descriptor, double delay = -1.0);
Message getMessage(const ContainerDescriptor& descriptor, double delay = -1.0);
Message getMessage(const HitDescriptor& descriptor, double delay = 0.0);
Message getMessage(const ExplosionDescriptor& descriptor, double delay = 0.0);
