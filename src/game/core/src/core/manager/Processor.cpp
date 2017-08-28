/*
    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "Processor.hpp"

#include <core/world/starsystem.hpp>
#include <core/common/Global.hpp>
#include <core/spaceobject/ALL>
#include <core/item/equipment/ALL>
#include <core/world/starsystem.hpp>
#include <core/descriptor/item/ALL>

#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/descriptor/comm/Creation.hpp>
#include <core/descriptor/comm/Hit.hpp>
#include <core/communication/TelegrammHub.hpp>
#include <core/communication/TelegrammManager.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

namespace core {
namespace manager {

Processor&
Processor::get()
{
    static Processor instance;
    return instance;
}

Processor::Processor()
    :
      m_telegrammHub(core::global::get().telegrammHub())
    , m_entitiesManager(manager::Entity::get())
    , m_descriptorManager(descriptor::Manager::get())
{

}

std::vector<glm::vec3>
Processor::__genImpulses(int num) const
{
    std::vector<glm::vec3> result;
    float delta_angle = float(2*M_PI/num);
    float angle = meti::rand::gen_angle();
    for (int i=0; i<num; ++i) {
        float radius = meti::rand::gen_float(1.0f, 2.0f);
        result.push_back(meti::get_vec3(radius, angle));
        angle += delta_angle;
    }
    return result;
}

void Processor::death_spaceobject(control::SpaceObject* object)
{
    switch(object->type()) {
    case entity::Type::ASTEROID: death(static_cast<control::Asteroid*>(object)); break;
    case entity::Type::CONTAINER: __death(static_cast<control::Container*>(object)); break;
    case entity::Type::BULLET: death(static_cast<control::Bullet*>(object)); break;
    case entity::Type::SHIP:
    case entity::Type::SPACESTATION:
    case entity::Type::SATELLITE: __death(static_cast<control::Vehicle*>(object)); break;
    default: assert(false);
    }
}

void Processor::death(control::Asteroid* asteroid)
{
    // create minerals
    int containers_num = meti::rand::gen_int(1,3);
    std::vector<glm::vec3> impulses = __genImpulses(containers_num);
    for (int i=0; i<containers_num; ++i) {
        int_t item_id = m_entitiesManager.genId();
        int amount = meti::rand::gen_int(3, 100);
        {
        int_t descriptor_id = m_descriptorManager.randGoods()->id();
        descriptor::comm::CreateGoodsPack telegramm_descriptor(item_id, descriptor_id, amount);
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_GOODS, telegramm_descriptor.data()));
        }
        int_t container_id = m_entitiesManager.genId();
        {
        int_t descriptor_id = m_descriptorManager.randContainer()->id();
        descriptor::comm::CreateContainer telegramm_descriptor(container_id, descriptor_id, item_id);
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_CONTAINER, telegramm_descriptor.data()));
        }
        {
        AddToStarsystemDescriptor telegramm_descriptor(asteroid->starsystem()->id(), container_id, asteroid->position(), impulses[i], asteroid->direction());
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM, telegramm_descriptor.data()));
        }
    }

    __removeSpaceObjectFromStarSystem(asteroid);
    __addSpaceObjectToGarbage(asteroid);

    __explosionEffect(asteroid->collisionRadius(), asteroid->position());
}

void Processor::__death(control::Vehicle* vehicle)
{
    // create containers
    int containers_num = meti::rand::gen_int(1,3);
    const ceti::pack<int_t> items = vehicle->model()->items().random(containers_num);
    containers_num = int(items.size());

    std::vector<glm::vec3> impulses = __genImpulses(containers_num);
    for (int i=0; i<containers_num; ++i) {
        int_t container_id = m_entitiesManager.genId();
        int_t descriptor_id = m_descriptorManager.randContainer()->id();
        int_t item_id = items[i];
        {
        descriptor::comm::CreateContainer telegramm_descriptor(container_id, descriptor_id, item_id);
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_CONTAINER, telegramm_descriptor.data()));
        }
        {
        AddToStarsystemDescriptor telegramm_descriptor(vehicle->starsystem()->id(), container_id, vehicle->position(), impulses[i], vehicle->direction()/* todo: add direction less way*/ );
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM, telegramm_descriptor.data()));
        }
    }

    __removeSpaceObjectFromStarSystem(vehicle);
    __addSpaceObjectToGarbage(vehicle);

    __explosionEffect(vehicle->collisionRadius(), vehicle->position());
}

void Processor::death(control::Bullet* bullet)
{
    __removeSpaceObjectFromStarSystem(bullet);
    __addSpaceObjectToGarbage(bullet);

    __explosionEffect(2*bullet->collisionRadius(), bullet->position());
}

void Processor::__death(control::Container* container)
{
    __removeSpaceObjectFromStarSystem(container);
    __addSpaceObjectToGarbage(container);

    __explosionEffect(2*container->collisionRadius(), container->position());
}


void Processor::genBullets_DEBUG(control::StarSystem* starsystem, int num) const
{
    if (starsystem->bullets().size() >= num) {
        return;
    }

    control::Vehicle* vehicle = meti::rand::get_pointer(starsystem->vehicles());
    if (starsystem->asteroids().empty()) { // ugly workaround
        return;
    }
    control::SpaceObject* target = meti::rand::get_pointer(starsystem->asteroids());
    if (!vehicle || !target) {
        return;
    }

    int_t owner_id = vehicle->id();
    int_t target_id = target->id();

    std::vector<control::item::Weapon*> rockets = vehicle->weapons().rockets();
    if (rockets.empty()) { //ugly workaround
        return;
    }
    control::item::Weapon* rocket = meti::rand::get_pointer(rockets);
    if (!rocket) {
        return;
    }

    int_t item_id = rocket->id();

    descriptor::comm::CreateBullet telegramm_descriptor(owner_id, item_id, target_id);
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_BULLET, telegramm_descriptor.data()));
}

void Processor::__removeSpaceObjectFromStarSystem(control::SpaceObject* object)
{
    descriptor::comm::StarSystemTransition descriptor(object->id(), object->starsystem()->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM, descriptor.data()));
}

void Processor::__addSpaceObjectToGarbage(control::SpaceObject* object)
{
    descriptor::comm::Object descriptor(object->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::ADD_SPACEOBJECT_TO_GARBAGE, descriptor.data()));
}

void Processor::__explosionEffect(float radius, const glm::vec3& position)
{
    descriptor::comm::effect::Explosion telegramm_descriptor(radius, position);
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
}

void Processor::hit(control::SpaceObject* object, int damage)
{
    descriptor::comm::Hit descriptor(object->id(), object->id(), damage);
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::HIT, descriptor.data()));
}


} // namespace manager
} // namespace core
