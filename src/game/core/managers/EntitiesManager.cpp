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

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/info_parser.hpp>

#include "EntityManager.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include <common/IdGenerator.hpp>

#include "../spaceobjects/IncludeSpaceObjects.hpp"

//#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../world/galaxy.hpp"
#include "../world/starsystem.hpp"

#include "../builder/items/IncludeItemBuilders.hpp"
#include "../builder/spaceobjects/IncludeSpaceObjectBuilders.hpp"

#include "../items/others/GoodsPack.hpp"

#include "../builder/slots/ItemSlotBuilder.hpp"
#include "../builder/slots/VehicleSlotBuilder.hpp"

#include "../builder/world/GalaxyBuilder.hpp"
#include "../builder/world/StarSystemBuilder.hpp"

//#include "../builder/pilots/PlayerBuilder.hpp"
#include "../builder/pilots/NpcBuilder.hpp"

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

#include "../items/equipment/BakEquipment.hpp"
#include "../items/equipment/DriveEquipment.hpp"
#include "../items/equipment/DroidEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../items/equipment/ProtectorEquipment.hpp"
#include "../items/equipment/RadarEquipment.hpp"
#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/ScanerEquipment.hpp"
#include "../items/equipment/EnergizerEquipment.hpp"
#include "../items/equipment/FreezerEquipment.hpp"

#include "../items/modules/BakModule.hpp"
#include "../items/modules/DriveModule.hpp"
#include "../items/modules/DroidModule.hpp"
#include "../items/modules/GrappleModule.hpp"
#include "../items/modules/LazerModule.hpp"
#include "../items/modules/ProtectorModule.hpp"
#include "../items/modules/RadarModule.hpp"
#include "../items/modules/RocketModule.hpp"
#include "../items/modules/ScanerModule.hpp"

#include "../items/others/Bomb.hpp"

#include "../items/artefacts/GravityArtefact.hpp"
#include "../items/artefacts/ProtectorArtefact.hpp"

#include "../dock/Goverment.hpp"
#include "../dock/NatureLand.hpp"
#include "../dock/Kosmoport.hpp"

#include "../slots/VehicleSlot.hpp"
//#include <ceti/StringUtils.hpp>
#include <common/Global.hpp>
#include <common/TurnTimer.hpp>

#include <slots/ItemSlot.hpp>

void EntityManager::clear()
{
    for (std::map<ID, Base*>::iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++)
    {
        //LOG("________EntityManager::Clear, delete " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
        delete iterator->second;
    }

    m_entities_map.clear();
}

void EntityManager::reg(Base* entity)
{
    //LOG("+++++++EntityManager::RegisterEntity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    
    if (entity->id() == NONE_ID) {
        entity->setId(IdGenerator::get().nextId());
    }
    m_entities_map.insert(std::make_pair(entity->id(), entity));
}

Base* EntityManager::get(const ID& id) const
{
    LOG("    EntityManager::entity requested_id=" + std::to_string(id));
    std::map<ID, Base*>::const_iterator slice = m_entities_map.find(id);
    assert(slice->second);
    //LOG("    EntityManager::GetEntityById type_id=" + getTypeStr(slice->second->typeId()));    
    return slice->second;
}

Player* EntityManager::player() const
{
    for (std::map<ID, Base*>::const_iterator it=m_entities_map.begin(); it!=m_entities_map.end(); ++it) {
        if (it->second->typeId() == TYPE::ENTITY::PLAYER_ID) {
            return (Player*)it->second;
        }
    }
    return nullptr;
}

