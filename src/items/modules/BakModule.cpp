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


BakModule::BakModule(int id)
{
	data_id.id         = id;
	data_id.subtype_id = SUBTYPE::BAK_ID;
	
    	fuel_max_add = 0;
}

/* virtual */
BakModule::~BakModule() 
{}

/* virtual */
void BakModule::AddUniqueInfo()
{
    	info.addTitleStr("bak module");
    	info.addNameStr("fuel_max_add:"); info.addValueStr( int2str(fuel_max_add) );
}

/*virtual*/
void BakModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "bak_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueBakModule(save_ptree, root);
}

/*virtual*/		
void BakModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueBakModule(load_ptree);
}
	
/*virtual*/	
void BakModule::ResolveData()
{
        ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueBakModule();
}

void BakModule::SaveDataUniqueBakModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"fuel_max_add", fuel_max_add);
}

void BakModule::LoadDataUniqueBakModule(const boost::property_tree::ptree& load_ptree)
{
	fuel_max_add = load_ptree.get<int>("fuel_max_add");
}

void BakModule::ResolveDataUniqueBakModule()
{}




BakModule* GetNewBakModule()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MODULE_ID);             	
    	int fuel_max_add = getRandInt(MODULE::BAK::FUEL_MIN, MODULE::BAK::FUEL_MAX);
        int id = g_ID_GENERATOR.getNextId();
        
    	BakModule* bak_module = new BakModule(id);
    	bak_module->SetFuelMaxAdd(fuel_max_add);
        bak_module->SetTextureOb(texOb);
        
        EntityManager::Instance().RegisterEntity(bak_module);
        
    	return bak_module;
}
