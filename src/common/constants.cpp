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
const int SHIP_PER_SYSTEM_MIN = 4;
const int SHIP_PER_SYSTEM_MAX = 4;
const int ENEMY_SHIP_PER_SYSTEM_MIN = 20;
const int ENEMY_SHIP_PER_SYSTEM_MAX = 30;

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
const int GRAPPLE_RADIUS_MIN = 50;
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
const int RADAR_RADIUS_MIN = 3000; //700
const int RADAR_RADIUS_MAX = 4000; //3000
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


const int CURSOR_ID     = g_TYPE_ID_GENERATOR.getNextId("CURSOR_ID");  

const int STARSYSTEM_ID = g_TYPE_ID_GENERATOR.getNextId("STARSYSTEM_ID");  
const int STAR_ID            = g_TYPE_ID_GENERATOR.getNextId("STAR_ID");  
const int ASTEROID_ID        = g_TYPE_ID_GENERATOR.getNextId("ASTEROID_ID");  
const int PLANET_ID          = g_TYPE_ID_GENERATOR.getNextId("PLANET_ID");  
const int KOSMOPORT_ID       = g_TYPE_ID_GENERATOR.getNextId("KOSMOPORT_ID");  
const int LAND_ID     = g_TYPE_ID_GENERATOR.getNextId("LAND_ID");  

const int GOODS_ID     = g_TYPE_ID_GENERATOR.getNextId("GOODS_ID");
const int MINERAL_ID   = g_TYPE_ID_GENERATOR.getNextId("MINERAL_ID");

const int PLANET_EARTH_SURFACE_ID = g_TYPE_ID_GENERATOR.getNextId("PLANET_EARTH_SURFACE_ID");
const int PLANET_WATER_SURFACE_ID = g_TYPE_ID_GENERATOR.getNextId("PLANET_WATER_SURFACE_ID");
const int PLANET_LAVA_SURFACE_ID = g_TYPE_ID_GENERATOR.getNextId("PLANET_LAVA_SURFACE_ID");
const int PLANET_ICE_SURFACE_ID = g_TYPE_ID_GENERATOR.getNextId("PLANET_ICE_SURFACE_ID");
const int PLANET_GAS_SURFACE_ID = g_TYPE_ID_GENERATOR.getNextId("PLANET_GAS_SURFACE_ID");





////// AI section start
//// global task
//const int DEFEND_SHIP_quest_id           = g_TYPE_ID_GENERATOR.getNextId("DEFEND_SHIP_quest_id");
//const int AREST_SHIP_quest_id            = g_TYPE_ID_GENERATOR.getNextId("AREST_SHIP_quest_id");
//const int TERROR_SHIP_quest_id           = g_TYPE_ID_GENERATOR.getNextId("TERROR_SHIP_quest_id");
//const int TRADE_GOODS_quest_id           = g_TYPE_ID_GENERATOR.getNextId("TRADE_GOODS_quest_id");
//const int DIPLOMACY_VISIT_quest_id       = g_TYPE_ID_GENERATOR.getNextId("DIPLOMACY_VISIT_quest_id");
const int LIBERATION_STARSYSTEM_QUEST_ID = g_TYPE_ID_GENERATOR.getNextId("LIBERATION_STARSYSTEM_QUEST_ID");

//// dynamic tasks (are aded if they are necesary)
//const int TASK_COMPLETED_id              = g_TYPE_ID_GENERATOR.getNextId("TASK_COMPLETED_id");
//const int DESTROY_ASTEROID_task_id       = g_TYPE_ID_GENERATOR.getNextId("DESTROY_ASTEROID_task_id");
//const int HYPER_JUMP_task_id             = g_TYPE_ID_GENERATOR.getNextId("HYPER_JUMP_task_id");
const int SELFCARE_TASK_ID               = g_TYPE_ID_GENERATOR.getNextId("SELFCARE_TASK_ID");
//const int LAUNCHING_task_id              = g_TYPE_ID_GENERATOR.getNextId("LAUNCHING_task_id");
const int LANDING_TASK_ID               = g_TYPE_ID_GENERATOR.getNextId("LANDING_TASK_ID");
//const int GRABBING_MINERAL_task_id       = g_TYPE_ID_GENERATOR.getNextId("GRABBING_MINERAL_task_id");
//const int GRABBING_CONTAINER_task_id     = g_TYPE_ID_GENERATOR.getNextId("GRABBING_CONTAINER_task_id");

