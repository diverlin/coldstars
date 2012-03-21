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


EquipmentBase :: EquipmentBase()
{
        race_id = RACE_0_ID;
          
    	is_DAMAGED = false;

    	condition       = 1000; //common_data.condition_max;
    	price = 0;
}


EquipmentBase :: ~EquipmentBase()
{
	for (unsigned int i = 0; i < modules_vec.size(); i++)
	{
		delete modules_vec[i];
	}
}

/* virtual */
void EquipmentBase :: addCommonInfo()
{
    	info.addNameStr("modules:");   info.addValueStr( int2str(common_data.modules_num_max) );
    	info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(common_data.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(common_data.mass) );
    	info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

bool EquipmentBase :: insertModule(ModuleBase* module)
{
	if (modules_vec.size() < common_data.modules_num_max)
    	{
	       	modules_vec.push_back(module);
        	updatePropetries();
        	
        	return true;
    	}

       	return false;   
} 

/* virtual */
void EquipmentBase :: render(Rect slot_rect)
{
    	drawTexturedRect(texOb, slot_rect, -1.0);
    	//if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        	//drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	Rect module_rect(slot_rect.getBottomLeft().x + (1.1 * INSERTED_MODULE_SIZE) * (i), 
        		         slot_rect.getBottomLeft().y + (1.1 * INSERTED_MODULE_SIZE),
        			 INSERTED_MODULE_SIZE, 
        			 INSERTED_MODULE_SIZE);
        	drawTexturedRect(modules_vec[i]->getTextureOb(), module_rect, -1);
    	}
}
