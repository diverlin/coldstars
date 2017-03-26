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

//#include <boost/property_tree/ptree.hpp>
//#include <boost/foreach.hpp>
//#include <boost/property_tree/info_parser.hpp>

#include "EntityManager.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/IdGenerator.hpp>

#include <core/spaceobject/ALL>

//#include "../pilots/Player.hpp"
#include <core/pilot/Npc.hpp>

#include "../world/galaxy.hpp"
#include "../world/starsystem.hpp"

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

#include <core/builder/slot/ItemSlotBuilder.hpp>
#include <core/builder/slot/VehicleSlotBuilder.hpp>

#include "../builder/world/GalaxyBuilder.hpp"
#include "../builder/world/StarSystemBuilder.hpp"

//#include "../builder/pilot/PlayerBuilder.hpp"
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
//#include <ceti/StringUtils.hpp>
#include <common/Global.hpp>
#include <common/TurnTimer.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/model/spaceobject/ALL>

#include <core/model/world/starsystem.hpp>

#include <core/model/item/equipment/ALL>

IdGenerator EntityManager::m_idGenerator;

EntityManager&
EntityManager::get()
{
    static EntityManager instance;
    return instance;
}

int_t
EntityManager::genId() {
    return m_idGenerator.nextId();
}

void
EntityManager::clear()
{
    assert(false);
//    for (std::map<int_t, core::Base*>::iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++)
//    {
//        //LOG("________EntityManager::Clear, delete " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
//        delete iterator->second;
//    }

//    m_entities_map.clear();
}

//void EntityManager::reg(core::Base* entity)
//{
//    assert(entity);
//    if (entity->id() == NONE) {
//        //assert(false);
//        // TODO fixme
//        entity->setId(core::global::get().idGenerator().nextId());
//    }
//    LOG("EntityManager::reg " + entity->dataTypeStr() << std::endl);

//    if (m_entities_map.find(entity->id()) != m_entities_map.end()) {
//        throw std::runtime_error("ERROR: attempt to create two entity with simmilar id =" + std::to_string(entity->id()) + " which already exists, type = " + entity->dataTypeStr());
//    }

//    m_entities_map.insert(std::make_pair(entity->id(), entity));
//}

void EntityManager::reg(model::Base* model)
{
    assert(model);
    if (model->id() == NONE) {
        model->setId(m_idGenerator.nextId());
    }
    //LOG("EntityManager::reg " + entity->dataTypeStr() << std::endl);

    if (m_models.find(model->id()) != m_models.end()) {
        throw std::runtime_error("ERROR: attempt to create two entity with simmilar id =" + std::to_string(model->id()) + " which already exists, descriptor = " + std::to_string(model->descriptor()));
    }

    m_models.insert(std::make_pair(model->id(), model));
}

//core::Base* EntityManager::getEntity(int_t id) const
//{
//    LOG(std::string("EntityManager::entity requested_id=") << std::to_string(id));
//    std::map<int_t, core::Base*>::const_iterator slice = m_entities_map.find(id);
//    assert(slice->second);
//    LOG(std::string("type=") << slice->second->dataTypeStr() << std::endl);
//    return slice->second;
//}

model::Base*
EntityManager::get(int_t id) const
{
    LOG(std::string("EntityManager::entity requested_id=") << std::to_string(id));
    std::map<int_t, model::Base*>::const_iterator it = m_models.find(id);
    assert(it->second);
    // TODO
    //LOG(std::string("type=") << slice->second->dataTypeStr() << std::endl);
    return it->second;
}

model::Item*
EntityManager::getItemBase(int_t id) const
{
    LOG(std::string("EntityManager::entity requested_id=") << std::to_string(id));
    std::map<int_t, model::Base*>::const_iterator it = m_models.find(id);
    assert(it->second);
    model::Item* item = static_cast<model::Item*>(it->second);
    assert(item);
    // TODO
    //LOG(std::string("type=") << slice->second->dataTypeStr() << std::endl);
    return item;
}

model::StarSystem*
EntityManager::starsystem(int_t id) const {
    model::StarSystem* model = static_cast<model::StarSystem*>(get(id));
    assert(model);
    return model;
}

model::Star*
EntityManager::star(int_t id) const {
    model::Star* model = static_cast<model::Star*>(get(id));
    assert(model);
    return model;
}

model::Planet*
EntityManager::planet(int_t id) const {
    model::Planet* model = static_cast<model::Planet*>(get(id));
    assert(model);
    return model;
}

model::Asteroid*
EntityManager::asteroid(int_t id) const {
    model::Asteroid* model = static_cast<model::Asteroid*>(get(id));
    assert(model);
    return model;
}

model::SpaceStation*
EntityManager::spacestation(int_t id) const {
    model::SpaceStation* model = static_cast<model::SpaceStation*>(get(id));
    assert(model);
    return model;
}

model::Ship*
EntityManager::ship(int_t id) const {
    model::Ship* model = static_cast<model::Ship*>(get(id));
    assert(model);
    return model;
}

model::Satellite*
EntityManager::satellite(int_t id) const {
    model::Satellite* model = static_cast<model::Satellite*>(get(id));
    assert(model);
    return model;
}

model::Container*
EntityManager::container(int_t id) const {
    model::Container* model = static_cast<model::Container*>(get(id));
    assert(model);
    return model;
}

