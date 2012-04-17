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


RadarEquipment::RadarEquipment(int id)
{
        data_id.id         = id;
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::RADAR_ID;
        
    	radius_orig = 0;
}

/* virtual */
RadarEquipment::~RadarEquipment() 
{}

/* virtual */
void RadarEquipment::UpdatePropetries()
{
    	radius_add  = 0;
    	
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	radius_add   += ((RadarModule*)modules_vec[i])->GetRadiusAdd();        	
    	}
    	
    	radius = radius_orig + radius_add;
}

void RadarEquipment::CountPrice()
{
    	float radius_rate         = (float)radius_orig / EQUIPMENT::RADAR::RADIUS_MIN;

    	float modules_num_rate    = (float)data_item.modules_num_max / EQUIPMENT::RADAR::MODULES_NUM_MAX;

    	float effectiveness_rate  = EQUIPMENT::RADAR::RADIUS_WEIGHT * radius_rate + EQUIPMENT::RADAR::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate           = (float)data_item.mass / EQUIPMENT::RADAR::MASS_MIN;
    	float condition_rate      = (float)condition / data_item.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void RadarEquipment::UpdateOwnerAbilities()
{
	slot->GetOwnerVehicle()->UpdateRadarAbility();
}
      
void RadarEquipment::AddUniqueInfo()
{
    	info.addTitleStr("RADAR");
    	info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string RadarEquipment::GetRadiusStr()
{
    	if (radius_add == 0)
        	return int2str(radius_orig);
    	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}

/*virtual*/
void RadarEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "radar_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueRadarEquipment(save_ptree, root);
}

/*virtual*/
void RadarEquipment::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueRadarEquipment(load_ptree);
}

/*virtual*/
void RadarEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueRadarEquipment();
}

void RadarEquipment::SaveDataUniqueRadarEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"radius_orig", radius_orig);
}
                
void RadarEquipment::LoadDataUniqueRadarEquipment(const boost::property_tree::ptree& load_ptree)
{
        radius_orig = load_ptree.get<int>("radius_orig");   
}                

void RadarEquipment::ResolveDataUniqueRadarEquipment()
{}

    

RadarEquipment* GetNewRadarEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::RADAR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	int radius_orig     = getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::RADAR::MASS_MIN, EQUIPMENT::RADAR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::RADAR::CONDITION_MIN, EQUIPMENT::RADAR::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        int id    = g_ID_GENERATOR.getNextId();
        
    	RadarEquipment* radar_equipment = new RadarEquipment(id);
        radar_equipment->SetRadiusOrig(radius_orig);
        radar_equipment->SetTextureOb(texOb_item);
        radar_equipment->SetFunctionalSlotSubTypeId(SLOT::RADAR_ID);
        radar_equipment->SetItemCommonData(common_data);
        
 
    	radar_equipment->UpdatePropetries();
    	radar_equipment->CountPrice();

        EntityManager::Instance().RegisterEntity(radar_equipment);
        
    	return radar_equipment;
}

