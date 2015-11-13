#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test


#include <spaceobjects/IncludeSpaceObjects.hpp>
#include <world/starsystem.hpp>
#include <descriptors/StarSystemDescriptor.hpp>
#include <builder/spaceobjects/IncludeSpaceObjectBuilders.hpp>
#include <builder/world/StarSystemBuilder.hpp>

#include <world/starsystem.hpp>

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
            m_messages_queue.erase(it);
        }
    }
}

void MessageManager::processMessage(const Message& message)
{
//    Base* receiver = global::get().entityManager().entity(message.receiver_id);
//    Base* sender   = global::get().entityManager().entity(message.sender_id);

//    std::cout<<"sender = "<<sender->dataTypeStr()<<std::endl;
//    std::cout<<"recever = "<<receiver->dataTypeStr()<<std::endl;
//    std::cout<<"disp_time = "<<message.dispatch_time;

//    assert(receiver);
//    assert(sender);

    switch(message.type_id) {
//        /** CREATE */
        case TELEGRAM::CREATE_STARSYSTEM: {
            auto starsystem = global::get().starSystemBuilder().create(StarSystemDescriptor(message.data));
            global::get().entityManager().reg(starsystem);
            break;
        }
//        case TELEGRAM::CREATE_SHIP: {
//            auto ship = global::get().shipBuilder().create(/*ShipDescriptor()*/);
//            global::get().entityManager().reg(ship);
//            break;
//        }
//        case TELEGRAM::CREATE_CONTAINER: {
//            auto container = global::get().containerBuilder().create(/*ContainerDescriptor()*/);
//            global::get().entityManager().reg(container);
//            break;
//        }
//        /** STARSYSTEM ADD */
//        case TELEGRAM::STARSYSTEM_ADD_SHIP: {
//            Ship* ob = static_cast<Ship*>(sender);
//            StarSystem* ss = static_cast<StarSystem*>(receiver);
//            assert(ob);
//            assert(ss);
//            ss->add(ob);
//            break;
//        }
//        case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
//            Container* ob = static_cast<Container*>(sender);
//            StarSystem* ss = static_cast<StarSystem*>(receiver);
//            assert(ob);
//            assert(ss);
//            ss->add(ob);
//            break;
//        }
        /** OTHER */
        case TELEGRAM::HIT: {
            HitEvent hitEvent(message.data);
            Base* victim = global::get().entityManager().entity(hitEvent.victim);
            assert(victim);
            SpaceObject* ob = static_cast<SpaceObject*>(victim);
            assert(ob);
            ob->hit(hitEvent.damage);
            break;
        }
        default:
        {
            break;
        }
    }
}



Message getMessage(const HitEvent& hitEvent, double delay) {
    return Message(TELEGRAM::HIT, hitEvent.data(), delay);
}

Message getMessage(const StarSystemDescriptor& descriptor, double delay) {
    return Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data(), delay);
}

