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

const float FLOAT_EPSILON = 0.1;    

int const SIZE_1 = 20;   // 1 - up to 20x20
int const SIZE_2 = 40;   // 2 - up to 40x40
int const SIZE_3 = 60;   // 3 - up to 60x60
int const SIZE_4 = 80;   // 4 - up to 80x80
int const SIZE_5 = 100;  // 5 - up to 100x100
int const SIZE_6 = 130;  // 6 - up to 130x130
int const SIZE_7 = 160;  // 7 - up to 160x160
int const SIZE_8 = 200;  // 8 - up to 200x200
int const SIZE_9 = 240;  // 9 - up to 240x240

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




////// AI section start
//// global task
//const int DEFEND_SHIP_quest_id           = g_TYPE_ID_GENERATOR.getNextId("DEFEND_SHIP_quest_id");
//const int AREST_SHIP_quest_id            = g_TYPE_ID_GENERATOR.getNextId("AREST_SHIP_quest_id");
//const int TERROR_SHIP_quest_id           = g_TYPE_ID_GENERATOR.getNextId("TERROR_SHIP_quest_id");
//const int TRADE_GOODS_quest_id           = g_TYPE_ID_GENERATOR.getNextId("TRADE_GOODS_quest_id");
//const int DIPLOMACY_VISIT_quest_id       = g_TYPE_ID_GENERATOR.getNextId("DIPLOMACY_VISIT_quest_id");
//const int LIBERATION_STARSYSTEM_QUEST_ID = g_TYPE_ID_GENERATOR.getNextId("LIBERATION_STARSYSTEM_QUEST_ID");

//// dynamic tasks (are aded if they are necesary)
//const int TASK_COMPLETED_id              = g_TYPE_ID_GENERATOR.getNextId("TASK_COMPLETED_id");
//const int DESTROY_ASTEROID_task_id       = g_TYPE_ID_GENERATOR.getNextId("DESTROY_ASTEROID_task_id");
//const int HYPER_JUMP_task_id             = g_TYPE_ID_GENERATOR.getNextId("HYPER_JUMP_task_id");
//const int SELFCARE_TASK_ID               = g_TYPE_ID_GENERATOR.getNextId("SELFCARE_TASK_ID");
//const int LAUNCHING_task_id              = g_TYPE_ID_GENERATOR.getNextId("LAUNCHING_task_id");
//const int LANDING_TASK_ID               = g_TYPE_ID_GENERATOR.getNextId("LANDING_TASK_ID");
//const int GRABBING_TASK_ID              = g_TYPE_ID_GENERATOR.getNextId("GRABBING_TASK_ID");
//const int GRABBING_GOODS_ID_task_id     = g_TYPE_ID_GENERATOR.getNextId("GRABBING_CONTAINER_task_id");

//const int REPAIR_NEEDED_id               = g_TYPE_ID_GENERATOR.getNextId("REPAIR_NEEDED_id");
//const int FUEL_NEEDED_id                 = g_TYPE_ID_GENERATOR.getNextId("FUEL_NEEDED_id");
//const int ROCKET_RELOAD_NEEDED_id        = g_TYPE_ID_GENERATOR.getNextId("ROCKET_RELOAD_NEEDED_id");
//const int BUY_NEEDED_id                  = g_TYPE_ID_GENERATOR.getNextId("BUY_NEEDED_id");
//const int SELL_NEEDED_id                 = g_TYPE_ID_GENERATOR.getNextId("SELL_NEEDED_id");
//// end dynamic tasks

//const int DESTROY_SHIP_QUEST_ID          = g_TYPE_ID_GENERATOR.getNextId("DESTROY_SHIP_QEST_ID");

//const int AREST_REQUEST_task_id          = g_TYPE_ID_GENERATOR.getNextId("AREST_REQUEST_task_id");
//const int TERROR_REQUEST_task_id         = g_TYPE_ID_GENERATOR.getNextId("TERROR_REQUEST_task_id");

//const int FIRE_LOW_task_id               = g_TYPE_ID_GENERATOR.getNextId("FIRE_LOW_task_id");
//const int FIRE_HIGH_task_id              = g_TYPE_ID_GENERATOR.getNextId("FIRE_HIGH_task_id");

//const int FIND_PLACE_TO_SELL_GOODS_task_id = g_TYPE_ID_GENERATOR.getNextId("FIND_PLACE_TO_SELL_GOODS_task_id");
//const int BUY_GOODS_task_id              = g_TYPE_ID_GENERATOR.getNextId("BUY_GOODS_task_id");
//const int SELL_GOODS_task_id             = g_TYPE_ID_GENERATOR.getNextId("SELL_GOODS_task_id");
////// END AI ssection

enum ENTITY_TYPE
{
	LIBERATION_STARSYSTEM_QUEST_ID, SELFCARE_TASK_ID, LANDING_TASK_ID, GRABBING_TASK_ID, DESTROY_SHIP_QUEST_ID,

	NONE_NAVIGATOR_ACTION_ID, DOCKING_NAVIGATOR_ACTION_ID, COLLECTING_NAVIGATOR_ACTION_ID, FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID, FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID, FOLLOWING_FAR_NAVIGATOR_ACTION_ID, 

	NONE_SLOT_ID, SLOT_ID, CARGO_SLOT_ID,  GATE_SLOT_ID,
	WEAPON_SLOT_ID, DRIVE_SLOT_ID, RADAR_SLOT_ID, BAK_SLOT_ID, ENERGIZER_SLOT_ID, PROTECTOR_SLOT_ID, DROID_SLOT_ID, FREEZER_SLOT_ID, GRAPPLE_SLOT_ID, SCANER_SLOT_ID, 

