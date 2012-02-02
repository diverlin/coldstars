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



SpaceStation :: SpaceStation()
{        
    	mass = getRandInt(SPACESTATION_MASS_MIN, SPACESTATION_MASS_MAX);
}

SpaceStation :: ~SpaceStation() {}
    
		
void SpaceStation :: update_inSpace_inDynamic_TRUE()
{}

void SpaceStation :: update_inSpace_inDynamic_FALSE()
{}

void SpaceStation :: updateInfo()
{
	info.clear();

    	info.addTitleStr("SPACESTATION" + int2str(data_id.subtype_id));

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void SpaceStation :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}


SpaceStation* getNewSpaceStation()
{
        IdData data_id;
        data_id.id         = g_SPACESTATION_ID_GENERATOR.getNextId();
    	data_id.type_id    = SPACESTATION_ID;
    	data_id.subtype_id = MILITARY_ID; 
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 1000;
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(SPACESTATION_TEXTURE_ID);  
	SpaceStation* spacestation = new SpaceStation();
	spacestation->setIdData(data_id);
	spacestation->setLifeData(data_life);
	spacestation->setTextureOb(texOb);
	
	spacestation->postCreateInit();
	
	return spacestation;
}