model::SpaceObject*
EntityManager::spaceObject(int_t id) const {
    model::SpaceObject* model = static_cast<model::SpaceObject*>(get(id));
    assert(model);
    return model;
}

model::item::Scaner*
EntityManager::scaner(int_t id) const
{
    model::item::Scaner* model = static_cast<model::item::Scaner*>(get(id));
    assert(model);
    return model;
}

model::item::Drive*
EntityManager::drive(int_t id) const
{
    model::item::Drive* model = static_cast<model::item::Drive*>(get(id));
    assert(model);
    return model;
}

model::item::Bak*
EntityManager::bak(int_t id) const
{
    model::item::Bak* model = static_cast<model::item::Bak*>(get(id));
    assert(model);
    return model;
}

model::item::Droid*
EntityManager::droid(int_t id) const
{
    model::item::Droid* model = static_cast<model::item::Droid*>(get(id));
    assert(model);
    return model;
}

model::item::Grapple*
EntityManager::grapple(int_t id) const
{
    model::item::Grapple* model = static_cast<model::item::Grapple*>(get(id));
    assert(model);
    return model;
}

model::item::Lazer*
EntityManager::lazer(int_t id) const
{
    model::item::Lazer* model = static_cast<model::item::Lazer*>(get(id));
    assert(model);
    return model;
}

model::item::Protector*
EntityManager::protector(int_t id) const
{
    model::item::Protector* model = static_cast<model::item::Protector*>(get(id));
    assert(model);
    return model;
}

model::item::Radar*
EntityManager::radar(int_t id) const
{
    model::item::Radar* model = static_cast<model::item::Radar*>(get(id));
    assert(model);
    return model;
}

model::item::Rocket*
EntityManager::rocket(int_t id) const
{
    model::item::Rocket* model = static_cast<model::item::Rocket*>(get(id));
    assert(model);
    return model;
}


Player* EntityManager::player() const
{
    assert(false);
//    for (std::map<int_t, core::Base*>::const_iterator it=m_entities_map.begin(); it!=m_entities_map.end(); ++it) {
//        if (it->second->type() == entity::Type::PLAYER) {
//            return (Player*)it->second;
//        }
//    }
    return nullptr;
}

//void EntityManager::removeEntity(core::Base* entity)
//{
//    //LOG("________EntityManager::RemoveEntity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));

//    if (m_entities_map.count(entity->id()) == 1) {
//        m_entities_map.erase(m_entities_map.find(entity->id()));
//    } else {
//        //LOG("fix the BUG ---EntityManager::RemoveEntity fails " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
//    }
//}


void EntityManager::saveEvent(const std::string& filename)
{
//    boost::property_tree::ptree save_ptree;

    assert(false);
//    for (std::map<int_t, core::Base*>::iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
//        //LOG("saving " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
//        iterator->second->Save(save_ptree);
//    }
    
    //write_info(filename, save_ptree);
//    write_info("save/save_last.info", save_ptree);
}

void EntityManager::loadEvent(const std::string&)
{
    assert(false);

    LOG("RESOLVING DEPENDENCY START");
//    for (std::map<int_t, core::Base*>::const_iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
//        LOG("Load() in " + iterator->second->dataTypeStr());
//        iterator->second->Resolve();
//    }

    LOG("RESOLVING DEPENDENCY FINISHED");
}


bool EntityManager::updateSaveRequest()
{        
    if (m_save_request == true) {
        saveEvent("save"+std::to_string(core::global::get().turnTimer().getStopTurnTimer())+".info");
        m_save_request = false;
        
        return true;
    }
    
    return false;
}

bool EntityManager::updateLoadRequest()
{
    if (m_load_request == true)
    {
        clear();
        loadEvent("save_last.info");

        m_load_request = false;
        
        return true;
    }
    
    return false;
}


//void EntityManager::addToGarbage(core::Base* entity)
//{
//    //LOG("EntetiesManager::AddToGarbage entity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
//    for (unsigned int i=0; i<m_entitiesGarbage.size(); i++) {
//        if (m_entitiesGarbage[i]->id() == entity->id()) {
//            //LOG("EntetiesManager::AddToGarbage dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
//            exit(1);
//        }
//    }

//    m_entitiesGarbage.push_back(entity);
//    entity->putChildrenToGarbage();
//}

void EntityManager::addToGarbage(model::Base* model)
{
    //LOG("EntetiesManager::AddToGarbage entity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    assert(false);
//    for (unsigned int i=0; i<m_entitiesGarbage.size(); i++) {
//        if (m_entitiesGarbage[i]->id() == model->id()) {
//            //LOG("EntetiesManager::AddToGarbage dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
//            exit(1);
//        }
//    }

    m_garbage.push_back(model);
    //model->putChildrenToGarbage();
}

void EntityManager::clearGarbage()
{
    assert(false);
//    for(unsigned int i=0; i<m_entitiesGarbage.size(); i++)
//    {
//        removeEntity(m_entitiesGarbage[i]);
//#if CREATEDESTROY_LOG_ENABLED == 1
//        LOG("________EntityManager::ClearGarbage delete entity " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
//#endif
//       core::global::get().idGenerator().addFreeId(m_entitiesGarbage[i]->id());
//        delete m_entitiesGarbage[i];
//    }
//    m_entitiesGarbage.clear();
}


