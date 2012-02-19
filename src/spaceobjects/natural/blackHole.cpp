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



BlackHole :: BlackHole()
{        
    	mass = getRandInt(1000, 4000);
    	keep_moving = false;
}

BlackHole :: ~BlackHole() {}
   
void BlackHole :: setEffect(BlackHoleEffect* effect) { this->effect = effect; } 
		
void BlackHole :: update_inSpace(int time, bool show_effect)
{
	//updateRotation();
	//effect->update();
	if (time > 0)
	{}
}

void BlackHole :: updateInfo()
{
	info.clear();

    	info.addTitleStr("BLACKHOLE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void BlackHole :: renderInfo_inSpace()
{
	updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, g_SCROLL_COORD_X, g_SCROLL_COORD_Y);    
}


void BlackHole :: render() const
{
	//effect->render();
}

BlackHole* getNewBlackHole()
{
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId();
    	data_id.type_id    = BLACKHOLE_ID;
    	//data_id.subtype_id = ; 
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 100000;
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(BLACKHOLE_TEXTURE_ID); 
	BlackHole* blackhole = new BlackHole();
	blackhole->setIdData(data_id);
	blackhole->setLifeData(data_life);
	blackhole->setTextureOb(texOb);
	
	blackhole->postCreateInit();
	
	return blackhole;
}




