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


LazerModule :: LazerModule(int damage_add, 
                           int radius_add)
{
     	this->damage_add = damage_add;
     	this->radius_add = radius_add;
}

LazerModule :: ~LazerModule() /* virtual */
{}


int LazerModule :: getDamageAdd() const { return damage_add; }
int LazerModule :: getRadiusAdd() const { return radius_add; }


void LazerModule :: AddUniqueInfo()
{
    	info.addTitleStr("lazer module");
    	if (damage_add != 0) 
    	{
    		info.addNameStr("damage_add:");   info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
    	}
}


LazerModule* getNewLazerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int damage_add = getRandInt(MODULE::LAZER::DAMAGE_MIN, MODULE::LAZER::DAMAGE_MAX);
    	int radius_add = getRandInt(MODULE::LAZER::RADIUS_MIN, MODULE::LAZER::RADIUS_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::LAZER_ID;  
        
    	LazerModule* lazer_module = new LazerModule(damage_add, radius_add);
        lazer_module->SetTextureOb(texOb);
        lazer_module->SetIdData(data_id);
                
    	return lazer_module;
}
