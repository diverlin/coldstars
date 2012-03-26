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

const int SCREEN_WIDTH_MIN  = 800;
const int SCREEN_HEIGHT_MIN = 600;

const int g_BPP = 32;
const int g_FPS_LIMIT = 60;
const bool g_VERT_SYNC = true;


const int SCROLL_VELOCITY_MAX = 20;
const int SCROLL_VELOCITY_STEP = 1;

const int TURN_TIME = 150;  //turn time, depends on game fps

const float FLOAT_EPSILON = 0.1;    

const int SIZE_1 = 20;   // 1 - up to 20x20
const int SIZE_2 = 40;   // 2 - up to 40x40
const int SIZE_3 = 60;   // 3 - up to 60x60
const int SIZE_4 = 80;   // 4 - up to 80x80
const int SIZE_5 = 100;  // 5 - up to 100x100
const int SIZE_6 = 130;  // 6 - up to 130x130
const int SIZE_7 = 160;  // 7 - up to 160x160
const int SIZE_8 = 200;  // 8 - up to 200x200
const int SIZE_9 = 240;  // 9 - up to 240x240

const int NONE_ID = -1;

const int MAP_OFFSET_X = 60;
const int MAP_OFFSET_Y = 60;

const int RED_COLOR_ID    = 0;
const int GREEN_COLOR_ID  = 1; 
const int BLUE_COLOR_ID   = 2;
const int YELLOW_COLOR_ID = 3;
const int GREY_COLOR_ID   = 4;


const int STARSYSTEM_TOTAL_NUM = 10;

// ASTEROID
const int ASTEROID_SIZE_MIN = 6;
const int ASTEROID_SIZE_MAX = 12;

// PLANET 
const int PLANET_PER_SYSTEM_MIN = 3;
const int PLANET_PER_SYSTEM_MAX = 5;
const int PLANET_DISTANCE_MIN = 400;
const int PLANET_DISTANCE_MAX = 500;
const int PLANET_SIZE_MIN = 40;
const int PLANET_SIZE_MAX = 60;
const int PLANET_SPEED_MIN = 40;
const int PLANET_SPEED_MAX = 50;
const int PLANET_POPULATION_MIN = 6000;
const int PLANET_POPULATION_MAX = 20000;

// STAR 
const int STAR_SIZE_MIN = 80;
const int STAR_SIZE_MAX = 120;

// SHIP
const int SHIP_PER_SYSTEM_MIN = 3;
const int SHIP_PER_SYSTEM_MAX = 5;
const int ENEMY_SHIP_PER_SYSTEM_MIN = 10;
const int ENEMY_SHIP_PER_SYSTEM_MAX = 20;

// trigonomerty
const float PI = 3.141592653589797;
const float HALF_PI = PI/2;
const float RADIAN_TO_DEGREE_RATE = 180 / PI; 


// ENERGIZER
const int ENERGIZER_ENERGY_MIN = 2000;
const int ENERGIZER_ENERGY_MAX = 10000;
const int ENERGIZER_RESTORATION_MIN = 20;
const int ENERGIZER_RESTORATION_MAX = 100;
const int ENERGIZER_MODULES_NUM_MIN = 1;
const int ENERGIZER_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int ENERGIZER_MASS_MIN = 20;
const int ENERGIZER_MASS_MAX = 80;
const int ENERGIZER_CONDITION_MIN = 1000;
const int ENERGIZER_CONDITION_MAX = 4000;

const float ENERGIZER_ENERGY_WEIGHT = 0.4;
const float ENERGIZER_RESTORATION_WEIGHT = 0.4;
const float ENERGIZER_MODULES_NUM  = 0.2;

const int ENERGIZER_MODULE_ENERGY_MIN = 0;
const int ENERGIZER_MODULE_ENERGY_MAX = 25;
const int ENERGIZER_MODULE_RESTORATION_MIN = 0;
const int ENERGIZER_MODULE_RESTORATION_MAX = 25;

