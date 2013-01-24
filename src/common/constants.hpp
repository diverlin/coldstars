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

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include "../common/myVector.hpp"

#define LOG_ENABLED 1
#if LOG_ENABLED == 1
	#define GRAPPLE_QUEUE_LOG_ENABLED 0
	#define DRIVECOMPLEX_LOG_ENABLED 0
	#define WEAPONSTARGET_LOG_ENABLED 0
	#define AISCENARIO_LOG_ENABLED 0
	#define AI_LOG_ENABLED 0
	#define SAVELOAD_LOG_ENABLED 0
	#define ENTITY_TRANSACTION_LOG_ENABLED 0
	#define CREATEDESTROY_LOG_ENABLED 0
	#define ITEMINFLUENCE_LOG_ENABLED 0
	#define TEXTURE_MANAGER_LOG_ENABLED 0
	#define GUI_LOG_ENABLED 0
	#define GOD_LOG_ENABLED 1
			
	const int GRAPPLE_QUEUE_LOG_DIP = 1;
	const int DRIVECOMPLEX_LOG_DIP = 1;
	const int WEAPONSTARGET_LOG_DIP = 1;
	const int ENTITY_TRANSACTION_LOG_DIP = 1;
	const int AISCENARIO_LOG_DIP = 2;
	const int AI_LOG_DIP = 2;
	const int SAVELOAD_LOG_DIP = 1;
	const int CREATEDESTROY_LOG_DIP = 0;
	const int ITEMINFLUENCE_LOG_DIP = 2;
	const int TEXTURE_MANAGER_LOG_DIP = 0;
	const int GUI_LOG_DIP = 0;
	const int GOD_LOG_DIP = 0;
#endif

#define DEBUG_ITEMDAMAGELOCKVIAGUI 1  // 1 - is locking/unlocking item by right mouse click; 2 - is damaging/undamaging item by right mouse click

const int DAYSINYEAR  = 360;
const int DAYSINMONTH = 31;

const int GOD_REST_IN_DAYS = 5;

// attack / defence / leader / trader / technic / diplomat   
const int SKILLS_NUM = 6;            
const int SKILLS_STRATEGY_WARRIOR[SKILLS_NUM]  = {4,4,1,1,1,1};
const int SKILLS_STRATEGY_PIRAT[SKILLS_NUM]    = {2,2,1,1,1,1};
const int SKILLS_STRATEGY_TRADER[SKILLS_NUM]   = {2,2,1,4,1,1};
const int SKILLS_STRATEGY_DIPLOMAT[SKILLS_NUM] = {1,1,1,1,1,1};

