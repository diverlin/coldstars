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


ScanerEquipment::ScanerEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = SUBTYPE::SCANER_ID; 
        
    	scan_orig = 0;
}

/* virtual */
ScanerEquipment::~ScanerEquipment() 
{}

/* virtual */
void ScanerEquipment::UpdatePropetries()
{
        scan_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		scan_add += ((ScanerModule*)modules_vec[i])->GetScanAdd();      	
    	}
    	
     	scan = scan_orig + scan_add;
}


void ScanerEquipment::CountPrice()
{
     	float scan_rate          = (float)scan_orig / EQUIPMENT::SCANER::SCAN_MIN;
     	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::SCANER::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::SCANER::SCAN_WEIGHT * scan_rate + 
     				   EQUIPMENT::SCANER::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::SCANER::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void ScanerEquipment::AddUniqueInfo()
{
    	info.addTitleStr("SCANER");
    	info.addNameStr("scan:");     info.addValueStr(GetScanStr());
}

std::string ScanerEquipment::GetScanStr()
{
     	if (scan_add == 0)
         	return int2str(scan_orig);
     	else
         	return int2str(scan_orig) + "+" + int2str(scan_add);
}


/*virtual*/
void ScanerEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "scaner_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueScanerEquipment(save_ptree, root);
}

/*virtual*/
void ScanerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueScanerEquipment(load_ptree);
}

/*virtual*/
void ScanerEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueScanerEquipment();
}

void ScanerEquipment::SaveDataUniqueScanerEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"scan_orig", scan_orig);
}
                
void ScanerEquipment::LoadDataUniqueScanerEquipment(const boost::property_tree::ptree& load_ptree)
{
        scan_orig = load_ptree.get<int>("scan_orig"); 
}                

void ScanerEquipment::ResolveDataUniqueScanerEquipment()
{}


