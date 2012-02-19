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


BaseModule :: BaseModule()
{}

/* virtual */
BaseModule :: ~BaseModule ()
{}


/* virtual */
void BaseModule :: updateOwnerAbilities()     { /* do nothing*/ } 

void BaseModule :: addCommonInfo()
{
    	//info.addNameStr("modules:");   info.addValueStr( int2str(common_data.modules_num_max) );
    	//info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	//info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(common_data.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(mass) );
    	//info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

//void BaseModule :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
//{  
	//updateInfo();
        //drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
//}

//void BaseModule :: render(Rect slot_rect)
//{
        //drawTexturedRect(texOb, slot_rect, -1);   
//}


