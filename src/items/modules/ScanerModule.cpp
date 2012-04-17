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


ScanerModule::ScanerModule(int id)
{
        data_id.id         = id;
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::SCANER_ID;
        
    	scan_add = 0;
}

/* virtual */
ScanerModule::~ScanerModule() 
{}

/* virtual */		
void ScanerModule::AddUniqueInfo()
{
    	info.addTitleStr("scaner module");
    	info.addNameStr("scan_add:");      info.addValueStr( int2str(scan_add) );
}

/*virtual*/
void ScanerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "scaner_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueScanerModule(save_ptree, root);
}

/*virtual*/		
void ScanerModule::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueScanerModule(load_ptree);
}
	
/*virtual*/	
void ScanerModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueScanerModule();
}

void ScanerModule::SaveDataUniqueScanerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"scan_add", scan_add);
}

void ScanerModule::LoadDataUniqueScanerModule(const boost::property_tree::ptree& load_ptree)
{
	scan_add = load_ptree.get<int>("scan_add");
}

void ScanerModule::ResolveDataUniqueScanerModule()
{}

ScanerModule* GetNewScanerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
         
    	int scan_add = getRandInt(MODULE::SCANER::SCAN_MIN, MODULE::SCANER::SCAN_MAX);

        int id = g_ID_GENERATOR.getNextId();
        
    	ScanerModule* scaner_module = new ScanerModule(scan_add);
        scaner_module->SetTextureOb(texOb);
        scaner_module->SetScanAdd(scan_add);
        
        EntityManager::Instance().RegisterEntity(scaner_module);
                
    	return scaner_module;
}
