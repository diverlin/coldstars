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


#include "energizerEquipment.h"

EnergizerEquipment :: EnergizerEquipment()
{}


EnergizerEquipment :: EnergizerEquipment(TextureOb* _itemTexOb, 
					 int _energy_max_orig, 
					 int _restoration_orig, 
					 EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(ENERGIZER_ID, _itemTexOb, _common_data);

    	energy_max_orig = _energy_max_orig;
    	energy_max_add  = 0;
    	energy = _energy_max_orig;

    	restoration_orig = _restoration_orig;
    	restoration_add  = 0;

    	updatePropetries();
    	countPrice();
    	updateInfo();
}

EnergizerEquipment :: ~EnergizerEquipment()
{}


int EnergizerEquipment :: getEnergy() const {  return energy; }
      		

void EnergizerEquipment :: updatePropetries()
{
    	energy_max  = energy_max_orig + energy_max_add;
    	restoration = restoration_orig + restoration_add;
}

void EnergizerEquipment :: countPrice()
{
    	float energy_rate          = (float)energy_max_orig / ENERGIZER_ENERGY_MIN;
    	float restoration_rate     = (float)restoration_orig / ENERGIZER_RESTORATION_MIN;
    	float modules_num_rate     = (float)common_data.modules_num_max / ENERGIZER_MODULES_NUM_MAX;

    	float effectiveness_rate = ENERGIZER_ENERGY_WEIGHT * energy_rate + ENERGIZER_RESTORATION_WEIGHT * restoration_rate + ENERGIZER_MODULES_NUM * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / ENERGIZER_MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void EnergizerEquipment :: updateOwnerPropetries()
{
    	slot->getShip()->updateEnergyAbility();
}


void EnergizerEquipment :: addUniqueInfo()
{
    	info.addTitleStr("ENERGYBLOCK");
    	info.addNameStr("energy:");      info.addValueStr( getEnergyStr() );
    	info.addNameStr("restoration:"); info.addValueStr( getRestorationStr() );
}
     		

std::string EnergizerEquipment :: getEnergyStr()
{
    	if (energy_max_add == 0)
        	return int2str(energy_max_orig) + "/" + int2str(energy);
    	else
        	return int2str(energy_max_orig) + "+" + int2str(energy_max_add) + "/" + int2str(energy);
}

std::string EnergizerEquipment :: getRestorationStr()
{
    	if (restoration_add == 0)
        	return int2str(restoration_orig);
    	else
        	return int2str(restoration_orig) + "+" + int2str(restoration_add);
}

bool EnergizerEquipment :: insertModule(EnergizerModule* _energizer_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	energy_max_add  += _energizer_module->getEnergyMaxAdd();
        	restoration_add += _energizer_module->getRestorationAdd();
        
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_energizer_module->getTexOb());
        	modules_pList.push_back(_energizer_module);
        	return true;
    	}
    	else
        	return false;    
}


EnergizerEquipment* energizerEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.energyBlockItem_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(ENERGIZER_ITEM_TEXTURE_ID, revision_id)

    	int energy_max_orig  = randIntInRange(ENERGIZER_ENERGY_MIN, ENERGIZER_ENERGY_MAX);
    	int restoration_orig = randIntInRange(ENERGIZER_RESTORATION_MIN, ENERGIZER_RESTORATION_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max  = randIntInRange(ENERGIZER_MODULES_NUM_MIN, ENERGIZER_MODULES_NUM_MAX);
    	common_data.mass             = randIntInRange(ENERGIZER_MASS_MIN, ENERGIZER_MASS_MAX);
    	common_data.condition_max    = randIntInRange(ENERGIZER_CONDITION_MIN, ENERGIZER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	EnergizerEquipment* energizer_equipment = new EnergizerEquipment(itemTexOb, energy_max_orig, restoration_orig, common_data);
    	return energizer_equipment;
}