	EQUIPMENT_ID, LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, DRIVE_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID, SCANER_EQUIPMENT_ID, 
        MODULE_ID,    LAZER_MODULE_ID,    ROCKET_MODULE_ID,    DRIVE_MODULE_ID,    RADAR_MODULE_ID,    BAK_MODULE_ID,    ENERGIZER_MODULE_ID,    PROTECTOR_MODULE_ID,    DROID_MODULE_ID,    FREEZER_MODULE_ID,    GRAPPLE_MODULE_ID,    SCANER_MODULE_ID,
	
	GOODS_ID, MINERAL_ID, ROCKET_BULLET_ID, CONTAINER_ID, BOMB_ID, SHIP_ID, NPC_ID, PLAYER_ID, STARSYSTEM_ID, STAR_ID, ASTEROID_ID, PLANET_ID, KOSMOPORT_ID, LAND_ID, BLACKHOLE_ID, 
	PLANET_EARTH_SURFACE_ID, PLANET_WATER_SURFACE_ID, PLANET_LAVA_SURFACE_ID, PLANET_ICE_SURFACE_ID, PLANET_GAS_SURFACE_ID,
	
	RACE_0_ID, RACE_1_ID, RACE_2_ID, RACE_3_ID, RACE_4_ID, RACE_6_ID, RACE_7_ID,
	
	RANGER_ID, WARRIOR_ID, PIRAT_ID, TRADER_ID, DIPLOMAT_ID,
	
	TECH_LEVEL_0_ID, TECH_LEVEL_1_ID, TECH_LEVEL_2_ID, TECH_LEVEL_3_ID,
	
	BUTTON_ID, REPAIR_BUTTON_ID, FUEL_BUTTON_ID, LAUNCH_BUTTON_ID, 
	INCREMENT_ATTACK_BUTTON_ID, DECREMENT_ATTACK_BUTTON_ID, INCREMENT_DEFENCE_BUTTON_ID, DECREMENT_DEFENCE_BUTTON_ID, INCREMENT_LEADER_BUTTON_ID,
	DECREMENT_LEADER_BUTTON_ID, INCREMENT_TRADER_BUTTON_ID, DECREMENT_TRADER_BUTTON_ID, INCREMENT_TECHNIC_BUTTON_ID, DECREMENT_TECHNIC_BUTTON_ID,
	INCREMENT_DIPLOMAT_BUTTON_ID, DECREMENT_DIPLOMAT_BUTTON_ID,
	
	SCREEN_ANGAR_ID, SCREEN_STORE_ID, SCREEN_SHOP_ID, SCREEN_GALAXYMAP_ID, SCREEN_GOVERMENT_ID,
	
	SPACE_ID, BUNKER_ID, 
	
	CURSOR_ID	
};


enum TEXTURE_TYPE
{ 
	TEXT_BACKGROUND_TEXTURE_ID, 
	
	LANDINGAREA_TEXTURE_ID, SLOT_TEXTURE_ID, TURREL_TEXTURE_ID,
	
	SPUTNIK_TEXTURE_ID, SHIP_TEXTURE_ID, STAR_TEXTURE_ID, NEBULA_TEXTURE_ID, PLANET_TEXTURE_ID, ATMOSPHERE_TEXTURE_ID, LAND_BG_TEXTURE_ID,
	
	ANGAR_BG_TEXTURE_ID, STORE_BG_TEXTURE_ID, SHOP_BG_TEXTURE_ID, GOVERMENT_BG_TEXTURE_ID, 
	
	PARTICLE_TEXTURE_ID, DISTANTSTAR_TEXTURE_ID, LAZER_EFFECT_TEXTURE_ID, SHIELD_EFFECT_TEXTURE_ID, FACE_TEXTURE_ID, 
	
	ASTEROID_TEXTURE_ID, MINERAL_TEXTURE_ID, CONTAINER_TEXTURE_ID, BOMB_TEXTURE_ID, BLACKHOLE_TEXTURE_ID, 
	
	DRIVE_ITEM_TEXTURE_ID, LAZER_ITEM_TEXTURE_ID, ROCKET_ITEM_TEXTURE_ID, TORPED_ITEM_TEXTURE_ID, PROTECTOR_ITEM_TEXTURE_ID, DROID_ITEM_TEXTURE_ID, GRAPPLE_ITEM_TEXTURE_ID, BAK_ITEM_TEXTURE_ID, ENERGYBLOCK_ITEM_TEXTURE_ID, 
	FREEZER_ITEM_TEXTURE_ID, RADAR_ITEM_TEXTURE_ID, SCANER_ITEM_TEXTURE_ID,
	
	ROCKET_BULLET_TEXTURE_ID, TORPED_BULLET_TEXTURE_ID
};
 


const int INTERFACE_ICON_SIZE = 20;
const int INSERTED_MODULE_SIZE = 15;

const int SHIP_SLOT_WIDTH  = 46;
const int SHIP_SLOT_HEIGHT = 49;

const int WEAPON_SLOT_WIDTH  = 46;
const int WEAPON_SLOT_HEIGHT = 49;

const int CURSOR_SLOT_WIDTH  = 46;
const int CURSOR_SLOT_HEIGHT = 49;

const int STORE_SLOT_WIDTH  = 46;
const int STORE_SLOT_HEIGHT = 49;

const int ANGAR_SLOT_WIDTH  = 46*2.5;
const int ANGAR_SLOT_HEIGHT = 49*2.5;


