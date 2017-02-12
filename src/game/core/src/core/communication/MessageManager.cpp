#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

#include <types/EntityTypes.hpp> // test

#include <core/descriptor/DescriptorManager.hpp>
#include <core/descriptor/VehicleDescriptor.hpp>
#include <core/descriptor/Base.hpp>
#include <core/descriptor/Descriptor.hpp>
#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/descriptor/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>
#include <core/descriptor/AddToStarsystemDescriptor.hpp>

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
        builder::Starsystem::create(message.data);
        break;
    }
    case TELEGRAM::CREATE_SHIP: {
        builder::Ship::getNew(message.data);
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
        builder::item::Bak().getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_DRIVE: {
        auto model = builder::item::Drive::getNew(message.data);
        assert(false);
        break;
    }
    case TELEGRAM::CREATE_DROID: {
        builder::item::Droid::getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_GRAPPLE: {
        builder::item::Grapple::getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_PROTECTOR: {
        builder::item::Protector::getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_SCANER: {
        builder::item::Scaner::getNew(message.data);
        break;
    }
    case TELEGRAM::CREATE_RADAR: {
        builder::item::Radar::getNew(message.data);
        break;
    }

        /** STARSYSTEM ADD */
    case TELEGRAM::STARSYSTEM_ADD_SHIP: {
        AddToStarsystemDescriptor descriptor(message.data);
        model::Starsystem* starsystem = model::getStarsystem(descriptor.owner);
        model::Ship* ship = model::getShip(descriptor.object);
        assert(false);
        //        starsystem->add(ship, descriptor.position/*, descriptor.angle*/);
        break;
    }
    case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
        AddToStarsystemDescriptor descriptor(message.data);
        model::Starsystem* starsystem = model::getStarsystem(descriptor.owner);
        model::Container* container = model::getContainer(descriptor.object);
        assert(false);
        //        starsystem->add(container, descriptor.position);
        break;
    }
        /** OTHER */
    case TELEGRAM::HIT: {
        descriptor::BaseOLD descriptor(message.data);
        model::SpaceObject* ob = model::getSpaceObject(descriptor.target());
        assert(false);
        //        ob->hit(descriptor.damage());
        break;
    }
    case TELEGRAM::EXPLOSION: {
        descriptor::Explosion descriptor(message.data);
        model::Starsystem* starsystem = model::getStarsystem(descriptor.starsystem_id);
        Explosion* explosion = new Explosion(descriptor.damage, descriptor.radius);
        assert(false);
        //        starsystem->add(explosion, descriptor.center);
        break;
    }
    default:
    {
        break;
    }
    }
}



