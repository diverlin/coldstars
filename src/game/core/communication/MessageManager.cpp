#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test

#include <descriptors/StarSystemDescriptor.hpp>
#include <descriptors/VehicleDescriptor.hpp>
#include <descriptors/Descriptor.hpp>
#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/ContainerDescriptor.hpp>
#include <descriptors/ExplosionDescriptor.hpp>
#include <descriptors/AddToStarsystemDescriptor.hpp>

#include <spaceobjects/IncludeSpaceObjects.hpp>
#include <world/starsystem.hpp>

#include <builder/spaceobjects/IncludeSpaceObjectBuilders.hpp>
#include <builder/items/IncludeItemBuilders.hpp>
#include <builder/world/StarSystemBuilder.hpp>

#include <world/starsystem.hpp>

void MessageManager::add(Message&& message)
{
    if (message.delay < 0) {
        process(message);
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

void MessageManager::update()
{ 
    for ( auto it = m_messages_queue.begin(); it != m_messages_queue.end(); ++it ) {
        const Message& message = *it;
        if (message.dispatch_time < currentTime()) {
            process(message);
            m_messages_queue.erase(it);
        }
    }
}

void MessageManager::process(const Message& message)
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
        /** STARSYSTEM ADD */
        case TELEGRAM::STARSYSTEM_ADD_SHIP: {
            AddToStarsystemDescriptor descriptor(message.data);
            StarSystem* starsystem = static_cast<StarSystem*>(global::get().entityManager().get(descriptor.owner));
            Ship* ship = static_cast<Ship*>(global::get().entityManager().get(descriptor.object));
            assert(starsystem);
            assert(ship);
            starsystem->add(ship, descriptor.position/*, descriptor.angle*/);
            break;
        }
        case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
            AddToStarsystemDescriptor descriptor(message.data);
            StarSystem* starsystem = static_cast<StarSystem*>(global::get().entityManager().get(descriptor.owner));
            Container* container = static_cast<Container*>(global::get().entityManager().get(descriptor.object));
            assert(starsystem);
            assert(container);
            starsystem->add(container, descriptor.position);
            break;
        }
        /** OTHER */
        case TELEGRAM::HIT: {
            Descriptor descriptor(message.data);
            SpaceObject* ob = static_cast<SpaceObject*>(global::get().entityManager().get(descriptor.target()));
            assert(ob);
            ob->hit(descriptor.damage());
            break;
        }
        case TELEGRAM::EXPLOSION: {
            ExplosionDescriptor descriptor(message.data);
            StarSystem* starsystem = static_cast<StarSystem*>(global::get().entityManager().get(descriptor.starsystem_id));
            assert(starsystem);
            Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
            starsystem->add(explosion, descriptor.center);
            break;
        }
        default:
        {
            break;
        }
    }
}



