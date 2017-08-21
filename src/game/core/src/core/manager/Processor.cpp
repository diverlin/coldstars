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

#include <core/common/Global.hpp>
#include <core/spaceobject/ALL>
#include <core/world/starsystem.hpp>
#include <core/descriptor/item/ALL>

#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/descriptor/comm/Creation.hpp>
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


void Processor::death(control::Asteroid* asteroid)
{

    // send message asteroid death
    {
    descriptor::comm::Object object(asteroid->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::KILL_ASTEROID, object.data()));
    }

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

    // send telegram to create explosion
    {
        descriptor::comm::effect::Explosion telegramm_descriptor(asteroid->collisionRadius(), asteroid->position());
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
    }
}

void Processor::death(control::Vehicle* vehicle)
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

    // send message vehicle death
    {
    descriptor::comm::Object object(vehicle->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::KILL_VEHICLE, object.data()));
    }

    // send telegram to create explosion
    {
        descriptor::comm::effect::Explosion telegramm_descriptor(vehicle->collisionRadius(), vehicle->position());
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
    }
}

void Processor::death(control::Bullet* bullet)
{
    // send message bullet death
    {
    descriptor::comm::Object object(bullet->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::KILL_BULLET, object.data()));
    }

    // send telegram to create explosion
    {
        descriptor::comm::effect::Explosion telegramm_descriptor(2*bullet->collisionRadius(), bullet->position());
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
    }
}

void Processor::death(control::Container* container)
{
    // send message container death
    {
    descriptor::comm::Object object(container->id());
    m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::KILL_CONTAINER, object.data()));
    }

    // send telegram to create explosion
    {
        descriptor::comm::effect::Explosion telegramm_descriptor(2*container->collisionRadius(), container->position());
        m_telegrammHub.add(core::comm::Telegramm(core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
    }
}


} // namespace manager
} // namespace core
