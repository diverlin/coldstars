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


GrappleModule::GrappleModule(int id)
{
        data_id.type_id    = id;
        data_id.subtype_id = SUBTYPE::GRAPPLE_ID;  
        
        strength_add   = 0;
        radius_add     = 0;
        speed_add      = 0;
        maxNumItem_add = 0;
}

/* virtual */
GrappleModule::~GrappleModule() 
{}

/* virtual */
void GrappleModule::AddUniqueInfo()
{
    	info.addTitleStr("grapple module");
    	if (strength_add != 0)
    	{
    		info.addNameStr("strength_add:");    info.addValueStr( int2str(strength_add) );
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");      info.addValueStr( int2str(radius_add) );
    	} 
    	if (speed_add != 0)
    	{
    		info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
    	}
    	if (maxNumItem_add != 0)
    	{
    		info.addNameStr("maxNumItem_add:");  info.addValueStr( int2str(maxNumItem_add) ); 
    	}
}

/*virtual*/
void GrappleModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "grapple_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueGrappleModule(save_ptree, root);
}

/*virtual*/		
void GrappleModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueGrappleModule(load_ptree);
}
	
/*virtual*/	
void GrappleModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueGrappleModule();
}

void GrappleModule::SaveDataUniqueGrappleModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"strength_add", strength_add);
	save_ptree.put(root+"radius_add", radius_add);
	save_ptree.put(root+"speed_add", speed_add);
	save_ptree.put(root+"maxNumItem_add", maxNumItem_add);
}

void GrappleModule::LoadDataUniqueGrappleModule(const boost::property_tree::ptree& load_ptree)
{
	strength_add = load_ptree.get<int>("strength_add");
	radius_add = load_ptree.get<int>("radius_add");
	speed_add = load_ptree.get<int>("speed_add");
	maxNumItem_add = load_ptree.get<int>("maxNumItem_add");
}

void GrappleModule::ResolveDataUniqueGrappleModule()
{}

GrappleModule* GetNewGrappleModule()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MODULE_ID);   
                       
    	int strength_add   = getRandInt(MODULE::GRAPPLE::STRENGTH_MIN, MODULE::GRAPPLE::STRENGTH_MAX);
    	int radius_add     = getRandInt(MODULE::GRAPPLE::RADIUS_MIN, MODULE::GRAPPLE::RADIUS_MAX);
    	int speed_add      = getRandInt(MODULE::GRAPPLE::SPEED_MIN, MODULE::GRAPPLE::SPEED_MAX);
    	int maxNumItem_add = getRandInt(MODULE::GRAPPLE::MAXNUMITEM_MIN, MODULE::GRAPPLE::MAXNUMITEM_MAX);
        
        int id = g_ID_GENERATOR.getNextId();
                
    	GrappleModule* grapple_module = new GrappleModule(id);    	
    	grapple_module->SetTextureOb(texOb);
        grapple_module->SetStrengthAdd(strength_add);
        grapple_module->SetRadiusAdd(radius_add);
        grapple_module->SetSpeedAdd(speed_add);
        grapple_module->SetMaxNumItemAdd(maxNumItem_add);
                                
        EntityManager::Instance().RegisterEntity(grapple_module);
                
        return grapple_module;
}







