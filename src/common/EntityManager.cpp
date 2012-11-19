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

#include "EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/SaveLoadManager.hpp"
#include "../common/myStr.hpp"

#include "../spaceobjects/Star.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/Container.hpp"
#include "../spaceobjects/RocketBullet.hpp"

#include "../builder/items/equipment/BakEquipmentBuilder.hpp"
#include "../builder/items/equipment/DriveEquipmentBuilder.hpp"
#include "../builder/items/equipment/GrappleEquipmentBuilder.hpp"
#include "../builder/items/equipment/LazerEquipmentBuilder.hpp"
#include "../builder/items/equipment/ProtectorEquipmentBuilder.hpp"
#include "../builder/items/equipment/RocketEquipmentBuilder.hpp"
#include "../builder/items/equipment/ScanerEquipmentBuilder.hpp"
#include "../builder/items/equipment/DroidEquipmentBuilder.hpp"
#include "../builder/items/equipment/RadarEquipmentBuilder.hpp"
#include "../builder/items/equipment/FreezerEquipmentBuilder.hpp"
#include "../builder/items/equipment/EnergizerEquipmentBuilder.hpp"

#include "../builder/items/modules/BakModuleBuilder.hpp"
#include "../builder/items/modules/DriveModuleBuilder.hpp"
#include "../builder/items/modules/GrappleModuleBuilder.hpp"
#include "../builder/items/modules/LazerModuleBuilder.hpp"
#include "../builder/items/modules/ProtectorModuleBuilder.hpp"
#include "../builder/items/modules/RocketModuleBuilder.hpp"
#include "../builder/items/modules/ScanerModuleBuilder.hpp"
#include "../builder/items/modules/DroidModuleBuilder.hpp"
#include "../builder/items/modules/RadarModuleBuilder.hpp"

#include "../builder/items/artefacts/GravityArtefactBuilder.hpp"
#include "../builder/items/artefacts/ProtectorArtefactBuilder.hpp"

#include "../builder/items/other/BombBuilder.hpp"
#include "../items/others/GoodsPack.hpp"

#include "../builder/ItemSlotBuilder.hpp"
#include "../builder/VehicleSlotBuilder.hpp"

#include "../builder/GalaxyBuilder.hpp"
#include "../builder/PlayerBuilder.hpp"
#include "../builder/StarSystemBuilder.hpp"
#include "../builder/StarBuilder.hpp"
#include "../builder/PlanetBuilder.hpp"
#include "../builder/AsteroidBuilder.hpp"
#include "../builder/ContainerBuilder.hpp"
#include "../builder/NpcBuilder.hpp"
#include "../builder/ShipBuilder.hpp"
#include "../builder/SpaceStationBuilder.hpp"
#include "../builder/SatelliteBuilder.hpp"
#include "../builder/RocketBulletBuilder.hpp"

#include "../builder/KosmoportBuilder.hpp"
#include "../builder/AngarBuilder.hpp"
#include "../builder/StoreBuilder.hpp"
#include "../builder/ShopBuilder.hpp"
#include "../builder/GovermentBuilder.hpp"

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

#include "../docking/Goverment.hpp"
#include "../docking/Kosmoport.hpp"

#include "../slots/VehicleSlot.hpp"

EntityManager& EntityManager::Instance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::Clear()
{
	entity_map.clear();
}
		
void EntityManager::RegisterEntity(Base* entity)
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("+++++++EntityManager register " + getTypeStr(entity->GetTypeId()) + "(" +int2str(entity->GetTypeId()) +") " + getTypeStr(entity->GetSubTypeId()) + "(" + int2str(entity->GetSubTypeId()) + ") id=" + int2str(entity->GetId()));
	#endif
	
	entity_map.insert(std::make_pair(entity->GetId(), entity));
}
	
