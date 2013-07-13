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

#include "constants.hpp"
#include <sstream>
#include "Base.hpp"

std::string int2str(long long int val) 
{
	if (val >= 0)
	{
    		std::ostringstream stm;
    		stm<<val;
    		return stm.str();
	}    	
    	else
    	{
    		std::ostringstream stm;
    		stm<<abs(val);
    		return "-"+stm.str();
    	}
}

std::string bool2str(bool var) 
{
    	std::ostringstream stm;
    	if (var == true)
       		stm << "true";
    	else
       		stm << "false";   
    	return stm.str() ;
}

std::string getSpecialActionStr(int id)
{
	switch(id)
	{
		case SPECIAL_ACTION::INITIATE_DOCKING_ID: 	{ return "INITIATE_DOCKING_ID"; break; }
		case SPECIAL_ACTION::INITIATE_LAUNCHING_ID:	{ return "INITIATE_LAUNCHING_ID"; break; }
		case SPECIAL_ACTION::INITIATE_JUMPIN_ID:	{ return "INITIATE_JUMPIN_ID"; break; }
		case SPECIAL_ACTION::INITIATE_JUMPOUT_ID:	{ return "INITIATE_JUMPOUT_ID"; break; }
		case NONE_ID:					{ return "NONE_ID"; break; }
						
		default:			{ return "UKNOWN ID"; break; }		
	}
}

std::string getAiModelStr(int id)
{
	switch(id)
	{
		case AIMODEL::CONQUEROR_ID: 	{ return "CONQUEROR_ID"; break; }
		case AIMODEL::RANGER_ID:	{ return "RANGER_ID"; break; }
		case AIMODEL::TRADER_ID:	{ return "TRADER_ID"; break; }
		
		default:			{ return "UKNOWN ID"; break; }		
	}
}

std::string getRaceStr(int race_id) 
{
	switch(race_id)
	{
		case RACE::R0_ID: 	{ return "RACE0"; break; }
		case RACE::R1_ID:	{ return "RACE1"; break; }
		case RACE::R2_ID:	{ return "RACE2"; break; }
		case RACE::R3_ID:	{ return "RACE3"; break; }
		case RACE::R4_ID:	{ return "RACE4"; break; }	

		case RACE::R6_ID:	{ return "RACE6"; break; }
		case RACE::R7_ID:	{ return "RACE7"; break; }	
		
		default:		{ return "UKNOWN ID"; break; }
	}
}

