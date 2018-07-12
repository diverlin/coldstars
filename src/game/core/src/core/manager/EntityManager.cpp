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

#include "EntityManager.hpp"
#include <ceti/Logger.hpp>
#include <ceti/IdGenerator.hpp>

#include <core/spaceobject/ALL>

#include <core/pilot/Npc.hpp>

#include "../world/galaxy.hpp"
#include <core/world/starsystem.hpp>

#include <builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <builder/item/modules/ALL>
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
#include <builder/item/artefacts/ALL>
#endif // USE_ARTEFACTS
#include <builder/item/other/ALL>

#include <core/builder/spaceobject/ALL>

#include <core/item/other/ALL>

#include "../builder/world/GalaxyBuilder.hpp"
#include "../builder/world/StarSystemBuilder.hpp"

#include <core/builder/pilot/NpcBuilder.hpp>

#include "../builder/dock/NatureLandBuilder.hpp"
#include "../builder/dock/KosmoportBuilder.hpp"
#include "../builder/dock/AngarBuilder.hpp"
#include "../builder/dock/StoreBuilder.hpp"
#include "../builder/dock/ShopBuilder.hpp"
#include "../builder/dock/GovermentBuilder.hpp"

#include "../dock/Angar.hpp"
#include "../dock/Store.hpp"
#include "../dock/Shop.hpp"
#include "../dock/Goverment.hpp"

#include <core/item/equipment/ALL>

#ifdef USE_MODULES
#include <core/item/modules/ALL>
#endif // USE_MODULES
#include <core/item/other/Bomb.hpp>

#ifdef USE_ARTEFACTS
#include <core/item/artefacts/ALL>
#endif // USE_ARTEFACTS
#include "../dock/Goverment.hpp"
#include "../dock/NatureLand.hpp"
#include "../dock/Kosmoport.hpp"

#include <core/slot/VehicleSlot.hpp>
#include <common/Global.hpp>
#include <common/TurnTimer.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/model/spaceobject/ALL>

#include <core/model/world/starsystem.hpp>

#include <core/model/item/equipment/ALL>

#include <core/item/equipment/Weapon.hpp>

