#pragma once


#include <communication/Message.hpp>
#include <descriptors/HitEvent.hpp>

#include <SFML/System/Clock.hpp>

#include <set>

class MessageManager
{
    public:
        MessageManager() {}
        void add(Message message);

        void runLoop();
        bool update();
        
    private:
        sf::Clock m_clock;
        std::set<Message> m_messages_queue;

        void processMessage(const Message& message);
        double currentTime() const;
};


Message getMessage(const HitEvent& hitEvent, double delay = 0.0);
