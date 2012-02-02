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



StarBase :: StarBase()
{        
    	mass = getRandInt(STARBASE_MASS_MIN, STARBASE_MASS_MAX);
}

StarBase :: ~StarBase() {}
    
		
void StarBase :: update_inSpace_inDynamic_TRUE()
{}

void StarBase :: update_inSpace_inDynamic_FALSE()
{}

void StarBase :: updateInfo()
{
	info.clear();

    	info.addTitleStr("StarBase" + int2str(data_id.subtype_id));

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void StarBase :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}


StarBase* getNewStarBase()
{
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(STARBASE_TEXTURE_ID); 
       
       	int protection_rate = 1;
       	//if (subtype_id == WARRIOR_ID)
        //{
        	protection_rate = 5;
        //}
        
        KorpusData data_korpus;
    	data_korpus.space       = 2500 + getRandInt(0, 1000);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 10000000;

        data_korpus.inhibit_GRAPPLE = false;
        data_korpus.weapon_slot_num = 5;
            
            
        LifeData data_life;
        data_life.armor = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
       
        IdData data_id;
        data_id.id         = g_VEHICLE_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = STARBASE_ID;
    	data_id.subtype_id = MILITARY_ID;       

        int size_threshold = 2; 
	data_korpus.render_TURRELS = true; 
                           
    	StarBase* starbase = new StarBase();
    	starbase->setKorpusData(data_korpus);
	starbase->setTextureOb(texOb);
	starbase->setIdData(data_id);
	starbase->setLifeData(data_life);
    	
    	starbase->postCreateInit();
    	    
    	return starbase;
}




