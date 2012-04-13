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


FreezerModule::FreezerModule(int freeze_add)
{
     	this->freeze_add = freeze_add;
}

/* virtual */
FreezerModule::~FreezerModule() 
{}

/* virtual */
void FreezerModule::AddUniqueInfo()
{
    	info.addTitleStr("freezer module");
    	info.addNameStr("freeze_add:");     info.addValueStr( int2str(freeze_add) );
}

/*virtual*/
void FreezerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "freezer_module." + int2str(GetId()) + ".";
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueFreezerModule(save_ptree, root);
}

/*virtual*/		
void FreezerModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueFreezerModule(load_ptree);
}
	
/*virtual*/	
void FreezerModule::ResolveData()
{
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueFreezerModule();
}

void FreezerModule::SaveDataUniqueFreezerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"freeze_add", freeze_add);
}

void FreezerModule::LoadDataUniqueFreezerModule(const boost::property_tree::ptree& load_ptree)
{
	freeze_add = load_ptree.get<int>("freeze_add");
}

void FreezerModule::ResolveDataUniqueFreezerModule()
{}


FreezerModule* GetNewFreezerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        int freeze_add = getRandInt(MODULE::FREEZER::FREEZE_MIN, MODULE::FREEZER::FREEZE_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::FREEZER_ID; 
        
        FreezerModule* freezer_module = new FreezerModule(freeze_add);
        freezer_module->SetTextureOb(texOb);
        freezer_module->SetIdData(data_id);
        
        EntityManager::Instance().RegisterEntity(freezer_module);
                
        return freezer_module;
}
