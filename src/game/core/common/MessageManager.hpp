#pragma once

#include <set>

#include <spaceobjects/SpaceObject.hpp>
#include "Message.hpp"

class MessageManager
{
    public:
        static MessageManager& Instance();

        void newMessage(double delay,
                        int    sender_id,
                        int    receiver_id,
                        int    type_id,
                        void*  extra);

        void updateQueue();
        
    private:
        std::set<Message> m_messages_queue;

//        void SendEvent(SpaceObject*, const Message&);

        MessageManager() {}
        MessageManager(const MessageManager&);
        MessageManager& operator=(const MessageManager&);
};
