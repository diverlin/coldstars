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


DroidEquipment::DroidEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = SUBTYPE::DROID_ID; 
        
    	repair_orig = 0;
}

/* virtual */
DroidEquipment::~DroidEquipment() 
{}

/* virtual */
void DroidEquipment::UpdatePropetries()
{
    	repair_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		repair_add += ((DroidModule*)modules_vec[i])->GetRepairAdd();    	
    	}
    	
     	repair = repair_orig + repair_add;
}

void DroidEquipment::CountPrice()
{
     	float repair_rate        = (float)repair_orig / EQUIPMENT::DROID::REPAIR_MIN;
     	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::DROID::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::DROID::REPAIR_WEIGHT * repair_rate + 
     				    EQUIPMENT::DROID::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::DROID::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void DroidEquipment::AddUniqueInfo()
{
    	info.addTitleStr("DROID");
   	info.addNameStr("repair:");     info.addValueStr(GetRepairStr());
}
     		
     		
std::string DroidEquipment::GetRepairStr()
{
    	if (repair_add == 0)
        	return int2str(repair_orig);
    	else
        	return int2str(repair_orig) + "+" + int2str(repair_add);
}

/*virtual*/
void DroidEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "droid_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueDroidEquipment(save_ptree, root);
}

/*virtual*/
void DroidEquipment::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueDroidEquipment(load_ptree);
}

/*virtual*/
void DroidEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueDroidEquipment();
}

void DroidEquipment::SaveDataUniqueDroidEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"repair_orig", repair_orig);
}
                
void DroidEquipment::LoadDataUniqueDroidEquipment(const boost::property_tree::ptree& load_ptree)
{
        repair_orig = load_ptree.get<int>("repair_orig");
}                

void DroidEquipment::ResolveDataUniqueDroidEquipment()
{}


DroidEquipment* GetNewDroidEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::DROID_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::DROID_EQUIPMENT_ID, revision_id)

    	int repair_orig     = getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        int id    = g_ID_GENERATOR.getNextId();
        
    	DroidEquipment* droid_equipment = new DroidEquipment(id);
        
        droid_equipment->SetRepairOrig(repair_orig);  
        droid_equipment->SetTextureOb(texOb_item);    	
        droid_equipment->SetFunctionalSlotSubTypeId(SLOT::DROID_ID);
        droid_equipment->SetItemCommonData(common_data);
                
                
    	droid_equipment->UpdatePropetries();
    	droid_equipment->CountPrice();
    	
        EntityManager::Instance().RegisterEntity(droid_equipment);
                
    	return droid_equipment;
}