// FREEZER
const int FREEZER_FREEZE_MIN = 1;
const int FREEZER_FREEZE_MAX = 5;
const int FREEZER_MODULES_NUM_MIN = 0;
const int FREEZER_MODULES_NUM_MAX = 3;   // 2 + 1(hack)
const int FREEZER_MASS_MIN = 10;
const int FREEZER_MASS_MAX = 20;
const int FREEZER_CONDITION_MIN = 3000;
const int FREEZER_CONDITION_MAX = 4000;

const float FREEZER_FREEZE_WEIGHT = 0.5;
const float FREEZER_MODULES_NUM_WEIGHT = 0.5;

const int FREEZER_MODULE_FREEZE_MIN = 1;
const int FREEZER_MODULE_FREEZE_MAX = 6;

// GRAPPLE
const int GRAPPLE_STRENGTH_MIN = 6;
const int GRAPPLE_STRENGTH_MAX = 50;
const int GRAPPLE_RADIUS_MIN = 100;
const int GRAPPLE_RADIUS_MAX = 200;
const int GRAPPLE_SPEED_MIN = 150;
const int GRAPPLE_SPEED_MAX = 250;
const int GRAPPLE_MAXNUMITEM_MIN = 1;
const int GRAPPLE_MAXNUMITEM_MAX = 4;
const int GRAPPLE_MODULES_NUM_MIN = 0;
const int GRAPPLE_MODULES_NUM_MAX = 3;   // 2 + 1(hack)
const int GRAPPLE_MASS_MIN = 10;
const int GRAPPLE_MASS_MAX = 40;
const int GRAPPLE_CONDITION_MIN = 100;
const int GRAPPLE_CONDITION_MAX = 1000;

const float GRAPPLE_STRENGTH_WEIGHT = 0.4;
const float GRAPPLE_RADIUS_WEIGHT = 0.3;
const float GRAPPLE_SPEED_WEIGHT = 0.2;
const float GRAPPLE_MAXNUMITEM_WEIGHT = 0.1;
const float GRAPPLE_MODULES_NUM_WEIGHT = 0.1;

const int GRAPPLE_MODULE_STRENGTH_MIN = 0;
const int GRAPPLE_MODULE_STRENGTH_MAX = 20;
const int GRAPPLE_MODULE_RADIUS_MIN = 0;
const int GRAPPLE_MODULE_RADIUS_MAX = 200;
const int GRAPPLE_MODULE_SPEED_MIN = 0;
const int GRAPPLE_MODULE_SPEED_MAX = 80;
const int GRAPPLE_MODULE_MAXNUMITEM_MIN = 0;
const int GRAPPLE_MODULE_MAXNUMITEM_MAX = 1;

// RADAR
const int RADAR_RADIUS_MIN = 1000; //700
const int RADAR_RADIUS_MAX = 1500; //1500
const int RADAR_MODULES_NUM_MIN = 0;
const int RADAR_MODULES_NUM_MAX = 3;   // 2 + 1(hack)
const int RADAR_MASS_MIN = 10;
const int RADAR_MASS_MAX = 50;
const int RADAR_CONDITION_MIN = 2000;
const int RADAR_CONDITION_MAX = 10000;

const float RADAR_RADIUS_WEIGHT = 0.6;
const float RADAR_MODULES_NUM_WEIGHT = 0.4;

const int RADAR_MODULE_RADIUS_MIN = 0;
const int RADAR_MODULE_RADIUS_MAX = 1200;
const int VISIBLE_DISTANCE_WITHOUT_RADAR = 200;


// DRIVE
const int DRIVE_SPEED_MIN = 130;   
const int DRIVE_SPEED_MAX = 300;   
//const int DRIVE_SPEED_MIN = 2000;   // debug
//const int DRIVE_SPEED_MAX = 2000;   // debug