namespace core {
namespace manager {

IdGenerator Entities::m_idGenerator;

//void
//Entities::clear()
//{
//    for (auto it: m_entities) {
//        delete it.second;
//    }
//    m_entities.clear();
//}

void Entities::add(control::Base* ob)
{
    assert(ob);
    if (ob->id() == NONE) {
        ob->setId(m_idGenerator.nextId());
    }

    if (m_entities.count(ob->id()) == 1) {
        ceti::abort("attempt to registry id =" + std::to_string(ob->id()) + " which already exists");
    }

    m_entities.insert(std::make_pair(ob->id(), ob));
}

control::Base*
Entities::base(int_t id) const
{
    LOG(std::string("EntityManager::entity requested_id=") + std::to_string(id));
    std::map<int_t, control::Base*>::const_iterator it = m_entities.find(id);
    assert(it->second);
    return it->second;
}

control::Npc*
Entities::npc(int_t id) const
{
    control::Npc* control = static_cast<control::Npc*>(base(id));
    assert(control);
    return control;
}

control::Galaxy*
Entities::galaxy(int_t id) const {
    control::Galaxy* control = static_cast<control::Galaxy*>(base(id));
    assert(control);
    return control;
}

control::StarSystem*
Entities::starsystem(int_t id) const {
    control::StarSystem* control = static_cast<control::StarSystem*>(base(id));
    assert(control);
    return control;
}

control::HyperSpace*
Entities::hyperspace() const {
    assert(m_hyperspace);
    return m_hyperspace;
}

control::Star*
Entities::star(int_t id) const {
    control::Star* control = static_cast<control::Star*>(base(id));
    assert(control);
    return control;
}

control::Planet*
Entities::planet(int_t id) const {
    control::Planet* control = static_cast<control::Planet*>(base(id));
    assert(control);
    return control;
}

control::Asteroid*
Entities::asteroid(int_t id) const {
    control::Asteroid* control = static_cast<control::Asteroid*>(base(id));
    assert(control);
    return control;
}
control::WormHole*
Entities::wormhole(int_t id) const {
    control::WormHole* control = static_cast<control::WormHole*>(base(id));
    assert(control);
    return control;
}

control::Vehicle*
Entities::vehicle(int_t id) const {
    control::Vehicle* control = static_cast<control::Vehicle*>(base(id));
    assert(control);
    return control;
}

control::SpaceStation*
Entities::spacestation(int_t id) const {
    control::SpaceStation* control = static_cast<control::SpaceStation*>(base(id));
    assert(control);
    return control;
}

control::Ship*
Entities::ship(int_t id) const {
    control::Ship* control = static_cast<control::Ship*>(base(id));
    assert(control);
    return control;
}

control::Satellite*
Entities::satellite(int_t id) const {
    control::Satellite* control = static_cast<control::Satellite*>(base(id));
    assert(control);
    return control;
}

control::Container*
Entities::container(int_t id) const {
    control::Container* control = static_cast<control::Container*>(base(id));
    assert(control);
    return control;
}

control::Bullet*
Entities::bullet(int_t id) const {
    control::Bullet* control = static_cast<control::Bullet*>(base(id));
    assert(control);
    return control;
}

control::SpaceObject*
Entities::spaceObject(int_t id) const {
    control::SpaceObject* control = static_cast<control::SpaceObject*>(base(id));
    assert(control);
    return control;
}

control::Land*
Entities::land(int_t id) const {
    control::Land* control = static_cast<control::Land*>(base(id));
    assert(control);
    return control;
}

control::Item*
Entities::item(int_t id) const {
    control::Item* control = static_cast<control::Item*>(base(id));
    assert(control);
    return control;
}

control::Weapon*
Entities::weapon(int_t id) const {
    control::Weapon* control = static_cast<control::Weapon*>(base(id));
    assert(control);
    return control;
}

control::Scaner*
Entities::scaner(int_t id) const
{
    control::Scaner* control = static_cast<control::Scaner*>(base(id));
    assert(control);
    return control;
}

control::Drive*
Entities::drive(int_t id) const
{
    control::Drive* control = static_cast<control::Drive*>(base(id));
    assert(control);
    return control;
}

control::Bak*
Entities::bak(int_t id) const
{
    control::Bak* control = static_cast<control::Bak*>(base(id));
    assert(control);
    return control;
}

control::Droid*
Entities::droid(int_t id) const
{
    control::Droid* control = static_cast<control::Droid*>(base(id));
    assert(control);
    return control;
}

control::Grapple*
Entities::grapple(int_t id) const
{
    control::Grapple* control = static_cast<control::Grapple*>(base(id));
    assert(control);
    return control;
}

control::Lazer*
Entities::lazer(int_t id) const
{
    control::Lazer* control = static_cast<control::Lazer*>(base(id));
    assert(control);
    return control;
}

control::Protector*
Entities::protector(int_t id) const
{
    control::Protector* control = static_cast<control::Protector*>(base(id));
    assert(control);
    return control;
}

control::Radar*
Entities::radar(int_t id) const
{
    control::Radar* control = static_cast<control::Radar*>(base(id));
    assert(control);
    return control;
}

control::Rocket*
Entities::rocket(int_t id) const
{
    control::Rocket* control = static_cast<control::Rocket*>(base(id));
    assert(control);
    return control;
}


Player* Entities::player() const
{
    assert(false);
//    for (std::map<int_t, core::Base*>::const_iterator it=m_entities_map.begin(); it!=m_entities_map.end(); ++it) {
//        if (it->second->type() == entity::Type::PLAYER) {
//            return (client::Player*)it->second;
//        }
//    }
    return nullptr;
}

void Entities::remove(control::Base* ob)
{
    std::map<int_t, control::Base*>::iterator it = m_entities.find(ob->id());
    if (it != m_entities.end()) {
        m_entities.erase(it);
    } else {
        ceti::abort("attempt to remove not existed id = " + std::to_string(ob->id()));
    }
}

int_t Entities::firstIdByType(entity::Type type) const {
    int_t result = -1;
    for(std::map<int_t, control::Base*>::const_iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
        if (it->second->type() == type) {
            return it->second->id();
        }
    }
    assert(false);
    return result;
}

//void EntityManager::saveEvent(const std::string& filename)
//{
////    boost::property_tree::ptree save_ptree;

//    assert(false);
////    for (std::map<int_t, core::Base*>::iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
////        //LOG("saving " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
////        iterator->second->Save(save_ptree);
////    }
    
//    //write_info(filename, save_ptree);
////    write_info("save/save_last.info", save_ptree);
//}

//void EntityManager::loadEvent(const std::string&)
//{
//    assert(false);

//    LOG("RESOLVING DEPENDENCY START");
////    for (std::map<int_t, core::Base*>::const_iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
////        LOG("Load() in " + iterator->second->dataTypeStr());
////        iterator->second->Resolve();
////    }

//    LOG("RESOLVING DEPENDENCY FINISHED");
//}


//bool EntityManager::updateSaveRequest()
//{
//    if (m_save_request == true) {
//        saveEvent("save"+std::to_string(core::global::get().turnTimer().getStopTurnTimer())+".info");
//        m_save_request = false;
        
//        return true;
//    }
    
//    return false;
//}

//bool EntityManager::updateLoadRequest()
//{
//    if (m_load_request == true)
//    {
//        clear();
//        loadEvent("save_last.info");

//        m_load_request = false;
        
//        return true;
//    }
    
//    return false;
//}

} // namespace manager
} // namespace core
