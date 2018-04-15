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

#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/descriptor/spaceobject/ALL>
#include <core/descriptor/pilot/Npc.hpp>
#include <core/communication/descriptor/ALL>

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
      m_telegramHub(core::global::get().telegramHub())
{

}

int_t TelegramCreator::__createPureGalaxy(int_t galaxy_descriptor_id) const
{
    int_t galaxy_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(galaxy_descriptor_id, galaxy_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_GALAXY, telegram_descriptor.data()));
    return galaxy_id;
}

int_t TelegramCreator::__createPureSector(int_t sector_descriptor_id) const
{
    int_t sector_id = shortcuts::entities()->nextId();

    core::comm::CreateComDescr telegram_descriptor(sector_descriptor_id, sector_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_SECTOR, telegram_descriptor.data()));

    return sector_id;
}

int_t TelegramCreator::__createPureStarsystem(int_t starsystem_descriptor_id) const
{
    int_t starsystem_id = shortcuts::entities()->nextId();

    core::comm::CreateComDescr telegram_descriptor(starsystem_descriptor_id, starsystem_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_STARSYSTEM, telegram_descriptor.data()));

    return starsystem_id;
}

int_t TelegramCreator::__createPureStar(int_t star_descriptor_id) const
{
    int_t star_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(star_descriptor_id, star_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_STAR, telegram_descriptor.data()));
    return star_id;
}

int_t TelegramCreator::__createPurePlanet(int_t planet_descriptor_id) const
{
    int_t planet_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(planet_descriptor_id, planet_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_PLANET, telegram_descriptor.data()));
    return planet_id;
}

int_t TelegramCreator::__createPureShip(int_t descriptor_id) const
{
    int_t ship_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, ship_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_SHIP, telegram_descriptor.data()));
    return ship_id;
}

int_t TelegramCreator::__createPureNpc(int_t descriptor_id) const
{
    int_t npc_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, npc_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_NPC, telegram_descriptor.data()));
    return npc_id;
}

void TelegramCreator::__addSectorToGalaxy(int_t sector_id, int_t galaxy_id) const
{
    glm::vec3 position = meti::rand::gen_vec3xy(0, ENTITY::GALAXY::PARSEC/2);
    core::comm::AddPositionalComDescr telegram_descriptor(sector_id, galaxy_id, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_SECTOR_TO_GALAXY, telegram_descriptor.data()));
}

void TelegramCreator::__addStarsystemToSector(int_t starsystem_id, int_t sector_id) const
{
    glm::vec3 position = meti::rand::gen_vec3xy(3, 8);
    core::comm::AddPositionalComDescr telegram_descriptor(starsystem_id, sector_id, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_STARSYSTEM_TO_SECTOR, telegram_descriptor.data()));
}

void TelegramCreator::__addStarToStarsystem(int_t star_id, int_t starsystem_id) const
{
    meti::vec3 position;
    core::comm::AddPositionalComDescr telegram_descriptor(star_id, starsystem_id, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_STAR_TO_STARSYSTEM, telegram_descriptor.data()));
}

void TelegramCreator::__addPlanetToStarsystem(int_t planet_id, int_t starsystem_id) const
{
    meti::vec3 position;
    core::comm::AddPositionalComDescr telegram_descriptor(planet_id, starsystem_id, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_PLANET_TO_STARSYSTEM, telegram_descriptor.data()));
}

void TelegramCreator::__addShipToStarSystem(int_t ship_id, int_t starsystem_id, const glm::vec3& center) const
{
    core::comm::AddToStarsystemComDescr telegram_descriptor(ship_id, starsystem_id, center);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_SHIP_TO_STARSYSTEM, telegram_descriptor.data()));
}

void TelegramCreator::__addNpcToShip(int_t npc_id, int_t ship_id) const
{
    core::comm::ObjectSubjectComDescr telegram_descriptor(npc_id, ship_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_NPC_TO_SHIP, telegram_descriptor.data()));
}

