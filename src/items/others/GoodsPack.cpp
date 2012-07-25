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

GoodsPack::GoodsPack(int id)
{
        data_id.id         = id; 
        data_id.type_id    = ENTITY::GOODS_ID;
        data_id.subtype_id = NONE_ID;
}

/* virtual */
GoodsPack::~GoodsPack() 
{}

           
/* virtual */
void GoodsPack::UpdateOwnerAbilities() { /* do nothing*/ }
                    

/* virtual */
void GoodsPack::AddUniqueInfo() 
{
    	info.addTitleStr("GOODS");
    	
    	switch(GetSubTypeId())
    	{
    		case ENTITY::MINERAL_ID: { info.addNameStr("mineral:"); info.addValueStr(int2str(data_item.mass)); break; }\
		//case
    	}
}
 	
/* virtual */	
void GoodsPack::AddCommonInfo()
{
    	//info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

 
/*virtual*/
void GoodsPack::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "goods_pack." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueGoodsPack(save_ptree, root);
}

/*virtual*/
void GoodsPack::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueGoodsPack(load_ptree);
}
	
/*virtual*/
void GoodsPack::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueGoodsPack();
}

void GoodsPack::SaveDataUniqueGoodsPack(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}
 		
void GoodsPack::LoadDataUniqueGoodsPack(const boost::property_tree::ptree& load_ptree)
{}

void GoodsPack::ResolveDataUniqueGoodsPack()
{}


GoodsPack* GetNewGoodsPack(int subtype_id, int id)
{
        if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}
        
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::CONTAINER_ID); 
	
	GoodsPack* goodsPack = new GoodsPack(id);
	goodsPack->SetSubTypeId(subtype_id);
	goodsPack->SetTextureOb(texOb);
	
	EntityManager::Instance().RegisterEntity(goodsPack);
	        
	return goodsPack;
}
