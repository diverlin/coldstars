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


#include "scanerItem.h"

ScanerItem :: ScanerItem()
{}

ScanerItem :: ScanerItem(TextureOb* _pTo_itemTexOb, int _scan_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
    CommonForItems_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

    type_id = EQUIPMENT_ID;
    subtype_id = SCANER_ID;

    scan_orig = _scan_orig;
    scan_add = 0;

    updatePropetries();
    countPrice();
    updateInfo();
}

ScanerItem :: ~ScanerItem()
{}


void ScanerItem :: updatePropetries()
{
     scan = scan_orig + scan_add;
}


void ScanerItem :: countPrice()
{
     float scan_rate          = (float)scan_orig / SCANER_SCAN_MIN;
     float modules_num_rate   = (float)modules_num_max / SCANER_MODULES_NUM_MAX;

     float effectiveness_rate = SCANER_SCAN_WEIGHT * scan_rate + SCANER_MODULES_NUM_WEIGHT * modules_num_rate;

     float mass_rate          = (float)mass / SCANER_MASS_MIN;
     float condition_rate     = (float)condition / condition_max;

     price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void ScanerItem :: updateOwnerPropetries()
{
    //self.owner.updateScanAbility()
}


void ScanerItem :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "SCANER";
    info_title_1 = "scan:";       info_value_1 = returnScanStr();

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

std::string ScanerItem :: returnScanStr()
{
     if (scan_add == 0)
         return int2str(scan_orig);
     else
         return int2str(scan_orig) + "+" + int2str(scan_add);
}

bool ScanerItem :: insertModule(ScanerModule* pTo_scanerModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        scan_add += pTo_scanerModule->scan_add;
    
        updatePropetries();
        updateInfo();     // ??
        
        texOb_modules_pList.push_back(pTo_scanerModule->pTo_texOb);
        modules_pList.push_back(pTo_scanerModule);
        return true;
    }
    else
        return false;     
}


ScanerItem* scanerItemGenerator(int race_id, int revision_id = -1)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.scanerItem_texOb_pList);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(SCANER_ITEM_TEXTURE_ID, revision_id)

    int scan_orig       = randIntInRange(SCANER_SCAN_MIN, SCANER_SCAN_MAX);
    int modules_num_max = randIntInRange(SCANER_MODULES_NUM_MIN, SCANER_MODULES_NUM_MAX);

    int mass            = randIntInRange(SCANER_MASS_MIN, SCANER_MASS_MAX);
    int condition_max   = randIntInRange(SCANER_CONDITION_MIN, SCANER_CONDITION_MAX) * tech_rate;

    int deterioration_rate = 1;

    ScanerItem* pTo_scaner = new ScanerItem(pTo_itemTexOb, scan_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_scaner;
}
