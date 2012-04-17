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


EnergizerModule::EnergizerModule(int id)
{
        data_id.id = id;
	data_id.type_id    = MODULE::MODULE_ID;
	data_id.subtype_id = MODULE::ENERGIZER_ID;
        
     	energy_max_add  = 0;
     	restoration_add = 0;
}

/* virtual */
EnergizerModule::~EnergizerModule()
{}

/* virtual */
void EnergizerModule::AddUniqueInfo()
{
    	info.addTitleStr("energizer module");
    	if (energy_max_add != 0)
    	{ 
    		info.addNameStr("energy_max_add:");  info.addValueStr( int2str(energy_max_add) );
    	}
    	if (restoration_add != 0)
    	{
    		info.addNameStr("restoration_add:"); info.addValueStr( int2str(restoration_add) );
    	} 
}

/*virtual*/
void EnergizerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "energizer_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueEnergizerModule(save_ptree, root);
}

/*virtual*/		
void EnergizerModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueEnergizerModule(load_ptree);
}
	
/*virtual*/	
void EnergizerModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueEnergizerModule();
}

void EnergizerModule::SaveDataUniqueEnergizerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"energy_max_add", energy_max_add);
	save_ptree.put(root+"restoration_add", restoration_add);
}

void EnergizerModule::LoadDataUniqueEnergizerModule(const boost::property_tree::ptree& load_ptree)
{
	energy_max_add = load_ptree.get<int>("energy_max_add");
	restoration_add = load_ptree.get<int>("restoration_add");
}

void EnergizerModule::ResolveDataUniqueEnergizerModule()
{}

EnergizerModule* GetNewEnergizerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        	
     	int energy_max_add  = getRandInt(MODULE::ENERGIZER::ENERGY_MIN, MODULE::ENERGIZER::ENERGY_MAX);
     	int restoration_add = getRandInt(MODULE::ENERGIZER::RESTORATION_MIN, MODULE::ENERGIZER::RESTORATION_MAX);
     	
        int id = g_ID_GENERATOR.getNextId();
        
     	EnergizerModule* energizer_module = new EnergizerModule(id);
        energizer_module->SetTextureOb(texOb);
        energizer_module->SetEnergyMaxAdd(energy_max_add);
        energizer_module->SetRestorationAdd(restoration_add);
        
        EntityManager::Instance().RegisterEntity(energizer_module);
                
        return energizer_module; 
}
