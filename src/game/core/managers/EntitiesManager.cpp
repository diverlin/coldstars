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

#include "EntitiesManager.hpp"
#include "../common/Logger.hpp"
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

void EntitiesManager::Clear()
{
    for (std::map<unsigned long int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
    {    
#if CREATEDESTROY_LOG_ENABLED == 1
        Logger::Instance().Log("________EntitiesManager::Clear, delete " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
#endif
        delete iterator->second;
    }

    entity_map.clear();
}
        
void EntitiesManager::RegisterEntity(Base* entity)
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("+++++++EntitiesManager::RegisterEntity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    #endif
    
    entity_map.insert(std::make_pair(entity->id(), entity));
}
    
Base* EntitiesManager::GetEntityById(unsigned long int id) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log("    EntitiesManager::GetEntityById requested_id=" + std::to_string(id));
    #endif
    
    std::map<unsigned long int, Base*>::const_iterator slice = entity_map.find(id);

    assert(slice->second);

    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log("    EntitiesManager::GetEntityById type_id=" + getTypeStr(slice->second->typeId()));
    #endif
    
    return slice->second;
}

Player* EntitiesManager::GetPlayer() const
{
    for (std::map<unsigned long int, Base*>::const_iterator it=entity_map.begin(); it!=entity_map.end(); ++it)
    {
        if (it->second->typeId() == TYPE::ENTITY::PLAYER_ID)
        {
            return (Player*)it->second;
        }
    }

    return nullptr;
}

void EntitiesManager::RemoveEntity(Base* entity)
{    
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("________EntitiesManager::RemoveEntity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    #endif
        
    if (entity_map.count(entity->id()) == 1)
    {
        entity_map.erase(entity_map.find(entity->id()));
    }
    else
    {    
        #if CREATEDESTROY_LOG_ENABLED == 1
        Logger::Instance().Log("fix the BUG ---EntitiesManager::RemoveEntity fails " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
        #endif
    }
} 

        
void EntitiesManager::SaveEvent(const std::string& filename)
{
    boost::property_tree::ptree save_ptree;
    
    for (std::map<unsigned long int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
    {
        #if SAVELOAD_LOG_ENABLED == 1
        Logger::Instance().Log("saving " + getTypeStr(iterator->second->typeId()) + "(" +std::to_string(iterator->second->typeId()) +") " + getTypeStr(iterator->second->subTypeId()) + "(" + std::to_string(iterator->second->subTypeId()) + ") id=" + std::to_string(iterator->second->id()));
        #endif
        iterator->second->Save(save_ptree);
    }
    
    //write_info(filename, save_ptree);
    write_info("save/save_last.info", save_ptree);
}
        
void EntitiesManager::LoadPass0(const std::string& filename)
{
    Logger::Instance().Log("LOADING STARTED");
    
    boost::property_tree::ptree load_ptree;
    read_info("save/" + filename, load_ptree);
    
    if (load_ptree.get_child_optional("galaxy"))
    {        
        Logger::Instance().Log("loading galaxys...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("galaxy"))
        {
            Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxyTemplate(v.second.get<unsigned long int>("data_id.id"));
            galaxy->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("player"))
    {
//        Logger::Instance().Log("loading players...");
//        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("player"))
//        {
//            Player* player = PlayerBuilder::Instance().GetNewPlayerTemplate(v.second.get<unsigned long int>("data_id.id"));
//            player->Load(v.second);
//        }
    }
    
    if (load_ptree.get_child_optional("starsystem"))
    {        
        Logger::Instance().Log("loading starsystems...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
        {
            StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystemTemplate(v.second.get<unsigned long int>("data_id.id"));
            starsystem->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("star"))
    {
        Logger::Instance().Log("loading stars...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
        {
            Star* star = StarBuilder::Instance().GetNewStarTemplate(v.second.get<unsigned long int>("data_id.id"));
            star->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("planet"))
    {
        Logger::Instance().Log("loading planets...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
        {
            Planet* planet = PlanetBuilder::Instance().GetNewPlanetTemplate(v.second.get<unsigned long int>("data_id.id"));
            planet->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("asteroid"))
    {
        Logger::Instance().Log("loading asteroids...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("asteroid"))
        {
            Asteroid* asteroid = AsteroidBuilder::Instance().GetNewAsteroidTemplate(v.second.get<unsigned long int>("data_id.id"));
            asteroid->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("blackhole"))
    {
        Logger::Instance().Log("loading blackhole...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("blackhole"))
        {
            BlackHole* blackhole = BlackHoleBuilder::Instance().GetNewBlackHoleTemplate(v.second.get<unsigned long int>("data_id.id"));
            blackhole->Load(v.second);
        }
    }
        
    //artefact
    if (load_ptree.get_child_optional("gravity_artefact"))
    {
        Logger::Instance().Log("loading gravity_artefact...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("gravity_artefact"))
        {
            GravityArtefact* gravity_artefact = GravityArtefactBuilder::Instance().GetNewGravityArtefactTemplate(v.second.get<unsigned long int>("data_id.id"));
                    gravity_artefact->Load(v.second);
        }
    }     

    if (load_ptree.get_child_optional("protector_artefact"))
    {
        Logger::Instance().Log("loading protector_artefact...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_artefact"))
        {
            ProtectorArtefact* protector_artefact = ProtectorArtefactBuilder::Instance().GetNewProtectorArtefactTemplate(v.second.get<unsigned long int>("data_id.id"));
                    protector_artefact->Load(v.second);
        }
    }     
          
        //module
    if (load_ptree.get_child_optional("bak_module"))
    {
        Logger::Instance().Log("loading bak_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_module"))
        {
            BakModule* bak_module = BakModuleBuilder::Instance().GetNewBakModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    bak_module->Load(v.second);
        }
    }     

    if (load_ptree.get_child_optional("drive_module"))
    {
        Logger::Instance().Log("loading drive_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_module"))
        {
            DriveModule* drive_module = DriveModuleBuilder::Instance().GetNewDriveModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    drive_module->Load(v.second);
        }
    }     
        
    if (load_ptree.get_child_optional("droid_module"))
    {
        Logger::Instance().Log("loading droid_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_module"))
        {
            DroidModule* droid_module = DroidModuleBuilder::Instance().GetNewDroidModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    droid_module->Load(v.second);
        }
    }     

    if (load_ptree.get_child_optional("grapple_module"))
    {
        Logger::Instance().Log("loading grapple_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_module"))
        {
            GrappleModule* grapple_module = GrappleModuleBuilder::Instance().GetNewGrappleModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    grapple_module->Load(v.second);
        }
    }     

    if (load_ptree.get_child_optional("lazer_module"))
    {
        Logger::Instance().Log("loading lazer_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_module"))
        {
            LazerModule* lazer_module = LazerModuleBuilder::Instance().GetNewLazerModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    lazer_module->Load(v.second);
        }
    }     

    if (load_ptree.get_child_optional("protector_module"))
    {
        Logger::Instance().Log("loading protector_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_module"))
        {
            ProtectorModule* protector_module = ProtectorModuleBuilder::Instance().GetNewProtectorModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    protector_module->Load(v.second);
        }
    }     
                
    if (load_ptree.get_child_optional("radar_module"))
    {
        Logger::Instance().Log("loading radar_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_module"))
        {
            RadarModule* radar_module = RadarModuleBuilder::Instance().GetNewRadarModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    radar_module->Load(v.second);
        }
    } 

    if (load_ptree.get_child_optional("rocket_module"))
    {
        Logger::Instance().Log("loading rocket_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_module"))
        {
            RocketModule* rocket_module = RocketModuleBuilder::Instance().GetNewRocketModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    rocket_module->Load(v.second);
        }
    } 

    if (load_ptree.get_child_optional("scaner_module"))
    {
        Logger::Instance().Log("loading scaner_modules...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_module"))
        {
            ScanerModule* scaner_module = ScanerModuleBuilder::Instance().GetNewScanerModuleTemplate(v.second.get<unsigned long int>("data_id.id"));
                    scaner_module->Load(v.second);
        }
    } 
            
        // equipment
    if (load_ptree.get_child_optional("bak_equipment"))
    {
        Logger::Instance().Log("loading bak_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_equipment"))
        {
            BakEquipment* bak_equipment = BakEquipmentBuilder::Instance().GetNewBakEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    bak_equipment->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("drive_equipment"))
    {
        Logger::Instance().Log("loading drive_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_equipment"))
        {
            DriveEquipment* drive_equipment = DriveEquipmentBuilder::Instance().GetNewDriveEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    drive_equipment->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("droid_equipment"))
    {
        Logger::Instance().Log("loading droid_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_equipment"))
        {
            DroidEquipment* droid_equipment = DroidEquipmentBuilder::Instance().GetNewDroidEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    droid_equipment->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("energizer_equipment"))
    {
        Logger::Instance().Log("loading energizer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("energizer_equipment"))
        {
            EnergizerEquipment* energizer_equipment = EnergizerEquipmentBuilder::Instance().GetNewEnergizerEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    energizer_equipment->Load(v.second);
        }
    }
    
        if (load_ptree.get_child_optional("freezer_equipment"))
    {
        Logger::Instance().Log("loading freezer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("freezer_equipment"))
        {
            FreezerEquipment* freezer_equipment = FreezerEquipmentBuilder::Instance().GetNewFreezerEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    freezer_equipment->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("grapple_equipment"))
    {
        Logger::Instance().Log("loading grapple_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_equipment"))
        {
            GrappleEquipment* grapple_equipment = GrappleEquipmentBuilder::Instance().GetNewGrappleEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    grapple_equipment->Load(v.second);
                }
    }
    
    if (load_ptree.get_child_optional("lazer_equipment"))
    {
        Logger::Instance().Log("loading lazer_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_equipment"))
        {
            LazerEquipment* lazer_equipment = LazerEquipmentBuilder::Instance().GetNewLazerEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    lazer_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("protector_equipment"))
    {
        Logger::Instance().Log("loading protector_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_equipment"))
        {
            ProtectorEquipment* protector_equipment = ProtectorEquipmentBuilder::Instance().GetNewProtectorEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    protector_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("radar_equipment"))
    {
        Logger::Instance().Log("loading radar_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_equipment"))
        {
            RadarEquipment* radar_equipment = RadarEquipmentBuilder::Instance().GetNewRadarEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    radar_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("rocket_equipment"))
    {
        Logger::Instance().Log("loading rocket_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_equipment"))
        {
            RocketEquipment* rocket_equipment = RocketEquipmentBuilder::Instance().GetNewRocketEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    rocket_equipment->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("scaner_equipment"))
    {
        Logger::Instance().Log("loading scaner_equipments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_equipment"))
        {
            ScanerEquipment* scaner_equipment = ScanerEquipmentBuilder::Instance().GetNewScanerEquipmentTemplate(v.second.get<unsigned long int>("data_id.id"));
                    scaner_equipment->Load(v.second);
        }
    }
    
    // other item
    if (load_ptree.get_child_optional("bomb"))
    {
        Logger::Instance().Log("loading bombs...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bomb"))
        {
            Bomb* bomb = BombBuilder::Instance().GetNewBombTemplate(v.second.get<unsigned long int>("data_id.id"));
                    bomb->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("goods_pack"))
    {
        Logger::Instance().Log("loading goods_packs...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goods_pack"))
        {
            GoodsPack* goods_pack = GetNewGoodsPack((TYPE::ENTITY)v.second.get<int>("data_id.subtype_id"), v.second.get<unsigned long int>("data_id.id"));
            goods_pack->Load(v.second);
        }
    }
    //
    
    if (load_ptree.get_child_optional("item_slot"))
    {
        Logger::Instance().Log("loading itemslots...");
            BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("item_slot"))
        {
            ItemSlot* itemslot = GetNewItemSlot((TYPE::ENTITY)v.second.get<int>("data_id.subtype_id"), v.second.get<unsigned long int>("data_id.id"));
            itemslot->Load(v.second);
        }
    }
    
    if (load_ptree.get_child_optional("vehicle_slot"))
    {
        Logger::Instance().Log("loading vehicle_slots...");
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
        Logger::Instance().Log("loading containers...");
            BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("container"))
        {
            Container* container = ContainerBuilder::Instance().GetNewContainerTemplate(v.second.get<unsigned long int>("data_id.id"));
            container->Load(v.second);
        }
    }
    //
        
    if (load_ptree.get_child_optional("npc"))
    {
        Logger::Instance().Log("loading npc...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("npc"))
        {
            unsigned long int id = v.second.get<unsigned long int>("data_id.id");
            TYPE::ENTITY subtype_id = (TYPE::ENTITY)v.second.get<int>("data_id.subtype_id");
            TYPE::ENTITY subsubtype_id = (TYPE::ENTITY)v.second.get<int>("data_id.subsubtype_id");
            Npc* npc = NpcBuilder::Instance().GetNewNpcTemplate( subtype_id, subsubtype_id, id);
            npc->Load(v.second);
        }
    }

    if (load_ptree.get_child_optional("ship"))
    {
        Logger::Instance().Log("loading ships...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("ship"))
        {
            Ship* ship = ShipBuilder::Instance().GetNewShipTemplate(v.second.get<unsigned long int>("data_id.id"));
            ship->Load(v.second);
        }
    }
    
        if (load_ptree.get_child_optional("spacestation"))
    {
        Logger::Instance().Log("loading spacestations...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("spacestation"))
        {
            SpaceStation* spacestation = SpaceStationBuilder::Instance().GetNewSpaceStationTemplate(v.second.get<unsigned long int>("data_id.id"));
            spacestation->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("satellite"))
    {
        Logger::Instance().Log("loading satellites...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("satellite"))
        {
            Satellite* satellite = SatelliteBuilder::Instance().GetNewSatelliteTemplate(v.second.get<unsigned long int>("data_id.id"));
            satellite->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("rocketbullet"))
    {
        Logger::Instance().Log("loading rocketbullets...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocketbullet"))
        {
            RocketBullet* rocket_bullet = RocketBulletBuilder::Instance().GetNewRocketBulletTemplate(v.second.get<unsigned long int>("data_id.id"));
            rocket_bullet->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("natureland"))
    {    
        Logger::Instance().Log("loading naturelands...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("natureland"))
        {
            NatureLand* natureland = NatureLandBuilder::Instance().GetNewNatureLandTemplate(v.second.get<unsigned long int>("data_id.id"));
            natureland->Load(v.second);
        }
    }
            
        if (load_ptree.get_child_optional("kosmoport"))
    {    
        Logger::Instance().Log("loading kosmoports...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("kosmoport"))
        {
            Kosmoport* kosmoport = KosmoportBuilder::Instance().GetNewKosmoportTemplate(v.second.get<unsigned long int>("data_id.id"));
            kosmoport->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("angar"))
    {
        Logger::Instance().Log("loading angars...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("angar"))
        {
            Angar* angar = AngarBuilder::Instance().GetNewAngarTemplate(v.second.get<unsigned long int>("data_id.id"));
            angar->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("store"))
    {
        Logger::Instance().Log("loading stores...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("store"))
        {
            Store* store = StoreBuilder::Instance().GetNewStoreTemplate(v.second.get<unsigned long int>("data_id.id"));
            store->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("shop"))
    {
        Logger::Instance().Log("loading shops...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("shop"))
        {
            Shop* shop = ShopBuilder::Instance().GetNewShopTemplate(v.second.get<unsigned long int>("data_id.id"));
            shop->Load(v.second);
        }
    }

        if (load_ptree.get_child_optional("goverment"))
    {
        Logger::Instance().Log("loading goverments...");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goverment"))
        {
            Goverment* goverment = GovermentBuilder::Instance().GetNewGovermentTemplate(v.second.get<unsigned long int>("data_id.id"));
            goverment->Load(v.second);
        }
    }

    Logger::Instance().Log("LOADING FINISHED");
    
}

void EntitiesManager::LoadPass1() const
{
    Logger::Instance().Log("RESOLVING DEPENDENCY START");
    for (std::map<unsigned long int, Base*>::const_iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
    {
        Logger::Instance().Log("Load() in " + iterator->second->dataTypeString());
        iterator->second->Resolve();
    }

    Logger::Instance().Log("RESOLVING DEPENDENCY FINISHED");
}


bool EntitiesManager::UpdateSaveRequest()
{        
    if (save_request == true)
    {
        SaveEvent("save"+std::to_string(global::get().turnTimer().GetTurnCounter())+".info");
        save_request = false;
        
        return true;
    }
    
    return false;
}

bool EntitiesManager::UpdateLoadRequest()
{
    if (load_request == true)
    {
        Clear();
        LoadPass0("save_last.info");
        LoadPass1();
                        
        load_request = false;
        
        return true;
    }
    
    return false;
}


void EntitiesManager::AddToGarbage(Base* entity)
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("EntetiesManager::AddToGarbage entity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    for (unsigned int i=0; i<m_garbage.size(); i++)
    {
        if (m_garbage[i]->id() == entity->id())
        {
            Logger::Instance().Log("EntetiesManager::AddToGarbage dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
            exit(0);
        }
    }
    #endif

    m_garbage.push_back(entity);
    entity->putChildrenToGarbage();
}

void EntitiesManager::ClearGarbage()
{
    for(unsigned int i=0; i<m_garbage.size(); i++)
    {
        RemoveEntity(m_garbage[i]);
#if CREATEDESTROY_LOG_ENABLED == 1
        Logger::Instance().Log("________EntitiesManager::ClearGarbage delete entity " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
#endif
        EntityIdGenerator::Instance().AddFreeId(m_garbage[i]->id());
        delete m_garbage[i];
    }
    m_garbage.clear();
}