Base* EntityManager::GetEntityById(int id) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log("    EntityManager.GetEntityById() requested_id=" + int2str(id));
	#endif
	
	std::map<int, Base*>::const_iterator slice = entity_map.find(id);

	assert(slice->second);

	return slice->second;
}

Base* EntityManager::GetPlayer() const
{
	for (std::map<int, Base*>::const_iterator it=entity_map.begin(); it!=entity_map.end(); ++it)
	{
		if (it->second->GetTypeId() == ENTITY::PLAYER_ID)
		{
			return it->second;
		}
	}

	return NULL;
}

void EntityManager::RemoveEntity(Base* entity)
{    
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("________EntityManager remove " + getTypeStr(entity->GetTypeId()) + "(" +int2str(entity->GetTypeId()) +") " + getTypeStr(entity->GetSubTypeId()) + "(" + int2str(entity->GetSubTypeId()) + ") id=" + int2str(entity->GetId()));
	#endif
		
	if (entity_map.count(entity->GetId()) == 1)
	{
		entity_map.erase(entity_map.find(entity->GetId()));
	}
	else
	{
		std::cout<<"fix the BUG ---EntityManager::RemoveEntity fails"<<std::endl;
	}
} 

		
void EntityManager::SaveEvent()
{
	boost::property_tree::ptree save_ptree;
	
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		Logger::Instance().Log("saving " + getTypeStr(iterator->second->GetTypeId()) + "(" +int2str(iterator->second->GetTypeId()) +") " + getTypeStr(iterator->second->GetSubTypeId()) + "(" + int2str(iterator->second->GetSubTypeId()) + ") id=" + int2str(iterator->second->GetId()));
		iterator->second->SaveData(save_ptree);
	}
	
	SaveLoadManager::Instance().SaveFile("save.info", save_ptree);
}
		
