#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test

#include <descriptors/VehicleDescriptor.hpp>
#include <descriptors/Base.hpp>
#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/Container.hpp> // ??
#include <descriptors/ExplosionDescriptor.hpp>
#include <descriptors/AddToStarsystemDescriptor.hpp>

#include <spaceobjects/ALL>
#include <world/starsystem.hpp>

#include <builder/spaceobjects/ALL>

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

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
            global::get().starsystemBuilder().getNew(message.data);
            break;
        }
        case TELEGRAM::CREATE_SHIP: {
            ShipBuilder::getNew(message.data);
            break;
        }
        case TELEGRAM::CREATE_BOMB: {
            global::get().bombBuilder().create(message.data);
            break;
        }
        case TELEGRAM::CREATE_CONTAINER: {
            global::get().containerBuilder().getNew(message.data);
            break;
        }
        /** STARSYSTEM ADD */
        case TELEGRAM::STARSYSTEM_ADD_SHIP: {
            AddToStarsystemDescriptor descriptor(message.data);
            Starsystem* starsystem = global::get().entityManager().get<Starsystem*>(descriptor.owner);
            Ship* ship = global::get().entityManager().get<Ship*>(descriptor.object);
            starsystem->add(ship, descriptor.position/*, descriptor.angle*/);
            break;
        }
        case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
            AddToStarsystemDescriptor descriptor(message.data);
            Starsystem* starsystem = global::get().entityManager().get<Starsystem*>(descriptor.owner);
            Container* container = global::get().entityManager().get<Container*>(descriptor.object);
            starsystem->add(container, descriptor.position);
            break;
        }
        /** OTHER */
        case TELEGRAM::HIT: {
            descriptor::Base descriptor(message.data);
            SpaceObject* ob = global::get().entityManager().get<SpaceObject*>(descriptor.target());
            ob->hit(descriptor.damage());
            break;
        }
        case TELEGRAM::EXPLOSION: {
            descriptor::Explosion descriptor(message.data);
            Starsystem* starsystem = global::get().entityManager().get<Starsystem*>(descriptor.starsystem_id);
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