const int DRIVE_HYPER_MIN = 100 * 20;
const int DRIVE_HYPER_MAX = 400 * 20;
const int DRIVE_MODULES_NUM_MIN = 0;
const int DRIVE_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int DRIVE_MASS_MIN = 20;
const int DRIVE_MASS_MAX = 70;
const int DRIVE_CONDITION_MIN = 500;
const int DRIVE_CONDITION_MAX = 2000;

const float DRIVE_SPEED_WEIGHT = 0.4;
const float DRIVE_HYPER_WEIGHT = 0.4;
const float DRIVE_MODULES_NUM_WEIGHT = 0.2;

const int DRIVE_MODULE_SPEED_MIN = 0;
const int DRIVE_MODULE_SPEED_MAX = 100;
const int DRIVE_MODULE_HYPER_MIN = 0;
const int DRIVE_MODULE_HYPER_MAX = 100;


// PROTECTOR
const int PROTECTOR_PROTECTION_MIN = 3;
const int PROTECTOR_PROTECTION_MAX = 30;
const int PROTECTOR_MODULES_NUM_MIN = 0;
const int PROTECTOR_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int PROTECTOR_CONDITION_MIN = 2000;
const int PROTECTOR_CONDITION_MAX = 10000;
const int PROTECTOR_MASS_MIN = 20;
const int PROTECTOR_MASS_MAX = 80;

const float PROTECTOR_PROTECTION_WEIGHT = 0.8;
const float PROTECTOR_MODULES_NUM_WEIGHT = 0.2;

const int PROTECTOR_MODULE_PROTECTION_MIN = 0;
const int PROTECTOR_MODULE_PROTECTION_MAX = 20;


// BAK
const int BAK_FUEL_MIN = 100 * 20;    // *20 - debug
const int BAK_FUEL_MAX = 400 * 20;          // *20 - debug
const int BAK_MODULES_NUM_MIN = 0;
const int BAK_MODULES_NUM_MAX = 1;

const int BAK_MASS_MIN = 10;
const int BAK_MASS_MAX = 40;
const int BAK_CONDITION_MIN = 30;
const int BAK_CONDITION_MAX = 100;

const float BAK_FUEL_WEIGHT = 0.7;
const float BAK_MODULES_NUM_WEIGHT = 0.3;

const int BAK_MODULE_FUEL_MIN = 0;
const int BAK_MODULE_FUEL_MAX = 100;

// DROID
const int DROID_REPAIR_MIN = 1;
const int DROID_REPAIR_MAX = 15;
const int DROID_MODULES_NUM_MIN = 0;
const int DROID_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int DROID_MASS_MIN = 10;
const int DROID_MASS_MAX = 50;
const int DROID_CONDITION_MIN = 80;
const int DROID_CONDITION_MAX = 300;

const float DROID_REPAIR_WEIGHT = 0.8;
const float DROID_MODULES_NUM_WEIGHT = 0.2;

const int DROID_MODULE_REPAIR_MIN = 0;
const int DROID_MODULE_REPAIR_MAX = 10;

// SCANER
const int SCANER_SCAN_MIN = 2;
const int SCANER_SCAN_MAX = 40;
const int SCANER_MODULES_NUM_MIN = 0;
const int SCANER_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int SCANER_MASS_MIN = 7;
const int SCANER_MASS_MAX = 38;
const int SCANER_CONDITION_MIN = 30;
const int SCANER_CONDITION_MAX = 100;

const float SCANER_SCAN_WEIGHT = 0.7;
const float SCANER_MODULES_NUM_WEIGHT = 0.3;

const int SCANER_MODULE_SCAN_MIN = 0;
const int SCANER_MODULE_SCAN_MAX = 10;

// LAZER
const int LAZER_RADIUS_MIN = 200;
const int LAZER_RADIUS_MAX = 500;
const int LAZER_DAMAGE_MIN = 4;
const int LAZER_DAMAGE_MAX = 20;
const int LAZER_MODULES_NUM_MIN = 0;
const int LAZER_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int LAZER_MASS_MIN = 10;
const int LAZER_MASS_MAX = 40;
const int LAZER_CONDITION_MIN = 100;
const int LAZER_CONDITION_MAX = 1000;

