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


LazerModule::LazerModule(int damage_add, 
                           int radius_add)
{
     	this->damage_add = damage_add;
     	this->radius_add = radius_add;
}

/* virtual */
LazerModule::~LazerModule()
{}

/* virtual */
void LazerModule::AddUniqueInfo()
{
    	info.addTitleStr("lazer module");
    	if (damage_add != 0) 
    	{
    		info.addNameStr("damage_add:");   info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
    	}
}

/*virtual*/
void LazerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "lazer_module." + int2str(GetId()) + ".";
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueLazerModule(save_ptree, root);
}

/*virtual*/		
void LazerModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueLazerModule(load_ptree);
}
	
/*virtual*/	
void LazerModule::ResolveData()
{
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueLazerModule();
}

void LazerModule::SaveDataUniqueLazerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"damage_add", damage_add);
	save_ptree.put(root+"radius_add", radius_add);
}

void LazerModule::LoadDataUniqueLazerModule(const boost::property_tree::ptree& load_ptree)
{
	damage_add = load_ptree.get<int>("damage_add");
	radius_add = load_ptree.get<int>("radius_add");
}

void LazerModule::ResolveDataUniqueLazerModule()
{}

LazerModule* GetNewLazerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int damage_add = getRandInt(MODULE::LAZER::DAMAGE_MIN, MODULE::LAZER::DAMAGE_MAX);
    	int radius_add = getRandInt(MODULE::LAZER::RADIUS_MIN, MODULE::LAZER::RADIUS_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::LAZER_ID;  
        
    	LazerModule* lazer_module = new LazerModule(damage_add, radius_add);
        lazer_module->SetTextureOb(texOb);
        lazer_module->SetIdData(data_id);
                
        EntityManager::Instance().RegisterEntity(lazer_module);
                        
    	return lazer_module;
}
