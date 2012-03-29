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


GoodsPack :: GoodsPack()
{
        mineral  = 0;
        food     = 0;
        medicine = 0;
        military = 0;
        drug     = 0;
}

GoodsPack :: ~GoodsPack()  /* virtual */
{}


        	
void GoodsPack :: increase(unsigned int _ammount)
{
	if (GetSubTypeId() == ENTITY::MINERAL_ID)
	{
		mineral += _ammount;
		data_item.mass = mineral;
	}
}
    
void GoodsPack :: decrease(unsigned int _ammount)
{
	if (GetSubTypeId() == ENTITY::MINERAL_ID)
	{
		mineral -= _ammount;
		data_item.mass = mineral;
	}
}
                
                
void GoodsPack :: updateInfo()
{
	info.clear();
	
    	info.addTitleStr("GOODS");
    	
    	if (GetSubTypeId() == ENTITY::MINERAL_ID)
    	{
    		info.addNameStr("mineral:");   info.addValueStr( int2str(mineral) );
    		info.addNameStr("mass:");   info.addValueStr( int2str(data_item.mass) );
    	}
	else
	{
	    	info.addNameStr("UNKNOWN:");   info.addValueStr( "---" );
	}
}                        	
      
void GoodsPack :: updateOwnerAbilities() { /* do nothing*/ } /* virtual */
                    
//void GoodsPack :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
//{
     	//drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
//}

 


GoodsPack* getNewGoodsPack(unsigned int _subtype_id)
{
        IdData data_id;
        data_id.id = g_ID_GENERATOR.getNextId(); 
        data_id.type_id = ENTITY::GOODS_ID;
        data_id.subtype_id = _subtype_id;
                
        LifeData data_life;
        data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;        
        
        vec3f d_angle;
        d_angle.z      = -getRandInt(10, 100)*0.01; 
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::CONTAINER_ID); 
	
	GoodsPack* goodsPack = new GoodsPack();
	goodsPack->setIdData(data_id);
	goodsPack->setTextureOb(texOb);
	
	return goodsPack;
}
