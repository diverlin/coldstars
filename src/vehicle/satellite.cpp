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



Satellite :: Satellite()
{        
    	mass = getRandInt(SATELLITE_MASS_MIN, SATELLITE_MASS_MAX);
    	keep_moving = false;
}

Satellite :: ~Satellite() {}
    
		
void Satellite :: update_inSpace_inDynamic_TRUE()
{}

void Satellite :: update_inSpace_inDynamic_FALSE()
{}

void Satellite :: updateInfo()
{
	info.clear();

    	info.addTitleStr("SATELLITE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void Satellite :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}


Satellite* getNewSatellite()
{
        IdData data_id;
        data_id.id         = g_VEHICLE_ID_GENERATOR.getNextId();
    	data_id.type_id    = SATELLITE_ID;
    	data_id.subtype_id = MILITARY_ID; 
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 1000;
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(SATELLITE_TEXTURE_ID);  
	Satellite* satellite = new Satellite();
	satellite->setIdData(data_id);
	satellite->setLifeData(data_life);
	satellite->setTextureOb(texOb);
	
	satellite->postCreateInit();
	
	return satellite;
}




