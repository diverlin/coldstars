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

#include "TelegramCreator.hpp"

#include <core/world/starsystem.hpp>
#include <core/common/Global.hpp>
#include <core/spaceobject/ALL>
#include <core/pilot/Npc.hpp>
#include <core/item/equipment/ALL>
#include <core/world/starsystem.hpp>
#include <core/descriptor/item/ALL>

#include <core/pilot/Player.hpp>

#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/descriptor/spaceobject/ALL>
#include <core/descriptor/pilot/Npc.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>
#include <core/descriptor/comm/Creation.hpp>
#include <core/descriptor/comm/AddingPositional.hpp>
#include <core/descriptor/comm/Hit.hpp>
#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

#include <core/communication/TelegramHub.hpp>
#include <core/communication/TelegramHandler.hpp>

#include <core/math/rand.hpp> // ugly

namespace core {

TelegramCreator&
TelegramCreator::get()
{
    static TelegramCreator instance;
    return instance;
}

TelegramCreator::TelegramCreator()
    :
      m_telegrammHub(core::global::get().telegrammHub())
{

}

void TelegramCreator::__createSectors(descriptor::Galaxy* galaxy_descriptor, int_t galaxy_id) const
{
    for(int_t sector_descriptor_id: galaxy_descriptor->sectors) {
        int_t sector_id = shortcuts::entities()->nextId();

        {
        descriptor::comm::Creation telegramm_descriptor(sector_descriptor_id, sector_id);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_SECTOR, telegramm_descriptor.data()));
        }

        {
        glm::vec3 position = meti::rand::gen_vec3xy(0, ENTITY::GALAXY::PARSEC/2);
        descriptor::comm::AddingPositional telegramm_descriptor(galaxy_id, sector_id, position);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_SECTOR_TO_GALAXY, telegramm_descriptor.data()));
        }

        __createStarsystems(sector_descriptor_id, sector_id);
    }
}

void TelegramCreator::__createStarsystems(int_t sector_descriptor_id, int_t sector_id) const
{
    descriptor::Sector* sector_descriptor = core::shortcuts::descriptors()->sector(sector_descriptor_id);
    for(const auto& starsystem_descriptor_id: sector_descriptor->starsystems) {
        int_t starsystem_id = shortcuts::entities()->nextId();

        {
        descriptor::comm::Creation telegramm_descriptor(starsystem_descriptor_id, starsystem_id);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_STARSYSTEM, telegramm_descriptor.data()));
        }

        {
        glm::vec3 position = meti::rand::gen_vec3xy(3, 8);
        descriptor::comm::AddingPositional telegramm_descriptor(sector_id, starsystem_id, position);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_STARSYSTEM_TO_SECTOR, telegramm_descriptor.data()));
        }

        __createStarsystemInternalls(starsystem_descriptor_id, starsystem_id);
    }
}

void TelegramCreator::__createStarsystemInternalls(int_t descriptor_starsystem_id, int_t starsystem_id) const
{
    __createStar(starsystem_id);
    __createPlanets(starsystem_id, meti::rand::gen_int(2,5));
    __createShips(starsystem_id, 10);
}


void TelegramCreator::__createStar(int_t starsystem_id) const
{
    int_t star_id = shortcuts::entities()->nextId();
    int_t star_descriptor_id = shortcuts::descriptors()->randStar()->id();

    {
    descriptor::comm::Creation telegramm_descriptor(star_descriptor_id, star_id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_STAR, telegramm_descriptor.data()));
    }

    {
    meti::vec3 position;
    descriptor::comm::AddingPositional telegramm_descriptor(starsystem_id, star_id, position);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_STAR_TO_STARSYSTEM, telegramm_descriptor.data()));
    }
}

void TelegramCreator::__createPlanets(int_t starsystem_id, int planet_per_system) const
{
    for(int i=0; i<planet_per_system; ++i) {
        int_t planet_id = shortcuts::entities()->nextId();
        int_t planet_descriptor_id = shortcuts::descriptors()->randPlanet()->id();

        {
        descriptor::comm::Creation telegramm_descriptor(planet_descriptor_id, planet_id);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_PLANET, telegramm_descriptor.data()));
        }

        {
        meti::vec3 position;
        descriptor::comm::AddingPositional telegramm_descriptor(starsystem_id, planet_id, position);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_PLANET_TO_STARSYSTEM, telegramm_descriptor.data()));
        }
    }
}

