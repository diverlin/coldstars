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


#include "bakEquipment.hpp"

BakEquipment :: BakEquipment()
{}


BakEquipment :: BakEquipment(TextureOb* _pTo_itemTexOb, 
			     int _fuel_max_orig, 
			     EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(BAK_ID, _pTo_itemTexOb, _common_data);

    	fuel_max_orig = _fuel_max_orig;
    	fuel_max_add  = 0;
    	fuel_max      = _fuel_max_orig;
    	fuel          = _fuel_max_orig;

    	updatePropetries();
    	countPrice();
}
   
BakEquipment :: ~BakEquipment()
{}


int BakEquipment :: getFuel() const { return fuel; }

void BakEquipment :: fill()
{
    	fuel = fuel_max;
}
		
				
void BakEquipment :: updatePropetries()
{
    	fuel_max = fuel_max_orig + fuel_max_add;
}

void BakEquipment :: countPrice()
{
    	float fuel_rate          = (float)fuel_max_orig / BAK_FUEL_MIN;
    	float modules_num_rate   = (float)common_data.modules_num_max / BAK_MODULES_NUM_MAX;

    	float effectiveness_rate = BAK_FUEL_WEIGHT * fuel_rate + BAK_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / BAK_MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

   	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void BakEquipment :: updateOwnerPropetries()
{
     	slot->getShip()->updateJumpAbility();
}



void BakEquipment :: addUniqueInfo()
{
    	info.addTitleStr("BAK");
    	info.addNameStr("fuel:");      info.addValueStr( getFuelStr() );
}


std::string BakEquipment :: getFuelStr()
{
     	if (fuel_max_add == 0)
        	return int2str(fuel_max_orig) + "/" + int2str(fuel);
     	else
        	return int2str(fuel_max_orig) + "+" + int2str(fuel_max_add) + "/" + int2str(fuel);
}


bool BakEquipment :: insertModule(BakModule* _bak_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	fuel_max_add += _bak_module->getFuelMaxAdd();
     
        	updatePropetries();
         
        	texOb_modules_pList.push_back(_bak_module->getTexOb());
        	modules_pList.push_back(_bak_module);
        	return true;
    	}
    	else 
        	return false;      
}


BakEquipment* bakEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* _itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.BakEquipment_texOb_pList);    // FAKE TEXTURE OB LIST IS USED HERE
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 
    	int fuel_max_orig = randIntInRange(BAK_FUEL_MIN, BAK_FUEL_MAX);

      EquipmentCommonData _common_data;

    	_common_data.modules_num_max = randIntInRange(BAK_MODULES_NUM_MIN, BAK_MODULES_NUM_MAX);
    	_common_data.mass = randIntInRange(BAK_MASS_MIN, BAK_MASS_MAX);
    	_common_data.condition_max = randIntInRange(BAK_CONDITION_MIN, BAK_CONDITION_MAX) * tech_rate;
    	_common_data.deterioration_rate = 1;

    	BakEquipment* _bak = new BakEquipment(_itemTexOb, fuel_max_orig, _common_data);
    	return _bak;
}