void EntityManager::removeEntity(Base* entity)
{    
    //LOG("________EntityManager::RemoveEntity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));

    if (m_entities_map.count(entity->id()) == 1) {
        m_entities_map.erase(m_entities_map.find(entity->id()));
    } else {
        //LOG("fix the BUG ---EntityManager::RemoveEntity fails " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    }
} 


void EntityManager::saveEvent(const std::string& filename)
{
    boost::property_tree::ptree save_ptree;
    
    for (std::map<ID, Base*>::iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
        //LOG("saving " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
        iterator->second->Save(save_ptree);
    }
    
    //write_info(filename, save_ptree);
    write_info("save/save_last.info", save_ptree);
}

void EntityManager::loadPass0(const std::string& filename)
{
    LOG("LOADING STARTED");
    
    boost::property_tree::ptree load_ptree;
    read_info("save/" + filename, load_ptree);
    
    if (load_ptree.get_child_optional("galaxy"))
    {
        LOG("loading galaxys...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("galaxy"))
        {
            Galaxy* galaxy = global::get().galaxyBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            galaxy->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("player"))
    {
        //        LOG("loading players...");
        //        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("player"))
        //        {
        //            Player* player = PlayerBuilder::Instance().GetNewPlayerTemplate(v.second.get<unsigned long int>("data_id.id"));
        //            player->Load(v.second);
        //        }
    }
    
    if (load_ptree.get_child_optional("starsystem"))
    {
        LOG("loading starsystems...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
        {
            StarSystem* starsystem = global::get().starSystemBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            starsystem->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("star"))
    {
        LOG("loading stars...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
        {
            Star* star = global::get().starBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            star->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("planet"))
    {
        LOG("loading planets...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
        {
            Planet* planet = global::get().planetBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            planet->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("asteroid"))
    {
        LOG("loading asteroids...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("asteroid"))
        {
            Asteroid* asteroid = global::get().asteroidBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            asteroid->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("blackhole"))
    {
        LOG("loading blackhole...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("blackhole"))
        {
            BlackHole* blackhole = global::get().blackHoleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            blackhole->Load(v.second);
        }
    }

    //artefact
    if (load_ptree.get_child_optional("gravity_artefact"))
    {
        LOG("loading gravity_artefact...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("gravity_artefact"))
        {
            GravityArtefact* gravity_artefact = global::get().gravityArtefactBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            gravity_artefact->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("protector_artefact"))
    {
        LOG("loading protector_artefact...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_artefact"))
        {
            ProtectorArtefact* protector_artefact = global::get().protectorArtefactBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            protector_artefact->Load(v.second);
        }
    }

    //module
    if (load_ptree.get_child_optional("bak_module"))
    {
        LOG("loading bak_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_module"))
        {
            BakModule* bak_module = global::get().bakModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            bak_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("drive_module"))
    {
        LOG("loading drive_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_module"))
        {
            DriveModule* drive_module = global::get().driveModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            drive_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("droid_module"))
    {
        LOG("loading droid_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_module"))
        {
            DroidModule* droid_module = global::get().droidModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            droid_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("grapple_module"))
    {
        LOG("loading grapple_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_module"))
        {
            GrappleModule* grapple_module = global::get().grappleModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            grapple_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("lazer_module"))
    {
        LOG("loading lazer_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_module"))
        {
            LazerModule* lazer_module = global::get().lazerModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            lazer_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("protector_module"))
    {
        LOG("loading protector_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_module"))
        {
            ProtectorModule* protector_module = global::get().protectorModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            protector_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("radar_module"))
    {
        LOG("loading radar_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_module"))
        {
            RadarModule* radar_module = global::get().radarModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            radar_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("rocket_module"))
    {
        LOG("loading rocket_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_module"))
        {
            RocketModule* rocket_module = global::get().rocketModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            rocket_module->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("scaner_module"))
    {
        LOG("loading scaner_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_module"))
        {
            ScanerModule* scaner_module = global::get().scanerModuleBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            scaner_module->Load(v.second);
        }
    }

    // equipment
    if (load_ptree.get_child_optional("bak_equipment"))
    {
        LOG("loading bak_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_equipment"))
        {
            BakEquipment* bak_equipment = global::get().bakEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            bak_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("drive_equipment"))
    {
        LOG("loading drive_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_equipment"))
        {
            DriveEquipment* drive_equipment = global::get().driveEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            drive_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("droid_equipment"))
    {
        LOG("loading droid_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_equipment"))
        {
            DroidEquipment* droid_equipment = global::get().droidEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            droid_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("energizer_equipment"))
    {
        LOG("loading energizer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("energizer_equipment"))
        {
            EnergizerEquipment* energizer_equipment = global::get().energizerEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            energizer_equipment->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("freezer_equipment"))
    {
        LOG("loading freezer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("freezer_equipment"))
        {
            FreezerEquipment* freezer_equipment = global::get().freezerEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            freezer_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("grapple_equipment"))
    {
        LOG("loading grapple_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_equipment"))
        {
            GrappleEquipment* grapple_equipment = global::get().grappleEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            grapple_equipment->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("lazer_equipment"))
    {
        LOG("loading lazer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_equipment"))
        {
            LazerEquipment* lazer_equipment = global::get().lazerEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            lazer_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("protector_equipment"))
    {
        LOG("loading protector_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_equipment"))
        {
            ProtectorEquipment* protector_equipment = global::get().protectorEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            protector_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("radar_equipment"))
    {
        LOG("loading radar_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_equipment"))
        {
            RadarEquipment* radar_equipment = global::get().radarEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            radar_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("rocket_equipment"))
    {
        LOG("loading rocket_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_equipment"))
        {
            RocketEquipment* rocket_equipment = global::get().rocketEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            rocket_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("scaner_equipment"))
    {
        LOG("loading scaner_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_equipment"))
        {
            ScanerEquipment* scaner_equipment = global::get().scanerEquipmentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            scaner_equipment->Load(v.second);
        }
    }
    
    // other item
    if (load_ptree.get_child_optional("bomb"))
    {
        LOG("loading bombs...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bomb"))
        {
            Bomb* bomb = global::get().bombBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            bomb->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("goods_pack"))
    {
        LOG("loading goods_packs...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goods_pack"))
        {
            GoodsPack* goods_pack = GetNewGoodsPack((TYPE::ENTITY)v.second.get<int>("data_id.subtype_id"), v.second.get<unsigned long int>("data_id.id"));
            goods_pack->Load(v.second);
        }
    }
    //
    
    if (load_ptree.get_child_optional("item_slot"))
    {
        LOG("loading itemslots...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("item_slot"))
        {
            ItemSlot* itemslot = GetNewItemSlot((TYPE::ENTITY)v.second.get<int>("data_id.subtype_id"), v.second.get<unsigned long int>("data_id.id"));
            itemslot->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("vehicle_slot"))
    {
        LOG("loading vehicle_slots...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("vehicle_slot"))
        {
            unsigned long int id = v.second.get<unsigned long int>("data_id.id");
            TYPE::ENTITY subtype_id = (TYPE::ENTITY)v.second.get<int>("data_id.subtype_id");
            VehicleSlot* vehicleslot = GetNewVehicleSlot(subtype_id, id);
            vehicleslot->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("container"))
    {
        LOG("loading containers...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("container"))
        {
            Container* container = global::get().containerBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            container->Load(v.second);
        }
    }
    //

    if (load_ptree.get_child_optional("npc"))
    {
        LOG("loading npc...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("npc"))
        {
            unsigned long int id = v.second.get<unsigned long int>("data_id.id");
            TYPE::ENTITY subtype_id = (TYPE::ENTITY)v.second.get<int>("data_id.subtype_id");
            TYPE::ENTITY subsubtype_id = (TYPE::ENTITY)v.second.get<int>("data_id.subsubtype_id");
            Npc* npc = global::get().npcBuilder().createTemplate( subtype_id, subsubtype_id, id);
            npc->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("ship"))
    {
        LOG("loading ships...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("ship"))
        {
            //Ship* ship = global::get().shipBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            //ship->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("spacestation"))
    {
        LOG("loading spacestations...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("spacestation"))
        {
            SpaceStation* spacestation = global::get().spaceStationBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            spacestation->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("satellite"))
    {
        LOG("loading satellites...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("satellite"))
        {
            Satellite* satellite = global::get().satelliteBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            satellite->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("rocketbullet"))
    {
        LOG("loading rocketbullets...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocketbullet"))
        {
            RocketBullet* rocket_bullet = global::get().rocketBulletBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            rocket_bullet->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("natureland"))
    {
        LOG("loading naturelands...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("natureland"))
        {
            NatureLand* natureland = global::get().natureLandBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            natureland->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("kosmoport"))
    {
        LOG("loading kosmoports...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("kosmoport"))
        {
            Kosmoport* kosmoport = global::get().kosmoportBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            kosmoport->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("angar"))
    {
        LOG("loading angars...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("angar"))
        {
            Angar* angar = global::get().angarBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            angar->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("store"))
    {
        LOG("loading stores...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("store"))
        {
            Store* store = global::get().storeBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            store->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("shop"))
    {
        LOG("loading shops...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("shop"))
        {
            Shop* shop = global::get().shopBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            shop->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("goverment"))
    {
        LOG("loading goverments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goverment"))
        {
            Goverment* goverment = global::get().govermentBuilder().createTemplate(v.second.get<unsigned long int>("data_id.id"));
            goverment->Load(v.second);
        }
    }

    LOG("LOADING FINISHED");
    
}

void EntityManager::loadPass1() const
{
    LOG("RESOLVING DEPENDENCY START");
    for (std::map<ID, Base*>::const_iterator iterator = m_entities_map.begin(); iterator != m_entities_map.end(); iterator++) {
        LOG("Load() in " + iterator->second->dataTypeStr());
        iterator->second->Resolve();
    }

    LOG("RESOLVING DEPENDENCY FINISHED");
}


bool EntityManager::updateSaveRequest()
{        
    if (m_save_request == true) {
        saveEvent("save"+std::to_string(global::get().turnTimer().getStopTurnTimer())+".info");
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
        loadPass0("save_last.info");
        loadPass1();

        m_load_request = false;
        
        return true;
    }
    
    return false;
}


void EntityManager::addToGarbage(Base* entity)
{
    //LOG("EntetiesManager::AddToGarbage entity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    for (unsigned int i=0; i<m_garbage.size(); i++) {
        if (m_garbage[i]->id() == entity->id()) {
            //LOG("EntetiesManager::AddToGarbage dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
            exit(1);
        }
    }

    m_garbage.push_back(entity);
    entity->putChildrenToGarbage();
}

void EntityManager::clearGarbage()
{
    for(unsigned int i=0; i<m_garbage.size(); i++)
    {
        removeEntity(m_garbage[i]);
#if CREATEDESTROY_LOG_ENABLED == 1
        LOG("________EntityManager::ClearGarbage delete entity " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
#endif
        IdGenerator::get().addFreeId(m_garbage[i]->id());
        delete m_garbage[i];
    }
    m_garbage.clear();
}


