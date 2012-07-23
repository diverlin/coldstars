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

#define LOG_ENABLED 0

float RADAR_SCALE = 1/50.0;
const std::string GAME_TITLE = "cold star V0.0.4.54 (SFML/C++)";

const int TURN_TIME = 150;  //turn time, depends on game fps


const int VISIBLE_DISTANCE_WITHOUT_RADAR = 200;

const int SHOCKWAVESBLACKHOLES_MAX_NUM = 3;
const int SHOCKWAVESEXPLOSION_MAX_NUM = 7;

const int PRICE_FUEL = 10;
const int PRICE_ARMOR = 10;

const vec2i GUI_VEHICLE_INSPACE_OFFSET(-180, 0);
const vec2i GUI_SKILL_INSPACE_OFFSET(100, 0);
const vec2i GUI_VEHICLE_INANGAR_OFFSET(-180, 0);
const vec2i GUI_SKILL_INANGAR_OFFSET(100, 0);
const vec2i GUI_VEHICLE_INSTORE_OFFSET(0, 200);
const vec2i GUI_STORE_OFFSET(0, -100);

namespace PRICE
{
	const int MINERALS_MAX = 10; 
}
const int MINERALS_AMOUNT_MIN = 10;
const int MINERALS_AMOUNT_MAX = 100;
const int FOOD_AMOUNT_MIN = 10;
const int FOOD_AMOUNT_MAX = 100;
const int MEDICINE_AMOUNT_MIN = 10;
const int MEDICINE_AMOUNT_MAX = 100;
const int MILITARY_AMOUNT_MIN = 10;
const int MILITARY_AMOUNT_MAX = 100;
const int DRUG_AMOUNT_MIN = 10;
const int DRUG_AMOUNT_MAX = 100;
const int EXCLUSIVE_AMOUNT_MIN = 10;
const int EXCLUSIVE_AMOUNT_MAX = 100;
        
        
namespace LOG
{
	enum { TOSCREEN, TOFILE, TOSCREENTOFILE };
}

// trigonomerty
const float PI = 3.141592653589797;
const float HALF_PI = PI/2;
const float RADIAN_TO_DEGREE_RATE = 180 / PI; 
//



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
const int SIZE_MIN = SIZE_1;

const int NONE_ID = -1;
const int FAIL_ID = 1;
const int SUCCESS_ID = 2;
const int PERFORM_ID = 3;


namespace MACROSCENARIO
{
	enum TYPE_ID
	{
		STARSYSTEMDEFENCE_ID, 
		STARSYSTEMLIBERATION_ID, 
		SELFSAFETY_ID, // replace selfsafety to survival
		
		ENUM_LAST
	};
	
} 

namespace MICROSCENARIO
{
	enum TYPE_ID
	{
		DESTROY_ID = MACROSCENARIO::TYPE_ID::ENUM_LAST,
		DOCKING_ID,		
		LAUNCHING_ID,
		GRAB_ID,
		JUMP_ID,
	
	};
}
 
namespace SKILL
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
	
	const float ATTACK_NORMALIZED_RATE = ATTACK_MIN/(float)ATTACK_MAX;
	const float DEFENCE_NORMALIZED_RATE = DEFENCE_MIN/(float)DEFENCE_MAX;
		
	const int EXPIRIENCE_THRESHOLD = 1000;
}
namespace COLOR
{
	enum ID
	{
		RED_ID, GREEN_ID, BLUE_ID, YELLOW_ID, GREY_ID
	};
	
	const Color4f DEFAULT4f;
	const Color4i DEFAULT4i;	
}

namespace ITEMSLOT
{
	enum TYPE
	{
		CARGO_ID, GATE_ID, WEAPON_ID, DRIVE_ID, RADAR_ID, BAK_ID, ENERGIZER_ID, PROTECTOR_ID, DROID_ID, FREEZER_ID, GRAPPLE_ID, SCANER_ID 
	};
}

