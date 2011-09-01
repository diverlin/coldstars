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


#include "mineral.h"

Mineral :: Mineral(TextureOb* _pTo_texOb, vec2f _start_pos)
{        
    CommonForSpaceItems_init(_pTo_texOb, _start_pos);

    id         = g_ENTITY_ID_GENERATOR.returnNextId();
    type_id    = MINERAL_ID;
    //subtype_id = ;

    mass = randIntInRange(6, 32);
    speed = randIntInRange(40, 42);
    stepCalculation();

    armor = randIntInRange(1,6);
}
    
    
void Mineral :: updateInfo()
{
	info.clear();

    	info.addTitleStr("MINERAL");

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(id) + " / " + int2str(starsystem->id));
    	info.addNameStr("armor:");       info.addValueStr(int2str(armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
    
std::string Mineral :: returnTypeStr()
{
    std::string sType = "";
    std::string sSubType = ""; 
        
    if (type_id == GOODS_ID)
       std::string sType = "GOODS_id ";
    if (subtype_id == MINERAL_ID)
       std::string sSubType = "MINERAL_id";
    return sType + sSubType;   
}
    
           
    //def return_(self):
        //_ = ''
        //for h in self.hunters_list:
            //_+= h.name + '_'
        //return _

void Mineral :: renderInfo()
{
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);    
}


Mineral* createMineral(vec2f _start_pos)
{
	TextureOb* _mTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.mineral_texOb_pList); 
	Mineral* _mineral = new Mineral(_mTexOb, vec2f(_start_pos.x, _start_pos.y));

	return _mineral;
}




