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

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "EntityManager.hpp"
#include "../common/Logger.hpp"

EntityManager& EntityManager::Instance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::RegisterEntity(Base* entity)
{
	entity_map.insert(std::make_pair(entity->GetId(), entity));
}
	
Base* EntityManager::GetEntityById(int id) const
{
	std::map<int, Base*>::const_iterator slice = entity_map.find(id);

	assert(slice->second);
	return slice->second;
}


void EntityManager::RemoveEntity(Base* entity)
{    
	entity_map.erase(entity_map.find(entity->GetId()));
} 

		
void EntityManager::SaveEvent()
{
	boost::property_tree::ptree save_ptree;
	
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		iterator->second->SaveData(save_ptree);
	}
	
	SaveManager::Instance().SaveFile("save.info", save_ptree);
}
		
void EntityManager::LoadPass0()
{       
	entity_map.clear();

	Logger::Instance().Log("LOADING STARTED");
	
	boost::property_tree::ptree load_ptree;
	SaveManager::Instance().LoadFile("save.info", load_ptree);
	
	if (load_ptree.get_child_optional("galaxy"))
	{		
		Logger::Instance().Log("loading galaxys...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("galaxy"))
		{
			GalaxyBuilder::Instance().CreateNewGalaxy(v.second.get<int>("data_id.id"));
			GalaxyBuilder::Instance().GetGalaxy()->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("player"))
	{
		Logger::Instance().Log("loading players...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("player"))
		{
			PlayerBuilder::Instance().CreateNewPlayer(v.second.get<int>("data_id.id"));
			PlayerBuilder::Instance().GetPlayer()->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("starsystem"))
	{		
		Logger::Instance().Log("loading starsystems...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
		{
			StarSystemBuilder::Instance().CreateNewStarSystem(v.second.get<int>("data_id.id"));
			StarSystemBuilder::Instance().GetStarSystem()->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("star"))
	{
		Logger::Instance().Log("loading stars...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
		{
			StarBuilder::Instance().CreateNewStar(v.second.get<int>("data_id.id"));
			StarBuilder::Instance().GetStar()->LoadData(v.second);
		}
	}
	
	if (load_ptree.get_child_optional("planet"))
	{
		Logger::Instance().Log("loading planets...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
		{
			PlanetBuilder::Instance().CreateNewPlanet(v.second.get<int>("data_id.id"));
			PlanetBuilder::Instance().GetPlanet()->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("asteroids"))
	{
		Logger::Instance().Log("loading asteroids...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("asteroid"))
		{
			AsteroidBuilder::Instance().CreateNewAsteroid(v.second.get<int>("data_id.id"));
			AsteroidBuilder::Instance().GetAsteroid()->LoadData(v.second);
		}
	}
	        
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
			ContainerBuilder::Instance().CreateNewContainer(v.second.get<int>("data_id.id"));
			ContainerBuilder::Instance().GetContainer()->LoadData(v.second);
		}
	}
        
        // equipment
	if (load_ptree.get_child_optional("bak_equipment"))
	{
		Logger::Instance().Log("loading bak_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bak_equipment"))
		{
			BakEquipmentBuilder::Instance().CreateNewBakEquipment(v.second.get<int>("data_id.id"));
			BakEquipment* bak_equipment = BakEquipmentBuilder::Instance().GetBakEquipment();
                	bak_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("drive_equipment"))
	{
		Logger::Instance().Log("loading drive_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("drive_equipment"))
		{
			DriveEquipmentBuilder::Instance().CreateNewDriveEquipment(v.second.get<int>("data_id.id"));
			DriveEquipment* drive_equipment = DriveEquipmentBuilder::Instance().GetDriveEquipment();
                	drive_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("droid_equipment"))
	{
		Logger::Instance().Log("loading droid_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("droid_equipment"))
		{
			DroidEquipmentBuilder::Instance().CreateNewDroidEquipment(v.second.get<int>("data_id.id"));
			DroidEquipment* droid_equipment = DroidEquipmentBuilder::Instance().GetDroidEquipment();
                	droid_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("energizer_equipment"))
	{
		Logger::Instance().Log("loading energizer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("energizer_equipment"))
		{
			EnergizerEquipmentBuilder::Instance().CreateNewEnergizerEquipment(v.second.get<int>("data_id.id"));
			EnergizerEquipment* energizer_equipment = EnergizerEquipmentBuilder::Instance().GetEnergizerEquipment();
                	energizer_equipment->LoadData(v.second);
		}
	}
	
        if (load_ptree.get_child_optional("freezer_equipment"))
	{
		Logger::Instance().Log("loading freezer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("freezer_equipment"))
		{
			FreezerEquipmentBuilder::Instance().CreateNewFreezerEquipment(v.second.get<int>("data_id.id"));
			FreezerEquipment* freezer_equipment = FreezerEquipmentBuilder::Instance().GetFreezerEquipment();
                	freezer_equipment->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("grapple_equipment"))
	{
		Logger::Instance().Log("loading grapple_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("grapple_equipment"))
		{
			GrappleEquipmentBuilder::Instance().CreateNewGrappleEquipment(v.second.get<int>("data_id.id"));
			GrappleEquipment* grapple_equipment = GrappleEquipmentBuilder::Instance().GetGrappleEquipment();
                	grapple_equipment->LoadData(v.second);
                }
	}
	
	if (load_ptree.get_child_optional("lazer_equipment"))
	{
		Logger::Instance().Log("loading lazer_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("lazer_equipment"))
		{
			LazerEquipmentBuilder::Instance().CreateNewLazerEquipment(v.second.get<int>("data_id.id"));
			LazerEquipment* lazer_equipment = LazerEquipmentBuilder::Instance().GetLazerEquipment();
                	lazer_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("protector_equipment"))
	{
		Logger::Instance().Log("loading protector_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("protector_equipment"))
		{
			ProtectorEquipmentBuilder::Instance().CreateNewProtectorEquipment(v.second.get<int>("data_id.id"));
			ProtectorEquipment* protector_equipment = ProtectorEquipmentBuilder::Instance().GetProtectorEquipment();
                	protector_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("radar_equipment"))
	{
		Logger::Instance().Log("loading radar_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_equipment"))
		{
			RadarEquipmentBuilder::Instance().CreateNewRadarEquipment(v.second.get<int>("data_id.id"));
			RadarEquipment* radar_equipment = RadarEquipmentBuilder::Instance().GetRadarEquipment();
                	radar_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("rocket_equipment"))
	{
		Logger::Instance().Log("loading rocket_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocket_equipment"))
		{
			RocketEquipmentBuilder::Instance().CreateNewRocketEquipment(v.second.get<int>("data_id.id"));
			RocketEquipment* rocket_equipment = RocketEquipmentBuilder::Instance().GetRocketEquipment();
                	rocket_equipment->LoadData(v.second);
		}
	}

	if (load_ptree.get_child_optional("scaner_equipment"))
	{
		Logger::Instance().Log("loading scaner_equipments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("scaner_equipment"))
		{
			ScanerEquipmentBuilder::Instance().CreateNewScanerEquipment(v.second.get<int>("data_id.id"));
			ScanerEquipment* scaner_equipment = ScanerEquipmentBuilder::Instance().GetScanerEquipment();
                	scaner_equipment->LoadData(v.second);
		}
	}
	
	//module
	if (load_ptree.get_child_optional("radar_module"))
	{
		Logger::Instance().Log("loading radar_modules...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("radar_module"))
		{
			RadarModuleBuilder::Instance().CreateNewRadarModule(v.second.get<int>("data_id.id"));
			RadarModule* radar_module = RadarModuleBuilder::Instance().GetRadarModule();
                	radar_module->LoadData(v.second);
		}
	}
	
	// other
	if (load_ptree.get_child_optional("bomb"))
	{
		Logger::Instance().Log("loading bombs...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("bomb"))
		{
			BombBuilder::Instance().CreateNewBomb(v.second.get<int>("data_id.id"));
			Bomb* bomb = BombBuilder::Instance().GetBomb();
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
	
		
	if (load_ptree.get_child_optional("npc"))
	{
		Logger::Instance().Log("loading npc...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("npc"))
		{
			NpcBuilder::Instance().CreateNewNpc(v.second.get<int>("data_id.id"));
			NpcBuilder::Instance().GetNpc()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("ship"))
	{
		Logger::Instance().Log("loading ships...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("ship"))
		{
			ShipBuilder::Instance().CreateNewShip(v.second.get<int>("data_id.id"));
			ShipBuilder::Instance().GetShip()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("spacestation"))
	{
		Logger::Instance().Log("loading spacestations...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("spacestation"))
		{
			SpaceStationBuilder::Instance().CreateNewSpaceStation(v.second.get<int>("data_id.id"));
			SpaceStationBuilder::Instance().GetSpaceStation()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("satellite"))
	{
		Logger::Instance().Log("loading satellites...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("satellite"))
		{
			SatelliteBuilder::Instance().CreateNewSatellite(v.second.get<int>("data_id.id"));
			SatelliteBuilder::Instance().GetSatellite()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("rocketbullet"))
	{
		Logger::Instance().Log("loading rocketbullets...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("rocketbullet"))
		{
			RocketBulletBuilder::Instance().CreateNewRocket(v.second.get<int>("data_id.id"));
			RocketBulletBuilder::Instance().GetRocket()->LoadData(v.second);
		}
	}
		
        if (load_ptree.get_child_optional("kosmoport"))
	{	
		Logger::Instance().Log("loading kosmoports...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("kosmoport"))
		{
			KosmoportBuilder::Instance().CreateNewKosmoport(v.second.get<int>("data_id.id"));
			KosmoportBuilder::Instance().GetKosmoport()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("angar"))
	{
		Logger::Instance().Log("loading angars...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("angar"))
		{
			AngarBuilder::Instance().CreateNewAngar(v.second.get<int>("data_id.id"));
			AngarBuilder::Instance().GetAngar()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("store"))
	{
		Logger::Instance().Log("loading stores...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("store"))
		{
			StoreBuilder::Instance().CreateNewStore(v.second.get<int>("data_id.id"));
			StoreBuilder::Instance().GetStore()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("shop"))
	{
		Logger::Instance().Log("loading shops...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("shop"))
		{
			ShopBuilder::Instance().CreateNewShop(v.second.get<int>("data_id.id"));
			ShopBuilder::Instance().GetShop()->LoadData(v.second);
		}
	}

        if (load_ptree.get_child_optional("goverment"))
	{
		Logger::Instance().Log("loading goverments...");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goverment"))
		{
			GovermentBuilder::Instance().CreateNewGoverment(v.second.get<int>("data_id.id"));
			GovermentBuilder::Instance().GetGoverment()->LoadData(v.second);
		}
	}

}

void EntityManager::LoadPass1()
{
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		iterator->second->ResolveData();
	}
}