const float LAZER_DAMAGE_WEIGHT = 0.4;
const float LAZER_RADIUS_WEIGHT = 0.4;
const float LAZER_MODULES_NUM_WEIGHT = 0.2;

const int LAZER_MODULE_DAMAGE_MIN = 0;
const int LAZER_MODULE_DAMAGE_MAX = 10;
const int LAZER_MODULE_RADIUS_MIN = 0;
const int LAZER_MODULE_RADIUS_MAX = 300;


// ROCKET
const int ROCKET_AMMO_MIN = 20;
const int ROCKET_AMMO_MAX = 40;
const int ROCKET_RADIUS_MIN = 350;
const int ROCKET_RADIUS_MAX = 750;
const int ROCKET_DAMAGE_MIN = 2;
const int ROCKET_DAMAGE_MAX = 12;
const int ROCKET_MODULES_NUM_MIN = 0;
const int ROCKET_MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int ROCKET_MASS_MIN = 30;
const int ROCKET_MASS_MAX = 60;
const int ROCKET_CONDITION_MIN = 100;
const int ROCKET_CONDITION_MAX = 900;

const float ROCKET_AMMO_WEIGHT = 0.3;
const float ROCKET_DAMAGE_WEIGHT = 0.3;
const float ROCKET_RADIUS_WEIGHT = 0.2;
const float ROCKET_MODULES_NUM_WEIGHT = 0.2;


const int ROCKET_MODULE_AMMO_MIN   = 0;
const int ROCKET_MODULE_AMMO_MAX   = 10;
const int ROCKET_MODULE_DAMAGE_MIN = 0;
const int ROCKET_MODULE_DAMAGE_MAX = 6;
const int ROCKET_MODULE_RADIUS_MIN = 0;
const int ROCKET_MODULE_RADIUS_MAX = 450;

const int ROCKET_ARMOR          = 6;
const int ROCKET_START_SPEED    = 200;
const int ROCKET_SPEED_MAX      = 300;
const float ROCKET_DELTA_SPEED    = 0.5;
const float ROCKET_ANGULAR_SPEED  = 1.0;
const int ROCKET_EXISTANCE_TIME = 3 * TURN_TIME;


const int DISTANTSTAR_SIZE_MIN = 3; 
const int DISTANTSTAR_SIZE_MAX = 15;

// SPACESTATION
const int STARBASE_MASS_MIN = 1000;
const int STARBASE_MASS_MAX = 2000;

// SATELLITE
const int SATELLITE_MASS_MIN = 100;
const int SATELLITE_MASS_MAX = 200;



namespace ENTITY 
{
	enum TYPE
	{
		SHIP_ID, NPC_ID, ROCKET_ID, SPACESTATION_ID, SATELLITE_ID, MINERAL_ID, CONTAINER_ID, 
		STARSYSTEM_ID, STAR_ID, ASTEROID_ID, PLANET_ID, BLACKHOLE_ID, BOMB_ID, GOODS_ID, PLAYER_ID, KOSMOPORT_ID, LAND_ID,
		SPACE_ID
	};
};

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
		NONE_ID, DOCKING_ID, COLLECTING_ID, KEEP_CLOSE_ID, KEEP_MIDDLE_ID, KEEP_FAR_ID 
	};
}

namespace SLOT
{
	enum TYPE
	{
		SLOT_ID, 
		CARGO_ID, GATE_ID, WEAPON_ID, DRIVE_ID, RADAR_ID, BAK_ID, ENERGIZER_ID, PROTECTOR_ID, DROID_ID, FREEZER_ID, GRAPPLE_ID, SCANER_ID 
	};
}

