#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test

#include <descriptors/DescriptorManager.hpp>
#include <descriptors/VehicleDescriptor.hpp>
#include <descriptors/Base.hpp>
#include <descriptors/Descriptor.hpp>
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
       core::global::get().starsystemBuilder().create(message.data);
        break;
    }
    case TELEGRAM::CREATE_SHIP: {
        ShipBuilder::getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_BOMB: {
       core::global::get().bombBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_CONTAINER: {
       core::global::get().containerBuilder().getNew(message.data);
        break;
    }

        // items
    case TELEGRAM::CREATE_BAK: {
       core::global::get().bakBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_DRIVE: {
       core::global::get().driveBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_DROID: {
       core::global::get().droidBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_GRAPPLE: {
       core::global::get().grappleBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_SCANER: {
       core::global::get().scanerBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_RADAR: {
       core::global::get().radarBuilder().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_PROTECTOR: {
       core::global::get().protectorBuilder().getNew(message.data);
        break;
    }

    /** STARSYSTEM ADD */
    case TELEGRAM::STARSYSTEM_ADD_SHIP: {
        AddToStarsystemDescriptor descriptor(message.data);
        Starsystem* starsystem =core::global::get().entityManager().getEntity<Starsystem*>(descriptor.owner);
        Ship* ship =core::global::get().entityManager().getEntity<Ship*>(descriptor.object);
        starsystem->add(ship, descriptor.position/*, descriptor.angle*/);
        break;
    }
    case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
        AddToStarsystemDescriptor descriptor(message.data);
        Starsystem* starsystem =core::global::get().entityManager().getEntity<Starsystem*>(descriptor.owner);
        Container* container =core::global::get().entityManager().getEntity<Container*>(descriptor.object);
        starsystem->add(container, descriptor.position);
        break;
    }
        /** OTHER */
    case TELEGRAM::HIT: {
        descriptor::BaseOLD descriptor(message.data);
        SpaceObject* ob =core::global::get().entityManager().getEntity<SpaceObject*>(descriptor.target());
        ob->hit(descriptor.damage());
        break;
    }
    case TELEGRAM::EXPLOSION: {
        descriptor::Explosion descriptor(message.data);
        Starsystem* starsystem =core::global::get().entityManager().getEntity<Starsystem*>(descriptor.starsystem_id);
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