int_t TelegramCreator::__createPureBak(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_BAK, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureDrive(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_DRIVE, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureProtector(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_PROTECTOR, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureScaner(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_SCANER, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureRadar(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_RADAR, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureGrapple(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_GRAPPLE, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureLazer(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_LAZER, telegram_descriptor.data()));
    return item_id;
}

int_t TelegramCreator::__createPureRocket(int_t descriptor_id) const
{
    int_t item_id = shortcuts::entities()->nextId();
    core::comm::CreateComDescr telegram_descriptor(descriptor_id, item_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_ROCKET, telegram_descriptor.data()));
    return item_id;
}

void TelegramCreator::__mountItem(int_t ship_id, int_t item_id) const
{
    core::comm::ObjectSubjectComDescr telegram_descriptor(item_id, ship_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::MOUNT_ITEM, telegram_descriptor.data()));
}

void TelegramCreator::__loadItem(int_t ship_id, int_t item_id) const
{
    core::comm::ObjectSubjectComDescr telegram_descriptor(item_id, ship_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::LOAD_ITEM, telegram_descriptor.data()));
}

void TelegramCreator::__equipShip(int_t ship_id) const
{
    {
        int_t descriptor_id = shortcuts::descriptors()->randBak()->id();
        int_t item_id = __createPureBak(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randDrive()->id();
        int_t item_id = __createPureDrive(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randProtector()->id();
        int_t item_id = __createPureProtector(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randScaner()->id();
        int_t item_id = __createPureScaner(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRadar()->id();
        int_t item_id = __createPureRadar(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randGrapple()->id();
        int_t item_id = __createPureGrapple(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randLazer()->id();
        int_t item_id = __createPureLazer(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRocket()->id();
        int_t item_id = __createPureRocket(descriptor_id);
        __mountItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRocket()->id();
        int_t item_id = __createPureRocket(descriptor_id);
        __loadItem(ship_id, item_id);
    }

    {
        int_t descriptor_id = shortcuts::descriptors()->randRocket()->id();
        int_t item_id = __createPureLazer(descriptor_id);
        __loadItem(ship_id, item_id);
    }
}

void TelegramCreator::createDummyGalaxy(int ships_num, int planets_num) const
{
    // create galaxy
    int_t galaxy_descriptor_id = shortcuts::descriptors()->randGalaxy()->id();
    int_t galaxy_id = __createPureGalaxy(galaxy_descriptor_id);

    // create sector
    int_t sector_descriptor_id = shortcuts::descriptors()->randSector()->id();
    int_t sector_id = __createPureSector(sector_descriptor_id);
    __addSectorToGalaxy(sector_id, galaxy_id);

    // create starsystem
    int_t starsystem_descriptor_id = shortcuts::descriptors()->randStarSystem()->id();
    int_t starsystem_id = __createPureStarsystem(starsystem_descriptor_id);
    __addStarsystemToSector(starsystem_id, sector_id);

    // create star
    int_t star_descriptor_id = shortcuts::descriptors()->randStar()->id();
    int_t star_id = __createPureStar(star_descriptor_id);
    __addStarToStarsystem(star_id, starsystem_id);

    // create planet
    __createPlanets(starsystem_id, planets_num);

    // create ships
    __createShips(starsystem_id, ships_num);
}

void TelegramCreator::createGalaxy(core::GalaxyDescr* galaxy_descriptor) const
{
    // create galaxy
    int_t galaxy_id = __createPureGalaxy(galaxy_descriptor->id());

    // create sectors
    for(int_t sector_descriptor_id: galaxy_descriptor->sectors) {
        int_t sector_id = __createPureSector(sector_descriptor_id);
        __addSectorToGalaxy(sector_id, galaxy_id);

        // create starsystems
        core::SectorDescr* sector_descriptor = core::shortcuts::descriptors()->sector(sector_descriptor_id);
        for(const auto& starsystem_descriptor_id: sector_descriptor->starsystems) {
            int_t starsystem_id = __createPureStarsystem(starsystem_descriptor_id);
            __addStarsystemToSector(starsystem_id, sector_id);

            // create star
            int_t star_descriptor_id = shortcuts::descriptors()->randStar()->id();
            int_t star_id = __createPureStar(star_descriptor_id);
            __addStarToStarsystem(star_id, starsystem_id);

            // create planets
            int planets_num = meti::rand::gen_int(2,5);
            __createPlanets(starsystem_id, planets_num);

            // create ships
            int ships_num = 10;
            __createShips(starsystem_id, ships_num);
        }
    }
}

void TelegramCreator::__createPlanets(int_t starsystem_id, int planets_num) const
{
    for(int i=0; i<planets_num; ++i) {
        int_t planet_descriptor_id = shortcuts::descriptors()->randPlanet()->id();
        int_t planet_id = __createPurePlanet(planet_descriptor_id);
        __addPlanetToStarsystem(planet_id, starsystem_id);
    }
}

void TelegramCreator::__createShips(int_t starsystem_id, int ships_num) const
{
    for(int i=0; i<ships_num; ++i) {
        // create ship
        int_t ship_descriptor_id = shortcuts::descriptors()->randShip()->id();
        int_t ship_id = __createPureShip(ship_descriptor_id);

        // create npc
        int_t npc_descriptor_id = shortcuts::descriptors()->randNpc()->id();
        int_t npc_id = __createPureNpc(npc_descriptor_id);
        __addNpcToShip(npc_id, ship_id);

        __equipShip(ship_id);

        glm::vec3 ship_pos = meti::rand::gen_vec3xy(300, 1200);
        __addShipToStarSystem(ship_id, starsystem_id, ship_pos);
    }
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

void TelegramCreator::death_spaceobject(core::control::SpaceObject* object)
{
    switch(object->type()) {
    case entity::Type::ASTEROID: death(static_cast<core::control::Asteroid*>(object)); break;
    case entity::Type::CONTAINER: __death(static_cast<core::control::Container*>(object)); break;
    case entity::Type::BULLET: death(static_cast<core::control::Bullet*>(object)); break;
    case entity::Type::SHIP:
    case entity::Type::SPACESTATION:
    case entity::Type::SATELLITE: __death(static_cast<core::control::Vehicle*>(object)); break;
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
        core::comm::CreateGoodsPackComDescr telegram_descriptor(descriptor_id, item_id, amount);
        m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_GOODS, telegram_descriptor.data()));
        }
        int_t container_id = shortcuts::entities()->nextId();
        {
        int_t descriptor_id = shortcuts::descriptors()->randContainer()->id();
        core::comm::CreateContainerComDescr telegram_descriptor(descriptor_id, container_id, item_id);
        m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_CONTAINER, telegram_descriptor.data()));
        }
        {
        core::comm::AddToStarsystemComDescr telegram_descriptor(container_id, asteroid->starsystem()->id(), asteroid->position(), impulses[i], asteroid->direction());
        m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_CONTAINER_TO_STARSYSTEM, telegram_descriptor.data()));
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
        core::comm::CreateContainerComDescr telegram_descriptor(descriptor_id, container_id, item_id);
        m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_CONTAINER, telegram_descriptor.data()));
        }
        {
        core::comm::AddToStarsystemComDescr telegram_descriptor(container_id, vehicle->starsystem()->id(), vehicle->position(), impulses[i], vehicle->direction()/* todo: add direction less way*/ );
        m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_CONTAINER_TO_STARSYSTEM, telegram_descriptor.data()));
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
    return;

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

    std::vector<control::Weapon*> rockets = vehicle->weapons().rockets();
    if (rockets.empty()) { //ugly workaround
        return;
    }
    control::Weapon* rocket = meti::rand::get_pointer(rockets);
    if (!rocket) {
        return;
    }

    int_t item_id = rocket->id();

    core::comm::CreateBulletComDescr telegram_descriptor(owner_id, item_id, target_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_BULLET, telegram_descriptor.data()));
}

