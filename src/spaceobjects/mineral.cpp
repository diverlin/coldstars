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

Mineral :: Mineral(TextureOb* _pTo_texOb, StarSystem* _pTo_starsystem, float _pos_x, float _pos_y, float _target_pos_x, float _target_pos_y)
{        
    CommonForSpaceItems_init(_pTo_starsystem, _pTo_texOb, _pos_x, _pos_y, _target_pos_x, _target_pos_y);
    //pTo_starsystem = _pTo_starsystem;

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
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "MINERAL";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(pTo_starsystem->id);
    info_title_2 = "armor:";
    info_value_2 = int2str(armor);
    info_title_3 = "mass:";
    info_value_3 = int2str(mass);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
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
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y);    
}




//void Mineral :: render2D()
//{ 
    //glBindTexture(GL_TEXTURE_2D, texture);
    ////drawDynamic(100, 100, angle_z, -50, -50, 50, 50, pos_z);
    //drawDynamic(points.center_x, points.center_y, angle_z, minus_half_w, minus_half_h, plus_half_w, plus_half_h, pos_z);
    ////printf("ddfs = %i,%i,%i,%i \n ", minus_half_w, minus_half_h, plus_half_w, plus_half_h);
    //angle_z += d_angle_z;
//}
