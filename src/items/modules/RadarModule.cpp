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


RadarModule::RadarModule(int id)
{
        data_id.id         = id;
        data_id.subtype_id = SUBTYPE::RADAR_ID; 
        
     	radius_add = 0;
}

/* virtual */
RadarModule::~RadarModule() 
{}

/* virtual */
void RadarModule::AddUniqueInfo()
{
    	info.addTitleStr("radar module");
    	info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
}

/*virtual*/
void RadarModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "radar_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueRadarModule(save_ptree, root);
}

/*virtual*/		
void RadarModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueRadarModule(load_ptree);
}
	
/*virtual*/	
void RadarModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueRadarModule();
}

void RadarModule::SaveDataUniqueRadarModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"radius_add", radius_add);
}

void RadarModule::LoadDataUniqueRadarModule(const boost::property_tree::ptree& load_ptree)
{
	radius_add = load_ptree.get<int>("radius_add");
}

void RadarModule::ResolveDataUniqueRadarModule()
{}

RadarModule* GetNewRadarModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
    	int radius_add  = getRandInt(MODULE::RADAR::RADIUS_MIN, MODULE::RADAR::RADIUS_MAX);
    
        int id = g_ID_GENERATOR.getNextId();
        
    	RadarModule* radar_module = new RadarModule(id);    
        radar_module->SetTextureOb(texOb);
        radar_module->SetRadiusAdd(radius_add);
                
        EntityManager::Instance().RegisterEntity(radar_module);
                        
    	return radar_module;
}
