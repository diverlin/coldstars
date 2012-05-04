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


ProtectorModule::ProtectorModule(int id)
{
        data_id.type_id    = id;
        data_id.subtype_id = SUBTYPE::PROTECTOR_ID;
        
     	protection_add = 0;
}

/* virtual */
ProtectorModule::~ProtectorModule () 
{}
		
/* virtual */		
void ProtectorModule::AddUniqueInfo()
{
    	info.addTitleStr("protector module");
    	info.addNameStr("protection_add:");  info.addValueStr( int2str(protection_add) );
}

/*virtual*/
void ProtectorModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "protector_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueProtectorModule(save_ptree, root);
}

/*virtual*/
void ProtectorModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueProtectorModule(load_ptree);
}

/*virtual*/
void ProtectorModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueProtectorModule();
}

void ProtectorModule::SaveDataUniqueProtectorModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"protection_add", protection_add);
}

void ProtectorModule::LoadDataUniqueProtectorModule(const boost::property_tree::ptree& load_ptree)
{
	protection_add = load_ptree.get<int>("protection_add");
}

void ProtectorModule::ResolveDataUniqueProtectorModule()
{}

ProtectorModule* GetNewProtectorModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int protection_add = getRandInt(MODULE::PROTECTOR::PROTECTION_MIN, MODULE::PROTECTOR::PROTECTION_MAX);

        int id = g_ID_GENERATOR.getNextId();
        
    	ProtectorModule* protector_module = new ProtectorModule(id);
        protector_module->SetTextureOb(texOb);
        protector_module->SetProtectionAdd(protection_add);
        
        EntityManager::Instance().RegisterEntity(protector_module);
                
    	return protector_module;
}
