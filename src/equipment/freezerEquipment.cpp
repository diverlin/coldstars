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


#include "freezerEquipment.h"

FreezerEquipment :: FreezerEquipment()
{}



FreezerEquipment :: FreezerEquipment(TextureOb* _pTo_itemTexOb, int _freeze_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
    CommonForEquipment_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

    type_id = EQUIPMENT_ID;
    subtype_id = FREEZER_ID;

    freeze_orig = _freeze_orig;
    freeze_add  = 0;

    updatePropetries();
    countPrice();
    updateInfo();
}


FreezerEquipment :: ~FreezerEquipment()
{}


void FreezerEquipment :: updatePropetries()
{
     freeze = freeze_orig + freeze_add;
}


void FreezerEquipment :: countPrice()
{
     float freeze_rate          = (float)freeze_orig / FREEZER_FREEZE_MIN;
     float modules_num_rate     = (float)modules_num_max / FREEZER_MODULES_NUM_MAX;

     float effectiveness_rate = FREEZER_FREEZE_WEIGHT * freeze_rate + FREEZER_MODULES_NUM_WEIGHT * modules_num_rate;

     float mass_rate          = (float)mass / FREEZER_MASS_MIN;
     float condition_rate     = (float)condition / condition_max;

     price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void FreezerEquipment :: updateOwnerPropetries()
{
    //     self.owner.updateFreezeAbility()
}

void FreezerEquipment :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "FREEZER";
    info_title_1 = "freeze:";     info_value_1 = returnFreezeStr();

    info_title_2 = "modules:";    info_value_2 = int2str(modules_num_max);
    info_title_3 = "condition:";  info_value_3 = int2str(condition) + "/" + int2str(condition_max);
    info_title_4 = "mass:";       info_value_4 = int2str(mass);
    info_title_5 = "price:";      info_value_5 = int2str(price);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
}
      
std::string FreezerEquipment :: returnFreezeStr()
{
     if (freeze_add == 0)
         return int2str(freeze_orig);
     else
         return int2str(freeze_orig) + "+" + int2str(freeze_add);
}


bool FreezerEquipment :: insertModule(FreezerModule* pTo_freezerModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        freeze_add += pTo_freezerModule->freeze_add;
    
        updatePropetries();
        updateInfo();     // ??
        
        texOb_modules_pList.push_back(pTo_freezerModule->pTo_texOb);
        modules_pList.push_back(pTo_freezerModule);
        return true;
    }
    else
        return false;    
}
      

FreezerEquipment* freezerGenerator(int race_id, int revision_id = -1)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.FreezerEquipment_texOb_pList);    // FAKE TEXTURE OB LIST IS USED HERE
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 

    int freeze_orig     = randIntInRange(FREEZER_FREEZE_MIN, FREEZER_FREEZE_MAX);
    int modules_num_max = randIntInRange(FREEZER_MODULES_NUM_MIN, FREEZER_MODULES_NUM_MAX);

    int mass            = randIntInRange(FREEZER_MASS_MIN, FREEZER_MASS_MAX);
    int condition_max   = randIntInRange(FREEZER_CONDITION_MIN, FREEZER_CONDITION_MAX) * tech_rate;

    int deterioration_rate = 1;

    FreezerEquipment* pTo_freezer = new FreezerEquipment(pTo_itemTexOb,  freeze_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_freezer;
}
