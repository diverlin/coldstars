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

#include "EntityTypes.hpp"

std::string getEntityTypeStr(ENTITY::TYPE type_id)
{
	switch(type_id)
	{
		case ENTITY::TYPE::NONE_ID: { return "ENTITY::NONE_ID"; break; }
			
		case ENTITY::TYPE::VEHICLE_ID: 		{ return "ENTITY::VEHICLE_ID"; break; }
		case ENTITY::TYPE::SHIP_ID: 			{ return "ENTITY::SHIP_ID"; break; }
		case ENTITY::TYPE::SPACESTATION_ID: 		{ return "ENTITY::SPACESTATION_ID"; break; }
		case ENTITY::TYPE::SATELLITE_ID: 		{ return "ENTITY::SATELLITE_ID"; break; }
		case ENTITY::TYPE::NPC_ID: 			{ return "ENTITY::NPC_ID"; break; }
		case ENTITY::TYPE::BULLET_ID: 		{ return "ENTITY::BULLET_ID"; break; }
		case ENTITY::TYPE::ROCKETBULLET_ID: 		{ return "ENTITY::ROCKETBULLET_ID"; break; }
		case ENTITY::TYPE::MINERALS_ID: 		{ return "ENTITY::MINERALS_ID"; break; }
		case ENTITY::TYPE::FOOD_ID: 			{ return "ENTITY::FOOD_ID"; break; }
		case ENTITY::TYPE::MEDICINE_ID: 		{ return "ENTITY::MEDICINE_ID"; break; }
		case ENTITY::TYPE::MILITARY_ID: 		{ return "ENTITY::MILITARY_ID"; break; }
		case ENTITY::TYPE::DRUG_ID: 			{ return "ENTITY::DRUG_ID"; break; }
		case ENTITY::TYPE::EXCLUSIVE_ID: 		{ return "ENTITY::EXCLUSIVE_ID"; break; }
		case ENTITY::TYPE::CONTAINER_ID: 		{ return "ENTITY::CONTAINER_ID"; break; }
		case ENTITY::TYPE::GALAXY_ID: 		{ return "ENTITY::GALAXY_ID"; break; }
		case ENTITY::TYPE::STARSYSTEM_ID: 		{ return "ENTITY::STARSYSTEM_ID"; break; }
		case ENTITY::TYPE::STAR_ID: 			{ return "ENTITY::STAR_ID"; break; }
		case ENTITY::TYPE::ASTEROID_ID: 		{ return "ENTITY::ASTEROID_ID"; break; }
		case ENTITY::TYPE::PLANET_ID: 		{ return "ENTITY::PLANET_ID"; break; }
		case ENTITY::TYPE::BLACKHOLE_ID: 		{ return "ENTITY::BLACKHOLE_ID"; break; }
		case ENTITY::TYPE::BOMB_ID: 			{ return "ENTITY::BOMB_ID"; break; }
		case ENTITY::TYPE::GOODS_ID: 		{ return "ENTITY::GOODS_ID"; break; }
		case ENTITY::TYPE::PLAYER_ID: 		{ return "ENTITY::PLAYER_ID"; break; }
		case ENTITY::TYPE::KOSMOPORT_ID: 		{ return "ENTITY::KOSMOPORT_ID"; break; }
		case ENTITY::TYPE::NATURELAND_ID: 			{ return "ENTITY::NATURELAND_ID"; break; }

		case ENTITY::TYPE::GOVERMENT_ID: 		{ return "ENTITY::GOVERMENT_ID"; break; }
		case ENTITY::TYPE::STORE_ID: 		{ return "ENTITY::STORE_ID"; break; }
		case ENTITY::TYPE::SHOP_ID: 			{ return "ENTITY::SHOP_ID"; break; }
		case ENTITY::TYPE::ANGAR_ID: 		{ return "ENTITY::ANGAR_ID"; break; }
		
		case ENTITY::TYPE::VEHICLE_SLOT_ID: 		{ return "ENTITY::VEHICLE_SLOT_ID"; break; }
		case ENTITY::TYPE::VEHICLE_MILITARY_SLOT_ID: 		{ return "ENTITY::VEHICLE_MILITARY_SLOT_ID"; break; }
		case ENTITY::TYPE::VEHICLE_VISITORS_SLOT_ID: 		{ return "ENTITY::VEHICLE_VISITORS_SLOT_ID"; break; }
		case ENTITY::TYPE::ITEM_SLOT_ID: 		{ return "ENTITY::ITEM_SLOT_ID"; break; }
		
		case ENTITY::TYPE::CARGO_SLOT_ID: 		{ return "ENTITY::CARGO_SLOT_ID"; break; }	
		case ENTITY::TYPE::GATE_SLOT_ID: 		{ return "ENTITY::GATE_SLOT_ID"; break; }		
		case ENTITY::TYPE::REPAIR_SLOT_ID: 		{ return "ENTITY::REPAIR_SLOT_ID"; break; }	
		case ENTITY::TYPE::WEAPON_SLOT_ID: 		{ return "ENTITY::WEAPON_SLOT_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT1_ID: 		{ return "ENTITY::WEAPON_SLOT1_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT2_ID: 		{ return "ENTITY::WEAPON_SLOT2_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT3_ID: 		{ return "ENTITY::WEAPON_SLOT3_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT4_ID: 		{ return "ENTITY::WEAPON_SLOT4_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT5_ID: 		{ return "ENTITY::WEAPON_SLOT5_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT6_ID: 		{ return "ENTITY::WEAPON_SLOT6_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT7_ID: 		{ return "ENTITY::WEAPON_SLOT7_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT8_ID: 		{ return "ENTITY::WEAPON_SLOT8_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT9_ID: 		{ return "ENTITY::WEAPON_SLOT9_ID"; break; }
		
		case ENTITY::TYPE::DRIVE_SLOT_ID: 		{ return "ENTITY::DRIVE_SLOT_ID"; break; }
		case ENTITY::TYPE::RADAR_SLOT_ID: 		{ return "ENTITY::RADAR_SLOT_ID"; break; }
		case ENTITY::TYPE::BAK_SLOT_ID: 		{ return "ENTITY::BAK_SLOT_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_SLOT_ID: 	{ return "ENTITY::ENERGIZER_SLOT_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_SLOT_ID: 	{ return "ENTITY::PROTECTOR_SLOT_ID"; break; }
		case ENTITY::TYPE::DROID_SLOT_ID: 		{ return "ENTITY::DROID_SLOT_ID"; break; }
		case ENTITY::TYPE::FREEZER_SLOT_ID: 		{ return "ENTITY::FREEZER_SLOT_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_SLOT_ID: 		{ return "ENTITY::GRAPPLE_SLOT_ID"; break; }
		case ENTITY::TYPE::SCANER_SLOT_ID: 		{ return "ENTITY::SCANER_SLOT_ID"; break; }
		case ENTITY::TYPE::ARTEFACT_SLOT_ID: 	{ return "ENTITY::ARTEFACT_SLOT_ID"; break; }

		case ENTITY::TYPE::EQUIPMENT_ID: 		{ return "ENTITY::EQUIPMENT_ID"; break; }		
		case ENTITY::TYPE::MODULE_ID: 		{ return "ENTITY::MODULE_ID"; break; }
		case ENTITY::TYPE::ARTEFACT_ID: 		{ return "ENTITY::ARTEFACT_ID"; break; }	
																								
		case ENTITY::TYPE::LAZER_EQUIPMENT_ID: 	{ return "ENTITY::LAZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::ROCKET_EQUIPMENT_ID: 	{ return "ENTITY::ROCKET_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::DRIVE_EQUIPMENT_ID: 	{ return "ENTITY::DRIVE_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::RADAR_EQUIPMENT_ID: 	{ return "ENTITY::RADAR_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::BAK_EQUIPMENT_ID: 	{ return "ENTITY::BAK_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_EQUIPMENT_ID: 	{ return "ENTITY::ENERGIZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_EQUIPMENT_ID: 	{ return "ENTITY::PROTECTOR_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::DROID_EQUIPMENT_ID: 	{ return "ENTITY::DROID_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::FREEZER_EQUIPMENT_ID: 	{ return "ENTITY::FREEZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_EQUIPMENT_ID: 	{ return "ENTITY::GRAPPLE_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::SCANER_EQUIPMENT_ID: 	{ return "ENTITY::SCANER_EQUIPMENT_ID"; break; }

		case ENTITY::TYPE::LAZER_MODULE_ID: 		{ return "ENTITY::LAZER_MODULE_ID"; break; }
		case ENTITY::TYPE::ROCKET_MODULE_ID: 	{ return "ENTITY::ROCKET_MODULE_ID"; break; }
		case ENTITY::TYPE::DRIVE_MODULE_ID: 		{ return "ENTITY::DRIVE_MODULE_ID"; break; }
		case ENTITY::TYPE::RADAR_MODULE_ID: 		{ return "ENTITY::RADAR_MODULE_ID"; break; }
		case ENTITY::TYPE::BAK_MODULE_ID: 		{ return "ENTITY::BAK_MODULE_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_MODULE_ID: 	{ return "ENTITY::ENERGIZER_MODULE_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_MODULE_ID: 	{ return "ENTITY::PROTECTOR_MODULE_ID"; break; }
		case ENTITY::TYPE::DROID_MODULE_ID: 		{ return "ENTITY::DROID_MODULE_ID"; break; }
		case ENTITY::TYPE::FREEZER_MODULE_ID: 	{ return "ENTITY::FREEZER_MODULE_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_MODULE_ID: 	{ return "ENTITY::GRAPPLE_MODULE_ID"; break; }						
		case ENTITY::TYPE::SCANER_MODULE_ID: 	{ return "ENTITY::SCANER_MODULE_ID"; break; }	
		
		case ENTITY::TYPE::GRAVITY_ARTEFACT_ID: 	{ return "ENTITY::GRAVITY_ARTEFACT_ID"; break; }						
		case ENTITY::TYPE::PROTECTOR_ARTEFACT_ID: 	{ return "ENTITY::PROTECTOR_ARTEFACT_ID"; break; }	

		case ENTITY::TYPE::RANGER_ID: 	{ return "ENTITY::RANGER_ID"; break; }
		case ENTITY::TYPE::WARRIOR_ID: 	{ return "ENTITY::WARRIOR_ID"; break; }
		case ENTITY::TYPE::PIRAT_ID: 	{ return "ENTITY::PIRAT_ID"; break; }
		case ENTITY::TYPE::TRADER_ID: 	{ return "ENTITY::TRADER_ID"; break; }						
		case ENTITY::TYPE::DIPLOMAT_ID: 	{ return "ENTITY::DIPLOMAT_ID"; break; }	
							
		default: { return "ENTITY::UNKNOWN ID"; }
	}
}