void EntityManager::LoadPass0()
{
	Logger::Instance().Log("LOADING STARTED");
	
	boost::property_tree::ptree load_ptree;
	SaveLoadManager::Instance().LoadFile("save.info", load_ptree);
	
	if (load_ptree.get_child_optional("galaxy"))
	{		
		Logger::Instance().Log("loading galaxys...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("galaxy"))
		{
			Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxyTemplate(v.second.get<int>("data_id.id"));
			galaxy->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("player"))
	{
		Logger::Instance().Log("loading players...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("player"))
		{
			Player* player = PlayerBuilder::Instance().GetNewPlayerTemplate(v.second.get<int>("data_id.id"));
			player->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("starsystem"))
	{		
		Logger::Instance().Log("loading starsystems...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
		{
			StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystemTemplate(v.second.get<int>("data_id.id"));
			starsystem->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("star"))
	{
		Logger::Instance().Log("loading stars...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
		{
			Star* star = StarBuilder::Instance().GetNewStarTemplate(v.second.get<int>("data_id.id"));
			star->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("planet"))
	{
		Logger::Instance().Log("loading planets...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
		{
			Planet* planet = PlanetBuilder::Instance().GetNewPlanetTemplate(v.second.get<int>("data_id.id"));
			planet->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("asteroid"))
	{
		Logger::Instance().Log("loading asteroids...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("asteroid"))
		{
			Asteroid* asteroid = AsteroidBuilder::Instance().GetNewAsteroidTemplate(v.second.get<int>("data_id.id"));
			asteroid->LoadData(v.second);
		}
	}
	
	//artefact
	if (load_ptree.get_child_optional("gravity_artefact"))
	{
		Logger::Instance().Log("loading gravity_artefact...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("gravity_artefact"))
		{
			GravityArtefact* gravity_artefact = GravityArtefactBuilder::Instance().GetNewGravityArtefactTemplate(v.second.get<int>("data_id.id"));
                	gravity_artefact->LoadData(v.second);
		}
	} 	

	if (load_ptree.get_child_optional("protector_artefact"))
	{
		Logger::Instance().Log("loading protector_artefact...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_artefact"))
		{
			ProtectorArtefact* protector_artefact = ProtectorArtefactBuilder::Instance().GetNewProtectorArtefactTemplate(v.second.get<int>("data_id.id"));
                	protector_artefact->LoadData(v.second);
		}
	} 	
		  
        //module
	if (load_ptree.get_child_optional("bak_module"))
	{
		Logger::Instance().Log("loading bak_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_module"))
		{
			BakModule* bak_module = BakModuleBuilder::Instance().GetNewBakModuleTemplate(v.second.get<int>("data_id.id"));
                	bak_module->LoadData(v.second);
		}
	} 	

	if (load_ptree.get_child_optional("drive_module"))
	{
		Logger::Instance().Log("loading drive_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_module"))
		{
			DriveModule* drive_module = DriveModuleBuilder::Instance().GetNewDriveModuleTemplate(v.second.get<int>("data_id.id"));
                	drive_module->LoadData(v.second);
		}
	} 	
		
	if (load_ptree.get_child_optional("droid_module"))
	{
		Logger::Instance().Log("loading droid_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_module"))
		{
			DroidModule* droid_module = DroidModuleBuilder::Instance().GetNewDroidModuleTemplate(v.second.get<int>("data_id.id"));
                	droid_module->LoadData(v.second);
		}
	} 	

	if (load_ptree.get_child_optional("grapple_module"))
	{
		Logger::Instance().Log("loading grapple_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_module"))
		{
			GrappleModule* grapple_module = GrappleModuleBuilder::Instance().GetNewGrappleModuleTemplate(v.second.get<int>("data_id.id"));
                	grapple_module->LoadData(v.second);
		}
	} 	

	if (load_ptree.get_child_optional("lazer_module"))
	{
		Logger::Instance().Log("loading lazer_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_module"))
		{
			LazerModule* lazer_module = LazerModuleBuilder::Instance().GetNewLazerModuleTemplate(v.second.get<int>("data_id.id"));
                	lazer_module->LoadData(v.second);
		}
	} 	

	if (load_ptree.get_child_optional("protector_module"))
	{
		Logger::Instance().Log("loading protector_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_module"))
		{
			ProtectorModule* protector_module = ProtectorModuleBuilder::Instance().GetNewProtectorModuleTemplate(v.second.get<int>("data_id.id"));
                	protector_module->LoadData(v.second);
		}
	} 	
				
	if (load_ptree.get_child_optional("radar_module"))
	{
		Logger::Instance().Log("loading radar_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_module"))
		{
			RadarModule* radar_module = RadarModuleBuilder::Instance().GetNewRadarModuleTemplate(v.second.get<int>("data_id.id"));
                	radar_module->LoadData(v.second);
		}
	} 

	if (load_ptree.get_child_optional("rocket_module"))
	{
		Logger::Instance().Log("loading rocket_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_module"))
		{
			RocketModule* rocket_module = RocketModuleBuilder::Instance().GetNewRocketModuleTemplate(v.second.get<int>("data_id.id"));
                	rocket_module->LoadData(v.second);
		}
	} 

	if (load_ptree.get_child_optional("scaner_module"))
	{
		Logger::Instance().Log("loading scaner_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_module"))
		{
			ScanerModule* scaner_module = ScanerModuleBuilder::Instance().GetNewScanerModuleTemplate(v.second.get<int>("data_id.id"));
                	scaner_module->LoadData(v.second);
		}
	} 
			
        // equipment
	if (load_ptree.get_child_optional("bak_equipment"))
	{
		Logger::Instance().Log("loading bak_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_equipment"))
		{
			BakEquipment* bak_equipment = BakEquipmentBuilder::Instance().GetNewBakEquipmentTemplate(v.second.get<int>("data_id.id"));
                	bak_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("drive_equipment"))
	{
		Logger::Instance().Log("loading drive_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_equipment"))
		{
			DriveEquipment* drive_equipment = DriveEquipmentBuilder::Instance().GetNewDriveEquipmentTemplate(v.second.get<int>("data_id.id"));
                	drive_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("droid_equipment"))
	{
		Logger::Instance().Log("loading droid_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_equipment"))
		{
			DroidEquipment* droid_equipment = DroidEquipmentBuilder::Instance().GetNewDroidEquipmentTemplate(v.second.get<int>("data_id.id"));
                	droid_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("energizer_equipment"))
	{
		Logger::Instance().Log("loading energizer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("energizer_equipment"))
		{
			EnergizerEquipment* energizer_equipment = EnergizerEquipmentBuilder::Instance().GetNewEnergizerEquipmentTemplate(v.second.get<int>("data_id.id"));
                	energizer_equipment->LoadData(v.second);
		}
	}
	
        if (load_ptree.get_child_optional("freezer_equipment"))
	{
		Logger::Instance().Log("loading freezer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("freezer_equipment"))
		{
			FreezerEquipment* freezer_equipment = FreezerEquipmentBuilder::Instance().GetNewFreezerEquipmentTemplate(v.second.get<int>("data_id.id"));
                	freezer_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("grapple_equipment"))
	{
		Logger::Instance().Log("loading grapple_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_equipment"))
		{
			GrappleEquipment* grapple_equipment = GrappleEquipmentBuilder::Instance().GetNewGrappleEquipmentTemplate(v.second.get<int>("data_id.id"));
                	grapple_equipment->LoadData(v.second);
                }
	}
	
	if (load_ptree.get_child_optional("lazer_equipment"))
	{
		Logger::Instance().Log("loading lazer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_equipment"))
		{
			LazerEquipment* lazer_equipment = LazerEquipmentBuilder::Instance().GetNewLazerEquipmentTemplate(v.second.get<int>("data_id.id"));
                	lazer_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("protector_equipment"))
	{
		Logger::Instance().Log("loading protector_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_equipment"))
		{
			ProtectorEquipment* protector_equipment = ProtectorEquipmentBuilder::Instance().GetNewProtectorEquipmentTemplate(v.second.get<int>("data_id.id"));
                	protector_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("radar_equipment"))
	{
		Logger::Instance().Log("loading radar_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_equipment"))
		{
			RadarEquipment* radar_equipment = RadarEquipmentBuilder::Instance().GetNewRadarEquipmentTemplate(v.second.get<int>("data_id.id"));
                	radar_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("rocket_equipment"))
	{
		Logger::Instance().Log("loading rocket_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_equipment"))
		{
			RocketEquipment* rocket_equipment = RocketEquipmentBuilder::Instance().GetNewRocketEquipmentTemplate(v.second.get<int>("data_id.id"));
                	rocket_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("scaner_equipment"))
	{
		Logger::Instance().Log("loading scaner_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_equipment"))
		{
			ScanerEquipment* scaner_equipment = ScanerEquipmentBuilder::Instance().GetNewScanerEquipmentTemplate(v.second.get<int>("data_id.id"));
                	scaner_equipment->LoadData(v.second);
		}
	}
	
	// other item
	if (load_ptree.get_child_optional("bomb"))
	{
		Logger::Instance().Log("loading bombs...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bomb"))
		{
			Bomb* bomb = BombBuilder::Instance().GetNewBombTemplate(v.second.get<int>("data_id.id"));
                	bomb->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("goods_pack"))
	{
		Logger::Instance().Log("loading goods_packs...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goods_pack"))
		{
			GoodsPack* goods_pack = GetNewGoodsPack(v.second.get<int>("data_id.subtype_id"), v.second.get<int>("data_id.id"));
                	goods_pack->LoadData(v.second);
		}
	}
	//
	
	if (load_ptree.get_child_optional("item_slot"))
	{
		Logger::Instance().Log("loading itemslots...");
        	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("item_slot"))
		{
			ItemSlot* itemslot = GetNewItemSlot(v.second.get<int>("data_id.subtype_id"), v.second.get<int>("data_id.id"));
			itemslot->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("vehicle_slot"))
	{
		Logger::Instance().Log("loading vehicle_slots...");
        	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("vehicle_slot"))
		{
			VehicleSlot* vehicleslot = GetNewVehicleSlot(v.second.get<int>("data_id.id"));
			vehicleslot->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("container"))
	{
		Logger::Instance().Log("loading containers...");
        	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("container"))
		{
			Container* container = ContainerBuilder::Instance().GetNewContainerTemplate(v.second.get<int>("data_id.id"));
			container->LoadData(v.second);
		}
	}
	//
		
	if (load_ptree.get_child_optional("npc"))
	{
		Logger::Instance().Log("loading npc...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("npc"))
		{
			Npc* npc = NpcBuilder::Instance().GetNewNpcTemplate(v.second.get<int>("data_id.id"));
			npc->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("ship"))
	{
		Logger::Instance().Log("loading ships...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("ship"))
		{
			Ship* ship = ShipBuilder::Instance().GetNewShipTemplate(v.second.get<int>("data_id.id"));
			ship->LoadData(v.second);
		}
	}
	
        if (load_ptree.get_child_optional("spacestation"))
	{
		Logger::Instance().Log("loading spacestations...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("spacestation"))
		{
			SpaceStation* spacestation = SpaceStationBuilder::Instance().GetNewSpaceStationTemplate(v.second.get<int>("data_id.id"));
			spacestation->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("satellite"))
	{
		Logger::Instance().Log("loading satellites...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("satellite"))
		{
			Satellite* satellite = SatelliteBuilder::Instance().GetNewSatelliteTemplate(v.second.get<int>("data_id.id"));
			satellite->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("rocketbullet"))
	{
		Logger::Instance().Log("loading rocketbullets...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocketbullet"))
		{
			RocketBullet* rocket_bullet = RocketBulletBuilder::Instance().GetNewRocketBulletTemplate(v.second.get<int>("data_id.id"));
			rocket_bullet->LoadData(v.second);
		}
	}
		
        if (load_ptree.get_child_optional("kosmoport"))
	{	
		Logger::Instance().Log("loading kosmoports...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("kosmoport"))
		{
			Kosmoport* kosmoport = KosmoportBuilder::Instance().GetNewKosmoportTemplate(v.second.get<int>("data_id.id"));
			kosmoport->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("angar"))
	{
		Logger::Instance().Log("loading angars...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("angar"))
		{
			Angar* angar = AngarBuilder::Instance().GetNewAngarTemplate(v.second.get<int>("data_id.id"));
			angar->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("store"))
	{
		Logger::Instance().Log("loading stores...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("store"))
		{
			Store* store = StoreBuilder::Instance().GetNewStoreTemplate(v.second.get<int>("data_id.id"));
			store->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("shop"))
	{
		Logger::Instance().Log("loading shops...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("shop"))
		{
			Shop* shop = ShopBuilder::Instance().GetNewShopTemplate(v.second.get<int>("data_id.id"));
			shop->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("goverment"))
	{
		Logger::Instance().Log("loading goverments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goverment"))
		{
			Goverment* goverment = GovermentBuilder::Instance().GetNewGovermentTemplate(v.second.get<int>("data_id.id"));
			goverment->LoadData(v.second);
		}
	}

	Logger::Instance().Log("LOADING FINISHED");
	
}

void EntityManager::LoadPass1() const
{
	Logger::Instance().Log("RESOLVING DEPENDENCY START");
	for (std::map<int, Base*>::const_iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		Logger::Instance().Log("ResolveData() in " + getTypeStr(iterator->second->GetTypeId()));
		iterator->second->ResolveData();
	}

	Logger::Instance().Log("RESOLVING DEPENDENCY FINISHED");
}