const int SKILLS_STRATEGY_RACE0[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE1[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE2[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE3[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE4[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE6[SKILLS_NUM] = {1,1,1,1,1,1};
const int SKILLS_STRATEGY_RACE7[SKILLS_NUM] = {1,1,1,1,1,1};

const float GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE = 0.1;
const int ASTEROD_GIVEN_EXPIRIENCE = 100;
const int CONTAINER_GIVEN_EXPIRIENCE = 10;

const int SHIPWARRIORS_PER_PLANET_MIN = 1;
const int SHIPWARRIORS_PER_PLANET_MAX = 5;

const int SATELLITEWARRIORS_PER_PLANET_MIN = 1;
const int SATELLITEWARRIORS_PER_PLANET_MAX = 1;

enum GAME_MODE
{ 
	NORMAL_RUN=0,
	SIMPLE_RUN,
	CRASH_TEST
};

enum CAMERADIRECTION
{
	NONE, LEFT, RIGHT, UP, DOWN
};

const float AMMO_PRICE_RATE = 0.01f;

const int STARSPAK_TURN_THRESHOLD_MIN = 5;
const int STARSPAK_TURN_THRESHOLD_MAX = 15;

const int HIBERNATION_ENERGY_THRESHOLD = 500;
const int SCROLL_BORDER_OFFSET = 10;
        
const double NO_DELAY = 0.0f;
const int NO_ADDITIONAL_INFO = 0;

const std::string GAME_TITLE = "cold star V0.0.4.61 (SFML/C++)";

const float RADAR_SCALE = 1/50.0;

const float REPAIR_ITEM_PRICE_RATE = 0.1f;
const float REPAIR_VEHICLEKORPUS_PRICE_RATE = 0.01f;

const int TURN_TIME = 150;  //turn time, depends on game fps

const int COLLISION_RADIUS_FOR_STATIC_COORD = 5;

const int VISIBLE_DISTANCE_WITHOUT_RADAR = 200;
const float MASS_DECREASE_SPEED_RATE = 0.4;

const int SHOCKWAVES_MAX_NUM = 10;

const int PRICE_FUEL = 10;

const vec2f GUI_VEHICLE_INSPACE_OFFSET(-180, 0);
const vec2f GUI_VEHICLE_INANGAR_OFFSET(-180, 0);
const vec2f GUI_VEHICLE_INSTORE_OFFSET(-180, -200);

const vec2f GUI_SKILLS_INSPACE_OFFSET(100, 0);
const vec2f GUI_SKILLS_INANGAR_OFFSET(100, 0);
const vec2f GUI_STORE_OFFSET(-200, 200);

const int NATURELAND_ITEM_SLOT_MIN = 2;
const int NATURELAND_ITEM_SLOT_MAX = 4;

const int STORE_VEHICLE_SLOTS_NUM = 6;
const int STORE_ITEM_SLOTS_NUM = 32;
const int ANGAR_ITEM_SLOTS_NUM = 10;
const int ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM = 6;
const int ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM = 6;
const int ANGAR_VEHICLE_SLOTS_NUM = ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM + ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM;

const int WEAPON_SLOT_MAX_NUM = 9;

namespace PRICE
{
	const int MINERALS_MAX = 10; 
	const int FOOD_MAX = 10; 
	const int MEDICINE_MAX = 10; 
	const int MILITARY_MAX = 10; 
	const int DRUG_MAX = 100; 
	const int EXCLUSIVE_MAX = 100; 
}

const int MINERALS_AMOUNT_MAX = 1000;
const int MINERALS_STARTAMOUNT_MIN = MINERALS_AMOUNT_MAX/100;
const int MINERALS_STARTAMOUNT_MAX = MINERALS_AMOUNT_MAX/10;

const int FOOD_AMOUNT_MAX = 1000;
const int FOOD_STARTAMOUNT_MIN = 10;
const int FOOD_STARTAMOUNT_MAX = FOOD_AMOUNT_MAX/10;

const int MEDICINE_AMOUNT_MAX = 1000;
const int MEDICINE_STARTAMOUNT_MIN = MEDICINE_AMOUNT_MAX/100;
const int MEDICINE_STARTAMOUNT_MAX = MEDICINE_AMOUNT_MAX/10;

const int MILITARY_AMOUNT_MAX = 1000;
const int MILITARY_STARTAMOUNT_MIN = MILITARY_AMOUNT_MAX/100;
const int MILITARY_STARTAMOUNT_MAX = MILITARY_AMOUNT_MAX/10;

const int DRUG_AMOUNT_MAX = 100;
const int DRUG_STARTAMOUNT_MIN = DRUG_AMOUNT_MAX/100;
const int DRUG_STARTAMOUNT_MAX = DRUG_AMOUNT_MAX/10;

const int EXCLUSIVE_AMOUNT_MAX = 100;  
const int EXCLUSIVE_STARTAMOUNT_MIN = EXCLUSIVE_AMOUNT_MAX/100;
const int EXCLUSIVE_STARTAMOUNT_MAX = EXCLUSIVE_AMOUNT_MAX/10;
   
namespace MESH
{
	enum TYPE_ID
	{ 
		SPHERE_NORMAL_ID, SPHERE_DEFORMED_ID 
	};
}  
        
namespace LOG
{
	enum { NONE=0, SCREEN, FILE, SCREENFILE };
}

// trigonomerty
const float PI = 3.141592653589797;
const float HALF_PI = PI/2;
const float RADIAN_TO_DEGREE_RATE = 180 / PI; 
const float DEGREE_TO_RADIAN_RATE = 1/RADIAN_TO_DEGREE_RATE; 
//

const float FLOAT_EPSILON = 0.1;    

const int SIZE_1_AREA = 20*20;
const int SIZE_2_AREA = 40*40;  
const int SIZE_3_AREA = 60*60; 
const int SIZE_4_AREA = 80*80; 
const int SIZE_5_AREA = 100*100;
const int SIZE_6_AREA = 130*130;
const int SIZE_7_AREA = 160*160;
const int SIZE_8_AREA = 200*200;
const int SIZE_9_AREA = 240*240;

enum SIZE
{
        SIZE_1_ID=1, SIZE_2_ID, SIZE_3_ID, SIZE_4_ID, SIZE_5_ID, 
        SIZE_6_ID, SIZE_7_ID, SIZE_8_ID, SIZE_9_ID, SIZE_10_ID 
};

const int NONE_ID = -1;
const int FAIL_ID = 1;
const int SUCCESS_ID = 2;
const int PERFORM_ID = 3;

namespace AIMODEL
{
	enum TYPE_ID
	{
		CONQUEROR_ID,
		RANGER_ID,
		TRADER_ID
	};
}

namespace MACROSCENARIO
{
	enum TYPE_ID
	{
		STARSYSTEMDEFENCE_ID, 
		STARSYSTEMLIBERATION_ID, 
		SELFSAFETY_ID, // replace selfsafety to survival
		
		GOODSTRADING_ID,
		ENUM_LAST
	};
	
} 

namespace MICROSCENARIO
{
	enum TYPE_ID
	{
		DESTROY_ID = MACROSCENARIO::ENUM_LAST,
		DOCKING_ID,		
		LAUNCHING_ID,
		GRAB_ID,
		JUMP_ID,
		EXPLORATION_ID
	
	};
}
 
namespace SKILLS
{
	const int ATTACK_MIN = 1;
	const int DEFENCE_MIN = 1;
	const int LEADER_MIN = 1;
	const int TRADER_MIN = 1;
	const int TECHNIC_MIN = 1;
	const int DIPLOMAT_MIN = 1;
	
	const int ATTACK_MAX = 10;
	const int DEFENCE_MAX = 10;
	const int LEADER_MAX = 10;
	const int TRADER_MAX = 10;
	const int TECHNIC_MAX = 10;
	const int DIPLOMAT_MAX = 10;
	
	const float ATTACK_NORMALIZED_RATE  = ATTACK_MIN/(float)ATTACK_MAX;
	const float DEFENCE_NORMALIZED_RATE = DEFENCE_MIN/(float)DEFENCE_MAX;
		
	const int EXPIRIENCE_THRESHOLD = 1000;
}
namespace COLOR
{
	enum ID
	{
		RED_ID, GREEN_ID, BLUE_ID, YELLOW_ID, GREY_ID
	};
	
	const Color4f COLOR4F_WHITE(1.0, 1.0, 1.0, 1.0);
	const Color4i COLOR4I_WHITE(255, 255, 255, 255);	
	const Color4i COLOR4I_RED_LIGHT(255, 128, 128, 255);
	const Color4i COLOR4I_BLUE_LIGHT(128, 128, 255, 255); 	
		

}


namespace ENTITY 
{
	enum TYPE
	{
		ENUM_START,
		
		VEHICLE_ID, SHIP_ID, SPACESTATION_ID, SATELLITE_ID, 
		NPC_ID, MINERALS_ID, FOOD_ID, MEDICINE_ID, MILITARY_ID, DRUG_ID, EXCLUSIVE_ID, CONTAINER_ID, 
		
		BULLET_ID, ROCKETBULLET_ID,
		
		GALAXY_ID, STARSYSTEM_ID, STAR_ID, ASTEROID_ID, PLANET_ID, BLACKHOLE_ID, BOMB_ID, GOODS_ID, PLAYER_ID, KOSMOPORT_ID, NATURELAND_ID,
		SPACE_ID, HYPER_SPACE_ID,
		GOVERMENT_ID, STORE_ID, SHOP_ID, ANGAR_ID,
		
		VEHICLE_SLOT_ID, VEHICLE_MILITARY_SLOT_ID, VEHICLE_VISITORS_SLOT_ID, ITEM_SLOT_ID, CARGO_SLOT_ID, WEAPON_SLOT_ID, WEAPON_SLOT1_ID, WEAPON_SLOT2_ID, WEAPON_SLOT3_ID, WEAPON_SLOT4_ID, WEAPON_SLOT5_ID, WEAPON_SLOT6_ID, WEAPON_SLOT7_ID, WEAPON_SLOT8_ID, WEAPON_SLOT9_ID,
		GATE_SLOT_ID, REPAIR_SLOT_ID, CHARGE_SLOT_ID,
		
		DRIVE_SLOT_ID, RADAR_SLOT_ID, BAK_SLOT_ID, ENERGIZER_SLOT_ID, PROTECTOR_SLOT_ID, DROID_SLOT_ID, FREEZER_SLOT_ID, GRAPPLE_SLOT_ID, SCANER_SLOT_ID, ARTEFACT_SLOT_ID, 

		EQUIPMENT_ID, MODULE_ID, ARTEFACT_ID,
				
		LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, DRIVE_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID, SCANER_EQUIPMENT_ID,  
		LAZER_MODULE_ID, ROCKET_MODULE_ID, DRIVE_MODULE_ID, RADAR_MODULE_ID, BAK_MODULE_ID, ENERGIZER_MODULE_ID, PROTECTOR_MODULE_ID, DROID_MODULE_ID, FREEZER_MODULE_ID, GRAPPLE_MODULE_ID, SCANER_MODULE_ID,
	
		GRAVITY_ARTEFACT_ID, PROTECTOR_ARTEFACT_ID,
		
		RANGER_ID, WARRIOR_ID, PIRAT_ID, TRADER_ID, DIPLOMAT_ID,
		
		ENUM_END
	};
 
	namespace GALAXY
	{
		const int PARSEC = 200;
				
		const int STARSYSTEM_SEGMENT_WIDTH_NUM = 4;
		const int STARSYSTEM_SEGMENT_HEIGHT_NUM = 3;

		const int STARSYSTEM_INSEGMENT_NUM_MIN = 2;
		const int STARSYSTEM_INSEGMENT_NUM_MAX = 4;

		const int DISTANTSTAR_SIZE_MIN = 3; 
		const int DISTANTSTAR_SIZE_MAX = 15;
	}

	namespace STARSYSTEM
	{
		const int JUMPRADIUS = 1200;
		
		const int PLANET_MIN = 3;
		const int PLANET_MAX = 5;
		
		const int SHIP_INIT_MIN = 4;
		const int SHIP_INIT_MAX = 7;
		const int SHIPENEMY_INIT_MIN = 50;
		const int SHIPENEMY_INIT_MAX = 100;

		const int SPACESTATION_INIT_MIN = 1;
		const int SPACESTATION_INIT_MAX = 3;
			
		const int DISTANT_NEBULA_MIN = 6;
		const int DISTANT_NEBULA_MAX = 8;
		
		const int DISTANT_STAR_MIN = 40;
		const int DISTANT_STAR_MAX = 60;
        
		enum CONDITION
		{
			WAR_ID, CAPTURED_ID, SAFE_ID
		};

	}

	namespace STAR
	{ 
		const int SIZE_MIN_ = 80;
		const int SIZE_MAX_ = 120;
	}

	namespace PLANET
	{
		namespace SURFACE
		{
			enum TYPE
			{
				EARTH_ID, WATER_ID, LAVA_ID, ICE_ID, GAS_ID, ROCK_ID		
			};
		}
	
		const int DISTANCE_MIN = 400;
		const int DISTANCE_MAX = 500;
		const int SIZE_MIN_ = 40;
		const int SIZE_MAX_ = 60;
		const int SPEED_MIN = 40;
		const int SPEED_MAX = 50;
		const int POPULATION_MIN = 6000;
		const int POPULATION_MAX = 20000;
	}

	namespace ASTEROID
	{
		const int SIZE_MIN_ = 6;
		const int SIZE_MAX_ = 12;
	}
	
	namespace SPACESTATION
	{
		const int MASS_MIN = 1000;
		const int MASS_MAX = 2000;
	}
	
	namespace SATELLITE
	{
		const int MASS_MIN = 100;
		const int MASS_MAX = 200;
	}

	namespace ROCKET
	{
		const int ARMOR          = 6;
		const int START_SPEED    = 200;
		const int SPEED_MAX      = 300;
		const float DELTA_SPEED    = 0.5;
		const float ANGULAR_SPEED  = 1.0;
		const int LIFE_TIME = 3 * TURN_TIME;
	}

}

namespace EQUIPMENT
{       
	namespace ENERGIZER
	{
		const int ENERGY_MIN = 2000;
		const int ENERGY_MAX = 10000;
		const float ENERGY_TECHLEVEL_RATE = 0.1f;
		
		const int RESTORATION_MIN = 20;
		const int RESTORATION_MAX = 100;
		const float RESTORATION_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 20;
		const int MASS_MAX = 80;
		const int CONDITION_MIN = 1000;
		const int CONDITION_MAX = 4000;
		
		const float ENERGY_WEIGHT = 0.4;
		const float RESTORATION_WEIGHT = 0.4;
		const float MODULES_NUM_WEIGHT  = 0.2;
	}
	
	namespace FREEZER
	{
		const int FREEZE_MIN = 1;
		const int FREEZE_MAX = 5;
		const float FREEZE_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		const int MASS_MIN = 10;
		const int MASS_MAX = 20;
		const int CONDITION_MIN = 3000;
		const int CONDITION_MAX = 4000;
		
		const float FREEZE_WEIGHT = 0.5;
		const float MODULES_NUM_WEIGHT = 0.5;
	}

	namespace GRAPPLE
	{
		const int STRENGTH_MIN = 6;
		const int STRENGTH_MAX = 50;
		const float STRENGTH_TECHLEVEL_RATE = 0.1f;
		
		const int RADIUS_MIN = 100;
		const int RADIUS_MAX = 200;
		const float RADIUS_TECHLEVEL_RATE = 0.1f;
				
		const int SPEED_MIN = 100;
		const int SPEED_MAX = 170;
		const float SPEED_TECHLEVEL_RATE = 0.1f;
		
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		const int MASS_MIN = 10;
		const int MASS_MAX = 40;
		const int CONDITION_MIN = 100;
		const int CONDITION_MAX = 1000;
		
		const float STRENGTH_WEIGHT = 0.4;
		const float RADIUS_WEIGHT = 0.3;
		const float SPEED_WEIGHT = 0.2;
		const float MAXNUMITEM_WEIGHT = 0.1;
		const float MODULES_NUM_WEIGHT = 0.1;
	}

	namespace RADAR
	{
		const int RADIUS_MIN = 700;
		const int RADIUS_MAX = 1500;
		const float RADIUS_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
				
		const int MASS_MIN = 10;
		const int MASS_MAX = 50;
		const int CONDITION_MIN = 2000;
		const int CONDITION_MAX = 10000;
		
		const float RADIUS_WEIGHT = 0.6;
		const float MODULES_NUM_WEIGHT = 0.4;
	}

	namespace DRIVE
	{
                const float OVERLOAD_RATE = 1.5f;
                const float OVERLOAD_DETERIORATION_RATE = 4.0f;
                                
		const int SPEED_MIN = 300;   
		const int SPEED_MAX = 400; 
		const float SPEED_TECHLEVEL_RATE = 0.1f;
				
		const int HYPER_MIN = 7;
		const int HYPER_MAX = 20;
		const float HYPER_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 20;
		const int MASS_MAX = 70;
		const int CONDITION_MIN = 500;
		const int CONDITION_MAX = 2000;
		
		const float SPEED_WEIGHT = 0.4;
		const float HYPER_WEIGHT = 0.4;
		const float MODULES_NUM_WEIGHT = 0.2;
	}

	namespace PROTECTOR
	{
		const int PROTECTION_MIN = 3;
		const int PROTECTION_MAX = 30;
		const float PROTECTION_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int CONDITION_MIN = 2000;
		const int CONDITION_MAX = 10000;
		const int MASS_MIN = 20;
		const int MASS_MAX = 80;
		
		const float PROTECTION_WEIGHT = 0.8;
		const float MODULES_NUM_WEIGHT = 0.2;
	}

	namespace BAK
	{
		const int FUEL_MIN = 10;    
		const int FUEL_MAX = 30;
		const float FUEL_TECHLEVEL_RATE = 0.1f;
				    
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 10;
		const int MASS_MAX = 40;
		const int CONDITION_MIN = 30;
		const int CONDITION_MAX = 100;
		
		const float FUEL_WEIGHT = 0.7;
		const float MODULES_NUM_WEIGHT = 0.3;
	}

	namespace DROID
	{
		const int REPAIR_MIN = 1;
		const int REPAIR_MAX = 15;
		const float REPAIR_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 10;
		const int MASS_MAX = 50;
		const int CONDITION_MIN = 300;
		const int CONDITION_MAX = 2000;
		
		const float REPAIR_WEIGHT = 0.8;
		const float MODULES_NUM_WEIGHT = 0.2;
	}

	namespace SCANER
	{
		const int SCAN_MIN = 2;
		const int SCAN_MAX = 40;
		const float SCAN_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 7;
		const int MASS_MAX = 38;
		const int CONDITION_MIN = 30;
		const int CONDITION_MAX = 100;
		
		const float SCAN_WEIGHT = 0.7;
		const float MODULES_NUM_WEIGHT = 0.3;
	}

	namespace LAZER
	{
		const int RADIUS_MIN = 200;
		const int RADIUS_MAX = 400;
		const float RADIUS_TECHLEVEL_RATE = 0.1f;
				
		const int DAMAGE_MIN = 40;
		const int DAMAGE_MAX = 200;
		const float DAMAGE_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 10;
		const int MASS_MAX = 40;
		const int CONDITION_MIN = 100;
		const int CONDITION_MAX = 1000;
		
		const float DAMAGE_WEIGHT = 0.4;
		const float RADIUS_WEIGHT = 0.4;
		const float MODULES_NUM_WEIGHT = 0.2;
	}

	namespace ROCKET
	{
		const int AMMO_MIN = 20;
		const int AMMO_MAX = 40;
		const float AMMO_TECHLEVEL_RATE = 0.1f;
				
		const int RADIUS_MIN = 350;
		const int RADIUS_MAX = 550;
		const float RADIUS_TECHLEVEL_RATE = 0.1f;
				
		const int DAMAGE_MIN = 10;
		const int DAMAGE_MAX = 20;
		const float DAMAGE_TECHLEVEL_RATE = 0.1f;
				
		const int MODULES_NUM_MIN = 0;
		const int MODULES_NUM_MAX = 2;
		
		const int MASS_MIN = 30;
		const int MASS_MAX = 60;
		const int CONDITION_MIN = 100;
		const int CONDITION_MAX = 900;
		
		const float AMMO_WEIGHT = 0.3;
		const float DAMAGE_WEIGHT = 0.3;
		const float RADIUS_WEIGHT = 0.2;
		const float MODULES_NUM_WEIGHT = 0.2;
	}
}

namespace MODULE
{

	namespace ENERGIZER
	{
		const int ENERGY_MIN = 0;
		const int ENERGY_MAX = 25;
		const int RESTORATION_MIN = 0;
		const int RESTORATION_MAX = 25;
	}

	namespace FREEZER
	{
		const int FREEZE_MIN = 1;
		const int FREEZE_MAX = 6;
	}

	namespace GRAPPLE
	{
		const int STRENGTH_MIN = 1;
		const int STRENGTH_MAX = 20;
		const int RADIUS_MIN = 0;
		const int RADIUS_MAX = 200;
		const int SPEED_MIN = 0;
		const int SPEED_MAX = 80;
	}

	namespace RADAR
	{
		const int RADIUS_MIN = 100;
		const int RADIUS_MAX = 1200;
	}

	namespace DRIVE
	{
		const int SPEED_MIN = 0;
		const int SPEED_MAX = 100;
		const int HYPER_MIN = 0;
		const int HYPER_MAX = 7;
	}

	namespace PROTECTOR
	{
		const int PROTECTION_MIN = 0;
		const int PROTECTION_MAX = 20;
	}

	namespace BAK
	{
		const int FUEL_MIN = 0;
		const int FUEL_MAX = 100;
	}
	
	namespace DROID
	{
		const int REPAIR_MIN = 0;
		const int REPAIR_MAX = 10;
	}
	
	namespace SCANER
	{
		const int SCAN_MIN = 0;
		const int SCAN_MAX = 10;
	}

	namespace LAZER
	{
		const int DAMAGE_MIN = 0;
		const int DAMAGE_MAX = 10;
		const int RADIUS_MIN = 0;
		const int RADIUS_MAX = 300;
	}
	
	namespace ROCKET
	{
		const int AMMO_MIN   = 0;
		const int AMMO_MAX   = 10;
		const int DAMAGE_MIN = 0;
		const int DAMAGE_MAX = 6;
		const int RADIUS_MIN = 0;
		const int RADIUS_MAX = 450;
	}
}	

namespace ARTEFACT
{
	namespace GRAVITY
	{
		const int GRAVITYRATE_MIN = 10;
		const int GRAVITYRATE_MAX = 40;		
	}

	namespace PROTECTOR
	{
		const int PROTECTION_MIN = 10;
		const int PROTECTION_MAX = 40;		
	}
}

namespace RACE 
{
	enum TYPE
	{
		R0_ID, R1_ID, R2_ID, R3_ID, R4_ID, R6_ID, R7_ID
	};
};

namespace NAVIGATOR_ACTION
{
	enum TYPE
	{
		NONE_ID, DOCKING_ID, COLLECTING_ID, KEEP_FIRE_DISTANCE_ID, KEEP_CLOSE_ID, KEEP_MIDDLE_ID, KEEP_FAR_ID 
	};
}

namespace SPECIAL_ACTION
{
	enum TYPE
	{
		INITIATE_DOCKING_ID, INITIATE_LAUNCHING_ID, INITIATE_JUMPIN_ID, INITIATE_JUMPOUT_ID
	};
}


namespace TECHLEVEL
{
	enum TYPE
	{
		L0_ID, L1_ID, L2_ID, L3_ID	
	};
}

namespace GUI
{
	const int BAR_HEIGHT = 30;
	const int STORE_SLOTS_INROW = 10;
	
	namespace SLIDER
	{
		enum TYPE
		{
			SLIDER_ID
		};
	}
	
	namespace BUTTON
	{
		enum TYPE
		{
			BUTTON_ID, 
			BUYARMOR_ID, BUYFUEL_ID, GETLAUNCH_ID,		
			WEAPON1_ACTIVATOR_ID, WEAPON2_ACTIVATOR_ID, WEAPON3_ACTIVATOR_ID, WEAPON4_ACTIVATOR_ID, WEAPON5_ACTIVATOR_ID, 
			WEAPON6_ACTIVATOR_ID, WEAPON7_ACTIVATOR_ID, WEAPON8_ACTIVATOR_ID, WEAPON9_ACTIVATOR_ID,
			
			ANGAR_ID, STORE_ID, SHOP_ID, GALAXYMAP_ID, GOVERMENT_ID,
			
			INCREMENT_ATTACK_ID, DECREMENT_ATTACK_ID, INCREMENT_DEFENCE_ID, DECREMENT_DEFENCE_ID, INCREMENT_LEADER_ID,
			DECREMENT_LEADER_ID, INCREMENT_TRADER_ID, DECREMENT_TRADER_ID, INCREMENT_TECHNIC_ID, DECREMENT_TECHNIC_ID,
			INCREMENT_DIPLOMAT_ID, DECREMENT_DIPLOMAT_ID,
			
			SAVE_ID, LOAD_ID,
			
			MINERALS_ID, FOOD_ID, MEDICINE_ID, MILITARY_ID, DRUG_ID, EXCLUSIVE_ID,
			
			SLIDE_ID, ACCEPT_ID, DECLINE_ID,
			
			ACTION_ATTACK_ID, ACTION_PRECISEATTACK_ID, ACTION_SCAN_ID, ACTION_GRAB_ID, ACTION_FOLLOW_ID
		};
		
		namespace SKILLS
		{
			const int BUTTON_WIDTH = 20;
			const int BUTTON_HEIGHT = 14;
		}
	}
	
	namespace SCREEN
	{
		enum TYPE
		{
			ANGAR_ID, STORE_ID, SHOP_ID, GALAXYMAP_ID, GOVERMENT_ID, LAUNCHING_ID
		};
	}
	
	const int ICON_SIZE = 20;
	const int SLIDER_WIDTH = 300;
	const int INSERTED_MODULE_SIZE = 15;

	namespace ITEMSLOT
	{
		const int WIDTH_FOR_SHIP  = 46;
		const int HEIGHT_FOR_SHIP = 49;

		const int WIDTH_FOR_CURSOR  = 46;
		const int HEIGHT_FOR_CURSOR = 49;

		const int WIDTH_FOR_STORE  = 46;
		const int HEIGHT_FOR_STORE = 49;

		const int WIDTH_FOR_ANGAR  = 46;
		const int HEIGHT_FOR_ANGAR = 49;
	}
	
	namespace VEHICLESLOT
	{
		const int WIDTH_FOR_ANGAR  = 46*2.5;
		const int HEIGHT_FOR_ANGAR = 49*2.5;
	}
	
	namespace MAP
	{
		const int BORDER_X = 60;
		const int BORDER_Y = 60;
	}
}

namespace SPACESTATION
{
	enum TYPE
	{
		MILITARY_ID, RESEARCH_ID, PIRAT_ID
	};
}



namespace TEXTURE
{
	enum TEXTURE_TYPE
	{ 
		ANGAR_BACKGROUND_ID, STORE_BACKGROUND_ID, SHOP_BACKGROUND_ID, GOVERMENT_BACKGROUND_ID, 
		NATURELAND_BACKGROUND_ID,
		NEBULA_BACKGROUND_ID, DISTANTSTAR_ID, 
		FACE_ID, 
					
		VEHICLE_SLOT_ID, ITEM_SLOT_ID, TURREL_ID,
	
		SPACESTATION_ID, SATELLITE_ID, SHIP_ID, STAR_ID, PLANET_ID, ATMOSPHERE_ID,
		ASTEROID_ID, MINERAL_ID, CONTAINER_ID, BOMB_ID, BLACKHOLE_ID,
	
		PARTICLE_EFFECT_ID, LAZER_EFFECT_ID, SHIELD_EFFECT_ID, 

	
		DRIVE_EQUIPMENT_ID, LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID, 
		BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, SCANER_EQUIPMENT_ID,
	
		MODULE_ID,
	
		ROCKET_BULLET_ID
	};
} 

namespace GAME
{
	const int WEAPONS_NUM_MAX = 9;
}

#endif

