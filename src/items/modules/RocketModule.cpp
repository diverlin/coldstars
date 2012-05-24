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


RocketModule::RocketModule(int id)
{
        data_id.type_id    = id;
        data_id.subtype_id = SUBTYPE::ROCKET_ID;  
        
     	ammo_max_add = 0;
     	damage_add   = 0;
     	radius_add   = 0;
}
       
/* virtual */
RocketModule::~RocketModule() 
{}

/* virtual */
void RocketModule::AddUniqueInfo()
{
    	info.addTitleStr("rocket module"); 
    	if (ammo_max_add != 0)
    	{
    		info.addNameStr("ammo_max_add:");   info.addValueStr(int2str(ammo_max_add));
    	}
    	if (damage_add != 0)
    	{
    		info.addNameStr("damage_add:");     info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{
    		info.addNameStr("radius_add:");     info.addValueStr(int2str(radius_add));
    	} 
}


/*virtual*/
void RocketModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "rocket_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueRocketModule(save_ptree, root);
}

/*virtual*/		
void RocketModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueRocketModule(load_ptree);
}
	
/*virtual*/	
void RocketModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueRocketModule();
}

void RocketModule::SaveDataUniqueRocketModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"ammo_max_add", ammo_max_add);
	save_ptree.put(root+"damage_add", damage_add);
	save_ptree.put(root+"radius_add", radius_add);
}

void RocketModule::LoadDataUniqueRocketModule(const boost::property_tree::ptree& load_ptree)
{
	ammo_max_add = load_ptree.get<int>("ammo_max_add");
	damage_add = load_ptree.get<int>("damage_add");
	radius_add = load_ptree.get<int>("radius_add");
}

void RocketModule::ResolveDataUniqueRocketModule()
{}



RocketModule* GetNewRocketModule()
{
    	TextureOb* texOb =  g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MODULE_ID);   
        
    	int ammo_max_add = getRandInt(MODULE::ROCKET::AMMO_MIN, MODULE::ROCKET::AMMO_MAX);
    	int damage_add = getRandInt(MODULE::ROCKET::DAMAGE_MIN, MODULE::ROCKET::DAMAGE_MAX);
    	int radius_add = getRandInt(MODULE::ROCKET::RADIUS_MIN, MODULE::ROCKET::RADIUS_MAX);

        int id    = g_ID_GENERATOR.getNextId();
        
    	RocketModule* rocket_module = new RocketModule(id);
        rocket_module->SetTextureOb(texOb);
        rocket_module->SetAmmoMaxAdd(ammo_max_add);
        rocket_module->SetDamageAdd(damage_add);
        rocket_module->SetRadiusAdd(radius_add);
                         
        EntityManager::Instance().RegisterEntity(rocket_module);
                        
    	return rocket_module;
}