void TelegramCreator::__createShips(int_t starsystem_id, int ship_num) const
{
    entity::Type group = entity::Type::NONE;
    entity::Type subgroup = entity::Type::NONE;

    entity::Type npc_group = entity::Type::NONE;
    entity::Type npc_subgroup = entity::Type::NONE;

    race::Type npc_race_id = race::Type::R0;

    for(int i=0; i<ship_num; ++i) {
        // VERY UGLY LOGIC START (TODO)
        if (group == entity::Type::NONE) {
            npc_group = getRandNpcSubTypeId(npc_race_id);
        } else {
            npc_group = group;
        }

        if (subgroup == entity::Type::NONE) {
            npc_subgroup = getRandNpcClass(npc_group);
        } else {
            npc_subgroup = subgroup;
        }
        // VERY UGLY LOGIC END

        int_t ship_descriptor_id = shortcuts::descriptors()->randShip()->id();
        int_t ship_id = shortcuts::entities()->nextId();
        __createShip(ship_descriptor_id, ship_id);

        __equipShip(ship_id);

        int_t npc_descriptor_id = shortcuts::descriptors()->randNpc()->id();
        int_t npc_id = shortcuts::entities()->nextId();
        __createNpc(npc_descriptor_id, npc_id);

        __addNpcToShip(ship_id, npc_id);

        glm::vec3 center = meti::rand::gen_vec3xy(300, 1200);
        __addShipToStarSystem(starsystem_id, ship_id, center);
    }
}

void TelegramCreator::__createShip(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_SHIP, telegramm_descriptor.data()));
}

void TelegramCreator::__createNpc(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_NPC, telegramm_descriptor.data()));
}

void TelegramCreator::__addShipToStarSystem(int_t starsystem_id, int_t ship_id, const glm::vec3& center) const
{
    AddToStarsystemDescriptor telegramm_descriptor(starsystem_id, ship_id, center);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_SHIP_TO_STARSYSTEM, telegramm_descriptor.data()));
}

void TelegramCreator::__addNpcToShip(int_t ship_id, int_t npc_id) const
{
    descriptor::comm::AddingPositional telegramm_descriptor(ship_id, npc_id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_NPC_TO_SHIP, telegramm_descriptor.data()));
}


void TelegramCreator::__createBak(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_BAK, telegramm_descriptor.data()));
}

void TelegramCreator::__createDrive(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_DRIVE, telegramm_descriptor.data()));
}

void TelegramCreator::__createProtector(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_PROTECTOR, telegramm_descriptor.data()));
}

void TelegramCreator::__createScaner(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_SCANER, telegramm_descriptor.data()));
}

void TelegramCreator::__createRadar(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_RADAR, telegramm_descriptor.data()));
}

void TelegramCreator::__createGrapple(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_GRAPPLE, telegramm_descriptor.data()));
}

void TelegramCreator::__createLazer(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_LAZER, telegramm_descriptor.data()));
}

void TelegramCreator::__createRocket(int_t descriptor_id, int_t id) const
{
    descriptor::comm::Creation telegramm_descriptor(descriptor_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_ROCKET, telegramm_descriptor.data()));
}

void TelegramCreator::__mountItem(int_t ship_id, int_t id) const
{
    descriptor::comm::AddingPositional telegramm_descriptor(ship_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::MOUNT_ITEM, telegramm_descriptor.data()));
}

void TelegramCreator::__loadItem(int_t ship_id, int_t id) const
{
    descriptor::comm::AddingPositional telegramm_descriptor(ship_id, id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::LOAD_ITEM, telegramm_descriptor.data()));
}

