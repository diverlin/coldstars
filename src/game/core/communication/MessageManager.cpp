#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test

#include <descriptors/StarSystemDescriptor.hpp>
#include <descriptors/VehicleDescriptor.hpp>
#include <descriptors/items/BombDescriptor.hpp>
#include <descriptors/ContainerDescriptor.hpp>
#include <descriptors/HitEvent.hpp>

#include <spaceobjects/IncludeSpaceObjects.hpp>
#include <world/starsystem.hpp>

#include <builder/spaceobjects/IncludeSpaceObjectBuilders.hpp>
#include <builder/items/IncludeItemBuilders.hpp>
#include <builder/world/StarSystemBuilder.hpp>

#include <world/starsystem.hpp>

void MessageManager::add(Message&& message)
{
    if (message.delay < 0) {
        processMessage(message);
    } else {
        message.dispatch_time = currentTime() + message.delay;
        m_messages_queue.insert(message);
    }
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
    switch(message.type_id) {
        /** CREATE */
        case TELEGRAM::CREATE_STARSYSTEM: {
            global::get().starSystemBuilder().create(message.data);
            break;
        }
        case TELEGRAM::CREATE_SHIP: {
            global::get().shipBuilder().create(message.data);
            break;
        }
        case TELEGRAM::CREATE_BOMB: {
            global::get().bombBuilder().create(message.data);
            break;
        }
        case TELEGRAM::CREATE_CONTAINER: {
            global::get().containerBuilder().create(message.data);
            break;
        }
        /** */
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
            Base* victim = global::get().entityManager().get(hitEvent.victim);
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

Message getMessage(const StarSystemDescriptor& descriptor, double delay) {
    return Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data(), delay);
}

Message getMessage(const VehicleDescriptor& descriptor, double delay) {
    return Message(TELEGRAM::CREATE_SHIP, descriptor.data(), delay);
}

Message getMessage(const BombDescriptor& descriptor, double delay) {
    return Message(TELEGRAM::CREATE_BOMB, descriptor.data(), delay);
}

Message getMessage(const ContainerDescriptor& descriptor, double delay) {
    return Message(TELEGRAM::CREATE_CONTAINER, descriptor.data(), delay);
}

Message getMessage(const HitEvent& hitEvent, double delay) {
    return Message(TELEGRAM::HIT, hitEvent.data(), delay);
}

