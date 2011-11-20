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


BakEquipment :: BakEquipment()
{}


BakEquipment :: BakEquipment(TextureOb* _texOb_item, 
			     int _fuel_max_orig, 
			     EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(BAK_EQUIPMENT_ID, BAK_SLOT_ID, _texOb_item, _common_data);

    	fuel_max_orig = _fuel_max_orig;
    	fuel_max_add  = 0;
    	fuel_max      = _fuel_max_orig;
    	fuel          = _fuel_max_orig;

    	updatePropetries();
    	countPrice();
}
   
BakEquipment :: ~BakEquipment()
{
	for (unsigned int mi = 0; mi<modules_vec.size(); mi++)
	{
		delete modules_vec[mi];
	}
}


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
    	slot->getOwnerShip()->updateDriveAbility();
    	slot->getOwnerShip()->updateJumpAbility(); 
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
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
        	fuel_max_add += _bak_module->getFuelMaxAdd();
     
        	updatePropetries();
         
        	texOb_modules_pList.push_back(_bak_module->getTexOb());
        	modules_vec.push_back(_bak_module);
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

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.BakEquipment_texOb_pList);    // FAKE TEXTURE OB LIST IS USED HERE
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 
    	int fuel_max_orig = getRandInt(BAK_FUEL_MIN, BAK_FUEL_MAX);

      	EquipmentCommonData common_data;

    	common_data.modules_num_max = getRandInt(BAK_MODULES_NUM_MIN, BAK_MODULES_NUM_MAX);
    	common_data.mass = getRandInt(BAK_MASS_MIN, BAK_MASS_MAX);
    	common_data.condition_max = getRandInt(BAK_CONDITION_MIN, BAK_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	BakEquipment* bak_equipment = new BakEquipment(texOb_item, fuel_max_orig, common_data);
    	return bak_equipment;
}
