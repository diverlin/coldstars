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

std::string int2str(int var) 
{
    	std::ostringstream stm;
    	stm << var;
    	return stm.str() ;
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




std::string getAiModelStr(int id)
{
	switch(id)
	{
		case AIMODEL::CONQUEROR_ID: 	{ return "CONQUEROR_ID"; break; }
		case AIMODEL::RANGER_ID:	{ return "RANGER_ID"; break; }
		case AIMODEL::TRADER_ID:	{ return "TRADER_ID"; break; }
		
		default:			{ return "UKNOWN. fix the bug"; break; }		
	}
}

std::string getClassStr(int id)
{
	switch(id)
	{
		case CLASS::RANGER_ID: 	{ return "RANGER_ID"; break; }
		case CLASS::WARRIOR_ID:	{ return "WARRIOR_ID"; break; }
		case CLASS::PIRAT_ID:		{ return "PIRAT_ID"; break; }
		case CLASS::TRADER_ID:		{ return "TRADER_ID"; break; }
		case CLASS::DIPLOMAT_ID:	{ return "DIPLOMAT_ID"; break; }
		
		default:			{ return "UKNOWN. fix the bug"; break; }		
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
		
		default:		{ return "UKNOWN. fix the bug"; break; }
	}
}

std::string getNavigatorActionStr(int type_id)
{
	switch(type_id)
	{
		case NAVIGATOR_ACTION::NONE_ID: 		{ return "NONE_ID"; break; }
		case NAVIGATOR_ACTION::DOCKING_ID:		{ return "DOCKING_ID"; break; }
		case NAVIGATOR_ACTION::COLLECTING_ID:	{ return "COLLECTING_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_CLOSE_ID:	{ return "KEEP_CLOSE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:	{ return "KEEP_MIDDLE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_FAR_ID: 		{ return "KEEP_FAR_ID"; break; }
		
		default: { return "UNKNOWN. fix the bug"; }
	}
}

std::string getEntityStr(int type_id)
{
	switch(type_id)
	{
		case ENTITY::VEHICLE_ID: 		{ return "VEHICLE_ID"; break; }
		case ENTITY::SHIP_ID: 			{ return "SHIP_ID"; break; }
		case ENTITY::SPACESTATION_ID: 		{ return "SPACESTATION_ID"; break; }
		case ENTITY::SATELLITE_ID: 		{ return "SATELLITE_ID"; break; }
		case ENTITY::NPC_ID: 			{ return "NPC_ID"; break; }
		case ENTITY::ROCKETBULLET_ID: 		{ return "ROCKETBULLET_ID"; break; }
		case ENTITY::MINERALS_ID: 		{ return "MINERALS_ID"; break; }
		case ENTITY::FOOD_ID: 			{ return "FOOD_ID"; break; }
		case ENTITY::MEDICINE_ID: 		{ return "MEDICINE_ID"; break; }
		case ENTITY::MILITARY_ID: 		{ return "MILITARY_ID"; break; }
		case ENTITY::DRUG_ID: 			{ return "DRUG_ID"; break; }
		case ENTITY::EXCLUSIVE_ID: 		{ return "EXCLUSIVE_ID"; break; }
		case ENTITY::CONTAINER_ID: 		{ return "CONTAINER_ID"; break; }
		case ENTITY::GALAXY_ID: 		{ return "GALAXY_ID"; break; }
		case ENTITY::STARSYSTEM_ID: 		{ return "STARSYSTEM_ID"; break; }
		case ENTITY::STAR_ID: 			{ return "STAR_ID"; break; }
		case ENTITY::ASTEROID_ID: 		{ return "ASTEROID_ID"; break; }
		case ENTITY::PLANET_ID: 		{ return "PLANET_ID"; break; }
		case ENTITY::BLACKHOLE_ID: 		{ return "BLACKHOLE_ID"; break; }
		case ENTITY::BOMB_ID: 			{ return "BOMB_ID"; break; }
		case ENTITY::GOODS_ID: 		{ return "GOODS_ID"; break; }
		case ENTITY::PLAYER_ID: 		{ return "PLAYER_ID"; break; }
		case ENTITY::KOSMOPORT_ID: 		{ return "KOSMOPORT_ID"; break; }
		case ENTITY::LAND_ID: 			{ return "LAND_ID"; break; }
		case ENTITY::SPACE_ID: 		{ return "SPACE_ID"; break; }
		case ENTITY::GOVERMENT_ID: 		{ return "GOVERMENT_ID"; break; }
		case ENTITY::STORE_ID: 		{ return "STORE_ID"; break; }
		case ENTITY::SHOP_ID: 			{ return "SHOP_ID"; break; }
		case ENTITY::ANGAR_ID: 		{ return "ANGAR_ID"; break; }
		case ENTITY::VEHICLE_SLOT_ID: 		{ return "VEHICLE_SLOT_ID"; break; }
		case ENTITY::ITEM_SLOT_ID: 		{ return "ITEM_SLOT_ID"; break; }
		
		case ENTITY::CARGO_SLOT_ID: 		{ return "CARGO_SLOT_ID"; break; }	
		case ENTITY::GATE_SLOT_ID: 		{ return "GATE_SLOT_ID"; break; }		
		case ENTITY::WEAPON_SLOT_ID: 		{ return "WEAPON_SLOT_ID"; break; }
		case ENTITY::WEAPON_SLOT1_ID: 		{ return "WEAPON_SLOT1_ID"; break; }
		case ENTITY::WEAPON_SLOT2_ID: 		{ return "WEAPON_SLOT2_ID"; break; }
		case ENTITY::WEAPON_SLOT3_ID: 		{ return "WEAPON_SLOT3_ID"; break; }
		case ENTITY::WEAPON_SLOT4_ID: 		{ return "WEAPON_SLOT4_ID"; break; }
		case ENTITY::WEAPON_SLOT5_ID: 		{ return "WEAPON_SLOT5_ID"; break; }
		case ENTITY::WEAPON_SLOT6_ID: 		{ return "WEAPON_SLOT6_ID"; break; }
		case ENTITY::WEAPON_SLOT7_ID: 		{ return "WEAPON_SLOT7_ID"; break; }
		case ENTITY::WEAPON_SLOT8_ID: 		{ return "WEAPON_SLOT8_ID"; break; }
		case ENTITY::WEAPON_SLOT9_ID: 		{ return "WEAPON_SLOT9_ID"; break; }
		
		case ENTITY::DRIVE_SLOT_ID: 		{ return "DRIVE_SLOT_ID"; break; }
		case ENTITY::RADAR_SLOT_ID: 		{ return "RADAR_SLOT_ID"; break; }
		case ENTITY::BAK_SLOT_ID: 		{ return "BAK_SLOT_ID"; break; }
		case ENTITY::ENERGIZER_SLOT_ID: 	{ return "ENERGIZER_SLOT_ID"; break; }
		case ENTITY::PROTECTOR_SLOT_ID: 	{ return "PROTECTOR_SLOT_ID"; break; }
		case ENTITY::DROID_SLOT_ID: 		{ return "DROID_SLOT_ID"; break; }
		case ENTITY::FREEZER_SLOT_ID: 		{ return "FREEZER_SLOT_ID"; break; }
		case ENTITY::GRAPPLE_SLOT_ID: 		{ return "GRAPPLE_SLOT_ID"; break; }
		case ENTITY::SCANER_SLOT_ID: 		{ return "SCANER_SLOT_ID"; break; }
		case ENTITY::ARTEFACT_SLOT_ID: 	{ return "ARTEFACT_SLOT_ID"; break; }
																						
		case ENTITY::LAZER_EQUIPMENT_ID: 	{ return "LAZER_EQUIPMENT_ID"; break; }
		case ENTITY::ROCKET_EQUIPMENT_ID: 	{ return "ROCKET_EQUIPMENT_ID"; break; }
		case ENTITY::DRIVE_EQUIPMENT_ID: 	{ return "DRIVE_EQUIPMENT_ID"; break; }
		case ENTITY::RADAR_EQUIPMENT_ID: 	{ return "RADAR_EQUIPMENT_ID"; break; }
		case ENTITY::BAK_EQUIPMENT_ID: 	{ return "BAK_EQUIPMENT_ID"; break; }
		case ENTITY::ENERGIZER_EQUIPMENT_ID: 	{ return "ENERGIZER_EQUIPMENT_ID"; break; }
		case ENTITY::PROTECTOR_EQUIPMENT_ID: 	{ return "PROTECTOR_EQUIPMENT_ID"; break; }
		case ENTITY::DROID_EQUIPMENT_ID: 	{ return "DROID_EQUIPMENT_ID"; break; }
		case ENTITY::FREEZER_EQUIPMENT_ID: 	{ return "FREEZER_EQUIPMENT_ID"; break; }
		case ENTITY::GRAPPLE_EQUIPMENT_ID: 	{ return "GRAPPLE_EQUIPMENT_ID"; break; }
		case ENTITY::SCANER_EQUIPMENT_ID: 	{ return "GRAPPLE_EQUIPMENT_ID"; break; }

		case ENTITY::LAZER_MODULE_ID: 		{ return "LAZER_MODULE_ID"; break; }
		case ENTITY::ROCKET_MODULE_ID: 	{ return "ROCKET_MODULE_ID"; break; }
		case ENTITY::DRIVE_MODULE_ID: 		{ return "DRIVE_MODULE_ID"; break; }
		case ENTITY::RADAR_MODULE_ID: 		{ return "RADAR_MODULE_ID"; break; }
		case ENTITY::BAK_MODULE_ID: 		{ return "BAK_MODULE_ID"; break; }
		case ENTITY::ENERGIZER_MODULE_ID: 	{ return "ENERGIZER_MODULE_ID"; break; }
		case ENTITY::PROTECTOR_MODULE_ID: 	{ return "PROTECTOR_MODULE_ID"; break; }
		case ENTITY::DROID_MODULE_ID: 		{ return "DROID_MODULE_ID"; break; }
		case ENTITY::FREEZER_MODULE_ID: 	{ return "FREEZER_MODULE_ID"; break; }
		case ENTITY::GRAPPLE_MODULE_ID: 	{ return "GRAPPLE_MODULE_ID"; break; }						
		case ENTITY::SCANER_MODULE_ID: 	{ return "SCANER_MODULE_ID"; break; }	
		
		case ENTITY::GRAVITY_ARTEFACT_ID: 	{ return "GRAVITY_ARTEFACT_ID"; break; }						
		case ENTITY::PROTECTOR_ARTEFACT_ID: 	{ return "PROTECTOR_ARTEFACT_ID"; break; }	
			
		default: { return "TYPE UNKNOWN. fix the bug"; }
	}
}


