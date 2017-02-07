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


#pragma once

#include <string>
#include <cstdint>
#include <meti/VectorUtils.hpp>
#include <vector>
#include <types/EntityTypes.hpp>
#include <types/GuiTypes.hpp>
#include "Converter.hpp"


namespace CONVERTER
{
    const Converter<glm::vec2, float> RADIUS2FORCE(glm::vec2(10, 500), glm::vec2(1.0, 0.0), 1000);
    const Converter<glm::vec2, float> SIZE2SIZEID(glm::vec2(0, 200), glm::vec2(1.0, 10.0), 1000);
    const Converter<glm::vec2, float> DIST2GRAVITY(glm::vec2(0, 600), glm::vec2(1.0, 0.0), 1000);
}

#define DEBUG_ITEMDAMAGELOCKVIAGUI 1  // 1 - is locking/unlocking item by right mouse click; 2 - is damaging/undamaging item by right mouse click

namespace GUI
{
    const float POS_Z = -2.0;
}
const float ZSIZE = 1;
    
const float DEFAULT_ENTITY_ZPOS = 0.0;
const float CAMERA_POS_Z = 500.0;

const int POPULATION_MIN = 1000;
const int POPULATION_MAX = 4000;


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
const int CONTAINER_GIVEN_EXPIRIENCE = 10;

const int SHIPINIT_PER_PLANET_MIN = 1;
const int SHIPINIT_PER_PLANET_MAX = 5;

const int SATELLITEWARRIORS_PER_PLANET_MIN = 1;
const int SATELLITEWARRIORS_PER_PLANET_MAX = 1;

const unsigned int INITIATE_STARSYSTEM_IVASION_NUM = 3;

enum GAME_MODE
{ 
    NORMAL_RUN=1,
    SIMPLE_RUN,
    CRASH_TEST
};

enum class CAMERADIRECTION
{
    NONE=0, LEFT, RIGHT, UP, DOWN
};

const float AMMO_PRICE_RATE = 0.01f;

const int STARSPAK_TURN_THRESHOLD_MIN = 5;
const int STARSPAK_TURN_THRESHOLD_MAX = 15;

const int HIBERNATION_ENERGY_THRESHOLD = 500;
const int SCROLL_BORDER_OFFSET = 10;
        
const double NO_DELAY = 0.0f;
const int NO_ADDITIONAL_INFO = 0;

const std::string GAME_TITLE = "cold star V0.0.4.64 (SFML/C++)";

const float RADAR_SCALE = 1/50.0;

const float REPAIR_ITEM_PRICE_RATE = 0.1f;
const float REPAIR_VEHICLEKORPUS_PRICE_RATE = 0.01f;

const int TURN_TIME = 150;  //turn time, depends on game fps

const int COLLISION_RADIUS_FOR_STATIC_COORD = 5;

const int VISIBLE_DISTANCE_WITHOUT_RADAR = 200;
const float MASS_DECREASE_SPEED_RATE = 0.004;

const unsigned int SHOCKWAVES_MAX_NUM = 10;

const int PRICE_FUEL = 10;

const glm::vec2 GUI_VEHICLE_INSPACE_OFFSET(-180, 0);
const glm::vec2 GUI_VEHICLE_INANGAR_OFFSET(-180, 0);
const glm::vec2 GUI_VEHICLE_INSTORE_OFFSET(-180, -200);

const glm::vec2 GUI_SKILLS_INSPACE_OFFSET(100, 0);
const glm::vec2 GUI_SKILLS_INANGAR_OFFSET(100, 0);
const glm::vec2 GUI_STORE_OFFSET(-200, 200);

const int NATURELAND_ITEM_SLOT_MIN = 2;
const int NATURELAND_ITEM_SLOT_MAX = 4;

const unsigned int STORE_VEHICLE_SLOTS_NUM = 6;
const unsigned int STORE_ITEM_SLOTS_NUM = 32;

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
   

        


// trigonomerty
const float PI = 3.141592653589797;
const float HALF_PI = PI/2;
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
        SIZE_1_ID=1, SIZE_2_ID, SIZE_3_ID, SIZE_4_ID, SIZE_5_ID, SIZE_6_ID, SIZE_7_ID, SIZE_8_ID, SIZE_9_ID, SIZE_10_ID 
};

const float INCREDIBLY_MAX_FLOAT = 1e10; 

const int FAIL_ID = 1;
const int SUCCESS_ID = 2;
const int PERFORM_ID = 3;

namespace AIMODEL
{
    enum TYPE_ID
    {
        CONQUEROR_ID=1,
        RANGER_ID,
        TRADER_ID
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
    enum id_type
    {
        RED_ID=1, GREEN_ID, BLUE_ID, YELLOW_ID, GREY_ID
    };
    
    const glm::vec4 COLOR4F_WHITE(1.0, 1.0, 1.0, 1.0);
    const glm::ivec4 COLOR4I_WHITE(255, 255, 255, 255);
    const glm::ivec4 COLOR4I_RED_LIGHT(255, 128, 128, 255);
    const glm::ivec4 COLOR4I_BLUE_LIGHT(128, 128, 255, 255);
        

}

namespace EFFECT 
{
    enum TYPE
    {
        EXPLOSION_ID
    };
}

namespace ENTITY 
{
    namespace GALAXY
    {
        const int PARSEC = 200;
                
        const int SECTOR_NUM = 3;

        const int STARSYSTEM_NUM_MIN = 2;
        const int STARSYSTEM_NUM_MAX = 4;

