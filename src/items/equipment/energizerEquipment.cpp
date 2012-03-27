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


EnergizerEquipment :: EnergizerEquipment(int energy_max_orig, 
					 int restoration_orig)
{
    	this->energy_max_orig  = energy_max_orig;
        this->restoration_orig = restoration_orig;

    	energy = energy_max_orig;
}

EnergizerEquipment :: ~EnergizerEquipment() /* virtual */
{}


int EnergizerEquipment :: getEnergy() const { return energy; }
      		
/* virtual */
void EnergizerEquipment :: updatePropetries()
{
    	energy_max_add  = 0;
    	restoration_add  = 0;
    	
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		energy_max_add  += ((EnergizerModule*)modules_vec[i])->getEnergyMaxAdd();
        	restoration_add += ((EnergizerModule*)modules_vec[i])->getRestorationAdd();    	
    	}
    	
    	energy_max  = energy_max_orig + energy_max_add;
    	restoration = restoration_orig + restoration_add;
}

void EnergizerEquipment :: countPrice()
{
    	float energy_rate          = (float)energy_max_orig / EQUIPMENT::ENERGIZER::ENERGY_MIN;
    	float restoration_rate     = (float)restoration_orig / EQUIPMENT::ENERGIZER::RESTORATION_MIN;
    	float modules_num_rate     = (float)common_data.modules_num_max / EQUIPMENT::ENERGIZER::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::ENERGIZER::ENERGY_WEIGHT * energy_rate + EQUIPMENT::ENERGIZER::RESTORATION_WEIGHT * restoration_rate + EQUIPMENT::ENERGIZER::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / EQUIPMENT::ENERGIZER::MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void EnergizerEquipment :: updateOwnerAbilities()
{
    	slot->getOwnerVehicle()->UpdateEnergyAbility();
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



EnergizerEquipment* getNewEnergizerEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::ENERGIZER_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(ENERGIZER_ITEM_TEXTURE_ID, revision_id)

    	int energy_max_orig  = getRandInt(EQUIPMENT::ENERGIZER::ENERGY_MIN, EQUIPMENT::ENERGIZER::ENERGY_MAX);
    	int restoration_orig = getRandInt(EQUIPMENT::ENERGIZER::RESTORATION_MIN, EQUIPMENT::ENERGIZER::RESTORATION_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max  = getRandInt(EQUIPMENT::ENERGIZER::MODULES_NUM_MIN, EQUIPMENT::ENERGIZER::MODULES_NUM_MAX);
    	common_data.mass             = getRandInt(EQUIPMENT::ENERGIZER::MASS_MIN, EQUIPMENT::ENERGIZER::MASS_MAX);
    	common_data.condition_max    = getRandInt(EQUIPMENT::ENERGIZER::CONDITION_MIN, EQUIPMENT::ENERGIZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::ENERGIZER_ID;
        
    	EnergizerEquipment* energizer_equipment = new EnergizerEquipment(energy_max_orig, restoration_orig);
        
        energizer_equipment->setIdData(data_id);  
        energizer_equipment->setTextureOb(texOb_item);    	
        energizer_equipment->setFunctionalSlotSubTypeId(SLOT::ENERGIZER_ID);
        energizer_equipment->setItemCommonData(common_data);
                
        energizer_equipment->updatePropetries();
    	energizer_equipment->countPrice();
    	
    	return energizer_equipment;
}
