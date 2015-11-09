#pragma once


#include <spaceobjects/SpaceObject.hpp>
#include <communication/Message.hpp>

#include <SFML/System/Clock.hpp>

#include <set>

class MessageManager
{
    public:
        MessageManager() {}
//        void newMessage(double delay,
//                        int    sender_id,
//                        int    receiver_id,
//                        int    type_id,
//                        void*  extra);

        void add(Message message);

        void runLoop();
        bool update();
        
    private:
        sf::Clock m_clock;
        std::set<Message> m_messages_queue;

        void processMessage(const Message& message);
        double currentTime() const;
//        void SendEvent(SpaceObject*, const Message&);
};
