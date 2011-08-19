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


#include "protectorEquipment.h"

ProtectorEquipment :: ProtectorEquipment(TextureOb* _pTo_itemTexOb, int _protection_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
    CommonForEquipment_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);
    
    subtype_id = PROTECTOR_ID;

    protection_orig = _protection_orig;
    protection_add  = 0;

    updatePropetries();
    countPrice();
    updateInfo();
}

ProtectorEquipment :: ~ProtectorEquipment()
{}

 void ProtectorEquipment :: updatePropetries()
{
      protection = protection_orig + protection_add;
}

void ProtectorEquipment :: countPrice()
{
      float protection_rate    = (float)protection_orig / PROTECTOR_PROTECTION_MIN;
      float modules_num_rate   = (float)modules_num_max / PROTECTOR_MODULES_NUM_MAX;

      float effectiveness_rate = PROTECTOR_PROTECTION_WEIGHT * protection_rate + PROTECTOR_MODULES_NUM_WEIGHT * modules_num_rate;

      float mass_rate          = (float)mass / PROTECTOR_MASS_MIN;
      float condition_rate     = (float)condition / condition_max;

      price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void ProtectorEquipment :: updateOwnerPropetries()
{
     //self.owner.updateProtectionAbility()
}


void ProtectorEquipment :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "PROTECTOR";
    info_title_1 = "protection:";  info_value_1 = returnProtectionStr();

    info_title_2 = "modules:";     info_value_2 = int2str(modules_num_max);
    info_title_3 = "condition:";   info_value_3 = int2str(condition) + "/" + int2str(condition_max);
    info_title_4 = "mass:";        info_value_4 = int2str(mass);
    info_title_5 = "price:";       info_value_5 = int2str(price);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
}


std::string ProtectorEquipment :: returnProtectionStr()
{
     if (protection_add == 0)
         return int2str(protection_orig);
     else
         return int2str(protection_orig) + "+" + int2str(protection_add);
}



bool ProtectorEquipment :: insertModule(ProtectorModule* pTo_protectorModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        protection_add += pTo_protectorModule->protection_add;
    
        updatePropetries();
        updateInfo();     // ??
        
        texOb_modules_pList.push_back(pTo_protectorModule->pTo_texOb);
        modules_pList.push_back(pTo_protectorModule);
        return true;
    }
    else
        return false;    
}
    


ProtectorEquipment* protectorGenerator(int race_id, int revision_id = -1)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.ProtectorEquipment_texOb_pList);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(PROTECTOR_ITEM_TEXTURE_ID, revision_id) 

    int protection_orig = randIntInRange(PROTECTOR_PROTECTION_MIN, PROTECTOR_PROTECTION_MAX);
    int modules_num_max = randIntInRange(PROTECTOR_MODULES_NUM_MIN, PROTECTOR_MODULES_NUM_MAX);

    int mass            = randIntInRange(PROTECTOR_MASS_MIN, PROTECTOR_MASS_MAX);
    int condition_max   = randIntInRange(PROTECTOR_CONDITION_MIN, PROTECTOR_CONDITION_MAX) * tech_rate;
    int deterioration_rate = 1;

    ProtectorEquipment* pTo_protector = new ProtectorEquipment(pTo_itemTexOb, protection_orig, modules_num_max, mass, condition_max, deterioration_rate);

    //(*pTo_protector).pTo_shield = new ShieldEffect((*pTo_protector).pTo_shieldTexOb);
    return pTo_protector;
}
