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


#include "driveItem.h"

DriveItem :: DriveItem()
{}

DriveItem :: DriveItem(TextureOb* _pTo_itemTexOb, int _speed_orig, int _hyper_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
     CommonForItems_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

     type_id = EQUIPMENT_ID;
     subtype_id = DRIVE_ITEM_ID;

     speed_orig = _speed_orig;
     speed_add  = 0;

     hyper_orig = _hyper_orig;
     hyper_add  = 0;


     pTo_particleTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList); ;
     particle_num = 5;
     particle_size = 6;
     particle_velocity = 1.2;
     particle_alpha_start = 1.0;
     particle_alpha_end = 0.0;
     particle_d_alpha = 0.05;
 
     updatePropetries();
     countPrice();
     updateInfo();
}

DriveItem :: ~DriveItem()
{}

void DriveItem :: updatePropetries()
{
     speed = speed_orig + speed_add;
     hyper = hyper_orig + hyper_add;
}


void DriveItem :: countPrice()
{
     float speed_rate         = (float)speed_orig / DRIVE_SPEED_MIN;
     float hyper_rate         = (float)hyper_orig / DRIVE_HYPER_MIN;
     float modules_num_rate   = (float)modules_num_max / DRIVE_MODULES_NUM_MAX;

     float effectiveness_rate = DRIVE_SPEED_WEIGHT * speed_rate + DRIVE_HYPER_WEIGHT * hyper_rate + DRIVE_MODULES_NUM_WEIGHT * modules_num_rate;

     float mass_rate          = (float)mass / DRIVE_MASS_MIN;
     float condition_rate     = (float)condition / condition_max;

     price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void DriveItem :: updateOwnerPropetries()
{
    //self.owner.updateDriveAbility()
}

std::string DriveItem :: returnSpeedStr()
{
     if (speed_add == 0)
        return int2str(speed_orig);
     else
        return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string DriveItem :: returnHyperStr()
{
     if (hyper_add == 0)
         return int2str(hyper_orig);
     else
         return int2str(hyper_orig) + "+" + int2str(hyper_add);
}



void DriveItem :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "DRIVE";
    info_title_1 = "speed:";       info_value_1 = returnSpeedStr();
    info_title_2 = "hyper:";       info_value_2 = returnHyperStr();

    info_title_3 = "modules:";    info_value_3 = int2str(modules_num_max);
    info_title_4 = "condition:";  info_value_4 = int2str(condition) + "/" + int2str(condition_max);
    info_title_5 = "mass:";       info_value_5 = int2str(mass);
    info_title_6 = "price:";      info_value_6 = int2str(price);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
    info_title_pList.push_back(&info_title_6);   info_value_pList.push_back(&info_value_6);
}


bool DriveItem :: insertModule(DriveModule* pTo_driveModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        speed_add += pTo_driveModule->speed_add;
        hyper_add += pTo_driveModule->hyper_add;
     
        updatePropetries();
        updateInfo();     // ??
         
        texOb_modules_pList.push_back(pTo_driveModule->pTo_texOb);
        modules_pList.push_back(pTo_driveModule);
        return true;
    }
    else    
        return false;
} 


DriveItem* driveGenerator(int race_id, int revision_id = -1)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.driveItem_texOb_pList);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(DRIVE_ITEM_TEXTURE_ID, revision_id) 

    int speed_orig      = randIntInRange(DRIVE_SPEED_MIN, DRIVE_SPEED_MAX);
    int hyper_orig      = randIntInRange(DRIVE_HYPER_MIN, DRIVE_HYPER_MAX);
    int modules_num_max = randIntInRange(DRIVE_MODULES_NUM_MIN, DRIVE_MODULES_NUM_MAX);

    int mass            = randIntInRange(DRIVE_MASS_MIN, DRIVE_MASS_MAX);
    int condition_max   = randIntInRange(DRIVE_CONDITION_MIN, DRIVE_CONDITION_MAX) * tech_rate;
    int deterioration_rate = 1;

    DriveItem* pTo_drive = new DriveItem(pTo_itemTexOb, speed_orig, hyper_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_drive;
}

