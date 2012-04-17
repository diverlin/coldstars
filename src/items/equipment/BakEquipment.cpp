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



BakEquipment::BakEquipment(int id)
{
        data_id.type_id    = id;
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::BAK_ID;
        
    	fuel_max_orig = 0;  
    	fuel          = 0;
}
   
/* virtual */
BakEquipment::~BakEquipment() 
{}
		
/* virtual */			
void BakEquipment::UpdatePropetries()
{
    	fuel_max_add = 0;
    	
    	for (unsigned int i = 0; i<modules_vec.size(); i++)
    	{
    		fuel_max_add += ((BakModule*)modules_vec[i])->GetFuelMaxAdd();
    	}
    	
    	fuel_max = fuel_max_orig + fuel_max_add;    	
}

void BakEquipment::CountPrice()
{
    	float fuel_rate          = (float)fuel_max_orig / EQUIPMENT::BAK::FUEL_MIN;
    	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::BAK::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::BAK::FUEL_WEIGHT * fuel_rate + 
    				   EQUIPMENT::BAK::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)data_item.mass / EQUIPMENT::BAK::MASS_MIN;
    	float condition_rate     = (float)condition / data_item.condition_max;

   	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void BakEquipment::UpdateOwnerAbilities()
{
    	slot->GetOwnerVehicle()->UpdateDriveAbility();
    	slot->GetOwnerVehicle()->UpdateJumpAbility(); 
}

void BakEquipment::AddUniqueInfo()
{
    	info.addTitleStr("BAK");
    	info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}


std::string BakEquipment::GetFuelStr()
{
     	if (fuel_max_add == 0)
        	return int2str(fuel_max_orig) + "/" + int2str(fuel);
     	else
        	return int2str(fuel_max_orig) + "+" + int2str(fuel_max_add) + "/" + int2str(fuel);
}

/*virtual*/
void BakEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "bak_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueBakEquipment(save_ptree, root);
}

/*virtual*/
void BakEquipment::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueBakEquipment(load_ptree);
}

/*virtual*/	
void BakEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueBakEquipment();
}

void BakEquipment::SaveDataUniqueBakEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"fuel_max_orig", fuel_max_orig);
        save_ptree.put(root+"fuel", fuel);
}
                
void BakEquipment::LoadDataUniqueBakEquipment(const boost::property_tree::ptree& load_ptree)
{
        fuel_max_orig = load_ptree.get<int>("fuel_max_orig");
        fuel = load_ptree.get<int>("fuel");
}                

void BakEquipment::ResolveDataUniqueBakEquipment()
{}

BakEquipment* GetNewBakEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::BAK_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    	int fuel_max_orig = getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX);

      	ItemCommonData common_data;

    	common_data.modules_num_max = getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    	common_data.mass = getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    	common_data.condition_max = getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        int id = g_ID_GENERATOR.getNextId();
        
    	BakEquipment* bak_equipment = new BakEquipment(id);
        bak_equipment->SetFuelMaxOrig(fuel_max_orig);
        bak_equipment->SetFuel(fuel_max_orig);
        bak_equipment->SetTextureOb(texOb_item);    	
        bak_equipment->SetFunctionalSlotSubTypeId(SLOT::BAK_ID);
        bak_equipment->SetItemCommonData(common_data);
                                
        bak_equipment->UpdatePropetries();
    	bak_equipment->CountPrice();
    	
        EntityManager::Instance().RegisterEntity(bak_equipment);
        
    	return bak_equipment;
}
