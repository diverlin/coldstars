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



GoodsPack :: GoodsPack(IdData _data_id, LifeData _data_life, TextureOb* _texOb)
{
    	CommonForSpaceItems_init(_data_id, _data_life, _texOb);
        
        mineral  = 0;
        food     = 0;
        medicine = 0;
        military = 0;
        drug     = 0;
        	
    	mass = 0;

    	velocity = getRandInt(40, 42) / 100.0;
}


GoodsPack :: ~GoodsPack()
{}


TextureOb* GoodsPack :: getTexOb() { return texOb; }        	
        	
void GoodsPack :: increase(unsigned int _ammount)
{
	if (data_id.subtype_id == MINERAL_ID)
	{
		mineral += _ammount;
		mass = mineral;
	}
}
    
void GoodsPack :: decrease(unsigned int _ammount)
{
	if (data_id.subtype_id == MINERAL_ID)
	{
		mineral -= _ammount;
		mass = mineral;
	}
}
                
                
void GoodsPack :: updateInfo()
{
	info.clear();
	
    	info.addTitleStr("GOODS");
    	
    	if (data_id.subtype_id == MINERAL_ID)
    	{
    		info.addNameStr("mineral:");   info.addValueStr( int2str(mineral) );
    		info.addNameStr("mass:");   info.addValueStr( int2str(mass) );
    	}
	else
	{
	    	info.addNameStr("UNKNOWN:");   info.addValueStr( "---" );
	}
}                        	
                    
                    
void GoodsPack :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}

 


GoodsPack* createGoodsPack(unsigned int _subtype_id)
{
        IdData data_id;
        data_id.id = g_CONTAINER_ID_GENERATOR.getNextId(); 
        data_id.type_id = GOODS_ID;
        data_id.subtype_id = _subtype_id;
                
        LifeData data_life;
        data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;        
        
	TextureOb* texOb_container = g_TEXTURE_MANAGER.getRandomTexOb(CONTAINER_TEXTURE_ID); 
	GoodsPack* goodsPack = new GoodsPack(data_id, data_life, texOb_container);
	
	return goodsPack;
}