//const int REPAIR_NEEDED_id               = g_TYPE_ID_GENERATOR.getNextId("REPAIR_NEEDED_id");
//const int FUEL_NEEDED_id                 = g_TYPE_ID_GENERATOR.getNextId("FUEL_NEEDED_id");
//const int ROCKET_RELOAD_NEEDED_id        = g_TYPE_ID_GENERATOR.getNextId("ROCKET_RELOAD_NEEDED_id");
//const int BUY_NEEDED_id                  = g_TYPE_ID_GENERATOR.getNextId("BUY_NEEDED_id");
//const int SELL_NEEDED_id                 = g_TYPE_ID_GENERATOR.getNextId("SELL_NEEDED_id");
//// end dynamic tasks

const int DESTROY_SHIP_QEST_ID          = g_TYPE_ID_GENERATOR.getNextId("DESTROY_SHIP_QEST_ID");

//const int AREST_REQUEST_task_id          = g_TYPE_ID_GENERATOR.getNextId("AREST_REQUEST_task_id");
//const int TERROR_REQUEST_task_id         = g_TYPE_ID_GENERATOR.getNextId("TERROR_REQUEST_task_id");

//const int FIRE_LOW_task_id               = g_TYPE_ID_GENERATOR.getNextId("FIRE_LOW_task_id");
//const int FIRE_HIGH_task_id              = g_TYPE_ID_GENERATOR.getNextId("FIRE_HIGH_task_id");

//const int FIND_PLACE_TO_SELL_GOODS_task_id = g_TYPE_ID_GENERATOR.getNextId("FIND_PLACE_TO_SELL_GOODS_task_id");
//const int BUY_GOODS_task_id              = g_TYPE_ID_GENERATOR.getNextId("BUY_GOODS_task_id");
//const int SELL_GOODS_task_id             = g_TYPE_ID_GENERATOR.getNextId("SELL_GOODS_task_id");
////// END AI ssection






//// TEXTURE TYPES 
const int SLOT_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("SLOT_TEXTURE_ID"); 
const int TURREL_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("TURREL_TEXTURE_ID"); 

// SLOTS ID
const int SLOT_ID           = g_TYPE_ID_GENERATOR.getNextId("SLOT_ID");
const int UNIVERSAL_SLOT_ID = g_TYPE_ID_GENERATOR.getNextId("UNIVERSAL_SLOT_ID");
const int WEAPON_SLOT_ID    = g_TYPE_ID_GENERATOR.getNextId("WEAPON_SLOT_ID");
const int GATE_SLOT_ID      = g_TYPE_ID_GENERATOR.getNextId("GATE_SLOT_ID");

const int EQUIPMENT_ID   = g_TYPE_ID_GENERATOR.getNextId("EQUIPMENT_ID");
const int MODULE_ID = g_TYPE_ID_GENERATOR.getNextId("MODULE_ID");

 
//#define LAZER_ID 5
const int LAZER_ID   = g_TYPE_ID_GENERATOR.getNextId("LAZER_ID"); 
const int ROCKET_ID  = g_TYPE_ID_GENERATOR.getNextId("ROCKET_ID");

const int DRIVE_ID = g_TYPE_ID_GENERATOR.getNextId("DRIVE_ID");
const int RADAR_ID = g_TYPE_ID_GENERATOR.getNextId("RADAR_ID");
const int BAK_ID = g_TYPE_ID_GENERATOR.getNextId("BAK_ID");
const int ENERGIZER_ID = g_TYPE_ID_GENERATOR.getNextId("ENERGIZER_ID");
const int PROTECTOR_ID = g_TYPE_ID_GENERATOR.getNextId("PROTECTOR_ID");
const int DROID_ID = g_TYPE_ID_GENERATOR.getNextId("DROID_ID");
const int FREEZER_ID = g_TYPE_ID_GENERATOR.getNextId("DROID_ID");
const int GRAPPLE_ID = g_TYPE_ID_GENERATOR.getNextId("GRAPPLE_ID");
const int SCANER_ID = g_TYPE_ID_GENERATOR.getNextId("SCANER_ID");


const int ROCKET_BULLET_ID = g_TYPE_ID_GENERATOR.getNextId("ROCKET_BULLET_ID");


// TEXTURES ID
const int SPUTNIK_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("SPUTNIK_TEXTURE_ID"); 
const int SHIP_TEXTURE_ID          = g_TYPE_ID_GENERATOR.getNextId("SHIP_TEXTURE_ID");
const int STAR_TEXTURE_ID          = g_TYPE_ID_GENERATOR.getNextId("STAR_TEXTURE_ID"); 
const int NEBULA_TEXTURE_ID        = g_TYPE_ID_GENERATOR.getNextId("NEBULA_TEXTURE_ID"); 
const int PLANET_TEXTURE_ID        = g_TYPE_ID_GENERATOR.getNextId("PLANET_TEXTURE_ID"); 
const int ATMOSPHERE_TEXTURE_ID    = g_TYPE_ID_GENERATOR.getNextId("ATMOSPHERE_TEXTURE_ID"); 
const int LAND_BG_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("LAND_BG_TEXTURE_ID"); 