void TelegramCreator::__equipShip(int_t ship_id) const
{
    {
        int_t descriptor_id = shortcuts::descriptors()->randBak()->id();
        int_t id = shortcuts::entities()->nextId();

        __createBak(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randDrive()->id();
        int_t id = shortcuts::entities()->nextId();

        __createDrive(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randProtector()->id();
        int_t id = shortcuts::entities()->nextId();

        __createProtector(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randScaner()->id();
        int_t id = shortcuts::entities()->nextId();

        __createScaner(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRadar()->id();
        int_t id = shortcuts::entities()->nextId();

        __createRadar(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randGrapple()->id();
        int_t id = shortcuts::entities()->nextId();

        __createGrapple(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randLazer()->id();
        int_t id = shortcuts::entities()->nextId();

        __createLazer(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRocket()->id();
        int_t id = shortcuts::entities()->nextId();

        __createRocket(descriptor_id, id);
        __mountItem(ship_id, id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRocket()->id();
        int_t id = shortcuts::entities()->nextId();

        __createRocket(descriptor_id, id);
        __loadItem(ship_id, id);
    }
}

void TelegramCreator::createGalaxy(descriptor::Galaxy* galaxy_descriptor)
{
    int_t galaxy_id = shortcuts::entities()->nextId();

    descriptor::comm::Creation telegramm_descriptor(galaxy_descriptor->id(), galaxy_id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_GALAXY, telegramm_descriptor.data()));

    __createSectors(galaxy_descriptor, galaxy_id);
}

std::vector<glm::vec3>
TelegramCreator::__genImpulses(int num) const
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

void TelegramCreator::death_spaceobject(control::SpaceObject* object)
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

void TelegramCreator::death(control::Asteroid* asteroid)
{
    // create minerals
    int containers_num = meti::rand::gen_int(1,3);
    std::vector<glm::vec3> impulses = __genImpulses(containers_num);
    for (int i=0; i<containers_num; ++i) {
        int_t item_id = shortcuts::entities()->nextId();
        int amount = meti::rand::gen_int(3, 100);
        {
        int_t descriptor_id = shortcuts::descriptors()->randGoods()->id();
        descriptor::comm::CreateGoodsPack telegramm_descriptor(descriptor_id, item_id, amount);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_GOODS, telegramm_descriptor.data()));
        }
        int_t container_id = shortcuts::entities()->nextId();
        {
        int_t descriptor_id = shortcuts::descriptors()->randContainer()->id();
        descriptor::comm::CreateContainer telegramm_descriptor(descriptor_id, container_id, item_id);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_CONTAINER, telegramm_descriptor.data()));
        }
        {
        AddToStarsystemDescriptor telegramm_descriptor(asteroid->starsystem()->id(), container_id, asteroid->position(), impulses[i], asteroid->direction());
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_CONTAINER_TO_STARSYSTEM, telegramm_descriptor.data()));
        }
    }

    __removeSpaceObjectFromStarSystem(asteroid);
    __addSpaceObjectToGarbage(asteroid);

    __explosionEffect(asteroid->collisionRadius(), asteroid->position());
}

void TelegramCreator::__death(control::Vehicle* vehicle)
{
    // create containers
    int containers_num = meti::rand::gen_int(1,3);
    const ceti::pack<int_t> items = vehicle->model()->items().random(containers_num);
    containers_num = int(items.size());

    std::vector<glm::vec3> impulses = __genImpulses(containers_num);
    for (int i=0; i<containers_num; ++i) {
        int_t container_id = shortcuts::entities()->nextId();
        int_t descriptor_id = shortcuts::descriptors()->randContainer()->id();
        int_t item_id = items[i];
        {
        descriptor::comm::CreateContainer telegramm_descriptor(descriptor_id, container_id, item_id);
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_CONTAINER, telegramm_descriptor.data()));
        }
        {
        AddToStarsystemDescriptor telegramm_descriptor(vehicle->starsystem()->id(), container_id, vehicle->position(), impulses[i], vehicle->direction()/* todo: add direction less way*/ );
        m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_CONTAINER_TO_STARSYSTEM, telegramm_descriptor.data()));
        }
    }

    __removeSpaceObjectFromStarSystem(vehicle);
    __addSpaceObjectToGarbage(vehicle);

    __explosionEffect(vehicle->collisionRadius(), vehicle->position());
}

void TelegramCreator::death(control::Bullet* bullet)
{
    __removeSpaceObjectFromStarSystem(bullet);
    __addSpaceObjectToGarbage(bullet);

    __explosionEffect(2*bullet->collisionRadius(), bullet->position());
}

void TelegramCreator::__death(control::Container* container)
{
    __removeSpaceObjectFromStarSystem(container);
    __addSpaceObjectToGarbage(container);

    __explosionEffect(2*container->collisionRadius(), container->position());
}


void TelegramCreator::genBullets_DEBUG(control::StarSystem* starsystem, int num) const
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
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_BULLET, telegramm_descriptor.data()));
}

void TelegramCreator::__removeSpaceObjectFromStarSystem(control::SpaceObject* object)
{
    descriptor::comm::StarSystemTransition descriptor(object->id(), object->starsystem()->id());
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM, descriptor.data()));
}

void TelegramCreator::__addSpaceObjectToGarbage(control::SpaceObject* object)
{
    descriptor::comm::Object descriptor(object->id());
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE, descriptor.data()));
}

void TelegramCreator::__explosionEffect(float radius, const glm::vec3& position)
{
    descriptor::comm::effect::Explosion telegramm_descriptor(radius, position);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_EXPLOSION_EFFECT, telegramm_descriptor.data()));
}

void TelegramCreator::hit(control::SpaceObject* object, int damage)
{
    descriptor::comm::Hit descriptor(object->id(), object->id(), damage);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::HIT, descriptor.data()));
}

void TelegramCreator::createPlayer(int_t player_id, int_t npc_id)
{
    descriptor::comm::CreatePlayer descriptor(player_id, npc_id);
    m_telegrammHub.add(core::comm::Telegram(telegram::Type::CREATE_PLAYER, descriptor.data()));
}

} // namespace core
