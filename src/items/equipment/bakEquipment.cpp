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



BakEquipment :: BakEquipment(int fuel_max_orig)
{
    	this->fuel_max_orig = fuel_max_orig;
        
    	fuel_max            = fuel_max_orig;
    	fuel                = fuel_max_orig;
}
   
BakEquipment :: ~BakEquipment() /* virtual */
{}


int BakEquipment :: getFuel() const { return fuel; }

void BakEquipment :: fill()
{
    	fuel = fuel_max;
}
		
/* virtual */			
void BakEquipment :: updatePropetries()
{
    	fuel_max_add        = 0;
    	
    	for (unsigned int i = 0; i<modules_vec.size(); i++)
    	{
    		fuel_max_add += ((BakModule*)modules_vec[i])->getFuelMaxAdd();
    	}
    	
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

/* virtual */
void BakEquipment :: updateOwnerAbilities()
{
    	slot->getOwnerVehicle()->UpdateDriveAbility();
    	slot->getOwnerVehicle()->UpdateJumpAbility(); 
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


BakEquipment* getNewBakEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(BAK_ITEM_TEXTURE_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 
    	int fuel_max_orig = getRandInt(BAK_FUEL_MIN, BAK_FUEL_MAX);

      	ItemCommonData common_data;

    	common_data.modules_num_max = getRandInt(BAK_MODULES_NUM_MIN, BAK_MODULES_NUM_MAX);
    	common_data.mass = getRandInt(BAK_MASS_MIN, BAK_MASS_MAX);
    	common_data.condition_max = getRandInt(BAK_CONDITION_MIN, BAK_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT_ID;
        data_id.subtype_id = BAK_EQUIPMENT_ID;
        
    	BakEquipment* bak_equipment = new BakEquipment(fuel_max_orig);
        
        bak_equipment->setIdData(data_id);  
        bak_equipment->setTextureOb(texOb_item);    	
        bak_equipment->setFunctionalSlotSubTypeId(SLOT::BAK);
        bak_equipment->setItemCommonData(common_data);
                
        bak_equipment->updatePropetries();
    	bak_equipment->countPrice();
    	
    	return bak_equipment;
}