const int ANGAR_BG_TEXTURE_ID      = g_TYPE_ID_GENERATOR.getNextId("ANGAR_BG_TEXTURE_ID"); 
const int STORE_BG_TEXTURE_ID      = g_TYPE_ID_GENERATOR.getNextId("STORE_BG_TEXTURE_ID");
const int SHOP_BG_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("SHOP_BG_TEXTURE_ID"); 
const int GOVERMENT_BG_TEXTURE_ID  = g_TYPE_ID_GENERATOR.getNextId("GOVERMENT_BG_TEXTURE_ID"); 

const int PARTICLE_TEXTURE_ID      = g_TYPE_ID_GENERATOR.getNextId("PARTICLE_TEXTURE_ID"); 
const int DISTANTSTAR_TEXTURE_ID   = g_TYPE_ID_GENERATOR.getNextId("DISTANTSTAR_TEXTURE_ID"); 
const int LAZER_EFFECT_TEXTURE_ID  = g_TYPE_ID_GENERATOR.getNextId("LAZER_EFFECT_TEXTURE_ID"); 
const int SHIELD_EFFECT_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("SHIELD_EFFECT_TEXTURE_ID");
const int FACE_TEXTURE_ID          = g_TYPE_ID_GENERATOR.getNextId("FACE_TEXTURE_ID"); 
const int ASTEROID_TEXTURE_ID      = g_TYPE_ID_GENERATOR.getNextId("ASTEROID_TEXTURE_ID"); 
const int MINERAL_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("MINERAL_TEXTURE_ID"); 
const int CONTAINER_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("CONTAINER_TEXTURE_ID"); 
const int BOMB_TEXTURE_ID          = g_TYPE_ID_GENERATOR.getNextId("BOMB_TEXTURE_ID"); 
const int BLACKHOLE_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("BLACKHOLE_TEXTURE_ID"); 


//// TEXTURES FOR ITEMS
const int DRIVE_ITEM_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("DRIVE_ITEM_TEXTURE_ID"); 
const int LAZER_ITEM_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("LAZER_ITEM_TEXTURE_ID");
const int ROCKET_ITEM_TEXTURE_ID    = g_TYPE_ID_GENERATOR.getNextId("ROCKET_ITEM_TEXTURE_ID"); 
const int TORPED_ITEM_TEXTURE_ID    = g_TYPE_ID_GENERATOR.getNextId("TORPED_ITEM_TEXTURE_ID"); 
const int PROTECTOR_ITEM_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("PROTECTOR_ITEM_TEXTURE_ID"); 
const int DROID_ITEM_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("DROID_ITEM_TEXTURE_ID"); 
const int GRAPPLE_ITEM_TEXTURE_ID   = g_TYPE_ID_GENERATOR.getNextId("GRAPPLE_ITEM_TEXTURE_ID"); 
const int BAK_ITEM_TEXTURE_ID       = g_TYPE_ID_GENERATOR.getNextId("BAK_ITEM_TEXTURE_ID"); 
const int ENERGYBLOCK_ITEM_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("ENERGYBLOCK_ITEM_TEXTURE_ID"); 
const int FREEZER_ITEM_TEXTURE_ID   = g_TYPE_ID_GENERATOR.getNextId("FREEZER_ITEM_TEXTURE_ID"); 
const int RADAR_ITEM_TEXTURE_ID     = g_TYPE_ID_GENERATOR.getNextId("RADAR_ITEM_TEXTURE_ID"); 
const int SCANER_ITEM_TEXTURE_ID    = g_TYPE_ID_GENERATOR.getNextId("SCANER_ITEM_TEXTURE_ID"); 

//// TEXTURES FOR BULLET
const int ROCKET_BULLET_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("ROCKET_BULLET_TEXTURE_ID"); 
const int TORPED_BULLET_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("TORPED_BULLET_TEXTURE_ID"); 

// RACE ID
const int RACE_0_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_0_ID"); //  # texnologi
const int RACE_1_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_1_ID"); //  # voiny
const int RACE_2_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_2_ID"); //  # zhuliki
const int RACE_3_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_3_ID"); //  # humans
const int RACE_4_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_4_ID"); //  # bio

const int RACE_6_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_6_ID"); //  # replikatory
const int RACE_7_ID = g_TYPE_ID_GENERATOR.getNextId("RACE_7_ID"); //  # shadow