namespace ENTITY 
{
enum TYPE
{
	VEHICLE_ID, SHIP_ID, SPACESTATION_ID, SATELLITE_ID, 
	NPC_ID, ROCKETBULLET_ID, MINERAL_ID, CONTAINER_ID, 
	GALAXY_ID, STARSYSTEM_ID, STAR_ID, ASTEROID_ID, PLANET_ID, BLACKHOLE_ID, BOMB_ID, GOODS_ID, PLAYER_ID, KOSMOPORT_ID, LAND_ID,
	SPACE_ID,
	GOVERMENT_ID, STORE_ID, SHOP_ID, ANGAR_ID, VEHICLESLOT_ID, ITEMSLOT_ID
};

namespace GALAXY
{
const int STARSYSTEM_NUM_MIN = 10;
const int STARSYSTEM_NUM_MAX = 10;

const int DISTANTSTAR_SIZE_MIN = 3; 
const int DISTANTSTAR_SIZE_MAX = 15;
}

namespace STARSYSTEM
{
const int PLANET_MIN = 3;
const int PLANET_MAX = 5;

const int SHIP_INIT_MIN = 3;
const int SHIP_INIT_MAX = 5;
const int ENEMYSHIP_INIT_MIN = 10;
const int ENEMYSHIP_INIT_MAX = 20;
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


namespace TYPE
{       
        enum TYPE
	{
                EQUIPMENT_ID, MODULE_ID
	};        
}

namespace SUBTYPE
{
        enum SUBTYPE
        {
                LAZER_ID, ROCKET_ID, DRIVE_ID, RADAR_ID, BAK_ID, ENERGIZER_ID, PROTECTOR_ID, DROID_ID, FREEZER_ID, GRAPPLE_ID, SCANER_ID  
        };
}


namespace EQUIPMENT
{       
namespace ENERGIZER
{
const int ENERGY_MIN = 2000;
const int ENERGY_MAX = 10000;
const int RESTORATION_MIN = 20;
const int RESTORATION_MAX = 100;
const int MODULES_NUM_MIN = 1;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

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
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)
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
const int RADIUS_MIN = 100;
const int RADIUS_MAX = 200;
const int SPEED_MIN = 150;
const int SPEED_MAX = 250;
const int MAXNUMITEM_MIN = 1;
const int MAXNUMITEM_MAX = 4;
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)
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
const int RADIUS_MIN = 1000; //700
const int RADIUS_MAX = 1500; //1500
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)
const int MASS_MIN = 10;
const int MASS_MAX = 50;
const int CONDITION_MIN = 2000;
const int CONDITION_MAX = 10000;

const float RADIUS_WEIGHT = 0.6;
const float MODULES_NUM_WEIGHT = 0.4;
}

namespace DRIVE
{
const int SPEED_MIN = 130;   
const int SPEED_MAX = 300;   

const int HYPER_MIN = 100 * 20;
const int HYPER_MAX = 400 * 20;
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

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
const int MODULES_NUM_MIN = 1;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int CONDITION_MIN = 2000;
const int CONDITION_MAX = 10000;
const int MASS_MIN = 20;
const int MASS_MAX = 80;

const float PROTECTION_WEIGHT = 0.8;
const float MODULES_NUM_WEIGHT = 0.2;
}

namespace BAK
{
const int FUEL_MIN = 100 * 20;    // *20 - debug
const int FUEL_MAX = 400 * 20;    // *20 - debug
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 1;

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
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

const int MASS_MIN = 10;
const int MASS_MAX = 50;
const int CONDITION_MIN = 80;
const int CONDITION_MAX = 300;

const float REPAIR_WEIGHT = 0.8;
const float MODULES_NUM_WEIGHT = 0.2;
}

namespace SCANER
{
const int SCAN_MIN = 2;
const int SCAN_MAX = 40;
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

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
const int RADIUS_MAX = 500;
const int DAMAGE_MIN = 40;
const int DAMAGE_MAX = 200;
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

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
const int RADIUS_MIN = 350;
const int RADIUS_MAX = 750;
const int DAMAGE_MIN = 2;
const int DAMAGE_MAX = 12;
const int MODULES_NUM_MIN = 0;
const int MODULES_NUM_MAX = 3;   // 2 + 1(hack)

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
const int STRENGTH_MIN = 0;
const int STRENGTH_MAX = 20;
const int RADIUS_MIN = 0;
const int RADIUS_MAX = 200;
const int SPEED_MIN = 0;
const int SPEED_MAX = 80;
const int MAXNUMITEM_MIN = 0;
const int MAXNUMITEM_MAX = 1;
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
const int HYPER_MAX = 100;
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
			INCREMENT_DIPLOMAT_ID, DECREMENT_DIPLOMAT_ID
		};
		
		namespace SKILL
		{
			const int BUTTON_WIDTH = 20;
			const int BUTTON_HEIGHT = 12;
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

	namespace ITEMSLOT
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
		LAND_BACKGROUND_ID,
		NEBULA_BACKGROUND_ID, DISTANTSTAR_ID, 
		FACE_ID, 
					
		VEHICLESLOT_ID, ITEMSLOT_ID, TURREL_ID,
	
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
#endif //CONSTANTS_HPP

