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



Mineral :: Mineral(IdData _data_id, LifeData _data_life, TextureOb* _texOb, vec2f _start_pos)
{        
    	CommonForSpaceItems_init(_data_id, _data_life, _texOb, _start_pos);

    	mass = getRandInt(1, 4);
    	velocity = getRandInt(40, 42) / 100.0;
}
    
    
void Mineral :: updateInfo()
{
	info.clear();

    	info.addTitleStr("MINERAL");

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void Mineral :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}


Mineral* createMineral(vec2f _start_pos)
{
        IdData data_id;
        data_id.id         = g_MINERAL_ID_GENERATOR.getNextId();
    	data_id.type_id    = MINERAL_ID;
    	//data_id.subtype_id = ; 
        
        LifeData data_life;
    	data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.mineral_texOb_pList); 
	Mineral* mineral = new Mineral(data_id, data_life, texOb, _start_pos);

	return mineral;
}




