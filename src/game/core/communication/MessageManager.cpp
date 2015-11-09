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

void MessageManager::add(Message message)
{
    message.dispatch_time = currentTime() + message.delay;
    m_messages_queue.insert(message);
}

double MessageManager::currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void MessageManager::runLoop()
{
    while(!m_messages_queue.empty()) {
        update();
    }
}

bool MessageManager::update()
{ 
    for ( auto it = m_messages_queue.begin(); it != m_messages_queue.end(); ++it ) {
        const Message& message = *it;
        if (message.dispatch_time < currentTime()) {
            processMessage(message);
            //SendEvent(receiver, message);
            m_messages_queue.erase(it);
        }
    }
}

void MessageManager::processMessage(const Message& message)
{
    Base* receiver = global::get().entityManager().entity(message.receiver_id);
    Base* sender   = global::get().entityManager().entity(message.sender_id);

    std::cout<<"sender = "<<sender->dataTypeStr()<<std::endl;
    std::cout<<"recever = "<<receiver->dataTypeStr()<<std::endl;
    std::cout<<"disp_time = "<<message.dispatch_time;

    assert(receiver);
    assert(sender);

    switch(message.type_id) {
        case TELEGRAM::HIT: {
            SpaceObject* ob = static_cast<SpaceObject*>(receiver);
            assert(ob);
            int damage = std::stoi(message.extra);
            //std::cout<<damage<<std::endl;
            ob->hit(damage);
            break;
        }
        default:
        {
            break;
        }
    }
}