const int CONTAINER_ID = g_TYPE_ID_GENERATOR.getNextId("CONTAINER_ID");
const int SHIP_ID = g_TYPE_ID_GENERATOR.getNextId("SHIP_ID");
const int NPC_ID = g_TYPE_ID_GENERATOR.getNextId("NPC_ID");
const int PLAYER_ID = g_TYPE_ID_GENERATOR.getNextId("PLAYER_ID");


// SUBTYPE FOR NPC/SHIP
const int RANGER_ID   = g_TYPE_ID_GENERATOR.getNextId("RANGER_ID"); 
const int WARRIOR_ID  = g_TYPE_ID_GENERATOR.getNextId("WARRIOR_ID"); 
const int PIRAT_ID    = g_TYPE_ID_GENERATOR.getNextId("PIRAT_ID");
const int TRADER_ID   = g_TYPE_ID_GENERATOR.getNextId("TRADER_ID");
const int DIPLOMAT_ID = g_TYPE_ID_GENERATOR.getNextId("DIPLOMAT_ID"); 
std::vector<int> SHIP_SUBTYPE_LIST;    // -- remove

// TECHLEVEL ID
const int TECH_LEVEL_0_ID = g_TYPE_ID_GENERATOR.getNextId("TECH_LEVEL_0_ID");
const int TECH_LEVEL_1_ID = g_TYPE_ID_GENERATOR.getNextId("TECH_LEVEL_1_ID");
const int TECH_LEVEL_2_ID = g_TYPE_ID_GENERATOR.getNextId("TECH_LEVEL_2_ID");
const int TECH_LEVEL_3_ID = g_TYPE_ID_GENERATOR.getNextId("TECH_LEVEL_3_ID");
const int TECH_LEVEL_4_ID = g_TYPE_ID_GENERATOR.getNextId("TECH_LEVEL_4_ID");


const int TEXT_BACKGROUND_TEXTURE_ID = g_TYPE_ID_GENERATOR.getNextId("TEXT_BACKGROUND_TEXTURE_ID");


const int INTERFACE_ICON_SIZE = 20;
const int INSERTED_MODULE_SIZE = 15;



//BUTTONS
const int BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("BUTTON_ID");

// screen
const int SCREEN_ANGAR_ID = g_TYPE_ID_GENERATOR.getNextId("SCREEN_ANGAR_ID");
const int SCREEN_STORE_ID = g_TYPE_ID_GENERATOR.getNextId("SCREEN_STORE_ID");
const int SCREEN_SHOP_ID = g_TYPE_ID_GENERATOR.getNextId("SCREEN_SHOP_ID");
const int SCREEN_GALAXYMAP_ID = g_TYPE_ID_GENERATOR.getNextId("SCREEN_GALAXYMAP_ID");
const int SCREEN_GOVERMENT_ID = g_TYPE_ID_GENERATOR.getNextId("SCREEN_GOVERMENT_ID");

const int REPAIR_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("REPAIR_BUTTON_ID");
const int FUEL_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("FUEL_BUTTON_ID");
const int LAUNCH_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("LAUNCH_BUTTON_ID");


//skill
const int INCREMENT_ATTACK_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_ATTACK_BUTTON_ID");
const int DECREMENT_ATTACK_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_ATTACK_BUTTON_ID");

const int INCREMENT_DEFENCE_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_DEFENCE_BUTTON_ID");
const int DECREMENT_DEFENCE_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_DEFENCE_BUTTON_ID");

const int INCREMENT_LEADER_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_LEADER_BUTTON_ID");
const int DECREMENT_LEADER_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_LEADER_BUTTON_ID");

const int INCREMENT_TRADER_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_TRADER_BUTTON_ID");
const int DECREMENT_TRADER_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_TRADER_BUTTON_ID");

const int INCREMENT_TECHNIC_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_TECHNIC_BUTTON_ID");
const int DECREMENT_TECHNIC_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_TECHNIC_BUTTON_ID");

const int INCREMENT_DIPLOMAT_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("INCREMENT_DIPLOMAT_BUTTON_ID");
const int DECREMENT_DIPLOMAT_BUTTON_ID = g_TYPE_ID_GENERATOR.getNextId("DECREMENT_DIPLOMAT_BUTTON_ID");


const int SPACE_ID = g_TYPE_ID_GENERATOR.getNextId("SPACE_ID");  
//const enum PLACE_ID { SPACE_ID, PLANET_ID};


// -- remove
std::vector<int> RACES_ALL_LIST;
std::vector<int> RACES_GOOD_LIST;
std::vector<int> RACES_EVIL_LIST;
std::vector<int> RACE4_ALLOWED_SUBTYPE_LIST;
// -- remove