        const int DISTANTSTAR_SIZE_MIN = 3; 
        const int DISTANTSTAR_SIZE_MAX = 15;
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
        const float ENERGY_TECH_RATE = 0.1f;
        
        const int RESTORATION_MIN = 20;
        const int RESTORATION_MAX = 100;
        const float RESTORATION_TECH_RATE = 0.1f;
                
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
        const float FREEZE_TECH_RATE = 0.1f;
                
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
        const float STRENGTH_TECH_RATE = 0.1f;
        
        const int RADIUS_MIN = 100;
        const int RADIUS_MAX = 200;
        const float RADIUS_TECH_RATE = 0.1f;
                
        const int SPEED_MIN = 100;
        const int SPEED_MAX = 170;
        const float SPEED_TECH_RATE = 0.1f;
        
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
        const float RADIUS_TECH_RATE = 0.1f;
                
        const int MODULES_NUM_MIN = 0;
        const int MODULES_NUM_MAX = 2;
                
        const int MASS_MIN = 10;
        const int MASS_MAX = 50;
        const int CONDITION_MIN = 2000;
        const int CONDITION_MAX = 10000;
        
        const float RADIUS_WEIGHT = 0.6;
        const float MODULES_NUM_WEIGHT = 0.4;
    }

//    namespace DRIVE
//    {
//        const float OVERLOAD_RATE = 1.5f;
//        const float OVERLOAD_DETERIORATION_RATE = 4.0f;
                                
//        const float SPEED_MIN = 3.0;
//        const float SPEED_MAX = 4.0;
//        const float SPEED_TECH_RATE = 0.1f;
                
//        const int HYPER_MIN = 7;
//        const int HYPER_MAX = 20;
//        const float HYPER_TECH_RATE = 0.1f;
                
//        const int MODULES_NUM_MIN = 0;
//        const int MODULES_NUM_MAX = 2;
        
//        const int MASS_MIN = 20;
//        const int MASS_MAX = 70;
//        const int CONDITION_MIN = 500;
//        const int CONDITION_MAX = 2000;
        
//        const float SPEED_WEIGHT = 0.4;
//        const float HYPER_WEIGHT = 0.4;
//        const float MODULES_NUM_WEIGHT = 0.2;
//    }

    namespace PROTECTOR
    {
        const int PROTECTION_MIN = 3;
        const int PROTECTION_MAX = 30;
        const float PROTECTION_TECH_RATE = 0.1f;
                
        const int MODULES_NUM_MIN = 0;
        const int MODULES_NUM_MAX = 2;
        
        const int CONDITION_MIN = 2000;
        const int CONDITION_MAX = 10000;
        const int MASS_MIN = 20;
        const int MASS_MAX = 80;
        
        const float PROTECTION_WEIGHT = 0.8;
        const float MODULES_NUM_WEIGHT = 0.2;
    }

//    namespace BAK
//    {
//        const int FUEL_MIN = 10;
//        const int FUEL_MAX = 30;
//        const float FUEL_TECH_RATE = 0.1f;
                    
//        const int MODULES_NUM_MIN = 0;
//        const int MODULES_NUM_MAX = 2;
        
//        const int MASS_MIN = 10;
//        const int MASS_MAX = 40;
//        const int CONDITION_MIN = 30;
//        const int CONDITION_MAX = 100;
        
//        const float FUEL_WEIGHT = 0.7;
//        const float MODULES_NUM_WEIGHT = 0.3;
//    }

//    namespace DROID
//    {
//        const int REPAIR_MIN = 1;
//        const int REPAIR_MAX = 15;
//        const float REPAIR_TECH_RATE = 0.1f;
                
//        const int MODULES_NUM_MIN = 0;
//        const int MODULES_NUM_MAX = 2;
        
//        const int MASS_MIN = 10;
//        const int MASS_MAX = 50;
//        const int CONDITION_MIN = 300;
//        const int CONDITION_MAX = 2000;
        
//        const float REPAIR_WEIGHT = 0.8;
//        const float MODULES_NUM_WEIGHT = 0.2;
//    }

    namespace SCANER
    {
        const int SCAN_MIN = 2;
        const int SCAN_MAX = 40;
        const float SCAN_TECH_RATE = 0.1f;
                
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
        const float RADIUS_TECH_RATE = 0.1f;
                
        const int DAMAGE_MIN = 40;
        const int DAMAGE_MAX = 200;
        const float DAMAGE_TECH_RATE = 0.1f;
                
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
        const float AMMO_TECH_RATE = 0.1f;
                
        const int RADIUS_MIN = 350;
        const int RADIUS_MAX = 550;
        const float RADIUS_TECH_RATE = 0.1f;
                
        const int DAMAGE_MIN = 10;
        const int DAMAGE_MAX = 20;
        const float DAMAGE_TECH_RATE = 0.1f;
                
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

namespace NAVIGATOR_ACTION
{
    enum TYPE
    {
        NONE_ID=0, DOCKING_ID=1, COLLECTING_ID, KEEP_FIRE_DISTANCE_ID, KEEP_CLOSE_ID, KEEP_MIDDLE_ID, KEEP_FAR_ID 
    };
}

namespace GUI
{ 
    const int BAR_HEIGHT = 30;
    const int STORE_SLOTS_INROW = 10;
    
    
    namespace BUTTON
    {
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
            ANGAR_ID=1, STORE_ID, SHOP_ID, GALAXYMAP_ID, GOVERMENT_ID, LAUNCHING_ID
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

namespace GAME
{
    const int WEAPONS_NUM_MAX = 9;
}