std::string getNavigatorActionStr(int type_id)
{
	switch(type_id)
	{
		case NAVIGATOR_ACTION::NONE_ID: 	{ return "NONE_ID"; break; }
		case NAVIGATOR_ACTION::DOCKING_ID:	{ return "DOCKING_ID"; break; }
		case NAVIGATOR_ACTION::COLLECTING_ID:	{ return "COLLECTING_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:	{ return "KEEP_FIRE_DISTANCE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_CLOSE_ID:	{ return "KEEP_CLOSE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:	{ return "KEEP_MIDDLE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_FAR_ID: 	{ return "KEEP_FAR_ID"; break; }
		
		default: { return "UNKNOWN ID"; }
	}
}

std::string getEntityTypeStr(ENTITY::TYPE type_id)
{
	switch(type_id)
	{
		case ENTITY::TYPE::NONE_ID: { return "NONE_ID"; break; }
			
		case ENTITY::TYPE::VEHICLE_ID: 		{ return "VEHICLE_ID"; break; }
		case ENTITY::TYPE::SHIP_ID: 			{ return "SHIP_ID"; break; }
		case ENTITY::TYPE::SPACESTATION_ID: 		{ return "SPACESTATION_ID"; break; }
		case ENTITY::TYPE::SATELLITE_ID: 		{ return "SATELLITE_ID"; break; }
		case ENTITY::TYPE::NPC_ID: 			{ return "NPC_ID"; break; }
		case ENTITY::TYPE::BULLET_ID: 		{ return "BULLET_ID"; break; }
		case ENTITY::TYPE::ROCKETBULLET_ID: 		{ return "ROCKETBULLET_ID"; break; }
		case ENTITY::TYPE::MINERALS_ID: 		{ return "MINERALS_ID"; break; }
		case ENTITY::TYPE::FOOD_ID: 			{ return "FOOD_ID"; break; }
		case ENTITY::TYPE::MEDICINE_ID: 		{ return "MEDICINE_ID"; break; }
		case ENTITY::TYPE::MILITARY_ID: 		{ return "MILITARY_ID"; break; }
		case ENTITY::TYPE::DRUG_ID: 			{ return "DRUG_ID"; break; }
		case ENTITY::TYPE::EXCLUSIVE_ID: 		{ return "EXCLUSIVE_ID"; break; }
		case ENTITY::TYPE::CONTAINER_ID: 		{ return "CONTAINER_ID"; break; }
		case ENTITY::TYPE::GALAXY_ID: 		{ return "GALAXY_ID"; break; }
		case ENTITY::TYPE::STARSYSTEM_ID: 		{ return "STARSYSTEM_ID"; break; }
		case ENTITY::TYPE::STAR_ID: 			{ return "STAR_ID"; break; }
		case ENTITY::TYPE::ASTEROID_ID: 		{ return "ASTEROID_ID"; break; }
		case ENTITY::TYPE::PLANET_ID: 		{ return "PLANET_ID"; break; }
		case ENTITY::TYPE::BLACKHOLE_ID: 		{ return "BLACKHOLE_ID"; break; }
		case ENTITY::TYPE::BOMB_ID: 			{ return "BOMB_ID"; break; }
		case ENTITY::TYPE::GOODS_ID: 		{ return "GOODS_ID"; break; }
		case ENTITY::TYPE::PLAYER_ID: 		{ return "PLAYER_ID"; break; }
		case ENTITY::TYPE::KOSMOPORT_ID: 		{ return "KOSMOPORT_ID"; break; }
		case ENTITY::TYPE::NATURELAND_ID: 			{ return "NATURELAND_ID"; break; }
		case ENTITY::TYPE::SPACE_ID: 		{ return "SPACE_ID"; break; }
		case ENTITY::TYPE::HYPER_SPACE_ID: 		{ return "HYPER_SPACE_ID"; break; }
		case ENTITY::TYPE::GOVERMENT_ID: 		{ return "GOVERMENT_ID"; break; }
		case ENTITY::TYPE::STORE_ID: 		{ return "STORE_ID"; break; }
		case ENTITY::TYPE::SHOP_ID: 			{ return "SHOP_ID"; break; }
		case ENTITY::TYPE::ANGAR_ID: 		{ return "ANGAR_ID"; break; }
		
		case ENTITY::TYPE::VEHICLE_SLOT_ID: 		{ return "VEHICLE_SLOT_ID"; break; }
		case ENTITY::TYPE::VEHICLE_MILITARY_SLOT_ID: 		{ return "VEHICLE_MILITARY_SLOT_ID"; break; }
		case ENTITY::TYPE::VEHICLE_VISITORS_SLOT_ID: 		{ return "VEHICLE_VISITORS_SLOT_ID"; break; }
		case ENTITY::TYPE::ITEM_SLOT_ID: 		{ return "ITEM_SLOT_ID"; break; }
		
		case ENTITY::TYPE::CARGO_SLOT_ID: 		{ return "CARGO_SLOT_ID"; break; }	
		case ENTITY::TYPE::GATE_SLOT_ID: 		{ return "GATE_SLOT_ID"; break; }		
		case ENTITY::TYPE::REPAIR_SLOT_ID: 		{ return "REPAIR_SLOT_ID"; break; }	
		case ENTITY::TYPE::WEAPON_SLOT_ID: 		{ return "WEAPON_SLOT_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT1_ID: 		{ return "WEAPON_SLOT1_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT2_ID: 		{ return "WEAPON_SLOT2_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT3_ID: 		{ return "WEAPON_SLOT3_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT4_ID: 		{ return "WEAPON_SLOT4_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT5_ID: 		{ return "WEAPON_SLOT5_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT6_ID: 		{ return "WEAPON_SLOT6_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT7_ID: 		{ return "WEAPON_SLOT7_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT8_ID: 		{ return "WEAPON_SLOT8_ID"; break; }
		case ENTITY::TYPE::WEAPON_SLOT9_ID: 		{ return "WEAPON_SLOT9_ID"; break; }
		
		case ENTITY::TYPE::DRIVE_SLOT_ID: 		{ return "DRIVE_SLOT_ID"; break; }
		case ENTITY::TYPE::RADAR_SLOT_ID: 		{ return "RADAR_SLOT_ID"; break; }
		case ENTITY::TYPE::BAK_SLOT_ID: 		{ return "BAK_SLOT_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_SLOT_ID: 	{ return "ENERGIZER_SLOT_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_SLOT_ID: 	{ return "PROTECTOR_SLOT_ID"; break; }
		case ENTITY::TYPE::DROID_SLOT_ID: 		{ return "DROID_SLOT_ID"; break; }
		case ENTITY::TYPE::FREEZER_SLOT_ID: 		{ return "FREEZER_SLOT_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_SLOT_ID: 		{ return "GRAPPLE_SLOT_ID"; break; }
		case ENTITY::TYPE::SCANER_SLOT_ID: 		{ return "SCANER_SLOT_ID"; break; }
		case ENTITY::TYPE::ARTEFACT_SLOT_ID: 	{ return "ARTEFACT_SLOT_ID"; break; }

		case ENTITY::TYPE::EQUIPMENT_ID: 		{ return "EQUIPMENT_ID"; break; }		
		case ENTITY::TYPE::MODULE_ID: 		{ return "MODULE_ID"; break; }
		case ENTITY::TYPE::ARTEFACT_ID: 		{ return "ARTEFACT_ID"; break; }	
																								
		case ENTITY::TYPE::LAZER_EQUIPMENT_ID: 	{ return "LAZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::ROCKET_EQUIPMENT_ID: 	{ return "ROCKET_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::DRIVE_EQUIPMENT_ID: 	{ return "DRIVE_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::RADAR_EQUIPMENT_ID: 	{ return "RADAR_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::BAK_EQUIPMENT_ID: 	{ return "BAK_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_EQUIPMENT_ID: 	{ return "ENERGIZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_EQUIPMENT_ID: 	{ return "PROTECTOR_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::DROID_EQUIPMENT_ID: 	{ return "DROID_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::FREEZER_EQUIPMENT_ID: 	{ return "FREEZER_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_EQUIPMENT_ID: 	{ return "GRAPPLE_EQUIPMENT_ID"; break; }
		case ENTITY::TYPE::SCANER_EQUIPMENT_ID: 	{ return "SCANER_EQUIPMENT_ID"; break; }

		case ENTITY::TYPE::LAZER_MODULE_ID: 		{ return "LAZER_MODULE_ID"; break; }
		case ENTITY::TYPE::ROCKET_MODULE_ID: 	{ return "ROCKET_MODULE_ID"; break; }
		case ENTITY::TYPE::DRIVE_MODULE_ID: 		{ return "DRIVE_MODULE_ID"; break; }
		case ENTITY::TYPE::RADAR_MODULE_ID: 		{ return "RADAR_MODULE_ID"; break; }
		case ENTITY::TYPE::BAK_MODULE_ID: 		{ return "BAK_MODULE_ID"; break; }
		case ENTITY::TYPE::ENERGIZER_MODULE_ID: 	{ return "ENERGIZER_MODULE_ID"; break; }
		case ENTITY::TYPE::PROTECTOR_MODULE_ID: 	{ return "PROTECTOR_MODULE_ID"; break; }
		case ENTITY::TYPE::DROID_MODULE_ID: 		{ return "DROID_MODULE_ID"; break; }
		case ENTITY::TYPE::FREEZER_MODULE_ID: 	{ return "FREEZER_MODULE_ID"; break; }
		case ENTITY::TYPE::GRAPPLE_MODULE_ID: 	{ return "GRAPPLE_MODULE_ID"; break; }						
		case ENTITY::TYPE::SCANER_MODULE_ID: 	{ return "SCANER_MODULE_ID"; break; }	
		
		case ENTITY::TYPE::GRAVITY_ARTEFACT_ID: 	{ return "GRAVITY_ARTEFACT_ID"; break; }						
		case ENTITY::TYPE::PROTECTOR_ARTEFACT_ID: 	{ return "PROTECTOR_ARTEFACT_ID"; break; }	

		case ENTITY::TYPE::RANGER_ID: 	{ return "RANGER_ID"; break; }
		case ENTITY::TYPE::WARRIOR_ID: 	{ return "WARRIOR_ID"; break; }
		case ENTITY::TYPE::PIRAT_ID: 	{ return "PIRAT_ID"; break; }
		case ENTITY::TYPE::TRADER_ID: 	{ return "TRADER_ID"; break; }						
		case ENTITY::TYPE::DIPLOMAT_ID: 	{ return "DIPLOMAT_ID"; break; }	
							
		default: { return "UNKNOWN ID"; }
	}
}




