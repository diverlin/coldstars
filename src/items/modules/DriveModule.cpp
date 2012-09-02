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


DriveModule::DriveModule(int id)
{
	data_id.id         = id;
	data_id.subtype_id = SUBTYPE::DRIVE_ID;
	
     	speed_add = 0;
     	hyper_add = 0;
}

/* virtual */
DriveModule::~DriveModule()
{}
		
/* virtual */
void DriveModule::AddUniqueInfo()
{ 
    	info.addTitleStr("drive module"); 
    	if (speed_add != 0)
    	{ 
    		info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
    	} 
    	
    	if (hyper_add != 0)
    	{ 
    		info.addNameStr("hyper_add:");       info.addValueStr( int2str(hyper_add) );
    	}
}


/*virtual*/
void DriveModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "drive_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueDriveModule(save_ptree, root);
}

/*virtual*/		
void DriveModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueDriveModule(load_ptree);
}
	
/*virtual*/	
void DriveModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueDriveModule();
}

void DriveModule::SaveDataUniqueDriveModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"speed_add", speed_add);
	save_ptree.put(root+"hyper_add", hyper_add);
}

void DriveModule::LoadDataUniqueDriveModule(const boost::property_tree::ptree& load_ptree)
{
	speed_add = load_ptree.get<int>("speed_add");
	hyper_add = load_ptree.get<int>("hyper_add");
}

void DriveModule::ResolveDataUniqueDriveModule()
{}



