#include "MessageManager.hpp"

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <common/constants.hpp>

#include <core/type/EntityTypes.hpp> // test

#include <core/descriptor/Hit.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Container.hpp> // ??
#include <core/descriptor/ExplosionDescriptor.hpp>
#include <core/descriptor/AddToStarsystemDescriptor.hpp>

#include <core/spaceobject/ALL>

#include <world/starsystem.hpp>

#include <core/builder/spaceobject/ALL>

#include <core/builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
#include <core/builder/item/artefact/ALL>
#endif // USE_ARTEFACTS
#include <core/builder/item/other/ALL>

#include <core/builder/world/StarSystemBuilder.hpp>

#include <core/world/starsystem.hpp>

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
        builder::StarSystem::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_SHIP: {
        assert(false);
//        builder::Ship::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_BOMB: {
        assert(false);
//        core::global::get().bombBuilder().gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_CONTAINER: {
        assert(false);
//        core::global::get().containerBuilder().gen(message.data);
        break;
    }

        // items
    case TELEGRAM::CREATE_BAK: {
        assert(false);
//        builder::item::Bak::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_DRIVE: {
        assert(false);
//        auto model = builder::item::Drive::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_DROID: {
        assert(false);
//        builder::item::Droid::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_GRAPPLE: {
        assert(false);
//        builder::item::Grapple::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_PROTECTOR: {
        assert(false);
//        builder::item::Protector::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_SCANER: {
        assert(false);
//        builder::item::Scaner::gen(message.data);
        break;
    }
    case TELEGRAM::CREATE_RADAR: {
        assert(false);
//        builder::item::Radar::gen(message.data);
        break;
    }

        /** STARSYSTEM ADD */
    case TELEGRAM::STARSYSTEM_ADD_SHIP: {
        AddToStarsystemDescriptor descriptor(message.data);
        model::StarSystem* starsystem = model::getStarsystem(descriptor.owner);
        model::Ship* ship = model::getShip(descriptor.object);
        assert(false);
        //        starsystem->add(ship, descriptor.position/*, descriptor.angle*/);
        break;
    }
    case TELEGRAM::STARSYSTEM_ADD_CONTAINER: {
        AddToStarsystemDescriptor descriptor(message.data);
        model::StarSystem* starsystem = model::getStarsystem(descriptor.owner);
        model::Container* container = model::getContainer(descriptor.object);
        assert(false);
        //        starsystem->add(container, descriptor.position);
        break;
    }
        /** OTHER */
    case TELEGRAM::HIT: {
        descriptor::Hit descr(message.data);
        model::SpaceObject* ob = model::getSpaceObject(descr.target());
        assert(false);
        //        ob->hit(descriptor.damage());
        break;
    }
    case TELEGRAM::EXPLOSION: {
        descriptor::Explosion descriptor(message.data);
        model::StarSystem* starsystem = model::getStarsystem(descriptor.starsystem_id);
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



