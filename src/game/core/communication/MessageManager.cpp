#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test


//void MessageManager::SendEvent(SpaceObject* receiver, const Message& message)
//{
//    //receiver->HandleMessage(message);
//}

//void MessageManager::newMessage(double delay,
//                                int    sender_id,
//                                int    receiver_id,
//                                int    type_id,
//                                void*  extra)
//{
//    Base* sender   = global::get().entityManager().entity(sender_id);
//    Base* receiver = global::get().entityManager().entity(receiver_id);
//    if (!receiver) {
//        return;
//    }

//    Message message(NO_DELAY, sender_id, receiver_id, type_id, extra);

//    if (delay <= 0.0f) {
//        //SendEvent(receiver, message);
//        return;
//    } else {
//        //double CurrentTime = Clock->GetCurrentTime();
//        //telegram.DispatchTime = CurrentTime + delay;
//    }
    
//    m_messages_queue.insert(message);
//}

void MessageManager::addMessage(const Message& message)
{
    m_messages_queue.insert(message);
}

void MessageManager::updateQueue()
{ 
    //double CurrentTime = Clock->GetCurrentTime();

    //while( !messages_queue.empty() && (messages_queue.begin()->DispatchTime < CurrentTime) && (messages_queue.begin()->DispatchTime > 0) )
    {
        const Message& message = *m_messages_queue.begin();
        processMessage(message);

        //SendEvent(receiver, message);

        m_messages_queue.erase(m_messages_queue.begin());
    }
}

void MessageManager::processMessage(const Message& message)
{
    Base* receiver = global::get().entityManager().entity(message.receiver_id);
    Base* sender   = global::get().entityManager().entity(message.sender_id);

    std::cout<<sender->dataTypeStr()<<std::endl;
    std::cout<<receiver->dataTypeStr()<<std::endl;

    assert(receiver);
    assert(sender);

    switch(message.type_id) {
        case TELEGRAM::HIT: {
            SpaceObject* ob = static_cast<SpaceObject*>(receiver);
            assert(ob);
            ob->hit(100);
            break;
        }
        default: { }
    }
}


