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
        
        mineral  = 0;
        food     = 0;
        medicine = 0;
        military = 0;
        drug     = 0;
}

/* virtual */
GoodsPack::~GoodsPack() 
{}

void GoodsPack::Increase(unsigned int _ammount)
{
	if (GetSubTypeId() == ENTITY::MINERAL_ID)
	{
		mineral += _ammount;
		data_item.mass = mineral;
	}
}
    
void GoodsPack::Decrease(unsigned int _ammount)
{
	if (GetSubTypeId() == ENTITY::MINERAL_ID)
	{
		mineral -= _ammount;
		data_item.mass = mineral;
	}
}
                
/* virtual */
void GoodsPack::UpdateOwnerAbilities() { /* do nothing*/ }
                    

/* virtual */
void GoodsPack::AddUniqueInfo() 
{
    	info.addTitleStr("GOODS");
    	
    	if (GetSubTypeId() == ENTITY::MINERAL_ID)
    	{
    		info.addNameStr("mineral:");   info.addValueStr( int2str(mineral) );

    	}
}
 	
/* virtual */	
void GoodsPack::AddCommonInfo()
{
    	info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

 
/*virtual*/
void GoodsPack::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void GoodsPack::LoadData(const boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void GoodsPack::ResolveData()
{

}

GoodsPack* GetNewGoodsPack(unsigned int subtype_id)
{
        int id = g_ID_GENERATOR.getNextId();   
        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::CONTAINER_ID); 
	
	GoodsPack* goodsPack = new GoodsPack(id);
	goodsPack->SetSubTypeId(subtype_id);
	goodsPack->SetTextureOb(texOb);
	
	return goodsPack;
}