namespace EQUIPMENT
{
	enum TYPE
	{
		EQUIPMENT_ID, 
		LAZER_ID, ROCKET_ID, DRIVE_ID, RADAR_ID, BAK_ID, ENERGIZER_ID, PROTECTOR_ID, DROID_ID, FREEZER_ID, GRAPPLE_ID, SCANER_ID
	};	
}

namespace MODULE
{
	enum TYPE
	{
		MODULE_ID, 
		LAZER_ID, ROCKET_ID, DRIVE_ID, RADAR_ID, BAK_ID, ENERGIZER_ID, PROTECTOR_ID, DROID_ID, FREEZER_ID, GRAPPLE_ID, SCANER_ID
	};	
}

namespace CLASS
{
	enum TYPE
	{
		RANGER_ID, WARRIOR_ID, PIRAT_ID, TRADER_ID, DIPLOMAT_ID	
	};
}

/*
namespace QUEST
{
	enum TYPE
	{
		LIBERATION_STARSYSTEM_ID, DESTROY_SHIP_ID	
	};
}

namespace TASK
{
	enum TYPE
	{
		SELFCARE_ID, LANDING_ID, GRABBING_ID
	};
}
*/

namespace PLANET
{
	namespace SURFACE
	{
		enum TYPE
		{
			EARTH_ID, WATER_ID, LAVA_ID, ICE_ID, GAS_ID, ROCK_ID		
		};
	}
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
	namespace BUTTON
	{
		enum TYPE
		{
			BUTTON_ID, 
			GETREPAIR_ID, GETFUEL_ID, GETLAUNCH_ID			
		};
		
		namespace SKILL
		{
			enum TYPE
			{
				INCREMENT_ATTACK_ID, DECREMENT_ATTACK_ID, INCREMENT_DEFENCE_ID, DECREMENT_DEFENCE_ID, INCREMENT_LEADER_ID,
				DECREMENT_LEADER_ID, INCREMENT_TRADER_ID, DECREMENT_TRADER_ID, INCREMENT_TECHNIC_ID, DECREMENT_TECHNIC_ID,
				INCREMENT_DIPLOMAT_ID, DECREMENT_DIPLOMAT_ID
			};
		}
	}
	
	namespace SCREEN
	{
		enum TYPE
		{
			ANGAR_ID, STORE_ID, SHOP_ID, GALAXYMAP_ID, GOVERMENT_ID
		};
	}
	
	const int ICON_SIZE = 20;
	const int INSERTED_MODULE_SIZE = 15;

	namespace SLOT
	{
		const int WIDTH_FOR_SHIP  = 46;
		const int HEIGHT_FOR_SHIP = 49;

		const int WIDTH_FOR_CURSOR  = 46;
		const int HEIGHT_FOR_CURSOR = 49;

		const int WIDTH_FOR_STORE  = 46;
		const int HEIGHT_FOR_STORE = 49;

		const int WIDTH_FOR_ANGAR  = 46*2.5;
		const int HEIGHT_FOR_ANGAR = 49*2.5;
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
		TEXT_BACKGROUND_ID, 
		ANGAR_BACKGROUND_ID, STORE_BACKGROUND_ID, SHOP_BACKGROUND_ID, GOVERMENT_BACKGROUND_ID, 
		LAND_BACKGROUND_ID,
		NEBULA_BACKGROUND_ID, DISTANTSTAR_ID, 
		FACE_ID, 
					
		LANDINGAREA_ID, SLOT_ID, TURREL_ID,
	
		SPACESTATION_ID, SATELLITE_ID, SHIP_ID, STAR_ID, PLANET_ID, ATMOSPHERE_ID,
		ASTEROID_ID, MINERAL_ID, CONTAINER_ID, BOMB_ID, BLACKHOLE_ID, 		
	
		PARTICLE_EFFECT_ID, LAZER_EFFECT_ID, SHIELD_EFFECT_ID, 

	
		DRIVE_EQUIPMENT_ID, LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID, 
		BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, SCANER_EQUIPMENT_ID,
	
		ROCKET_BULLET_ID
	};
} 
 





