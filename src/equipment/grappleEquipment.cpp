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


#include "grappleEquipment.h"

GrappleEquipment :: GrappleEquipment()
{}

GrappleEquipment :: GrappleEquipment(TextureOb* _pTo_itemTexOb, int _strength_orig, int _radius_orig, int _speed_orig, int _maxNumItem_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)   // joun strength and speed attributes into one
{
    CommonForEquipment_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

    subtype_id = GRAPPLE_ID;

    //grapple_list = []
    //grapple_remove_queue = []

    strength_orig = _strength_orig;
    strength_add  = 0;

    radius_orig = _radius_orig;
    radius_add  = 0;
    
    speed_orig = _speed_orig;
    speed_add  = 0;

    maxNumItem_orig = _maxNumItem_orig;
    maxNumItem_add  = 0;

    updatePropetries();
    countPrice();
    updateInfo();
}

GrappleEquipment :: ~GrappleEquipment()
{}


void GrappleEquipment :: updatePropetries()
{
    strength   = strength_orig + strength_add;
    radius     = radius_orig + radius_add;
    speed      = speed_orig + speed_add;
    maxNumItem = maxNumItem_orig + maxNumItem_add;
}

void GrappleEquipment :: countPrice()
{
    float strength_rate      = (float)strength_orig / GRAPPLE_STRENGTH_MIN;
    float radius_rate        = (float)radius_orig / GRAPPLE_RADIUS_MIN;
    float speed_rate         = (float)speed_orig / GRAPPLE_SPEED_MIN;
    float maxNumItem_rate    = (float)maxNumItem_orig / GRAPPLE_MAXNUMITEM_MIN;

    float modules_num_rate   = (float)modules_num_max / GRAPPLE_MODULES_NUM_MAX;

    float effectiveness_rate = GRAPPLE_STRENGTH_WEIGHT * strength_rate + GRAPPLE_RADIUS_WEIGHT * radius_rate + GRAPPLE_SPEED_WEIGHT * speed_rate + GRAPPLE_MAXNUMITEM_WEIGHT * maxNumItem_rate + GRAPPLE_MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)mass / GRAPPLE_MASS_MIN;
    float condition_rate     = (float)condition / condition_max;

    price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void GrappleEquipment :: updateOwnerPropetries()
{
    //      self.owner.updateGrabAbility()
}


void GrappleEquipment :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "GRAPPLE";
    info_title_1 = "strength:";    info_value_1 = returnStrengthStr();
    info_title_2 = "radius:";      info_value_2 = returnRadiusStr();
    info_title_3 = "speed:";       info_value_3 = returnSpeedStr();
    info_title_4 = "maxNumItem:";  info_value_4 = returnMaxNumItemStr(); 

    info_title_5 = "modules:";     info_value_5 = int2str(modules_num_max);
    info_title_6 = "condition:";   info_value_6 = int2str(condition) + "/" + int2str(condition_max);
    info_title_7 = "mass:";        info_value_7 = int2str(mass);
    info_title_8 = "price:";       info_value_8 = int2str(price);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
    info_title_pList.push_back(&info_title_6);   info_value_pList.push_back(&info_value_6);
    info_title_pList.push_back(&info_title_7);   info_value_pList.push_back(&info_value_7);
    info_title_pList.push_back(&info_title_8);   info_value_pList.push_back(&info_value_8);
}



std::string GrappleEquipment :: returnStrengthStr()
{
     if (strength_add == 0)
        return int2str(strength_orig);
     else
        return int2str(strength_orig) + "+" + int2str(strength_add);
}

std::string GrappleEquipment :: returnRadiusStr()
{
     if (radius_add == 0)
        return int2str(radius_orig);
     else
        return int2str(radius_orig) + "+" + int2str(radius_add);
}

std::string GrappleEquipment :: returnSpeedStr()
{
     if (speed_add == 0)
        return int2str(speed_orig);
     else
        return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string GrappleEquipment :: returnMaxNumItemStr()
{
     if (maxNumItem_add == 0)
        return int2str(maxNumItem_orig);
     else
        return int2str(maxNumItem_orig) + "+" + int2str(maxNumItem_add);
}



bool GrappleEquipment :: insertModule(GrappleModule* pTo_grappleModule)
{
    if (modules_pList.size() < modules_num_max)
    {
        strength_add += pTo_grappleModule->strength_add;
        radius_add += pTo_grappleModule->radius_add;
        speed_add += pTo_grappleModule->speed_add;
        maxNumItem_add += pTo_grappleModule->maxNumItem_add;
            
        updatePropetries();
        updateInfo();     // ??
        
        texOb_modules_pList.push_back(pTo_grappleModule->pTo_texOb);
        modules_pList.push_back(pTo_grappleModule);
        return true;
    }
    else
        return false;    
}
    


GrappleEquipment* grappleEquipmentGenerator(int race_id, int revision_id)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.GrappleEquipment_texOb_pList);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(GRAPPLE_ITEM_TEXTURE_ID, revision_id) 

    int strength_orig   = randIntInRange(GRAPPLE_STRENGTH_MIN, GRAPPLE_STRENGTH_MAX);
    int radius_orig     = randIntInRange(GRAPPLE_RADIUS_MIN, GRAPPLE_RADIUS_MAX);
    int speed_orig      = randIntInRange(GRAPPLE_SPEED_MIN, GRAPPLE_SPEED_MAX);
    int maxNumItem_orig = randIntInRange(GRAPPLE_MAXNUMITEM_MIN, GRAPPLE_MAXNUMITEM_MAX);
    int modules_num_max = randIntInRange(GRAPPLE_MODULES_NUM_MIN, GRAPPLE_MODULES_NUM_MAX);

    int mass            = randIntInRange(GRAPPLE_MASS_MIN, GRAPPLE_MASS_MAX);
    int condition_max   = randIntInRange(GRAPPLE_CONDITION_MIN, GRAPPLE_CONDITION_MAX) * tech_rate;

    int deterioration_rate = 1;

    GrappleEquipment* pTo_grapple = new GrappleEquipment(pTo_itemTexOb, strength_orig, radius_orig, speed_orig, maxNumItem_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_grapple;
}
