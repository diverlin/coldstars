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


#include "bakItem.h"

BakItem :: BakItem()
{}


BakItem :: BakItem(TextureOb* _pTo_itemTexOb, int _fuel_max_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
    CommonForItems_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

    type_id = EQUIPMENT_ID;
    subtype_id = BAK_ITEM_ID;

    fuel_max_orig = _fuel_max_orig;
    fuel_max_add  = 0;
    fuel_max      = _fuel_max_orig;
    fuel          = _fuel_max_orig;

    updatePropetries();
    countPrice();
    updateInfo();
}
   
BakItem :: ~BakItem()
{}

void BakItem :: updatePropetries()
{
    fuel_max = fuel_max_orig + fuel_max_add;
}

void BakItem :: countPrice()
{
    float fuel_rate          = (float)fuel_max_orig / BAK_FUEL_MIN;
    float modules_num_rate   = (float)modules_num_max / BAK_MODULES_NUM_MAX;

    float effectiveness_rate = BAK_FUEL_WEIGHT * fuel_rate + BAK_MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)mass / BAK_MASS_MIN;
    float condition_rate     = (float)condition / condition_max;

    price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void BakItem :: updateOwnerPropetries()
{
     //self.owner.updateJumpAbility()
}


void BakItem :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "BAK";
    info_title_1 = "fuel:";     info_value_1 = returnFuelStr();

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




std::string BakItem :: returnFuelStr()
{
     if (fuel_max_add == 0)
        return int2str(fuel_max_orig) + "/" + int2str(fuel);
     else
        return int2str(fuel_max_orig) + "+" + int2str(fuel_max_add) + "/" + int2str(fuel);
}


bool BakItem :: insertModule(BakModule* pTo_bakModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        fuel_max_add += pTo_bakModule->fuel_max_add;
     
        updatePropetries();
        updateInfo();     // ??
         
        texOb_modules_pList.push_back(pTo_bakModule->pTo_texOb);
        modules_pList.push_back(pTo_bakModule);
        return true;
    }
    else 
        return false;      
}


BakItem* bakGenerator(int race_id, int revision_id = -1)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.bakItem_texOb_pList);    // FAKE TEXTURE OB LIST IS USED HERE
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 
    int fuel_max_orig = randIntInRange(BAK_FUEL_MIN, BAK_FUEL_MAX);

    int modules_num_max = randIntInRange(BAK_MODULES_NUM_MIN, BAK_MODULES_NUM_MAX);

    int mass = randIntInRange(BAK_MASS_MIN, BAK_MASS_MAX);
    int condition_max = randIntInRange(BAK_CONDITION_MIN, BAK_CONDITION_MAX) * tech_rate;

    int deterioration_rate = 1;

    BakItem* pTo_bak = new BakItem(pTo_itemTexOb, fuel_max_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_bak;
}