void TelegramCreator::__removeSpaceObjectFromStarSystem(control::SpaceObject* object)
{
    comm::ObjectSubjectComDescr descriptor(object->id(), object->starsystem()->id());
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM, descriptor.data()));
}

void TelegramCreator::__addSpaceObjectToGarbage(control::SpaceObject* object)
{
    comm::ObjectDescr descriptor(object->id());
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE, descriptor.data()));
}

void TelegramCreator::__explosionEffect(float radius, const glm::vec3& position)
{
    core::ExplosionEffectComDescr telegram_descriptor(radius, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_EXPLOSION_EFFECT, telegram_descriptor.data()));
}

void TelegramCreator::hit(control::SpaceObject* object, int damage)
{
    comm::HitComDescr descriptor(object->id(), object->id(), damage);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::HIT, descriptor.data()));
}

void TelegramCreator::createPlayer(int_t player_id, int_t npc_id)
{
    comm::CreatePlayerComDescr descriptor(player_id, npc_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::CREATE_PLAYER, descriptor.data()));
}

void TelegramCreator::moveVehicle(int_t vehicle_id, const glm::vec3& position) const
{
    comm::MoveVehicleComDescr descriptor(vehicle_id, position);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::MOVE_VEHICLE, descriptor.data()));
}

void TelegramCreator::endTurn() const
{
    comm::ObjectDescr descriptor(-1);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::END_TURN, descriptor.data()));
}


void TelegramCreator::targetingSpaceObject(int_t vehicle_id, int_t target_id) const
{
    comm::ObjectSubjectComDescr descriptor(vehicle_id, target_id);
    m_telegramHub.add(core::comm::ServerTelegram(telegram::Type::VEHICLE_TARGET_SPACEOBJECT, descriptor.data()));
}

} // namespace core
